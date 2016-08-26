#include "datapicker_test.h"
#include <assert.h>
#include "../../languages/c/c_datapicker.h"

bool PickerTest::Setup() {
	return true;
}

bool PickerTest::Run() {
	CDataPicker picker;
	const char *test_str0 = "//#include \"str0.h\"";
	const char *test_str1 = "/*#include \"str1.h\"*/";
	const char *test_str2 = "/*#include \"str2.h\"";
	const char *test_str3 = "#include \"str3.h\"*/";
	const char *test_str4 = "int main() {";
	const char *test_str5 = "#include \"str5.h\"";

	char buf[1024] = {0};
	assert(!picker.PickImport(test_str0, buf, 1024));
	assert(!picker.PickImport(test_str1, buf, 1024));	
	assert(!picker.PickImport(test_str2, buf, 1024));	
	assert(!picker.PickImport(test_str3, buf, 1024));	
	assert(!picker.PickImport(test_str4, buf, 1024));	
	assert( picker.PickImport(test_str5, buf, 1024));	
	return true;
}

bool PickerTest::TearDown() {
	return true;
}
