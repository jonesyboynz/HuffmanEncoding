"""
Program for converting text to binary.
Accepts 0s and 1s as inputs.
Outputs corresponding character for every 8 binary symbols which have been recieved.
Skips white space.  
"""

import sys

def validate(data):
	if len(data) % 8 != 0:
		raise ValueError("Number of symbols should be a multiple of 8.")
	invalid_characters = data.replace("1", "").replace("0", "")
	if len(invalid_characters) != 0:
		raise ValueError("Input string contains invalid characters: {0}".format(invalid_characters))		

def process_and_output(data):
	index = 0
	prev_index = 0
	while prev_index < len(data):
		index = index + 8 if index + 8 <= len(data) else len(data)
		print(chr(int(data[prev_index:index], 2)), end="")
		prev_index = index

def main():
	try:
		data = input("Enter Binary: ")
		data = data.replace(" ", "").replace("\n", "")
		validate(data)
		process_and_output(data)
	except EOFError:
		pass

if __name__ == "__main__":
	main()