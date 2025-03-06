#include "c_encryp.h"
#include <stdio.h>
int main(){
	char encode[17] = "hello,new world!";
	encode[17] = '\0';
	char key[3] = "abc";
	printf("before encryption: \"");
	for (int i = 0; i < 16; i++){
		printf("%b", encode[i]);
	}
	printf("\" - \"%s\"\n", encode);
	encrypt_data(encode, key, 3);
	printf("after encryption: \"");
	for (int i = 0; i < 16; i++){
		printf("%b", encode[i]);
	}
	printf("\"\n");
	decrypt_data(encode, key, 3);
	printf("after decryption: \"");
	for (int i = 0; i < 16; i++){
		printf("%b", encode[i]);
	}
	printf("\" - \"%s\"\n", encode);
	return 0;
}
