# Rakefile
require 'rake/clean'
require_relative 'rakefile_helper/RakefileHelper'
require 'colorize'

C_EXTENSION = '.c'.freeze

target = ENV["RAKE_TARGET"] ? ENV["RAKE_TARGET"] : 'teensy'

DEPLOY_CONFIG = "target_#{target}.yml".freeze
DEFAULT_TEST_CONFIG = 'target_testing.yml'.freeze

TEMP_DIRS = [
  File.join(__dir__, 'build/')
].freeze

TEMP_DIRS.each do |dir|
  directory(dir)
  CLEAN.include(dir + '*.o', dir + '*.exe')
  CLOBBER.include(dir + '*.elf', dir + '*.hex', dir + '*.testfail', dir + '*.testpass', dir + '*/*Runner.c')
end

HELPER = RakefileHelper.new(config: DEPLOY_CONFIG)

source_objs_list = HELPER.objs_list(:source)
target_objs_list = HELPER.objs_list(:target)
sources_list = HELPER.sources_list
target_sources_list = HELPER.target_sources_list

CLEAN.include(HELPER.objs_folder + '*.o',HELPER.objs_folder + '*.d',)

task default: [:unit]

task :prepare_for_tests  do
	puts "Clearing build directory".yellow

	TEMP_DIRS
  
  HELPER = RakefileHelper.new(config: DEFAULT_TEST_CONFIG)

  objs_list = HELPER.objs_list(:source)
  sources_list = HELPER.sources_list

  HELPER.configure_clean
end

task unit: [:prepare_for_tests] do
  puts "Running unit tests".yellow
  puts HELPER.unit_test_files.to_s.yellow
  HELPER.run_tests
end

task unit_stage_2: [:prepare_for_tests] do
  puts "Running unit tests on arm-none-eabi-gcc".yellow
  run_tests HELPER.unit_test_files
end

task :deploy do
  if HELPER.usb_port == nil
    puts "no valid USB".red
    return
  end

  puts "Deploying #{target} to #{HELPER.usb_port}".yellow
  case target 
  when 'teensy'
    :prepare_teensy_binary
    target = 'main'
    HELPER.load_to_teensy(target)
  when 'KL2Z'
    :prepare_KL2Z_binary
    `cp build/dac_adc.srec /run/media/al/FRDM-KL25Z/`
  else
    puts "`#{target}` is not a recognized target".yellow
  end
end

task :prepare_KL2Z_binary do
  `arm-none-eabi-objcopy -O srec #{HELPER.build_folder}dac_adc.elf #{HELPER.build_folder}dac_adc.srec`
end

task prepare_teensy_binary: [:build_target, :build_main] do
  puts "Build successful, preparing to link".yellow
  target = 'main'
  target_elf = HELPER.build_folder + target + '.elf '
  HELPER.link_obj(source_objs_list, target_elf)
  puts 'fetching .elf size'.yellow
  HELPER.get_elf_size
  puts 'copying .elf to hex'.yellow
  HELPER.copy_hex(target_elf)   
end

task :build_target => target_objs_list do
  puts "Building for #{target}".yellow
  puts "preparing #{target} library".yellow
  `ar rc build/libmy#{target}.a #{HELPER.squash("",target_objs_list)}`
end

task :build_main => source_objs_list do
  puts "Building main".yellow
end

def map_sources_to_objs(list)
  list.each do |source|
    obj = HELPER.get_objfile(source)
    file obj => source do
  puts "compiling: #{source}".yellow
      exit if HELPER.compile_and_assemble(source).include?("ABORT")
    end
  end
end

map_sources_to_objs(target_sources_list)
sources_list.each do |source|
  obj = HELPER.get_objfile(source)
  file obj => source do
puts "compiling: #{source}".yellow
    exit if HELPER.compile_and_assemble(source).include?("ABORT")
  end
end