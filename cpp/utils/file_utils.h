#ifndef DEPENDENCE_KILLER_FILEUTILS_H_
#define DEPENDENCE_KILLER_FILEUTILS_H_

#include <stdio.h>

class File {
public:
	virtual ~File() {}
	virtual bool Exist() = 0;
	virtual bool IsDirectory() = 0;
	virtual bool IsFile() = 0;
	virtual const char *Path() = 0;
	
	virtual const char *NextEntityName() = 0;
};

class FileUtils {
public:
	static FileUtils *GetInstance();
	virtual File *OpenFile(const char *path) {return NULL;}

	virtual bool GetParentPath(const char *file_name, char *buf, size_t buf_len) = 0;
	virtual bool GetAbsolutePath(const char *file_name, char *buf, size_t buf_len) = 0;
	
	static int ReadLine(FILE *f, char *buf, size_t buf_size);
protected:
	FileUtils() {s_instance = this;}
	virtual ~FileUtils() {}

private:
	FileUtils(const FileUtils &other);
	FileUtils &operator=(const FileUtils &other);

	static FileUtils *s_instance;
};

#endif
