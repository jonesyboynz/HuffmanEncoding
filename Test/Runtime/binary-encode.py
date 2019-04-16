"""
Program for converting text to binary.
Accepts 0s and 1s as inputs.
Outputs bytes to a file.
Skips white space.  
"""

import sys
import argparse

def get_aruments():
	parser = argparse.ArgumentParser(description="Program for converting text to binary.\nAccepts 0s and 1s as inputs.\nOutputs bytes to a file.\nSkips white space.  ")
	parser.add_argument("output_filename", help="filename for the file which the binary data is written to", type=str)
	return parser.parse_args()

def validate(data):
	if len(data) % 8 != 0:
		raise ValueError("Number of symbols should be a multiple of 8.")
	invalid_characters = data.replace("1", "").replace("0", "")
	if len(invalid_characters) != 0:
		raise ValueError("Input string contains invalid characters: {0}".format(invalid_characters))		

def process_and_output(data, file):
	index = 0
	prev_index = 0
	output = []
	while prev_index < len(data):
		index = index + 8 if index + 8 <= len(data) else len(data)
		output.append(int(data[prev_index:index], 2))
		prev_index = index
	file.write(bytes(output))

def main():
	arguments = get_aruments()
	with open(arguments.output_filename, "wb") as output_file:
		try:
			data = input("Enter Binary: ")
			data = data.replace(" ", "").replace("\n", "")
			validate(data)
			process_and_output(data, output_file)
		except EOFError:
			pass

if __name__ == "__main__":
	main()