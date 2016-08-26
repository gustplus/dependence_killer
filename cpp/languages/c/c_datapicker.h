#ifndef DEPENDENCE_KILLER_C_DATA_PICKER_H_
#define DEPENDENCE_KILLER_C_DATA_PICKER_H_

/*
	use for analysing c and cpp files
*/


#include "../../framework/i_datapicker.h"
#include <sys/types.h>

class CDataPicker : public IDataPicker {
public:
	CDataPicker() :IDataPicker(), m_incomment(false), m_inclass(false), m_isabsolute(false) {}
	virtual bool IsPathValid(const char *path);
	virtual bool PickImport(const char *line, char *ret, size_t ret_len);
	virtual bool PickInherit(const char *line, char *ret, size_t ret_len);
	virtual bool PickAbsoluteClass(const char *line, char *ret, size_t ret_len);
private:
	bool m_incomment;
	bool m_inclass;
	bool m_isabsolute;
};

#endif
