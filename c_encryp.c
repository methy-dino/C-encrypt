#include"encryptor.h"
#include"decryptor.h"
#include<stdio.h>
#include<stdlib.h>
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
char* batch_encrypt_cp(char* str, size_t len, size_t* n_len, char* key, size_t key_l){
    // +1 to grant space for fill indicator.
    //ceil((len+1) / 16) * 16;
		len++;
	n_len[0] = ((len + 15) / 16) * 16;
    unsigned int seed = 0;
	for (size_t i = 0; i < key_l; i++){
		seed += key[i] * 11;
	}
  srand(seed);
	char* encrypted = malloc(n_len[0]+1);
	size_t i = 0;
	while(i < len){
		encrypted[i] = str[i];
		i++;
	}
	// garbage data for safety
	char fill = (n_len[0] - i); 
	while (i < n_len[0]){
		encrypted[i] = rand() % 256;
		i++;
	}
	encrypted[n_len[0]] = fill;
	for (size_t i = 0; i < n_len[0] / 16; i++){
		// sets up a pointer to the current batch and sends it to encryption.
		encrypt_data(&encrypted[i*16], key, key_l);
	}
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

char* batch_decrypt_cp(char* encrypted, size_t* len, char* key, size_t key_l){
	for (size_t i = 0; i < len[0] / 16; i++){
        decrypt_data(&encrypted[i*16], key, key_l);
	}
	char* decrypted = (char*) malloc(len[0] - encrypted[len[0]]);
	for (size_t i = 0; i < len[0] - encrypted[len[0]]; i++){
		decrypted[i] = encrypted[i];
	}
	len[0] -= encrypted[len[0]];
	free(encrypted);
	return decrypted;
}
// creates an encrypted copy of the file pointed by the string, and returns the filepath of that encrypted copy, otherwise returns NULL
char* encrypt_file(char* file, char* destination, char* key, size_t k_len){
	unsigned int seed = 0;
	for (size_t i = 0; i < k_len; i++){
		seed += key[i] * 11;
	}
	srand(seed);
	FILE* target = fopen(file, "rb");
	if (target == NULL){
		return NULL;
	}
	FILE* enc_cp = fopen(destination, "wb+");
    if (enc_cp == NULL){
        fclose(target);
        return NULL;    
    }
	char batch[16];
	int curr;
	char batch_i = 0;
	while ((curr = fgetc(target)) != EOF){
		batch[batch_i] = (char)curr;
		batch_i++;
		if (batch_i == 16){
			batch_i = 0;
			encrypt_data(batch, key, k_len);
			fwrite((void*)batch, 1, 16, enc_cp);
		}
	}
	fclose(target);
    // assume first to append 16 bytes, avoids an if. 
	char fill = 16;
	if (batch_i > 0){
        fill = batch_i;
		while (batch_i < 16){
			// fill with garbo data based on key, should kill many attempts to reverse engineer keys using a poorly occupied last batch, and it doesn't change the results!!! 
			batch[batch_i] = rand() % 256;
			batch_i++;
		}
		encrypt_data(batch, key, k_len);
		fwrite((void*)batch, 1, 16, enc_cp);
	}
	// save how much filler was needed.
	fwrite((void*)&fill, 1, 1, enc_cp);  
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
	char batch[16];
	int curr;
	char batch_i = 0;
	while ((curr = fgetc(target)) != EOF){
		batch[batch_i] = (char)curr;
		batch_i++;
		if (batch_i == 16){
			// check if it's the last buffer batch.
			curr = fgetc(target);
			int temp = fgetc(target); 
			if (temp == EOF){
				// if so, then write only curr bytes to the file.
				decrypt_data(batch, key, k_len);
                fwrite(batch, 1, curr, dec_cp);    
				break;
			} else {
				// if not, then write all 16 bytes to the file.
				batch_i = 2;
				decrypt_data(batch, key, k_len);
				fwrite(batch, 1, 16, dec_cp);
				batch[0] = (char) curr;
				batch[1] = (char) temp;
			}
		}
	}
	fclose(target);
	//if (batch_i > 0){
		//while (batch_i < 16){
			//batch[batch_i] = '\0';
			//batch_i++;
		//}
		//decrypt_data(batch, key, k_len);
		//fwrite((void*)batch, 1, 16, enc_cp);
	//}
	fclose(dec_cp);
	return destination;
}
