void decrypt_data(char* byte_data, char* key, size_t key_len){
	for (size_t i = key_len; i > -1; i--){
		key_remove(byte_data, key[i]);
		for (int i = 3; i > -1; i--){
			row_unshift(byte_data, key, k_len, i);	
		}
		for (int i = 3; i > -1; i--){
			col_unshift(byte_data, key, k_len, i);	
		}
	}
}
