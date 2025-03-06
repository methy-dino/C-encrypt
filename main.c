#include "c_encryp.h"
#include <stdio.h>
#include <string.h>
int main(){
	char encode[17] = "hello new world!";
	encode[17] = '\0';
	char key[3] = "KeY";
	printf("before encryption: \"");
	for (int i = 0; i < 16; i++){
		printf("%b ", encode[i]);
	}
	printf("\" - \"%s\"\n", encode);
	encrypt_data(encode, key, 3);
	printf("after encryption: \"");
	for (int i = 0; i < 16; i++){
		printf("%b ", encode[i]);
	}
	printf("\"\n");
	decrypt_data(encode, key, 3);
	printf("after decryption: \"");
	for (int i = 0; i < 16; i++){
		printf("%b ", encode[i]);
	}
	printf("\" - \"%s\"\n", encode);
    char big_str[] = "hello guys, and welcome back to my twitter thread!";
    char big_key[8] = "Twitter!";
    size_t new_size = 0;
    char* encrypted = batch_encrypt(big_str, strlen(big_str), &new_size, big_key, 8);
    batch_decrypt(encrypted, new_size, big_key, 8);
    printf("batch: \"%s\"\n", encrypted);
 	return 0;
}
