require 'yaml'
require 'fileutils'
require 'pathname'
require 'rake/clean'
require 'colorize'
require_relative '../unity.framework/auto/generate_test_runner'
require_relative '../unity.framework/auto/colour_reporter'


class RakefileHelper
	attr_reader :config_file, 
				:objs_folder, 
				:build_folder, 
				:source_folder,
				:unit_tests_folder,
				:mocks_folder,
				:target_folder,
				:includes,
				:usb_addresses,
				:linker_path,
				:cc_compiler_options,
				:cpp_compiler_options,
				:linker_options,
				:elf_path,
				:hex_path,
				:tools_path,
				:arduino_path,
				:unity_source				

	def initialize(*args)
			@config_file = 'target_teensy.yml' 
			@system_file = 'system.yml' 
		if args.count > 0
			args = args[0]
			load_helper_config(args)
		end

		@CONFIG = YAML.load(File.read(@config_file))
		@SYSTEM = YAML.load(File.read(@system_file))
		@source_folder = @CONFIG['compiler']['source_path']
		@build_folder = @CONFIG['compiler']['build_path']
		@unit_tests_folder = @CONFIG['compiler']['unit_tests_path']
		@mocks_folder = @CONFIG['compiler']['mocks_path']
		@target_folder = @CONFIG['compiler']['target_path']
		@arduino_path = @CONFIG['arduino_path']
		@MCU = @CONFIG['mcu']
		@linker_path = @target_folder + @MCU.downcase + '.ld' if (@target_folder && @MCU)

		@defines ||= get_defines if @CONFIG['defines']
		@includes ||= get_includes if @CONFIG['includes']
		@cc_compiler_options ||= get_compiler_options('CC') if @CONFIG['cc_compiler_options']
		@linker_options ||= get_compiler_options('linker')	if @CONFIG['linker']

		@objs_folder = @CONFIG['compiler']['objs_path']
		@cpp_compiler_options ||= get_compiler_options('CPP') if @CONFIG['cpp_compiler_options']
		
		@elf_path = build_folder + @CONFIG['target'] + '.elf' if elf_path
		@hex_path = build_folder + @CONFIG['target'] + '.hex' if hex_path
		@tools_path = arduino_path + @CONFIG['tools_path'] if arduino_path

		@unity_source = @CONFIG['unity_source']
		
		@usb_addresses = @SYSTEM['usb_addresses']
		@C_EXTENSION = '.c'.freeze
		@CPP_EXTENSION = '.cpp'.freeze
	end
	
	def load_helper_config(args)
		if args[:config]
			@config_file = args[:config]
		elsif args[:mode] == 'test'
			@config_file = 'spec/spec.yml'
		elsif args[:system]
			@system_file = args[:system]
		else
			raise "RakefileHelper was called with invalid parameters"
		end
	end

	def check_exit_status(message)
		if ($?.exitstatus == 1) 
			raise "ABORT RakefileHelper error: #{message}"
		end
	end

	def gcc(instruction)
		shell_command = @CONFIG['CC'] + cc_compiler_options + instruction 
puts shell_command
		output = `#{shell_command}`
		check_exit_status('error during gcc compilation')
		output
	end

	def gpp(instruction)
		shell_command = @CONFIG['CPP'] + cpp_compiler_options + cc_compiler_options + instruction 
puts shell_command
		output = `#{shell_command}`
		check_exit_status('error during gpp compilation')
		output
	end

	def link(instruction)
		shell_command = @CONFIG['CC'] + linker_options + instruction + ' -lm'
puts shell_command
		output = `#{shell_command}`
		check_exit_status('error during linking')
		output
	end

	def compile_and_assemble(target)
		source = Pathname.new(target)
		object = get_objfile(source)

		case source.extname
		when '.c'
			string = "#{@defines} #{@includes} -c -o #{object} #{source}"
# puts "cc: #{string}"
			output = gcc(string)
		when '.cpp'
			string = "#{@defines} #{@includes} -c -o #{object} #{source} "
# puts "cpp: #{string}"
			output = gpp(string)
		else
			raise "RakefileHelper error: #{target} is an invalid sourcefile"
		end
		return output
	end

	def link_obj(object_list, binary, targetlib = nil)
		output = " -o #{binary} "
		output += "-lmy#{targetlib} -Lbuild -lc -lrdimon " if targetlib
		string = ' '

		if object_list.is_a?(Array)
			object_list.each do |object|
				string += object + " "
			end
		else
			puts "string: " + object_list
			puts "linker: " + linker_path
			string += object_list + @linker_path
		end

		string += output
