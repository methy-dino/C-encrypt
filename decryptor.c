#include<stddef.h>
#include "libs/gal_mult.h"
void key_remove(unsigned char* byte_data, char key){
	for (int i = 15; i > 0; i--){
		byte_data[i] = byte_data[i] ^ key;
	}
    byte_data[0] = byte_data[0] ^ key;	
}
void row_unshift(unsigned char* row){
	char temp = row[3];
	row[3] = row[2];
	row[2] = row[1];
	row[1] = row[0];
	row[0] = temp;
}
void col_unmix(unsigned char* col){
	unsigned char col_cp[4];
  int i;
  for (i = 0; i < 4; i++){
		col_cp[i] = col[i];
  }
  col[0] = gal_mult(col_cp[0], 14) ^ gal_mult(col_cp[3], 9) ^ gal_mult(col_cp[2], 13) ^ gal_mult(col_cp[1], 11);
    col[1] = gal_mult(col_cp[1], 14) ^ gal_mult(col_cp[0], 9) ^ gal_mult(col_cp[3], 13) ^ gal_mult(col_cp[2], 11);
    col[2] = gal_mult(col_cp[2], 14) ^ gal_mult(col_cp[1], 9) ^ gal_mult(col_cp[0], 13) ^ gal_mult(col_cp[3], 11);
    col[3] = gal_mult(col_cp[3], 14) ^ gal_mult(col_cp[2], 9) ^ gal_mult(col_cp[1], 13) ^ gal_mult(col_cp[0], 11);
}
void col_unshift(unsigned char* byte_data){
	unsigned char col[4];
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++){
			col[j] = byte_data[(j * 4) + i];
		}
		col_unmix(col);
		for (int j = 0; j < 4; j++){
			byte_data[(j * 4) + i] = col[j];
		}
	}
}
void decrypt_data(unsigned char* byte_data, unsigned char* key, size_t key_len){
	for (size_t i = key_len-1; i > 0; i--){
		key_remove(byte_data, key[i]);
		for (int i = 3; i > -1; i--){
			for (int j = i; j > 0; j--){
				row_unshift(&byte_data[i*4]);	
			}
		}
		for (int i = 3; i > -1; i--){
			col_unshift(byte_data);	
		}
	}
  key_remove(byte_data, key[0]);
	for (int i = 3; i > -1; i--){
			for (int j = i; j > 0; j--){
				row_unshift(&byte_data[i*4]);	
			}	
	}
	for (int i = 3; i > -1; i--){
		col_unshift(byte_data);	
	}
}
