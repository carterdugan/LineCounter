import os
import sys

# TODO: Add comments 
# TODO: Convert extensions to lowercase
# TODO: Catch read permission error

with open('extensions.txt', 'r') as f:
	formats = f.readline()

def count_file_lines(path):
	if not path.split(".")[-1] in formats:
		return 0
	try:
		with open(path, 'r') as f:
			lines = f.readlines()
			print(path + ":", len(lines))
			return len(lines)
	except:
		print("ERROR: Cannot find '{}' - Not a file or directory. Use '--help' for more info.".format(path))
		return -1

def count_directory_lines(path):
	if path[-1] != '/':
		path += '/'
	directory = os.listdir(path)
	total = 0
	for i in directory:
		if os.path.isdir(path + i):
			total += count_directory_lines(path + i)
		else:
			num = count_file_lines(path + i)
			if not num == -1:
				total += num
	return total
	
if __name__  == "__main__":
	os.chdir(os.path.expanduser('~'))

	if(len(sys.argv) < 2):
		path = input("Enter file path: ")
	elif("--help" in sys.argv):
		print("Usage: linecounter <PATH>")
		quit()
	else:
		path = sys.argv[1]

	if(os.path.isdir(path)):
		print("Total: {}".format(count_directory_lines(path)))
	else:
		if(count_file_lines(path) == -1):
			print("ERROR: Cannot find '{}' - Not a file or directory. Use '--help' for more info.".format(path))
