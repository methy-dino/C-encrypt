#include"encryptor.h"
#include"decryptor.h"
#include<stdio.h>
#include<stdlib.h>
#include "libs/dependencies/std.h"
void batch_encrypt(char* bytes, size_t len, char* key, size_t key_l){
	for (size_t i = 0; i < (len / 16); i++){
		encrypt_data(&bytes[i*16], key, key_l);
	}
	encrypt_data(&bytes[len - 15], key, key_l);
	//encrypt_data(&bytes[(len / 16 - 1) * 16], key, key_l);
}
void batch_decrypt(char* bytes, size_t len, char* key, size_t key_l){
	//decrypt_data(&bytes[(len / 16 - 1) * 16], key, key_l);
	//bytes[len] = bytes[len] ^ bytes[key[0] % len];
	decrypt_data(&bytes[len - 15], key, key_l);
	for (size_t i = 0; i < len / 16; i++){
		decrypt_data(&bytes[i*16], key, key_l);
	}
}

/* ********** args **********  
 *	char* str -> the bytes of the data to be encrypted.
 *	size_t len -> the index of the data's last byte.
 *	size_t* n_len -> variable to hold the length (index of fill indicator) after encryption.
 *	char* key -> the key to the encryption.
 *	size_t key_l -> length of the key's bytes.
 * ********** returns **********
 * char* -> encrypted data that can be written to a file and decoded by file_decrypt.
 */
char* batch_encrypt_cp(char* str, size_t len, char* key, size_t key_l){
    char* encrypted = malloc(len+1);
    for (size_t i = 0; i < len+1; i++){
		encrypted[i] = str[i];
	}    
	for (size_t i = 0; i < len / 16; i++){
		encrypt_data(&encrypted[i*16], key, key_l);
	}
    encrypt_data(&encrypted[len - 15], key, key_l);
	return encrypted;
}
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

char* batch_decrypt_cp(char* encrypted, size_t len, char* key, size_t key_l){
	char* decrypted = (char*) malloc(len+1);
	for (size_t i = 0; i < len+1; i++){
		decrypted[i] = encrypted[i];
	}
    decrypt_data(&decrypted[len - 15], key, key_l);
	for (size_t i = 0; i < len / 16; i++){
		decrypt_data(&decrypted[i*16], key, key_l);
	}
	free(encrypted);
	return decrypted;
}
// creates an encrypted copy of the file pointed by the string, and returns the filepath of that encrypted copy, otherwise returns NULL
char* encrypt_file(char* file, char* destination, char* key, size_t k_len){
	FILE* target = fopen(file, "rb");
	if (target == NULL){
		return NULL;
	}
	FILE* enc_cp = fopen(destination, "wb+");
  if (enc_cp == NULL){
	  fclose(target);
		return NULL;    
  }
	char batch_i = 0;
	long max = f_len(file);
	long batches = max - 16 - (max % 16);
	char batch[16 + (max % 16)];
	long i = 0;
	while (i < batches){
			i += 16;
			fread((void*) batch, 1, 16, target);
			encrypt_data(batch, key, k_len);
			fwrite((void*)batch, 1, 16, enc_cp);
	}
	fread((void*) batch, 1, 16 + (max % 16), target);
	encrypt_data(batch, key, k_len);
	encrypt_data(&batch[16 + (max % 16) - 16], key, k_len);
    fwrite((void*)batch, 1,16 + (max % 16), enc_cp);	
    fclose(target);
	fclose(enc_cp);
	return destination;
}
char* decrypt_file(char* file, char* destination, char* key, size_t k_len){	
	FILE* target = fopen(file, "rb");
	if (target == NULL){
		return NULL;
	}
	FILE* dec_cp = fopen(destination, "wb+");
    if (dec_cp == NULL){
        fclose(target);
        return NULL;    
    }
	long max = f_len(file);
	long batches = max - 16 - (max % 16);
	char batch[16 + (max % 16)];
	long i = 0;
	while (i < batches){
			i += 16;
			fread((void*) batch, 1, 16, target);
			decrypt_data(batch, key, k_len);
			fwrite((void*)batch, 1, 16, dec_cp);
	}
	fread((void*) batch, 1, 16 + (max % 16), target);
	decrypt_data(&batch[16 + (max % 16) - 16], key, k_len);
	decrypt_data(batch, key, k_len);
    fwrite((void*)batch, 1,16 + (max % 16), dec_cp);
	fclose(target);
	fclose(dec_cp);
	return destination;
}
