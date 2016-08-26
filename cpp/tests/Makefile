UNITTEST_PATH=../unit_test/
UTILS_PATH=../utils/
C_LANG_PATH=../languages/c/
PICKERTEST_PATH=picker_test/
UTILSTEST_PATH=utils_test/

test:datapicker.o unit_test.o picker_test.o utilstest.o stringutils.o test.cpp
	gcc -lstdc++ datapicker.o unit_test.o picker_test.o utilstest.o stringutils.o test.cpp -o test

unit_test.o:$(UNITTEST_PATH)i_testcase.h $(UNITTEST_PATH)unit_test.h $(UNITTEST_PATH)unit_test.cpp
	gcc -c $(UNITTEST_PATH)unit_test.cpp -o unit_test.o

picker_test.o:$(PICKERTEST_PATH)datapicker_test.h $(PICKERTEST_PATH)datapicker_test.cpp $(UNITTEST_PATH)i_testcase.h
	gcc -c $(PICKERTEST_PATH)datapicker_test.cpp -o picker_test.o

datapicker.o:$(C_LANG_PATH)c_datapicker.h $(C_LANG_PATH)c_datapicker.cpp
	gcc -c $(C_LANG_PATH)c_datapicker.cpp -o datapicker.o


utilstest.o:$(UTILSTEST_PATH)utils_test.h $(UTILSTEST_PATH)utils_test.cpp $(UNITTEST_PATH)i_testcase.h
	gcc -c $(UTILSTEST_PATH)utils_test.cpp -o utilstest.o


stringutils.o:$(UTILS_PATH)string_utils.h $(UTILS_PATH)string_utils.cpp
	gcc -c $(UTILS_PATH)string_utils.cpp -o stringutils.o
