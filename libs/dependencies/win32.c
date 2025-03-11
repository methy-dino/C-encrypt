#include<io.h>

long f_len(char* f_path){
	FILE* file = fopen(f_path, "rb");
	if (fp == NULL){
		return 0;
	}
	int f_des = _fileno(fp);
	long f_len= = _filelength(fd);
	fclose(fp);
	return f_len;
}
