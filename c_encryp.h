//header automatically generated by autoHead
#pragma once
#include"encryptor.h"
#include"decryptor.h"
#include<stdio.h>
#include<stdlib.h>
void batch_encrypt(char* bytes, size_t len, char* key, size_t key_l);
void batch_decrypt(char* bytes, size_t len, char* key, size_t key_l);
/* ********** args **********  
 *	char* str -> the bytes of the data to be encrypted.
 *	size_t len -> the index of the data's last byte.
 *	size_t* n_len -> variable to hold the length (index of fill indicator) after encryption.
 *	char* key -> the key to the encryption.
 *	size_t key_l -> length of the key's bytes.
 * ********** returns **********
 * char* -> encrypted data that can be written to a file and decoded by file_decrypt.
 */
char* batch_encrypt_cp(char* str, size_t len, char* key, size_t key_l);
/* ********** args **********  
 *	char* encrypted -> the bytes of the data to be decrypted.
 *	size_t* len -> the index of the data's last byte. (which is automatically written by batch_encrypt's size_t* n_len) and is also a variable to hold the length (index of last byte) after decryption.
 *	char* key -> the key to the decryption.
 *	size_t key_l -> length of the key's bytes.
 * ********** returns **********
 * char* -> decrypted data.
 * ********** warnings **********
 * frees the memory block of encrypted automatically. 
 */
char* batch_decrypt_cp(char* encrypted, size_t len, char* key, size_t key_l);
// creates an encrypted copy of the file pointed by the string, and returns the filepath of that encrypted copy, otherwise returns NULL
char* encrypt_file(char* file, char* destination, char* key, size_t k_len);
char* decrypt_file(char* file, char* destination, char* key, size_t k_len);
