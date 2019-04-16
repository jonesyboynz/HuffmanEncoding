"""
Program for viewing data in binary
Accepts text as input
Outputs binary values for input
"""

import argparse

def get_aruments():
	parser = argparse.ArgumentParser(description="Program for viewing a file in binary.")
	parser.add_argument("input_filename", help="file to view", type=str)
	parser.add_argument("-not_raw", action="store_true")
	return parser.parse_args()

def main():
	arguments = get_aruments()
	if arguments.not_raw:
		file = open(arguments.input_filename, 'r')
		data = [ord(x) for x in file.read()]
	else:
		file = open(arguments.input_filename, "rb")
		data = file.read()
	for i in range(0, len(data) // 8 + 1 if(len(data) % 8 > 0) else 0):
		print("{0:04X} {1:04X} | ".format((i * 8) // 0x10000, (i * 8) % 0x10000), end="")
		print(" ".join(["{0:08b}".format(x) for x in data[i * 8 : (i + 1) * 8]]))

if __name__ == "__main__":
	main()
