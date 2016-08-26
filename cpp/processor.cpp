#include "processor.h"
#include <stdio.h>
#include "utils/file_utils.h"
#include "framework/i_logger.h"
#include "framework/i_datapicker.h"
#include "framework/i_datamanager.h"

#define BUF_SIZE 1024

bool Processor::Process(const char *file_path) {
	if(m_picker && m_manager) {
		if(!m_picker->IsPathValid(file_path)) return true;
		FILE *f = fopen(file_path, "r");
		if(f) {
			char buf[BUF_SIZE] = {0};
			char ret[BUF_SIZE] = {0};
			Data data;
			const char *file_name = strrchr(file_path, '/');
			file_name = (file_name != NULL ? file_name + 1 : file_path);
			char *end = strrchr(file_name, '.');
			if(end) {
				data.data0 = std::string(file_name, end - file_name);
			}else{
				data.data0 = file_name;
			}
			while(-1 < FileUtils::ReadLine(f, buf, BUF_SIZE)) {
				if(m_picker->PickImport(buf, ret, BUF_SIZE)) {
					data.data1 = ret;
					m_manager->ReceiveImport(data);
				}else if(m_picker->PickInherit(buf, ret, BUF_SIZE)) {
					m_manager->ReceiveInherit(data);
				}else if(m_picker->PickAbsoluteClass(buf, ret, BUF_SIZE)) {
					m_manager->ReceiveAbsoluteClass(data);
				}
			}
			return true;
		}else{
			fprintf(stderr, "file open failed!\n");
		}
	}else{
		fprintf(stderr, "datapicker or datamanager hasn't been set!\n");
	}
	return false;
}
