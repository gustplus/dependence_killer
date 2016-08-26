#ifndef DEPENDENCE_KILLER_FRAMEWORK_IDATAMANAGER_H_
#define DEPENDENCE_KILLER_FRAMEWORK_IDATAMANAGER_H_

#include <string>

class Data {
public:
	std::string data0;
	std::string data1;
};

class IDataManager {
public:
	virtual ~IDataManager() {}
	virtual void EnterPath(const char *path) = 0;
	virtual void ExitPath() = 0;
	virtual void ReceiveImport(Data &data) = 0;
	virtual void ReceiveInherit(Data &data) = 0;
	virtual void ReceiveAbsoluteClass(Data &data) = 0;
	virtual void Dump() = 0;
	virtual void DumpDependences() = 0;
};

#endif
