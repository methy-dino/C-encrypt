#include <stdlib.h>
void row_shift(char* byte_data, char* key, size_t key_s, int row);
void col_shift(char* byte_data, char* key, int col);
void key_apply(char* byte_data, char key);
 //in place encryption, assumes 16 bytes of data
void encrypt_data(char* byte_data, char* key, size_t k_len);
