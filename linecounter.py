import os

def countFileLines(path):
	with open(path) as f:
		lines = f.readlines()
		print(path + ":", len(lines))
		return len(lines)

def countDirectoryLines(path):
	formats = ["makefile", "py", "c", "h", "cpp", "hpp"]

	directory = os.listdir(path)
	total = 0
	for i in directory:
		if i.split(".")[-1] in formats:
			total += countFileLines(path + '/' + i)
		elif os.path.isdir(path + '/' + i):
			total += countDirectoryLines(path + '/' + i)
	return total

choice = input("1.) File\n2.) Director\n>>> ")
try:
	choice = int(choice)
except:
	choice = -1

path = input("Now enter the path\n>>> ")

if(choice == 1):
	countFileLines(path)
elif(choice == 2):
	print("\n\nTotal: {} lines of code".format(countDirectoryLines(path)))
else:
	print("Invalid option")