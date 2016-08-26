#include <stdio.h>
#include <stdlib.h>
#include "application.h"
#include "utils/file_logger.h"
#include "languages/c/c_datapicker.h"
#include "platforms/unix_like/file_unix.h"
#include "managements/map_management/map_datamanager.h"

int main(int argc, const char **argv) {
	if(argc == 1) {
		return -1;
	}	
	FileUtilsUnix unix;

	char log_path[1024] = {0};
	strcpy(log_path, argv[1]);
	int len = strlen(log_path);
	if(log_path[len - 1] != '/' ) {
		log_path[len++] = '/';
	}
	strcpy(log_path + len, "info.dk");
	FileLogger logger(log_path);
	
	Application app(new CDataPicker, new MapDataManager);
	app.Process(argv[1]);
	exit(0);
}
