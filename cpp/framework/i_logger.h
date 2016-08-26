#ifndef DEPENDENCE_KILLER_FRAMEWORK_ILOGGER_H_
#define DEPENDENCE_KILLER_FRAMEWORK_ILOGGER_H_

#include <sys/types.h>

class ILogger {
public:	
	static ILogger *GetInstance() { return s_instance; }
	ILogger() { s_instance = this; }
	virtual ~ILogger() {}
	void Log(const char *format, ...);
	virtual void Log(const char *log, size_t len) = 0;

private:
	static ILogger *s_instance;
};

#endif
