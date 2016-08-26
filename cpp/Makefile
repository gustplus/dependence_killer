MANAGEMENT_PATH:=managements/map_management/
UNIX_FILE_PATH:=platforms/unix_like/
DATA_STRUCTS_PATH:=data_structs/
C_LANG_PATH:=languages/c/
FW_PATH:=framework/
PLATFORM_PATH:=platforms/
UTILS_PATH:=utils/

dependence_killer:.file_utils.o .stringutils.o .processor.o .datapicker.o .datamanager.o .app.o .file_unix.o .map_items.o $(FW_PATH)comparable.h .d_logger.o .i_logger.o .f_logger.o info.h main.cpp 
	gcc -lstdc++ .datapicker.o .d_logger.o .i_logger.o .f_logger.o .datamanager.o .file_utils.o .stringutils.o .processor.o .app.o .file_unix.o .map_items.o \
main.cpp -o dependence_killer

.app.o:application.h application.cpp
	gcc -c application.cpp -o .app.o

.datapicker.o:$(C_LANG_PATH)c_datapicker.h $(C_LANG_PATH)c_datapicker.cpp
	gcc -c $(C_LANG_PATH)c_datapicker.cpp -o .datapicker.o

.datamanager.o:$(MANAGEMENT_PATH)map_items.h $(MANAGEMENT_PATH)map_datamanager.h $(MANAGEMENT_PATH)map_datamanager.cpp
	gcc -c $(MANAGEMENT_PATH)map_datamanager.cpp -o .datamanager.o

.processor.o:processor.h processor.cpp
	gcc -c processor.cpp -o .processor.o

.file_utils.o:$(UTILS_PATH)file_utils.h $(UTILS_PATH)file_utils.cpp
	gcc -c $(UTILS_PATH)file_utils.cpp -o .file_utils.o

.map_items.o:info.h $(MANAGEMENT_PATH)map_items.h $(MANAGEMENT_PATH)map_items.cpp
	gcc -c $(MANAGEMENT_PATH)map_items.cpp -o .map_items.o

.graph.o:$(DATA_STRUCTS_PATH)graph.h $(DATA_STRUCTS_PATH)graph.cpp
	gcc -c $(DATA_STRUCTS_PATH)graph.cpp -o .graph.o

.link_node.o:$(DATA_STRUCTS_PATH)graph.h $(DATA_STRUCTS_PATH)link_node.h $(DATA_STRUCTS_PATH)link_node.cpp
	gcc -c $(DATA_STRUCTS_PATH)link_node.cpp -o .link_node.o

.file_unix.o:$(UTILS_PATH)string_utils.h $(UNIX_FILE_PATH)file_unix.h $(UNIX_FILE_PATH)file_unix.cpp .file_utils.o
	gcc -c $(UNIX_FILE_PATH)file_unix.cpp -o .file_unix.o

.stringutils.o:$(UTILS_PATH)string_utils.h $(UTILS_PATH)string_utils.cpp
	gcc -c $(UTILS_PATH)string_utils.cpp -o .stringutils.o

.i_logger.o:$(FW_PATH)i_logger.h $(FW_PATH)i_logger.cpp
	gcc -c $(FW_PATH)i_logger.cpp -o .i_logger.o

.d_logger.o:.i_logger.o $(UTILS_PATH)default_logger.h $(UTILS_PATH)default_logger.cpp
	gcc -c $(UTILS_PATH)default_logger.cpp -o .d_logger.o

.f_logger.o:.i_logger.o $(UTILS_PATH)file_logger.h $(UTILS_PATH)file_logger.cpp
	gcc -c $(UTILS_PATH)file_logger.cpp -o .f_logger.o
