from sympy import isprime
from math import gcd
import random

GENERATE_VALUES = True

def ext_euclidean_alg(a, b):

    if a == 0:
        return (b, 0, 1)

    else:
        gcd, x, y = ext_euclidean_alg(b % a, a)
        return (gcd, y - (b // a) * x, x)


def generate_pq(bits_num):

	p = random.getrandbits(bits_num)
	q = random.getrandbits(bits_num)

	while not (isprime(p) and isprime(q)):

		if not isprime(p):
			p = random.getrandbits(bits_num)
		if not isprime(q):
			q = random.getrandbits(bits_num)

	return p,q


def generate_e(phi):

	while True:

		e = random.randint(2, phi)
		if gcd(e, phi) == 1:

			return e


def generate_d(e, phi):

    gcd, y, x = ext_euclidean_alg(e, phi)
    d = y % phi

    return d


def generate_val():

	bits_num = 8

	p, q = generate_pq(bits_num)
	n = p * q
	phi = (p - 1) * (q - 1)
	e = generate_e(phi)
	d = generate_d(e, phi)

	return (n, e, d)


def encrypt(public_key, msg):

	n, e = public_key
	encrypted_string = ""
	encrypted_list = []

	for symbol in msg:
		encrypted_symbol = (ord(symbol) ** e) % n

		encrypted_string += str(encrypted_symbol)
		encrypted_list.append(encrypted_symbol)

	return encrypted_string, encrypted_list


def decrypt(private_key, msg):

	n, d = private_key
	decrypted = ""

	for symbol in msg:
		decrypted_symbol = chr((symbol ** d) % n)
		decrypted += decrypted_symbol

	return decrypted

def get_msg():
	
	msg = []
	with open("text_var26.txt") as f:
		text = f.readlines()
		print(text)
		print("--------------------------------")
		for line in text:
			for char in line:
				msg.append(char)
	return msg

def main():

	if GENERATE_VALUES == True : 
		n, e, d = generate_val()
	else:
		print("Enter p : ")
		p = int(input())
		print("Enter q : ")
		q = int(input())
		print("Enter e : ")
		e = int(input())

		n = p * q
		phi = (p - 1) * (q - 1)
		d = generate_d(e, phi)

	
	public_key = (n, e)
	private_key = (n, d)

	print("public_key: ", public_key)
	print("private_key: ", private_key)
	print("--------------------------------")

	msg = get_msg()

	encrypted_string, encrypted_list = encrypt(public_key, msg)
	print("Encrypted message: ",encrypted_string)
	print("--------------------------------")

	decrypted_msg = decrypt(private_key, encrypted_list)
	print("Decrypted message: ",decrypted_msg)

if __name__ == "__main__":
	main()






