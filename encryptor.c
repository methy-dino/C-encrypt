#include <stdlib.h>
void row_shift(char* byte_data, char* key, size_t key_s, int row){
	int o_row_s = row;
	int n_row_s = (key[(key_s - row) % key_s] % 4);
	if (n_row_s == o_row_s){
		n_row_s = (n_row_s + 1) % 4;
	}
	char temp[4];
	temp[0] = byte_data[n_row_s + (0*4)];
	temp[1] = byte_data[n_row_s + (1*4)];
	temp[2] = byte_data[n_row_s + (2*4)];
	temp[3] = byte_data[n_row_s + (3*4)];
	byte_data[n_row_s + (0*4)] = byte_data[o_row_s + (0*4)];
	byte_data[n_row_s + (1*4)] = byte_data[o_row_s + (1*4)];
	byte_data[n_row_s + (2*4)] = byte_data[o_row_s + (2*4)];
	byte_data[n_row_s + (3*4)] = byte_data[o_row_s + (3*4)];
	byte_data[o_row_s + (0*4)] = temp[0];
	byte_data[o_row_s + (1*4)] = temp[1];
	byte_data[o_row_s + (2*4)] = temp[2];
	byte_data[o_row_s + (3*4)] = temp[3];
}
void col_shift(char* byte_data, char* key, int col){
	int o_col_s = col * 4;
	int n_col_s = 4 * (key[col] % 4);
	if (n_col_s == o_col_s){
		n_col_s = (n_col_s + 4) % 16;
	}
	char temp[4];
	temp[0] = byte_data[n_col_s + 0];
	temp[1] = byte_data[n_col_s + 1];
	temp[2] = byte_data[n_col_s + 2];
	temp[3] = byte_data[n_col_s + 3];
	byte_data[n_col_s+0] = byte_data[o_col_s + 0];
	byte_data[n_col_s+1] = byte_data[o_col_s + 1];
	byte_data[n_col_s+2] = byte_data[o_col_s + 2];
	byte_data[n_col_s+3] = byte_data[o_col_s + 3];
	byte_data[o_col_s+0] = temp[0];
	byte_data[o_col_s+1] = temp[1];
	byte_data[o_col_s+2] = temp[2];
	byte_data[o_col_s+3] = temp[3];
}
void key_apply(char* byte_data, char key){
	for (int i = 0; i < 16; i++){
		byte_data[i] = (byte_data[i] + key * 11) % 256;
	}
}
 //in place encryption, assumes 16 bytes of data
void encrypt_data(char* byte_data, char* key, size_t k_len){
	for (size_t i = 0; i < k_len; i++){
		for (int i = 0; i < 4; i++){
			col_shift(byte_data, key, i);
		}
		for (int i = 0; i < 4; i++){
			row_shift(byte_data, key, k_len, i);
		}
		key_apply(byte_data, key[i]);
	}
}
