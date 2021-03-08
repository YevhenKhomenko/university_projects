import rsa
import transpositional_cipher as tc
from sha1_hashing import SHA1Hash

message = "Yevhen Khomenko Group DA-72 Yevhen Khomenko Group DA-72 Yevhen Khomenko Group DA-72 Yevhen Khomenko Group DA-72"
msg_key = (10 + (26 + 72) % 7)  # 10
print("message: ",message)
print("key: ",msg_key)

hash_input = bytes(message, "utf-8")
hashed_msg  = SHA1Hash(hash_input).hash()
print("message hash : ",hashed_msg)

encrypted_msg_hash = tc.encrypt(msg_key, hashed_msg)
print("encrypted message hash: ", encrypted_msg_hash)

n,e,d = rsa.generate_val()
public_key = (n, e)
private_key = (n, d)

encrypted_key_string, encrypted_key_list = rsa.encrypt(public_key,list(str(msg_key)))
print("encrypted key: ",encrypted_key_string)

decrypted_key = int(rsa.decrypt(private_key, encrypted_key_list))
print("decrypted key: ",decrypted_key)

decrypted_msg_hash = tc.decrypt(decrypted_key, encrypted_msg_hash)
print("decrypted message hash: ", decrypted_msg_hash)
print("message hash          : ", hashed_msg)








