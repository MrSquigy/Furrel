# Copyright (c) 2019 Jonathan Vice
# This file is part of Furrel.

# This script encodes Turing Machines into strings for use with Furrel

import os
import sys

# Script settings
# Dirs
encoded_tms_dir = 'encoded_tms'
decoded_tms_dir = 'decoded_tms'

# CWL Characters
on = 'a'
off = 'b'
blank = '^'
start = '#'
move_left = 'l'
move_right = 'r'

def encode_character(char):
	for word in cwl:
		if char == word[0]:
			return word[1]

def encode_number(num):
	return ''.join([on for _ in range(num)]) + off

def encode_line(line):
	tokens = line.split()
	#print(tokens, end=' ')

	encoded_line = encode_number(int(tokens[0]))
	encoded_line += encode_number(int(tokens[1]))
	encoded_line += encode_character(tokens[2])
	encoded_line += encode_character(tokens[3])
	
	if tokens[4] == move_left:
		encoded_line += on
	elif tokens[4] == move_right:
		encoded_line += off

	#print(encoded_line)
	return encoded_line

if __name__ == '__main__':
	cwl = [[on, on + on], [off, on + off], [blank, off + on], [start, off + off]]

	# Create output dirs if don't exist
	os.makedirs(encoded_tms_dir, exist_ok = True)
	os.makedirs(decoded_tms_dir, exist_ok = True)

	if len(sys.argv) < 3:
		print('usage: coder.py [-d] [-e] <input file>')
		sys.exit()
	
	mode = sys.argv[1][-1]
	file_name = sys.argv[2]

	if not os.path.isfile(file_name):
		print('\'' + file_name + '\' not found... exiting')
		sys.exit()
	
	with open(file_name, 'r') as f:
		tm = f.read().split('\n')
	
	if mode == 'e': # Encode mode
		encoded_tm = ''
		for row in tm:
			encoded_tm += encode_line(row)
			encoded_file = encoded_tms_dir + '/' + file_name

		with open(encoded_file, 'w') as new_file:
			new_file.write(encoded_tm)
		print('Encoding complete! Encoded TM saved as ' + encoded_file)

	elif mode == 'd': # Decode mode
		print('Decoding is not implemented yet')