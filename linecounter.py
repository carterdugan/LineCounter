import os
import sys

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

# Does the same as above but for errors
verboseErrors = Flag(["-ve", "--verbose-errors"])

# Displays the subtotals of lines of code per extension
subtotals = Flag(["-st", "--subtotals"])

# Includes .git folders, idk why you would want to do this, but feel free
includeGit = Flag(["-ig", "--include-git"])

# Continues counting down the directory tree
tree = Flag(["-t", "--tree"])

# A list of options flags
optionFlags = [verboseFile, verboseDirectory, verboseErrors, subtotals, tree, includeGit]

# File extension dictionary, is a disctionary in order to count subtotals
formats = {}

# Counts the lines in a file
def count_file_lines(path):

	extension = path.split(".")[-1]

	# Check if the file being checked at path has a valid extension
	if not extension in formats:
		if(verboseErrors.flag):
			print("'{}' file extension not recognized. Skipping.".format(path))
		return 0

	# Attempt to open the file and count the lines
	try:
		with open(path, 'r') as f:
			lines = [line for line in f.readlines() if line != "\n"]
			num = len(lines)
			
			if(verboseFile.flag):
				print(path + ":", num)

			# Increment subtotal
			formats[extension] += num

			return num
	
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

	if(".git" in path and not includeGit.flag):
		return 0


	if path[-1] != '/':
		path += '/'
	
	directory = os.listdir(path)
	
	total = 0
	for i in directory:
		newPath = path + i
		# Recursively navigate directories
		if os.path.isdir(newPath) and tree.flag:
			total += count_directory_lines(path + i)
		# Otherwise count file lines
		else:
			num = count_file_lines(newPath)
			if not num == -1:
				total += num
	
	if(total > 0 and verboseDirectory.flag):
		print("Directory subtotal for '{}': {}".format(path, total))
	return total
	
if __name__  == "__main__":

	if("--help" in sys.argv):
		print("Usage: linecounter [OPTIONS] <PATH> <EXTENSION_1>,[EXTENSION_2],...,[EXTENSION_N]\n")
		print("{:^25}".format("[[OPTIONS]]\n"))
		
		for flag in optionFlags:
			print("{:>10} {:<15}\n".format(flag.options[0], flag.options[1]))
		quit()

	os.chdir(os.path.expanduser('~'))

	options = []

	if(len(sys.argv) < 3):
		print("Usage: linecounter [OPTIONS] <PATH> <EXTENSION_1>,[EXTENSION_2],...,[EXTENSION_N]")
		quit()
	else:
		path = sys.argv[-2]
		extensions = sys.argv[-1].split(",")
		options = sys.argv[1:-2]

	for flag in optionFlags:
		for option in flag.options:
			if option in options:
				flag.flag = not flag.flag
				break

	for i in extensions:
		formats.update({i.strip("."):0})

	total = count_directory_lines(path)

	if(subtotals.flag):
		for extension in formats:
			print(".{}: {} lines".format(extension, formats[extension]))

	if(os.path.isdir(path)):
		print("Total: {} lines".format(total))
	else:
		verboseFile.flag = True
		count_file_lines(path)
