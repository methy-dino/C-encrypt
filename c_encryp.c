#include"encryptor.h"
#include"decryptor.h"
#include<stddef.h>
// can't encrypt in place due to chance of bad size
char* batch_encrypt(char* str, size_t len, size_t* n_len, char* key, size_t key_l){
	//ceil(len / 16) * 16; 
	n_len[0] = ((len + 15) / 16) * 16;
	char* encrypted = malloc(n_len[0]);
	size_t i = 0;
	while(i < len){
		encrypted[i] = str[i];
		i++;
	}
	// better than calling calloc
	while(i < n_len[0]){
		encrypted[i] = '\0';
		i++;
	}
	for (size_t i = 0; i < n_len[0] / 16; i++){
		// sets up a pointer to the current batch and sends it to encryption.
		encrypt_data(&encrypted[i*16], key, key_l);
	}
	return encrypted;
}
// should always be a multiple of 16, it is a pair to batch_encrypt.
void batch_decrypt(char* encrypted, size_t len, char* key, size_t key_l){
	for (size_t i = 0; i < len / 16; i++){
		decrypt_data(&encrypted[i*16], key, key_l);
	}
	// shrimple
}	
