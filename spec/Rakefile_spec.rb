require 'yaml'
require_relative 'helper_methods/helper_methods'
require_relative 'support/teensy'

RSpec.describe "Rakefile" do
	let(:project_yaml) { YAML.load(File.read("project.yml")) }
	let(:build_folder) { project_yaml["compiler"]["build_path"] }
	let(:objs_folder) { project_yaml["compiler"]["objs_path"] }
	let(:target_elf_filepath) { build_folder + 'main.elf' }
	let(:target_hex_filepath) { build_folder + 'main.hex' }

	it 'cleans the objs folder on rake clean' do
		create_file(objs_folder + 'example.o') unless check_for_filetype(objs_folder, 'o')

		`rake clean`
		expect(check_for_filetype(objs_folder, 'o')).to eq(false)
	end
	
	it 'defaults to unit tests' do
		target_exe_filepath = build_folder + 'TestLedController.exe'
		`rake`

		expect(check_for_file(target_exe_filepath)).to eq(true)
	end

	# it 'deploys onto teensy', :teensy => true do
	# 	skip unless	 get_usb_port

	# 	delete_file_if_exists(target_elf_filepath)
	# 	delete_file_if_exists(target_hex_filepath)

	# 	`rake deploy_teensy`

	# 	expect(check_for_file(target_elf_filepath)).to eq(true)
	# 	expect(check_for_file(target_hex_filepath)).to eq(true)

	# 	wait_for_usb
	# 	usb_port = get_usb_port

	# 	expect(`head -n 6 #{usb_port}`).to include("G'day from teensy!")
	# end
end