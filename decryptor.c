#include<stddef.h>
void key_remove(char* byte_data, char key){
	for (int i = 15; i > 0; i--){
		byte_data[i] = byte_data[i] ^ key;
	}
    byte_data[0] = byte_data[0] ^ key;	
}
void row_unshift(char* byte_data, char* key, size_t key_s, int row){
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
void col_unshift(char* byte_data, char* key,size_t key_s, int col){
	int o_col_s = col * 4;
	int n_col_s = 4 * (key[col % key_s] % 4);
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
void decrypt_data(char* byte_data, char* key, size_t key_len){
	for (size_t i = key_len-1; i > 0; i--){
		key_remove(byte_data, key[i]);
		for (int i = 3; i > -1; i--){
			row_unshift(byte_data, key, key_len, i);	
		}
		for (int i = 3; i > -1; i--){
			col_unshift(byte_data, key, key_len, i);	
		}
	}
    	key_remove(byte_data, key[0]);
		for (int i = 3; i > -1; i--){
			row_unshift(byte_data, key, key_len, i);	
		}
		for (int i = 3; i > -1; i--){
			col_unshift(byte_data, key, key_len, i);	
		}
}
