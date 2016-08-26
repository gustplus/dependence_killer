#include "../framework/i_logger.h"

#include <stdio.h>

class FileLogger : public ILogger {
public:
	FileLogger(const char *path);
	~FileLogger();
	virtual void Log(const char *log, size_t len);

private:
	FILE *m_file;
};

