# Rakefile
require 'rake/clean'
require_relative 'rakefile_helper/RakefileHelper'
require 'colorize'


C_EXTENSION = '.c'.freeze


TEMP_DIRS = [
  File.join(__dir__, 'build/')
].freeze

TEMP_DIRS.each do |dir|
  directory(dir)
  CLEAN.include(dir + '*.o', dir + '*.exe')
  CLOBBER.include(dir + '*.elf', dir + '*.hex', dir + '*.testfail', dir + '*.testpass', dir + '*/*Runner.c')
end

helper = RakefileHelper.new

objs_list = helper.objs_list
sources_list = helper.sources_list

CLEAN.include(helper.objs_folder + '*.o',helper.objs_folder + '*.d',)

task default: [:unit]

task :prepare_for_tests  do
	puts "Clearing build directory".yellow

	TEMP_DIRS
  
  DEFAULT_CONFIG_FILE = 'target_gcc_32.yml'.freeze
  helper = RakefileHelper.new(config: DEFAULT_CONFIG_FILE)

  objs_list = helper.objs_list
  sources_list = helper.sources_list

  helper.configure_clean
end

# Load default configuration, for now



task unit: [:prepare_for_tests] do
  puts "Running unit tests".yellow
puts helper.unit_test_files.to_s.yellow
  # run_tests helper.unit_test_files
  helper.run_tests
end

task unit_stage_2: [:prepare_for_tests] do
  puts "Running unit tests on arm-none-eabi-gcc".yellow
  run_tests helper.unit_test_files
end

task deploy_teensy: [:prepare_teensy_hex] do
  if helper.usb_port == nil
      puts "no valid USB".red
  else
      puts "Deploying to #{helper.usb_port}".yellow
      target = 'main'
      helper.load_to_teensy(target)
  end
end

task prepare_teensy_hex: [:build_for_teensy] do
  puts "Build successful, preparing to link".yellow
  target = 'main'
  target_elf = helper.build_folder + target + '.elf '
  helper.link_obj(helper.objs_list, target_elf)
  puts 'fetching .elf size'.yellow
  helper.get_elf_size
  puts 'copying .elf to hex'.yellow
  helper.copy_hex(target_elf)   
end

  
task :build_for_teensy => objs_list do
  puts "Building for teensy".yellow
end

sources_list.each do |source|
  obj = helper.get_objfile(source)
  file obj => source do
puts "compiling: #{source}".yellow
    exit if helper.compile_and_assemble(source).include?("ABORT")
  end
end