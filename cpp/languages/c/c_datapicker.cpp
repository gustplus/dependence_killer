#include "c_datapicker.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "../../utils/string_utils.h"

#define INCLUDE_PREFIX "#include \""
#define INCLUDE_PREFIX_LEN 10

bool CDataPicker::IsPathValid(const char *path) {
	return (StringUtils::EndWith(path, ".c") || StringUtils::EndWith(path, ".cpp") || StringUtils::EndWith(path, ".h"));
}

bool CDataPicker::PickImport(const char *line, char *ret, size_t ret_len) {
	if(!line) return false;
	line = StringUtils::SkipSpaces(line);
	if(!line) return false;
	if(m_incomment) {
		line = strstr(line, "*/");
		if(line) {
			m_incomment = false;
			line += 2;
		}else{
			return false;
		}
	}
	if(line[0] == '/' && line[1] == '/') {
		return false;
	}
	if(line[0] == '/' && line[1] == '*') {
		m_incomment = true;
		line += 2;
		return PickImport(line, ret, ret_len);
	}
	
	char *ptr = strstr(line, INCLUDE_PREFIX);
	if(ptr) {
		ptr += INCLUDE_PREFIX_LEN;
		char *end = strchr(ptr, '"');
		if(end) {
			int file_name_len = end - ptr;
			assert(file_name_len < ret_len);
			strncpy(ret, ptr, file_name_len);
			ret[file_name_len] = '\0';
			return true;
		}
	}
	return false;
}

#define CLASS_PREFIX "class "
#define PUBLIC_PREFIX "public "
#define PROTECTED_PREFIX "protected "
#define PRIVATE_PREFIX "private "
bool CDataPicker::PickInherit(const char *line, char *ret, size_t ret_len) {
	if(!line) return false;
	line = StringUtils::SkipSpaces(line);
	if(!line) return false;
	
	if(m_inclass && strstr(line, "};") == line) {
		m_inclass = false;
		m_isabsolute = false;
	}
	if(strstr(line, CLASS_PREFIX) == line) {
		m_inclass = true;
		strcpy(ret, line);
		char *ptr = strchr(ret, ':');
		if(ptr) {	//has parent class
			return true;
		}
	}
	return false;
}

#define VIRTUAL_PREFIX "virtual "
#define VIRTUAL_POSTFIX "0;"
bool CDataPicker::PickAbsoluteClass(const char *line, char *ret, size_t ret_len) {
	if(!line) return false;
	line = StringUtils::SkipSpaces(line);
	if(!line) return false;
	
	if(m_inclass && !m_isabsolute) {
		char *ptr = strstr(line, VIRTUAL_PREFIX);
		if(ptr && StringUtils::EndWith(line, VIRTUAL_POSTFIX, true)) {
			m_isabsolute = true;
			return true;
		}
	}
	return false;
}
