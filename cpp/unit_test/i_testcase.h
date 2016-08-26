#ifndef DEPENDENCE_KILLER_UNITTEST_ITESTCASE_H_
#define DEPENDENCE_KILLER_UNITTEST_ITESTCASE_H_

#include <string>

class ITestCase {
public:
	ITestCase(const char *name) : m_name(name) {}
	const std::string &Name() { return m_name; }
	virtual ~ITestCase() {}
	virtual bool Setup() = 0;
	virtual bool Run() = 0;
	virtual bool TearDown() = 0;

private:
	std::string m_name;
};

#endif
