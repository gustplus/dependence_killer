#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "../utils.h"

#define TEST_FILE_NAME "utils_t.txt"
#define BUF_S 20

int main(int argc, const char **argv) {
	FILE *f = fopen(TEST_FILE_NAME, "r");
	char buf[BUF_S] = {0};
	while(0 < ReadLine(f, buf, BUF_S)) {
		printf("%s\n", buf);
	}
	exit(0);
}
