#ifndef DEPENDENCE_KILLER_APPLICATION_H_
#define DEPENDENCE_KILLER_APPLICATION_H_

class IDataPicker;
class IDataManager;
class Processor;
class File;

class Application {
public:
	Application(IDataPicker *picker, IDataManager *manager);
	~Application();
	bool Process(const char *path);
private:
	void ProcessDir(File *file);
	void ProcessPath(const char *path);

	IDataPicker *m_picker;
	IDataManager *m_manager;
	Processor *m_processor;
};

#endif