# puts "string: " + string
		output = link(string)
	end

	def get_compiler_options(compiler)
		if compiler == 'CC' 
			options_list = @CONFIG['cc_compiler_options']
		elsif compiler == 'CPP' 
			options_list = @CONFIG['cpp_compiler_options']
		elsif compiler == 'linker'
			options_list = @CONFIG['linker']['options']
		end
		squash('-', options_list)
	end

	def get_includes
		if @CONFIG['includes']
			includes_list = @CONFIG['includes']['items']
			includes_prefix = @CONFIG['includes']['prefix']
			includes_list.each do |include|
				get_subfolders(include).each do |sub|
					includes_list.push(sub)
				end
			end
			squash(includes_prefix, includes_list)
		end
	end

	def get_defines
		if @CONFIG['defines']
			defines_list = @CONFIG['defines']['items'] 
			defines_prefix = @CONFIG['defines']['prefix']
			squash(defines_prefix, defines_list)
		end
	end

	def get_subfolders(folder)
		Dir.glob("#{folder}*/")
	end

	def map_sources_to_objs(list)
		list.map do |src|
			get_objfile(src)
		end
	end

	def objs_list(type)
		case type
		when :source
			map_sources_to_objs(sources_list)
		when :target
			map_sources_to_objs(target_sources_list)
		end
	end

	def get_elf_size
		if elf_path
			shell_command = "arm-none-eabi-size #{elf_path}"
			output = `#{shell_command}`
		end
		output
	end

	def copy_hex(target)
		shell_command = "arm-none-eabi-objcopy -O ihex -R .eeprom #{target} build/main.hex"
		`#{shell_command}`
	end

	def sources_list
		Rake::FileList.new(
				source_folder + "**/*.c",
				source_folder + "**/*.cpp"
			) if source_folder
	end

	def target_sources_list
		Rake::FileList.new(
				@target_folder + "**/*.c",
				@target_folder + "**/*.cpp"
			) if source_folder
	end

	def get_sourcefile(obj_path)
		[target_folder, source_folder].each do |folder|
			target = obj_path.ext('cpp').gsub(objs_folder, folder)
			return target if sources_list.include? target

			target = obj_path.ext('c').gsub(objs_folder, folder)
			return target if sources_list.include? target
		end
	end

	def get_objfile(src_path)
		base = File.basename(src_path)
		objs_folder + base
			.gsub('.cpp', '.o')
			.gsub('.c', '.o')
	end

	def configure_clean
		CLEAN.include(objs_folder + '*.*') unless objs_folder.nil?
	end

	def usb_port
		if system("test -e \"/dev/ttyACM0\"")
			return "/dev/ttyACM0"
		elsif system("test -e \"/dev/ttyACM1\"")
			return "/dev/ttyACM1"
		else
			return nil
		end
	end

	def load_to_teensy(hex)
		shell_command = tools_path + "teensy_post_compile "
		shell_command += "-file=#{build_folder + hex} "
		shell_command += "-path=#{Dir.pwd} -tools=#{tools_path}"
puts shell_command
		`#{shell_command}`
		
		reboot_command = "#{tools_path}teensy_reboot"
puts reboot_command
		`#{reboot_command}`
	end

	def squash(prefix, items)
	  result = ''
	  items.each { |item| result += " #{prefix}#{tackit(item)}" }
	  result
	end

	def tackit(strings)
	  result = if strings.is_a?(Array)
	             "\"#{strings.join}\""
	           else
	             strings
	           end
	  result
	end

	def unit_test_files
	  test_path = (@unit_tests_folder + '**/Test*' + @C_EXTENSION).tr('\\', '/')
	  cpp_test_path = (@unit_tests_folder + '**/Test*' + @CPP_EXTENSION).tr('\\', '/')
	  mocks_path = (@mocks_folder + '**/Test*' + @C_EXTENSION).tr('\\', '/')
	  list = FileList.new(test_path)
	  list.add(cpp_test_path)
	  list.add(mocks_path)
# puts "test_files: " + list.to_s
		list
	end

	def run_tests
puts "Running system tests..."

		unit_test_files.each do |test_file|
# puts "test_file: " + test_file
			compile_and_assemble(test_file)
			runner_name = generate_runner_name(test_file)
			test_gen = create_runner_generator(test_file)

			compile_and_assemble(runner_name)
			objs = get_test_objs(test_file)
# puts "objs" + objs.to_s
			exe = generate_executable(objs, test_file)
puts exe
		end
	end

	def generate_runner_name(filename)
		basename = File.basename(filename, '.*')
		runner_name = basename + '_Runner.c'
		runner_name = @objs_folder + runner_name
	end

	def create_runner_generator(test)
		test_gen = UnityTestRunnerGenerator.new(@CONFIG)
		test_gen.run(test, generate_runner_name(test))
	end

	def extract_headers(filename)
		includes = []
  		lines = File.readlines(filename)
  		lines.each do |line|
    		m = line.match(/^\s*#include\s+\"\s*(.+\.[hH])\s*\"/)
    		includes << (objs_folder + m[1]) unless m.nil?
  		end
  		includes
	end

	def compile_test_files(filename)
			compile_and_assemble(filename)
			runner_name = filename.sub(unit_tests_folder, objs_folder).sub('.c', '_Runner.c')
			compile_and_assemble(runner_name)
	end

	def get_test_objs(filename)
		objs = []
		['.c', '.cpp'].each do |ext|
			if File.extname(filename) == ext
				objs.push(objs_folder + File.basename(filename, '.*') + ".o")
				objs.push(objs_folder + File.basename(filename, '.*') + "_Runner.o")
			end
		end
# puts "objs" + objs.to_s
		extract_headers(filename).each do |include|
			source = check_for_source(include)
			
			if source
# puts "source: " + source				
				compile_and_assemble(source)
				objs.push(include.sub(unit_tests_folder,objs_folder).sub(".h", ".o")) 
			end
		end
		objs
	end

	def check_for_source(header)
		header_name = File.basename(header)
		['.cpp', '.c'].each do |ext|
			source_name = header_name.sub('.h', ext)

			if File.exist?(source_folder + source_name) 
				return source_folder + source_name
			elsif File.exist?(unity_source + source_name) 
				return unity_source + source_name
			elsif File.exist?(mocks_folder + source_name) 
				return mocks_folder + source_name
			else
				get_subfolders(source_folder).each do |subfolder|
					if File.exist?(subfolder + source_name) 
						return subfolder + source_name
					end
				end
			end
		end
		false
	end

	def generate_executable(objs, target)
	    executable = build_folder + File.basename(target).sub('.c', @CONFIG['exe_filetype'])

		link_obj(objs, executable)
		report(`#{executable}`)
	end

end