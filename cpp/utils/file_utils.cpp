#include "file_utils.h"
#include <string.h>

FileUtils *FileUtils::s_instance = NULL;

FileUtils *FileUtils::GetInstance() {
	return FileUtils::s_instance;
}

int FileUtils::ReadLine(FILE *f, char *buf, size_t buf_size) {
	if(f) {
		char *ret = fgets(buf, buf_size, f);
		if(ret) {
			int len = strlen(ret);
			if(len == buf_size - 1 && buf[len - 1] != '\n' && !feof(f)) {	//means the buf is not large enough to fill the line
				fprintf(stderr, "buf is small\n");
				return -1;
			}
			if(buf[len - 1] == '\n') {
				buf[--len] = '\0';
			}
			return len;
		}
		if(feof(f)) {
			return -1;
		}
		return 0;
	}
	return -1;
}
