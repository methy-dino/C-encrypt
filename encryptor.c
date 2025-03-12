#include <stdlib.h>
#include "libs/gal_mult.h"
#include "libs/swap_tables.h"
void row_shift(unsigned char* row){
	char temp = row[0];
	row[0] = row[1];
	row[1] = row[2];
	row[2] = row[3];
	row[3] = temp;
}
void col_mix(unsigned char* col){
  unsigned char col_cp[4];
  for (int i = 0; i < 4; i++){
		col_cp[i] = col[i];
  }
    col[0] = gal_mult(col_cp[0], 2) ^ gal_mult(col_cp[3], 1) ^ gal_mult(col_cp[2], 1) ^ gal_mult(col_cp[1], 3);
    col[1] = gal_mult(col_cp[1], 2) ^ gal_mult(col_cp[0], 1) ^ gal_mult(col_cp[3], 1) ^ gal_mult(col_cp[2], 3);
    col[2] = gal_mult(col_cp[2], 2) ^ gal_mult(col_cp[1], 1) ^ gal_mult(col_cp[0], 1) ^ gal_mult(col_cp[3], 3);
    col[3] = gal_mult(col_cp[3], 2) ^ gal_mult(col_cp[2], 1) ^ gal_mult(col_cp[1], 1) ^ gal_mult(col_cp[0], 3);
}
void col_shift(unsigned char* byte_data, unsigned char* key, size_t key_s, int col){
	unsigned char col_cp[4];
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++){
			col_cp[j] = byte_data[(j*4) + i];
		}
		col_mix(col_cp);
		for (int j = 0; j < 4; j++){
			byte_data[(j*4) + i] = col_cp[j];
		}
	}
}
void key_apply(unsigned char* byte_data, unsigned char key){
	for (int i = 0; i < 16; i++){
		byte_data[i] = byte_data[i] ^ key;
	}
}
 //in place encryption, assumes 16 bytes of data
void encrypt_data(unsigned char* byte_data, unsigned char* key, size_t k_len){
	key_apply(byte_data, key[0]);
    for (size_t i = 1; i < k_len-1; i++){
		for (int j = 0; j < 16; j++){
			byte_data[j] = do_swap[byte_data[j]];
		}
		for (int j = 0; j < 4; j++){
			for (int k = 0; k < j; k++){
				row_shift(&byte_data[j*4]);
			}
		}
		for (int j = 0; j < 4; j++){
			col_shift(byte_data, key, k_len, i);
		}
		key_apply(byte_data, key[i]);
	}
	for (int j = 0; j < 16; j++){
			byte_data[j] = do_swap[byte_data[j]];
	}
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < i; j++){
			row_shift(&byte_data[i*4]);
		}
	}
	key_apply(byte_data, key[k_len-1]);
}
