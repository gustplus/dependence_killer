#include <stdlib.h>
#include "../unit_test/unit_test.h"
#include "picker_test/datapicker_test.h"
#include "utils_test/utils_test.h"

int main(int argc, const char **argv) {
	UnitTest test("dependence killer");
	UtilsTest utils_test;
	test.AddTest(&utils_test);
	PickerTest picker_test;
	test.AddTest(&picker_test);
	test.Run();
	exit(0);
}
