require 'yaml'
require 'fileutils'
require 'pathname'
require 'rake/clean'
require 'colorize'

class RakefileHelper
	attr_reader :config_file, 
				:objs_folder, 
				:build_folder, 
				:source_folder,
				:unit_tests_folder,
				:mocks_folder,
				:target_folder,
				:sources_list,
				:includes,
				:usb_addresses,
				:objs_list,
				:linker_path,
				:cc_compiler_options,
				:cpp_compiler_options,
				:linker_options,
				:elf_path,
				:hex_path,
				:tools_path,
				:arduino_path				

	def initialize(*args)
			@config_file = 'project.yml' 
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
		@target_folder = @CONFIG['target_folder']
		@arduino_path = @CONFIG['arduino_path']
		@MCU = @CONFIG['mcu']
		@linker_path = @target_folder + @MCU.downcase + '.ld' if (@target_folder && @MCU)

		@sources_list ||= get_sources_list
		@defines ||= get_defines
		@includes ||= get_includes

		@objs_folder = @CONFIG['compiler']['objs_path']
		@objs_list = get_objs_list
		target_folder = @CONFIG['target_folder'] if target_folder
		@cc_compiler_options = @CONFIG['cc_compiler_options']
		@cpp_compiler_options = @CONFIG['cpp_compiler_options']
		@linker_options = @CONFIG['linker_options']
		
		@elf_path = build_folder + @CONFIG['target'] + '.elf' if elf_path
		@hex_path = build_folder + @CONFIG['target'] + '.hex' if hex_path
		@tools_path = arduino_path + @CONFIG['tools_path'] if arduino_path

		@usb_addresses = @SYSTEM['usb_addresses']
		@C_EXTENSION = '.c'.freeze
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
puts "cc: #{string}"
			output = gcc(string)
		when '.cpp'
			string = "#{@defines} #{@includes} -c -o #{object} #{source} "
puts "cpp: #{string}"
			output = gpp(string)
		else
			raise "RakefileHelper error: #{target} is an invalid sourcefile"
		end
		return output
	end

	def link_obj(object_list, binary)
		binary_path =  binary
# puts object_list
		string = " -o #{binary_path} "
		if object_list.is_a?(Array)
			object_list.each do |object|
				string += object + " "
			end
		else
			puts "string: " + object_list
			puts "linker: " + linker_path
			string += object_list + @linker_path
		end

		output = link(string)
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

	def get_objs_list
		if sources_list
			sources_list.map do |src|
				base = File.basename(src)
				objs_folder + base
					.gsub('.cpp', '.o')
					.gsub('.c', '.o')
			end
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

	def get_sources_list
		Rake::FileList.new(
				source_folder + "**/*.c",
				source_folder + "**/*.cpp",
				@target_folder + "*.c",
				@target_folder + "*.cpp"
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
		source = Pathname.new(src_path)
		object = objs_folder + source.basename.to_s.split('.')[0] + '.o'
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
	  mocks_path = (@mocks_folder + '**/Test*' + @C_EXTENSION).tr('\\', '/')
	  list = FileList.new(test_path)
	  list.add(mocks_path).shuffle
	end

	def run_tests
puts "Running system tests..."
puts "defines" + @defines

		unit_test_files.each do |test_file|
			compile_and_assemble(test_file)
		end
	end
end