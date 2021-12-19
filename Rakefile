# Rakefile
require 'rake/clean'
require_relative 'rakefile_helper/RakefileHelper'
require 'colorize'

C_EXTENSION = '.c'.freeze

DEFAULT_DEPLOY_CONFIG = 'target_teensy.yml'.freeze
DEFAULT_TEST_CONFIG = 'target_testing.yml'.freeze

TEMP_DIRS = [
  File.join(__dir__, 'build/')
].freeze

TEMP_DIRS.each do |dir|
  directory(dir)
  CLEAN.include(dir + '*.o', dir + '*.exe')
  CLOBBER.include(dir + '*.elf', dir + '*.hex', dir + '*.testfail', dir + '*.testpass', dir + '*/*Runner.c')
end

helper = RakefileHelper.new(config: DEFAULT_DEPLOY_CONFIG)

source_objs_list = helper.objs_list(:source)
target_objs_list = helper.objs_list(:target)
sources_list = helper.sources_list
target_sources_list = helper.target_sources_list

CLEAN.include(helper.objs_folder + '*.o',helper.objs_folder + '*.d',)

task default: [:unit]

task :prepare_for_tests  do
	puts "Clearing build directory".yellow

	TEMP_DIRS
  
  helper = RakefileHelper.new(config: DEFAULT_TEST_CONFIG)

  objs_list = helper.objs_list(:source)
  sources_list = helper.sources_list

  helper.configure_clean
end


task unit: [:prepare_for_tests] do
  puts "Running unit tests".yellow
  puts helper.unit_test_files.to_s.yellow
  helper.run_tests
end

task unit_stage_2: [:prepare_for_tests] do
  puts "Running unit tests on arm-none-eabi-gcc".yellow
  run_tests helper.unit_test_files
end

task :deploy, [:target] do |t, args|
  if helper.usb_port == nil
    puts "no valid USB".red
    return
  end

  case args[:target] 
  when 'teensy'
    :prepare_teensy_binary
    puts "Deploying to #{helper.usb_port}".yellow
    target = 'main'
    helper.load_to_teensy(target)
  when 'KL25Z'
    :prepare_KL25Z_binary
    `cp build/dac_adc.srec /run/media/al/FRDM-KL25Z/`
  else
    puts "`#{args[:target]}` is not a recognized target".yellow
  end
end

task :prepare_KL25Z_binary do
  `arm-none-eabi-objcopy -O srec #{helper.build_folder}dac_adc.elf #{helper.build_folder}dac_adc.srec`
end

task prepare_teensy_binary: [:build_for_teensy, :build_main] do
  puts "Build successful, preparing to link".yellow
  target = 'main'
  target_elf = helper.build_folder + target + '.elf '
  helper.link_obj(source_objs_list, target_elf)
  puts 'fetching .elf size'.yellow
  helper.get_elf_size
  puts 'copying .elf to hex'.yellow
  helper.copy_hex(target_elf)   
end

task :build_for_teensy => target_objs_list do
  puts "Building for teensy".yellow
  puts "preparing teensy library".yellow
  `ar rc build/libmyteensy.a #{helper.squash("",target_objs_list)}`
end

task :build_main => source_objs_list do
  puts "Building main".yellow
end

target_sources_list.each do |source|
  obj = helper.get_objfile(source)
  file obj => source do
puts "compiling: #{source}".yellow
    exit if helper.compile_and_assemble(source).include?("ABORT")
  end
end

sources_list.each do |source|
  obj = helper.get_objfile(source)
  file obj => source do
puts "compiling: #{source}".yellow
    exit if helper.compile_and_assemble(source).include?("ABORT")
  end
end