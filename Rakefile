# Rakefile
require 'rake/clean'
require_relative 'rakefile_helper/RakefileHelper'
require 'colorize'

C_EXTENSION = '.c'.freeze

target = ENV["RAKE_TARGET"] ? ENV["RAKE_TARGET"] : 'teensy'

DEPLOY_CONFIG = "target_#{target}.yml".freeze
DEFAULT_TEST_CONFIG = 'target_testing.yml'.freeze

helper = RakefileHelper.new(config: DEPLOY_CONFIG)

source_objs_list = helper.objs_list(:source)
target_objs_list = helper.objs_list(:target)
sources_list = helper.sources_list
target_sources_list = helper.target_sources_list

helper.configure_clean()

task default: [:unit]

task :prepare_for_tests  do
	puts "Clearing build directory".yellow

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

task deploy: [:prepare_binary] do
  if helper.usb_port == nil
    puts "no valid USB".red
    return
  end

  puts "Deploying #{ENV["RAKE_TARGET"]} to #{helper.usb_port}".yellow
  case ENV["RAKE_TARGET"] 
  when 'teensy'
    target = 'main'
    helper.load_to_teensy(target)
  when 'KL2Z'
    `arm-none-eabi-objcopy -O srec #{helper.build_folder}#{target}.elf #{helper.build_folder}#{target}.srec`
    `cp build/#{target}.srec /run/media/al/FRDM-KL25Z/`
  else
    puts "`#{ENV["RAKE_TARGET"]}` is not a recognized target".yellow
  end
end


task prepare_binary: [:build_target, :build_main] do
  puts "Build successful, preparing to link".yellow
  target = 'main'
  target_elf = helper.build_folder + target + '.elf'
  helper.link_obj(source_objs_list, target_elf, ENV["RAKE_TARGET"])
  puts 'fetching .elf size'.yellow
  helper.get_elf_size
  puts 'copying .elf to hex'.yellow
  helper.copy_hex(target_elf)
end

task :build_target => target_objs_list do
  puts "Building for #{target}".yellow
  puts "preparing #{target} library".yellow
  `ar rc build/libmy#{target}.a #{helper.squash("",target_objs_list)}`
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