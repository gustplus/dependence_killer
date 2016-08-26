#include "utils_test.h"
#include <stdio.h>
#include <assert.h>
#include "../../utils/string_utils.h"

bool UtilsTest::Setup() {
	return true;
}

bool UtilsTest::Run() {
	const char *test_str0 = "  	hello";
	char test_str1[] = "  	0123	4 56    7	 ";
	char test_str2[] = "  	0123	4 56    7";
	
	const char *ret0 = StringUtils::SkipSpaces(test_str0);
	StringUtils::Trim(test_str1);
	StringUtils::Trim(test_str2);

	assert(0 == strcmp(ret0, "hello"));
	assert(0 == strcmp(test_str1, "01234567"));	
	assert(0 == strcmp(test_str2, "01234567"));	
	return true;
}

bool UtilsTest::TearDown() {
	return true;
}
