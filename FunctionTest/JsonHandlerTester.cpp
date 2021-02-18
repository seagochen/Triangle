#include "FunctionTest.h"

#ifdef FUNC_TEST_2
#define FUNCTION_UNIT_TEST
#endif

#include <JXml/JXML.h>
#include <iostream>

#ifdef FUNCTION_UNIT_TEST

void test_func1(sge::JsonHandler &json)
{
	// add some values
	json.set_null("nullkey")
		.set_bool("boolkey", false)
		.set_int("intkey", 1000)
		.set_double("doublekey", 13.2845)
		.set_string("strkey", "this is string key");

	// add some array values
	bool list1[] = { true, false, true, true };
	json.set_bool_list("bool_list", list1, 4);

	int list2[] = { 1, 2, 3, 4, 5 };
	json.set_int_list("int_list", list2, 5);

	double list3[] = { 13.45, 19.01, 0.789, 0.123 };
	json.set_double_list("double_list", list3, 4);

	const char* arr4[] = { "english", "japanese", "chinese" };
	json.set_string_list("str_list", arr4, 3);

	// print out new string
	std::cout << json.to_str(TRUE) << std::endl;
}


void test_func2(sge::JsonHandler& json)
{
	// modify some values
	json.set_bool("boolkey", true)
		.set_int("intkey", -300)
		.set_double("doublekey", 0.72319)
		.set_string("strkey", "value modified");

	// modify some array values
	bool list1[] = { false, false, false, false };
	json.set_bool_list("bool_list", list1, 4);

	int list2[] = { 3, 1, 2, 4, 5 };
	json.set_int_list("int_list", list2, 5);

	double list3[] = { 0.45, 307.01, 9.789, 3.123 };
	json.set_double_list("double_list", list3, 4);

	const char* arr4[] = { "japanese", "japanese", "japanese" };
	json.set_string_list("str_list", arr4, 3);

	// print out new string
	std::cout << json.to_str(TRUE) << std::endl;
}


int main() {

	std::string file = "D:\\Repositories\\Repo\\Triangle\\FunctionTest\\test.json";
	sge::JsonHandler json(file);

	// add values to json object
	test_func1(json);

	std::cout << "--------------------------------" << std::endl;

	// modify some values
	test_func2(json);

	return 0;
}

#endif