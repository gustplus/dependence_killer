#ifndef TESTS_PICKERTEST_DATAPICKERTEST_H_
#define TESTS_PICKERTEST_DATAPICKERTEST_H_

#include "../../unit_test/i_testcase.h"

class PickerTest : public ITestCase {
public:
	PickerTest() : ITestCase("datapicker test") {}
	virtual bool Setup();
	virtual bool Run();
	virtual bool TearDown();
	
};


#endif
