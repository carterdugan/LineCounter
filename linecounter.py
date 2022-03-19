import os

formats = [
"makefile",
"py",
"c", "h",
"cpp", "hpp",
"js",
"cs",
"php"
]

def countFileLines(path):
	if not path.split(".")[-1] in formats:
		return 0
	try:
		with open(path) as f:
			lines = f.readlines()
			print(path + ":", len(lines))
			return len(lines)
	except:
		print("ERROR: Cannot find {} - Not a file or directory.".format(path))
		return 0

def countDirectoryLines(path):
	if path[-1] != '/':
		path += '/'
	directory = os.listdir(path)
	total = 0
	for i in directory:
		if os.path.isdir(path + i):
			total += countDirectoryLines(path + i)
		else:
			total += countFileLines(path + i)
	return total

def main():
	path = input("Enter file path: ")

	if(os.path.isdir(path)):
		print("Total: {}".format(countDirectoryLines(path)))
	else:
		countFileLines(path)

if __name__  == "__main__":
	main()