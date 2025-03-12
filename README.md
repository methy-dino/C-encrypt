# C-encryp, a dumbed down AES implementation.

### how much different is it from AES?
there are not many differences from AES, in fact, there is only one, it does not build key parts, it uses just a byte from the main key instead.
### How to use it?
The library has two main functions, ```encrypt_data```, and ```decrypt_data```, both of which take a ```char*``` (with assumed length of 16), a key, and the key's length (in bytes), keys can be any length, but it is recommended to make them bigger than 16 bytes.
### batch encryption.
c_encryp has a batch encryption function, which encrypts any given string, padding it to have a length multiple of 16.
### file encryption.
c_encryp has a function similar to batch encrypting, except it takes a file pathas a pointer and encrypts such file, writing the contents to a second file, pointed by another file path, it supports any file type.
