require_relative "../../rakefile_helper/RakefileHelper"

RSpec.configure do |config|
	helper = RakefileHelper.new
	if helper.usb_port == nil
		config.filter_run_excluding :teensy => true
	else
		config.after(:suite) do 
			helper.load_to_teensy('main')
		end
	end
end
	# end