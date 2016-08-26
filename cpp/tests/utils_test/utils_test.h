#ifndef TESTS_UTILSTEST_UTILSTEST_H_
#define TESTS_UTILSTEST_UTILSTEST_H_

#include "../../unit_test/i_testcase.h"

class UtilsTest : public ITestCase {
public:
	UtilsTest() : ITestCase("utils test") {}
	virtual bool Setup();
	virtual bool Run();
	virtual bool TearDown();
	
};


#endif
