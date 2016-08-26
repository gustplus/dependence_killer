#ifndef DEPENDENCE_KILLER_UNITTEST_UNITTEST_H_
#define DEPENDENCE_KILLER_UNITTEST_UNITTEST_H_

#include <string>
#include <vector>

class ITestCase;

class UnitTest {
public:
	UnitTest(const char *name) : m_name(name) {}
	void AddTest(ITestCase *test);
	void Run();

private:
	std::string m_name;
	std::vector<ITestCase *> m_tests;

};

#endif
