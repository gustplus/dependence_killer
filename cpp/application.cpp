#include "application.h"
#include "processor.h"
#include "utils/file_utils.h"
#include "utils/string_utils.h"
#include "framework/i_datapicker.h"
#include "framework/i_datamanager.h"

#define MAX_PATH_SIZE 1024

Application::Application(IDataPicker *picker, IDataManager *manager) {
	m_picker = picker;
	m_manager = manager;
	m_processor = new Processor();
	m_processor->SetDataPicker(m_picker);
	m_processor->SetDataManager(m_manager);
}

Application::~Application() {
	if(m_picker) {
		delete m_picker;
	}
	if(m_manager) {
		delete m_manager;
	}
	if(m_processor) {
		delete m_processor;
	}
}

void Application::ProcessDir(File *file) {
	m_manager->EnterPath(file->Path());
	char path[1024] = {0};
	strcpy(path, file->Path());
	int root_path_len = strlen(file->Path());
	if(path[root_path_len - 1] != '/') {
		path[root_path_len++] = '/';
		path[root_path_len] = '\0';
	}
	const char *subdir_name = NULL;
	while(NULL != (subdir_name = file->NextEntityName())) {
		if(0 != strcmp(subdir_name, ".") && 0 != strcmp(subdir_name, "..")) {
			path[root_path_len] = '\0';
			strcpy(path + root_path_len, subdir_name);
			ProcessPath(path);
		}
	}
	m_manager->ExitPath();
}

void Application::ProcessPath(const char *path) {
	File *file = FileUtils::GetInstance()->OpenFile(path);
	if(!file->Exist()) {
		fprintf(stderr, "path %s not exist\n", path);
		return;
	}
	if(file->IsDirectory()) {
		ProcessDir(file);
	}else{
		m_processor->Process(path);
	}
	delete file;
}

bool Application::Process(const char * path) {
	char ab_path[MAX_PATH_SIZE] = {0};
	FileUtils::GetInstance()->GetAbsolutePath(path, ab_path, MAX_PATH_SIZE);
	ProcessPath(ab_path);
	m_manager->Dump();
	m_manager->DumpDependences();
	return true;
}
