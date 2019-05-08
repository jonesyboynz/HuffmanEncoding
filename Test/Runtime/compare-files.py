"""
Program for comparing two files.
"""

import argparse

EXIT_SUCCESS = 0
EXIT_FAILED = 1

def compare(file1, file2):
	running = True
	position = 0
	while running:
		byte1 = file1.read(1)
		byte2 = file2.read(1)
		if byte1 != byte2:
			if len(byte1) == 0 or len(byte2) == 0:
				print("Error: EOF files are different lengths. Files were the same up to position {0}".format(position))
			else:
				print("Error: {0} and {1} do not match. Bytes differ at position {2}: {3}, {4}.".format(file1.name, file2.name, position, hex(byte1[0]), hex(byte2[0])))
			return False
		position += 1
		running = byte1 and byte2
	print("Success: {0} and {1} match.".format(file1.name, file2.name))
	return True


def get_aruments():
	parser = argparse.ArgumentParser(description="Program for comparing two files.")
	parser.add_argument("file1", help="Filename for first file to compare", type=str)
	parser.add_argument("file2", help="Filename for second file to compare", type=str)
	return parser.parse_args()

def main():
	arguments = get_aruments()
	file1 = open(arguments.file1, "rb")
	file2 = open(arguments.file2, "rb")
	if compare(file1, file2):
		exit(EXIT_SUCCESS)
	else:
		exit(EXIT_FAILED)

if __name__ == "__main__":
	main()
