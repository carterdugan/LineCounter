import os
import sys

# TODO: Add flag descriptions

# Class for command line flags
class Flag:
	def __init__(self, options, default=False):

		# Options that specify that the flag will be flipped
		self.options = options

		self.flag = default
		self.description = ""

# Explicitly states which files are being counted and how many lines were counted
verboseFile = Flag(["-vf", "--verbose-file"])

# Does the same as above, but for directories
verboseDirectory = Flag(["-vd", "--verbose-directory"])

verboseErrors = Flag(["-ve", "--verbose-errors"])

# Continues counting down the directory tree
tree = Flag(["-t", "--tree"])

optionFlags = [verboseFile, verboseDirectory, verboseErrors, tree]

# File extension list
formats = []

# Counts the lines in a file
def count_file_lines(path):
	# Check if the file being checked at path has a valid extension
	if not path.split(".")[-1] in formats:
		if(verboseErrors.flag):
			print("\n'{}' file extension not recognized. Skipping.\n".format(path))
		return 0

	# Attempt to open the file and count the lines
	try:
		with open(path, 'r') as f:
			lines = f.readlines()

			if(verboseFile.flag):
				print(path + ":", len(lines))
			
			return len(lines)
	
	except FileNotFoundError:
		if(verboseErrors.flag):
			print("Cannot find '{}' - Not a file or directory. Use '--help' for more info.".format(path))
		return -1
	except PermissionError:
		if(verboseErrors.flag):
			print("Permission denied. Cannot access '{}'".format(path))
		return -1

# Counts the lines in a directory through recursion and calls to count_file_lines()
def count_directory_lines(path):

	if path[-1] != '/':
		path += '/'
	
	directory = os.listdir(path)
	
	total = 0
	for i in directory:
		if os.path.isdir(path + i) and tree.flag:
			total += count_directory_lines(path + i)
		else:
			num = count_file_lines(path + i)
			if not num == -1:
				total += num
	
	if(total > 0 and verboseDirectory.flag):
		print("Directory subtotal for '{}': {}".format(path, total))
	return total
	
if __name__  == "__main__":

	if("--help" in sys.argv):
		print("Usage: linecounter [OPTIONS] <PATH> <EXTENSION_1>,[EXTENSION_2],...,[EXTENSION_N]")
		print("~~~OPTIONS~~~")
		
		for flag in optionFlags:
			print("{:>10} {:<15}\n".format(flag.options[0], flag.options[1]))
		quit()

	os.chdir(os.path.expanduser('~'))

	options = []

	if(len(sys.argv) < 2):
		path = input("Enter file or directory path: ")
	else:
		path = sys.argv[-2]
	if(len(sys.argv) < 3):
		extensions = input("Enter your file extensions, separated by space [.c .py .cpp ... etc]: ").split()
	else:
		extensions = sys.argv[-1].split(",")
		options = sys.argv[1:-2]

	for flag in optionFlags:
		for option in flag.options:
			if option in options:
				flag.flag = not flag.flag
				break

	for i in extensions:
		formats.append(i.strip("."))

	if(os.path.isdir(path)):
		print("Total: {}".format(count_directory_lines(path)))
	else:
		verboseFile.flag = True
		count_file_lines(path)
