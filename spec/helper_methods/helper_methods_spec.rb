require_relative 'helper_methods'

RSpec.describe "helper_methods" do
	let(:helper_dir) { 'spec/helper_methods/' }
	describe "checking for files" do
		it "checks if a file exists" do
			file = helper_dir + 'test.rb'
			File.open(file, 'w')
			expect(check_for_file(file)).to eq(true)
			File.delete(file)
		end

	describe "deleting files" do
		it "deletes a file if it exists" do
			file = helper_dir + 'test.txt'
			File.open(file, 'w')
			expect(check_for_file(file)).to eq(true)
			delete_file_if_exists(file)
			expect(check_for_file(file)).to eq(false)
		end

		it "returns a string if asked to delete a file that doesn't exist" do
			file = helper_dir + 'test.txt'
			expect(check_for_file(file)).to eq(false)
			expect(delete_file_if_exists(file)).to eq("DELETE: '#{file}' not found")
		end

		it "deletes all files of a type if they exist" do
			target_file2 = helper_dir + 'test2.txt'
			target_file = helper_dir + 'test.txt'
			non_target_file = helper_dir + 'test.jpeg'
			
			File.open(target_file, 'w')
			File.open(target_file2, 'w')
			File.open(non_target_file, 'w')

			expect(check_for_file(target_file)).to eq(true)
			expect(check_for_file(target_file2)).to eq(true)
			expect(check_for_file(non_target_file)).to eq(true)

			delete_filetype_if_exists(helper_dir, 'txt')

			expect(check_for_file(target_file)).to eq(false)
			expect(check_for_file(target_file2)).to eq(false)
			expect(check_for_file(non_target_file)).to eq(true)

			delete_file_if_exists(target_file)
			delete_file_if_exists(non_target_file)
		end

		it "deletes an array of files" do
			file1 = 'inside.txt'
			file2 = 'the.io'
			file3 = 'computer.lol'

			delete_file_if_exists(file1)
			delete_file_if_exists(file2)
			delete_file_if_exists(file3)

			file_list = create_files([file1, file2, file3])
			expect(check_for_file(file1)).to eq(true)
			expect(check_for_file(file2)).to eq(true)
			expect(check_for_file(file3)).to eq(true)
			
			delete_array_of_files([file1, file2, file3])

			expect(check_for_file(file1)).to eq(false)
			expect(check_for_file(file2)).to eq(false)
			expect(check_for_file(file3)).to eq(false)
		end			


		it "returns a string if asked to delete a filetype that doesn't exist" do
			file = helper_dir + 'test.jpeg'
			File.open(file, 'w')
			expect(check_for_filetype(helper_dir, '.txt')).to eq(false)
			expect(delete_filetype_if_exists(file, 'txt')).to eq("DELETE: filetype '.txt' not found")
			delete_file_if_exists(file)
		end
	end

		it "checks if a file type exists" do
			target_file = helper_dir + 'test.png'
			non_target_file = helper_dir + 'test.jpeg'
			
			expect(check_for_filetype(helper_dir, 'png')).to eq(false)
			
			File.open(non_target_file, 'w')
			expect(check_for_filetype(helper_dir, 'png')).to eq(false)

			File.open(target_file, 'w')
			expect(check_for_filetype(helper_dir, 'png')).to eq(true)		

			delete_file_if_exists(target_file)
			delete_file_if_exists(non_target_file)
		end	
	end

	describe "creating test files" do
		let(:filename) { helper_dir + 'example.ollie' }
		it "returns a string when asked to create a file that exists" do
			delete_file_if_exists(filename)

			create_file(filename)
			expect(check_for_file(filename)).to eq(true)

			expect(create_file(filename)).to eq("CREATE: '#{filename}' already exists")

			delete_file_if_exists(filename)
		end

		it "creates an empty test file in none already exists" do
			delete_file_if_exists(filename)

			create_file(filename)
			expect(check_for_file(filename)).to eq(true)

			delete_file_if_exists(filename)
		end

		it "creates multiple files" do
			file1 = 'inside.txt'
			file2 = 'the.io'
			file3 = 'computer.lol'

			delete_file_if_exists(file1)
			delete_file_if_exists(file2)
			delete_file_if_exists(file3)

			file_list = create_files([file1, file2, file3])
			expect(check_for_file(file1)).to eq(true)
			expect(check_for_file(file2)).to eq(true)
			expect(check_for_file(file3)).to eq(true)
			
			delete_file_if_exists(file1)
			delete_file_if_exists(file2)
			delete_file_if_exists(file3)
		end
	end

	describe "generating file lists" do
		it "generates a list of sourcefiles for a target directory" do
			sourcefile1 = helper_dir + 'mainly.c'
			sourcefile2 = helper_dir + 'modularly.c'
			nonsourcefile = helper_dir + 'irrelevant.gris'
			files = [sourcefile1, sourcefile2, nonsourcefile]
			
			create_files(files)

			filelist = generate_source_filelist(helper_dir)

			expect(filelist).to contain_exactly(sourcefile1, sourcefile2)

			delete_array_of_files(files)
		end

		it "generates a list of objectfiles from a list of sourcefiles" do
			sourcefile1 = helper_dir + 'src/mainly.c'
			sourcefile2 = helper_dir + 'src/modularly.c'
			sourcelist = [sourcefile1, sourcefile2]
			

			objlist = generate_objlist_from_sourcelist(sourcelist)

			expect(objlist).to contain_exactly(helper_dir + 'objs/mainly.o', helper_dir + 'objs/modularly.o')
		end
	end
	describe "filepath manipulation" do
		it "adds a path and '.c' extension to a file by default" do
			src_dir = 'src/'
			objs_dir = 'objs/'
			target = 'on_point'
			expect(add_src_wrappers(src_dir, target)).to eq('src/on_point.c')
			expect(add_objs_wrappers(objs_dir, target)).to eq('objs/on_point.o')
		end
		it "adds a path and '.cpp' extension to a file if 'cpp' arg given" do
			src_dir = 'src/'
			objs_dir = 'objs/'
			target = 'on_point'
			expect(add_src_wrappers(src_dir, target, 'cpp')).to eq('src/on_point.cpp')
			expect(add_objs_wrappers(objs_dir, target)).to eq('objs/on_point.o')
		end

	end
	describe "file contents manipulation" do
		it "replaces a line within a file" do
			filepath = helper_dir + 'test_file.txt'

			delete_file_if_exists(filepath)
			file = create_file(filepath)
			
			file.close
			
			File.open(filepath, 'a') do |file|
				file.puts "user1, user2, user3"
				file.puts "user4, user5, user6"
				file.puts "user7, user8, user9"
			end
			

			filelines_array = read_lines_to_array(filepath)
			expect(filelines_array).to eq(["user1, user2, user3", "user4, user5, user6", "user7, user8, user9"])

			replace_line_in_file(filepath, "user5", "us3er9")

			filelines_array = read_lines_to_array(filepath)
			expect(read_lines_to_array(file)).to eq(["user1, user2, user3", "user4, us3er9, user6", "user7, user8, user9"])
		end
	end
	describe "usb_ports" do
		it "finds connected usb_ports using system()" do
			allow_any_instance_of(Kernel).to receive("system").with("test -e \"/dev/ttyACM0\"").and_return(false)
			allow_any_instance_of(Kernel).to receive("system").with("test -e \"/dev/ttyACM1\"").and_return(true)

			expect(get_usb_port).to eq('/dev/ttyACM1')
		end
		it "waits for a usb port to appear" do
			allow_any_instance_of(Kernel).to receive("system").with("test -e \"/dev/ttyACM0\"").and_return(false)
			allow_any_instance_of(Kernel).to receive("system").with("test -e \"/dev/ttyACM1\"").and_return(false)
			Thread.new{wait_for_usb}
			sleep(0.1)
			allow_any_instance_of(Kernel).to receive("system").with("test -e \"/dev/ttyACM1\"").and_return(true)
		end
	end
end