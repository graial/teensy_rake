require_relative '../rakefile_helper/RakefileHelper'
require_relative 'helper_methods/helper_methods'
require_relative 'support/teensy'

RSpec.describe RakefileHelper do
	let(:project_yaml) { YAML.load(File.read("project.yml")) }
	let(:spec_yaml) { YAML.load(File.read("spec/spec.yml")) }
	let(:helper) { RakefileHelper.new({mode: 'test'}) }
	let(:obj_folder) { helper.objs_folder }
	let(:target_folder) { helper.target_folder }
	let(:build_folder) { helper.build_folder }
	let(:source_folder) { helper.source_folder }
	let(:unit_tests_folder) { helper.unit_tests_folder }

	describe "shell commands and clean" do
		it 'calls gcc' do
			expect(helper.gcc(' --version')).to eq(`gcc --version`)
		end

		it 'calls g++' do
			expect(helper.gpp(' --version')).to eq(`g++ --version`)
		end

		it "prepares folders for clean" do
			expect(helper.configure_clean).to include(
				"spec/spec_objs/app.exe", 
				"spec/spec_objs/main.o", 
				"spec/spec_objs/module.o"
			)
		end
		it 'returns an ABORT message when a shell call fails' do
			expect{ helper.gpp(' this-command-sucks')}.to raise_error("ABORT RakefileHelper error: error during gpp compilation")
		end
	end
	describe "compile_and_assemble" do
		it 'returns an error if asked to compile a sourcefile of unhandled extension' do
			source_filepath = 'main.what'
			expect { helper.compile_and_assemble(source_filepath) }.to raise_error("RakefileHelper error: #{source_filepath} is an invalid sourcefile")
		end
		it 'returns an error if asked to compile a broken sourcefile' do
			source_filepath = helper.source_folder + 'module.c'
			replace_line_in_file(source_filepath, "void module_run()", "void module_run();" )
			expect { helper.compile_and_assemble(source_filepath) }.to raise_error("ABORT RakefileHelper error: error during gcc compilation")
			replace_line_in_file(source_filepath, "void module_run();", "void module_run()" )
		end

		it 'compiles and assembles a single c object' do
			delete_filetype_if_exists(obj_folder, 'o')
			
			target = 'main'

			source_filepath = add_src_wrappers(source_folder, target)
			obj_filepath = add_objs_wrappers(obj_folder, target)
			helper.compile_and_assemble(source_filepath)

			expect(check_for_file(obj_filepath)).to eq(true)
		end

		it 'compiles and assembles a single c++ object' do
			delete_filetype_if_exists(obj_folder, 'o')
			
			target = 'mainPlus'

			source_filepath = add_src_wrappers(source_folder, target, 'cpp')
			obj_filepath = add_objs_wrappers(obj_folder, target)
			helper.compile_and_assemble(source_filepath)

			expect(check_for_file(obj_filepath)).to eq(true)
		end
	end

	describe "helper_configuration" do
		it "knows if it is being called for tests" do
			normal_helper = RakefileHelper.new
			expect(normal_helper.objs_folder).to eq(project_yaml['compiler']["objs_path"])
			test_helper = RakefileHelper.new({:mode => 'test'})
			expect(test_helper.objs_folder).to eq('spec/spec_objs/')
		end

		it "gets its config from a YAML file" do
			yaml_path = 'spec/dummy.yml'
			yaml = File.open(yaml_path, 'w') { |f|
				f << "compiler:\n"
				f << "  objs_path: 'dummy_yaml'\n"
			}
			test_helper = RakefileHelper.new(config: yaml_path)

			expect(test_helper.objs_folder).to eq('dummy_yaml')

			delete_file_if_exists(yaml_path)
		end

		it "gets its usb_port_address from system.yml which can be overridden" do
			yaml_path = 'spec/spec_system.yml'
			test_helper = RakefileHelper.new(system: yaml_path)

			expect(test_helper.usb_addresses).to contain_exactly('usb_address1', 'usb_address2')
		end
		it "raises an error when created with only a bogus parameter" do
			expect { 
				bogus_helper = RakefileHelper.new(bogus_key: 'spec/dummy_yaml.yml') 
			}.to raise_error("RakefileHelper was called with invalid parameters")
		end
	end
	describe "directory & file lists" do
		it 'finds includes with subdirectories of the target directory' do
			expect(helper.includes).to match(/ -Ispec\/spec_src\/includes\//)
			expect(helper.includes).to match(/ -Ispec\/spec_src\/includes\/sub_includes\//)
		end

		it 'adds an include directory' do
			delete_filetype_if_exists(obj_folder, 'o')
			
			includes = helper.get_includes

			target = 'main_with_other'
			source_filepath = add_src_wrappers(source_folder, target)
			obj_filepath = add_objs_wrappers(obj_folder, target)
			helper.compile_and_assemble(source_filepath)

			expect(check_for_file(obj_filepath)).to eq(true)
		end
		it 'knows its sources list' do
			source1 = source_folder + 'main.c'
			source2 = source_folder + 'module.c'
			source3 = source_folder + 'sub_src/module_in_sub.c'
			expect(helper.sources_list).to include(source1, source2, source3)
		end

		it 'knows its objs list' do
			allow(helper).to receive(:get_sources_list).and_return(
				[
					source_folder + 'main.c',
					source_folder + 'main_with_other.c',
					source_folder + 'sub_src/module_in_sub.c',
					target_folder + 'module.c',
					source_folder + 'mainPlus.cpp'
				]
			)
			
			obj1 = obj_folder + 'main.o'
			obj2 = obj_folder + 'main_with_other.o'
			obj3 = obj_folder + 'module.o'
			obj4 = obj_folder + 'mainPlus.o'
			obj5 = obj_folder + 'module_in_sub.o'

			expect(helper.objs_list).to include(obj1, obj2, obj3, obj4, obj5)
		end
		
		it 'return the target .o file for a given source' do
			c_in_source = helper.source_folder + 'c_source_obj.c'
			cpp_in_target = helper.target_folder + 'cpp_target_obj.cpp'

			expect(helper.get_objfile(c_in_source)).to eq(obj_folder + 'c_source_obj.o')
			expect(helper.get_objfile(cpp_in_target)).to eq(obj_folder + 'cpp_target_obj.o')
		end

		it 'identifies the correct sourcefile for a given object' do
			c_in_source = helper.source_folder + 'c_source_obj.c'
			cpp_in_source = helper.source_folder + 'cpp_source_obj.cpp'
			c_in_target = helper.target_folder + 'c_target_obj.c'
			cpp_in_target = helper.target_folder + 'cpp_target_obj.cpp'

			allow(helper).to receive(:sources_list).and_return(
				[
					c_in_source,
					cpp_in_source,
					c_in_target, 
					cpp_in_target
				]
			)

			c_source_obj = helper.objs_folder + 'c_source_obj.o'
			cpp_source_obj = helper.objs_folder + 'cpp_source_obj.o'
			c_target_obj = helper.objs_folder + 'c_target_obj.o'
			cpp_target_obj = helper.objs_folder + 'cpp_target_obj.o'

			expect(helper.get_sourcefile(c_source_obj)).to eq(c_in_source)
		end
		it 'gets subfolders from a folder path' do
			target_folder = 'spec/spec_src/'
			expect(helper.get_subfolders(target_folder)).to contain_exactly('spec/spec_src/includes/', 'spec/spec_src/sub_src/')
		end
	end
	
	describe "linking" do
		it 'links a single main.o with no external calls' do
			obj_arr = []
			target	= 'main'
			exe  = obj_folder + 'app.exe'

			source_filepath = add_src_wrappers(source_folder, target)
			obj_filepath = add_objs_wrappers(obj_folder, target)

			replace_line_in_file(source_filepath, "\tmodule_run();", "\t// module_run();" )
			helper.compile_and_assemble(source_filepath)

			delete_filetype_if_exists(obj_folder, 'exe')

			expect(check_for_file(obj_filepath)).to eq(true)
			expect(check_for_file(exe)).to eq(false)

			obj_arr.push(obj_filepath)

			helper.link_obj(obj_arr, exe)
			expect(check_for_file(exe)).to eq(true)
			replace_line_in_file(source_filepath, "\t// module_run();", "\tmodule_run();" )

			expect(run_executable(exe)).to eq("Running main\n")
		end

		it 'returns an error if linking is unsuccessful' do
			modified_filepath = helper.source_folder + 'main.c'
			replace_line_in_file(modified_filepath, "\tmodule_run();", "\tmodule_runWrong();" )

			obj_arr = []
			targets	= ['main', 'module']
			exe  = obj_folder + 'app.exe'

			targets.each do |target|
				source_filepath = add_src_wrappers(source_folder, target)
				obj_filepath = add_objs_wrappers(obj_folder, target)

				helper.compile_and_assemble(source_filepath)
				
				expect(check_for_file(obj_filepath)).to eq(true)
				obj_arr.push(obj_filepath)
			end
			expect { helper.link_obj(obj_arr, exe) }.to raise_error("ABORT RakefileHelper error: error during linking")

			replace_line_in_file(modified_filepath, "\tmodule_runWrong();", "\tmodule_run();" )
		end
		
		it 'links a main.o with an external call' do
			obj_arr = []
			targets	= ['main', 'module']
			exe  = obj_folder + 'app.exe'

			targets.each do |target|
				source_filepath = add_src_wrappers(source_folder, target)
				obj_filepath = add_objs_wrappers(obj_folder, target)

				helper.compile_and_assemble(source_filepath)
				
				expect(check_for_file(obj_filepath)).to eq(true)
				obj_arr.push(obj_filepath)
			end

			delete_filetype_if_exists(obj_folder, 'exe')

			expect(check_for_file(exe)).to eq(false)
			
			helper.link_obj(obj_arr, exe)
			expect(check_for_file(exe)).to eq(true)

			expect(run_executable(exe)).to eq("Running main\nRunning module\n")
		end

		it 'links a main.o with an external call to module' do
			target1	= 'main'
			target2	= 'module'
			exe  	= obj_folder + 'app.exe'

			source1 = add_src_wrappers(source_folder, target1)
			source2 = add_src_wrappers(source_folder, target2)
			obj1 = add_objs_wrappers(obj_folder, target1)
			obj2 = add_objs_wrappers(obj_folder, target2)

			delete_filetype_if_exists(obj_folder, 'o')
			delete_filetype_if_exists(obj_folder, 'exe')

			helper.compile_and_assemble(source1)
			helper.compile_and_assemble(source2)

			expect(check_for_file(obj1)).to eq(true)
			expect(check_for_file(obj2)).to eq(true)
			expect(check_for_file(exe)).to eq(false)
			
			test_obj_list = [obj1, obj2]

			helper.link_obj(test_obj_list, exe)
			expect(check_for_file(exe)).to eq(true)
		end
	
		it 'knows the linker script for the build target' do
			expected_string = spec_yaml["compiler"]["target_path"] + spec_yaml["mcu"].downcase + '.ld'
			expect(helper.linker_path).to eq(expected_string)
		end
	end

	it "queries the size of the .elf generated" do
		allow(helper).to receive(:elf_path).and_return(build_folder + 'main.elf')

		expect(helper.get_elf_size).to eq("   text\t   data\t    bss\t    dec\t    hex\tfilename\n  47484\t      0\t   2776\t  50260\t   c454\tspec/spec_build/main.elf\n")
	end

	it "uploads a hex to the teensy", :teensy do
		source_hex = 'main_for_teensy'
		wait_for_usb
		
		helper.load_to_teensy(source_hex)

		wait_for_usb
		usb_port = get_usb_port

		expect(`head -n 6 #{usb_port}`).to include("G'day from rspec!") 
	end

	describe "system checks" do
		it 'returns false if no usb_port found' do
			allow(helper).to receive("system").with("test -e \"/dev/ttyACM0\"").and_return(false)
			allow(helper).to receive("system").with("test -e \"/dev/ttyACM1\"").and_return(false)
			expect(helper.usb_port).to eq(nil)
		end
		it 'returns a valid usb_port name if found' do
			allow(helper).to receive("system").with("test -e \"/dev/ttyACM0\"").and_return(false)
			allow(helper).to receive("system").with("test -e \"/dev/ttyACM1\"").and_return(true)

			expect(helper.usb_port).to eq('/dev/ttyACM1')
		end
	end

	describe "Unity supplied methods" do
		it "creates a string of arguments from an array " do
			arr = ["option1", "option2"]
			expect(helper.tackit(arr)).to eq("\"option1option2\"")		
		end
		it "appends a common flag to a series of arguments " do
			arr = ["option1", "option2"]
			expect(helper.squash("-flag ", arr)).to eq(" -flag option1 -flag option2")
		end
		it "identifies test files within the 'test' and 'mocks' folders, prefixed by Test" do
			expect(helper.unit_test_files).to contain_exactly('spec/spec_test/TestModule1.c', 'spec/spec_mocks/TestModuleSpy.c')
		end
	end

	describe "Getting defines from config" do
		it "pulls list of defines from the yaml" do 
			expect(helper.get_defines).to eq(' -DSAMPLE_DEFINE -DOTHER_SAMPLE_DEFINE -DTEST')
		end
	end

	describe "Building and running tests" do
		let(:compile_unity) { helper.compile_and_assemble(helper.unity_source + 'unity.c') }

		it "compiles unity" do
			delete_file_if_exists(obj_folder + 'unity.o')
			compile_unity
			expect(check_for_file(obj_folder + 'unity.o')).to be true
		end

		it "runs tests" do
			expect{ helper.run_tests }.to output(/Running system tests.../).to_stdout 
		end
		it "adds a -DTEST to the gcc call" do 
			expect{ helper.run_tests }.to output(/-DTEST/).to_stdout 
		end
		it "gets the list of test files" do
			expect{ helper.run_tests }.to (
				output(/spec_test\/TestModule1.c/).to_stdout &&
				output(/spec_mocks\/TestModuleSpy.c/).to_stdout
			)
		end
		it "rename a test runner and locates it in the build folder" do
			test_file = 'spec/spec_mocks/TestRandom.c'
			expect(helper.generate_runner_name(test_file)).to eq('spec/spec_objs/TestRandom_Runner.c')
		end
		it "creates a UnityTestRunnerGenerator object" do
			target_file = unit_tests_folder + 'TestModule1.c'
			delete_file_if_exists(obj_folder + 'TestModule1_Runner.c')

			generator = helper.create_runner_generator(target_file)

			expect(check_for_file(obj_folder + 'TestModule1_Runner.c')).to be true
		end

		it "extracts includes from a target file" do
			target_file = 'spec/spec_src/main_with_other.c'

			expect(helper.extract_headers(target_file)).to contain_exactly(
				"spec/spec_objs/module.h", 
				"spec/spec_objs/other_module.h"
			)
		end

		it "compiles the test objs" do 
			target_file = unit_tests_folder + 'TestModule1.c'
			delete_file_if_exists target_file.sub(unit_tests_folder, obj_folder).sub('.c', '.o')
			delete_file_if_exists target_file.sub(unit_tests_folder, obj_folder).sub('.c', '_Runner.c')
			delete_file_if_exists target_file.sub(unit_tests_folder, obj_folder).sub('.c', '_Runner.o')
			
			helper.create_runner_generator(target_file)
			# helper.compile_test_files(target_file)

			# expect(check_for_file(target_file.sub(unit_tests_folder, obj_folder).sub('.c', '.o'))).to be true
			# expect(check_for_file(target_file.sub(unit_tests_folder, obj_folder).sub('_Runner.c', '._Runner.o'))).to be true
		end

		it "creates a list of test objs from a target Test file" do
			target_file = 'spec/spec_test/TestModule1.c'

			expect(helper.get_test_objs(target_file)).to contain_exactly(
				"spec/spec_objs/unity.o",
				"spec/spec_objs/Module1.o", 
				"spec/spec_objs/TestModule1.o", 
				"spec/spec_objs/TestModule1_Runner.o" 
			)
		end

		it "searches the sources folder for a given header and returns it if found" do
			header_with_source = source_folder + 'includes/Module1.h'
			header_without_source = source_folder + 'includes/other_module.h'

			expect(helper.check_for_source(header_with_source)).to eq(source_folder + 'Module1.c')
			expect(helper.check_for_source(header_without_source)).to be false
		end
	end
end