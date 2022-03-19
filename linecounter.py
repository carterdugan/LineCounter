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
	with open(path) as f:
		lines = f.readlines()
		print(path + ":", len(lines))
		return len(lines)

def countDirectoryLines(path):

	directory = os.listdir(path)
	total = 0
	for i in directory:
		if i.split(".")[-1] in formats:
			total += countFileLines(path + i)
		elif os.path.isdir(path + i):
			total += countDirectoryLines(path + i)
	return total

path = input("Enter file path: ")

if(os.path.isdir(path)):
	if path[-1] != '/':
		path += '/'
	countDirectoryLines(path)
else:
	countFileLines(path)