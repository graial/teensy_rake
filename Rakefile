# Rakefile
require 'rake/clean'
require_relative 'rakefile_helper/RakefileHelper'
require 'colorize'

C_EXTENSION = '.c'.freeze

target = ENV["RAKE_TARGET"] ? ENV["RAKE_TARGET"] : 'teensy'

DEPLOY_CONFIG = "target_#{target}.yml".freeze
DEFAULT_TEST_CONFIG = 'target_testing.yml'.freeze

HELPER = RakefileHelper.new(config: DEPLOY_CONFIG)

source_objs_list = HELPER.objs_list(:source)
target_objs_list = HELPER.objs_list(:target)
sources_list = HELPER.sources_list
target_sources_list = HELPER.target_sources_list

HELPER.configure_clean()

task default: [:unit]

task :prepare_for_tests  do
	puts "Clearing build directory".yellow

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

task deploy: [:prepare_binary] do
  if HELPER.usb_port == nil
    puts "no valid USB".red
    return
  end

  puts "Deploying #{ENV["RAKE_TARGET"]} to #{HELPER.usb_port}".yellow
  case ENV["RAKE_TARGET"] 
  when 'teensy'
    target = 'main'
    HELPER.load_to_teensy(target)
  when 'KL2Z'
    `cp build/#{target}.srec /run/media/al/FRDM-KL25Z/`
  else
    puts "`#{target}` is not a recognized target".yellow
  end
end

task :prepare_generate_srec do
  target = 'main'
  `arm-none-eabi-objcopy -O srec #{HELPER.build_folder}#{target}.elf #{HELPER.build_folder}#{target}.srec`
end

task prepare_binary: [:build_target, :build_main] do
  puts "Build successful, preparing to link".yellow
  target = 'main'
  target_elf = HELPER.build_folder + target + '.elf'
  HELPER.link_obj(source_objs_list, target_elf, ENV["RAKE_TARGET"])
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


target_sources_list.each do |source|
  obj = HELPER.get_objfile(source)
  file obj => source do
puts "compiling: #{source}".yellow
    exit if HELPER.compile_and_assemble(source).include?("ABORT")
  end
end

sources_list.each do |source|
  obj = HELPER.get_objfile(source)
  file obj => source do
puts "compiling: #{source}".yellow
    exit if HELPER.compile_and_assemble(source).include?("ABORT")
  end
end