#ifndef DEPENDENCE_KILLER_PROCESSOR_H_
#define DEPENDENCE_KILLER_PROCESSOR_H_

#include <stdio.h>

class IDataPicker;
class IDataManager;

class Processor {
public:
	Processor(): m_picker(NULL), m_manager(NULL) {}
	void SetDataPicker(IDataPicker *picker) {m_picker = picker;}
	void SetDataManager(IDataManager *manager) {m_manager = manager;}
	bool Process(const char *file_name);
private:
	IDataPicker *m_picker;
	IDataManager *m_manager;
};

#endif
