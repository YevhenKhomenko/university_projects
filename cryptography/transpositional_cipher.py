import math
import hashlib
import numpy as np

def encrypt(key, msg):

	ciphertext = [''] * key

	for column in range(key):
		current_index = column
		while current_index < len(msg):
			ciphertext[column] += msg[current_index]
			current_index += key
	return ''.join(ciphertext)


def decrypt(key, msg):

	num_columns = math.ceil(len(msg) / key)
	num_rows = key
	num_shaded_boxes = (num_columns * num_rows) - len(msg)
	plaintext = [''] * num_columns

	column = row = 0
	for symbol in msg:
		plaintext[column] += symbol
		column += 1
		if (column == num_columns
				or (column == num_columns - 1 and row >= num_rows - num_shaded_boxes)):
			column = 0
			row += 1
	return ''.join(plaintext)
	
def main():

	text = "Yevhen Khomenko"

	hash_object = hashlib.sha1(bytes(text, 'UTF-8'))
	hex_dig = hash_object.hexdigest()
	print(hex_dig)

	w = (10 + (26 + 72) % 7)  # 10

	print(encrypt(w, hex_dig))
	print(decrypt(w,encrypt(w, hex_dig)))

if __name__ == '__main__':
	main()
