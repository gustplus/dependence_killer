#include "unit_test.h"
#include "i_testcase.h"

void UnitTest::AddTest(ITestCase *test) {
	this->m_tests.push_back(test);
}

void UnitTest::Run() {
	std::vector<ITestCase *>::iterator it = this->m_tests.begin();
	std::vector<ITestCase *>::iterator end = this->m_tests.end();
	for(; it != end; ++it) {
		printf("testing %s ...\n", (*it)->Name().c_str());
		(*it)->Setup();
		(*it)->Run();
		(*it)->TearDown();
		printf("test %s finished\n", (*it)->Name().c_str());
	}
}

