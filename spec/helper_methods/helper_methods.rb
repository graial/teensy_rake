require 'rake'

def check_for_file(file)
	File.exist?(file)
end

def delete_file_if_exists(file)
	if check_for_file(file) 
		File.delete(file)
	else
		"DELETE: '#{file}' not found"
	end
end

def delete_array_of_files(file_array)
	file_array.each do |file|
		delete_file_if_exists(file)
	end
end

def check_for_filetype(folder_path, extension)
	Dir[folder_path + "*.#{extension}"].count > 0
end

def delete_filetype_if_exists(folder_path, extension)
	matched_files = Dir[folder_path + "*.#{extension}"]
	if matched_files.count > 0
		matched_files.each { |file| File.delete(file) }
	else
		"DELETE: filetype '.#{extension}' not found"
	end
end

def create_file(filepath)
	if check_for_file(filepath)
		"CREATE: '#{filepath}' already exists"
	else
		File.open(filepath, 'w')
	end
end

def create_files(file_array)
	file_array.each do |file|
		create_file(file)
	end
end

def generate_source_filelist(dir)
	Rake::FileList[dir + "*.c"]
end

def generate_objlist_from_sourcelist(source_array)
	obj_array = []
	source_array.each do |filename|
		new_filename = filename.gsub("src/", "objs/").gsub(".c", ".o")
		obj_array.push(new_filename)
	end
	obj_array
end

def add_src_wrappers(path, target, ext = 'c')
	path + target + '.' + ext
end

def add_objs_wrappers(path, target)
	path + target + '.o'
end

def read_lines_to_array(filepath)
	file = File.open(filepath, 'r')
	lines = file.readlines.map(&:chomp)
	file.close
	lines
end

def replace_line_in_file(filepath, line_to_replace, replacement_line)
	file_lines = read_lines_to_array(filepath)
	new_lines = ''
	file_lines.each do |line|
		new_lines += line.gsub(line_to_replace, replacement_line) + "\n"
	end
	File.write(filepath, new_lines, mode: 'w')

end

def run_executable(exe)
	puts "running executable: #{exe}"
	`./#{exe}`
end


def get_usb_port
	if system("test -e \"/dev/ttyACM0\"")
		'/dev/ttyACM0'
	elsif system("test -e \"/dev/ttyACM1\"")
		'/dev/ttyACM1'
	else
		nil
	end
end

def wait_for_usb
	puts "trying teensy usb port"
	while (!system("test -e \"/dev/ttyACM0\"") && !system("test -e \"/dev/ttyACM1\"")) do
		puts "trying teensy usb port again"
		sleep(0.5)
	end
end