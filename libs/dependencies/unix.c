#include <sys/stat.h>
#include <stdlib.h>
long f_len(char* f_path){
	struct stat st = {0};
	stat(f_path, &st);
	return (long)st.st_size;
}
