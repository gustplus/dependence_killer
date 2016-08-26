#include "../framework/i_logger.h"

class DefaultLogger : public ILogger {
public:
	virtual void Log(const char *log, size_t len);
};

