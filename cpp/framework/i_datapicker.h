#ifndef DEPENDENCE_KILLER_FRAMEWORK_IDATAPICKER_H_
#define DEPENDENCE_KILLER_FRAMEWORK_IDATAPICKER_H_
#include <sys/types.h>

class IDataPicker {
public:
	virtual ~IDataPicker() {}
	virtual bool IsPathValid(const char *path) = 0;
	virtual bool PickImport(const char *line, char *ret, size_t ret_len) = 0;
	virtual bool PickInherit(const char *line, char *ret, size_t ret_len) = 0;
	virtual bool PickAbsoluteClass(const char *line, char *ret, size_t ret_len) = 0;
};

#endif
