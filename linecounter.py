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
verbose_file = Flag(("-f", "--verbose-file"))

# Does the same as above, but for directories
verbose_directory = Flag(("-d", "--verbose-directory"))

# Does the same as above but for errors
verbose_errors = Flag(("-e", "--verbose-errors"))

# Displays the subtotals of lines of code per extension
subtotals = Flag(("-s", "--subtotals"))

# Includes .git folders, idk why you would want to do this, but feel free
include_git = Flag(("-g", "--include-git"))

# Continues counting down the directory tree
tree = Flag(("-t", "--tree"))

# A list of options flags
option_flags = [verbose_file, verbose_directory, verbose_errors, subtotals, tree, include_git]

# File extension dictionary, is a disctionary in order to count subtotals
formats = {}

def print_help():
	print("Use option --help to view this message.")
	print("Usage: linecounter [OPTIONS] <PATH> <EXTENSION_1>,[EXTENSION_2],...,[EXTENSION_N]\n")
	print("{:^25}".format("[[OPTIONS]]\n"))
		
	for flag in option_flags:
		print("{:>10} {:<15}\n".format(flag.options[0], flag.options[1]))
	quit()

# Counts the lines in a file
def count_file_lines(path):

	if os.path.isdir(path):
		return 0

	extension = path.split(".")[-1]

	# Check if the file being checked at path has a valid extension
	if not extension in formats:
		if verbose_errors.flag:
			print("'{}' file extension not recognized. Skipping.".format(path))
		return 0

	# Attempt to open the file and count the lines
	try:
		with open(path, 'r') as f:
			lines = [line for line in f.readlines() if line != "\n"]
			num = len(lines)
			
			if verbose_file.flag:
				print(path + ":", num)

			# Increment subtotal
			formats[extension] += num

			return num
	
	except FileNotFoundError:
		if verbose_errors.flag:
			print("Cannot find '{}' - Not a file or directory. Use '--help' for more info.".format(path))
		return -1
	except PermissionError:
		if verbose_errors.flag:
			print("Permission denied. Cannot access '{}'".format(path))
		return -1


# Counts the lines in a directory through recursion and calls to count_file_lines()
def count_directory_lines(path):

	if ".git" in path and not include_git.flag:
		return 0


	if path[-1] != '/':
		path += '/'
	
	# Permission error catch
	try:
		directory = os.listdir(path)
	except PermissionError:
		if verbose_errors.flag:
			print("Permission denied. Cannot access '{}'".format(path))
		return 0


	total = 0
	for i in directory:
		new_path = path + i
		# Recursively navigate directories
		if os.path.isdir(new_path) and tree.flag:
			total += count_directory_lines(new_path)
		# Otherwise count file lines
		else:
			num = count_file_lines(path + i)
			if not num == -1:
				total += num
	
	if total > 0 and verbose_directory.flag:
		print("Directory subtotal for '{}': {}".format(path, total))
	return total
	
if __name__  == "__main__":

	if "--help" in sys.argv:
		print_help()

	os.chdir(os.path.expanduser('~'))

	options = []

	# Missing path and extension minimum
	if len(sys.argv) < 3:
		print_help()
	else:
		path = sys.argv[-2]
		extensions = sys.argv[-1].split(",")
		options = sys.argv[1:-2]

	for flag in option_flags:
		for option in flag.options:
			if option in options:
				flag.flag = not flag.flag
				break

	for i in extensions:
		formats.update({i.strip("."):0})

	if os.path.isdir(path):
		total = count_directory_lines(path)
		if subtotals.flag:
			for extension in formats:
				percent = 0 if total <= 0 else "{0:.2f}".format(formats[extension] / total * 100)
				print(".{}: {} lines ({}%)".format(extension, formats[extension], percent))
		print("Total: {} lines".format(total))
	else:
		verbose_file.flag = True
		count_file_lines(path)
