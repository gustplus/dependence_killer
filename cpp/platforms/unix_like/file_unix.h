#ifndef DEPENDENCE_KILLER_PLATFORMS_UNIXLIKE_FILE_UNIX_H_
#define DEPENDENCE_KILLER_PLATFORMS_UNIXLIKE_FILE_UNIX_H_

#include <string>
#include <dirent.h>
#include "../../utils/file_utils.h"

class FileUnix : public File {
public:
	FileUnix(const char *path) : m_path(path), m_dir(NULL) {}
	~FileUnix();
	virtual bool Exist();
	virtual bool IsDirectory();
	virtual bool IsFile();
	virtual const char *Path();
	
	virtual const char *NextEntityName();
	
	std::string m_path;
	DIR *m_dir;
};

class FileUtilsUnix : public FileUtils {
public:
	File *OpenFile(const char *path);
	virtual bool GetParentPath(const char *file_name, char *buf, size_t buf_len);
	virtual bool GetAbsolutePath(const char *file_name, char *buf, size_t buf_len);
private:
};

#endif
