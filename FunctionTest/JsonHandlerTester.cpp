#include "FunctionTest.h"

#ifdef FUNC_TEST_2
#define FUNCTION_UNIT_TEST
#endif

#include <JXml/JXML.h>
#include <iostream>

#ifdef FUNCTION_UNIT_TEST

void func1() {
	//std::string file = "D:\\Repositories\\Repo\\Triangle\\FunctionTest\\test.json";
	//sge::JsonHandler json(file);

	//std::cout << json.has_item("hello") << std::endl
	//	<< json.has_item("test_float_array") << std::endl
	//	<< json.has_item("vec_key") << std::endl;

	//json.append_item("key_test01", false);
	//json.append_item("key_test02", -1000);
	//json.append_item("key_test03", 13.975);

	//bool arr1[] = {true, false, true, true};
	//json.append_array("key_test04", arr1, 4);
	//
	//int arr2[] = { 100, 101, -101, 102 };
	//json.append_array("key_test05", arr2, 4);
	//
	//double arr3[] = { 13.45, 19.01, 0.789, 0.123 };
	//json.append_array("key_test06", arr3, 4);

	//const char *arr4[] = { "english", "japanese", "chinese" };
	//json.append_array("key_test07", arr4, 3);


	//std::string jstr = " { \"hello\" : \"world\", \"t\" : true , \"f\" : false, \"n\": null, \"i\":123, \"pi\": 3.1416, \"a\":[1, 2, 3, 4] } ";;
	//json.append_json("key_test08", jstr);
	//json.clear();

	//std::cout << json.to_cstr() << std::endl;

}

void func2() 
{
	std::string file = "D:\\Repositories\\Repo\\Triangle\\FunctionTest\\test.json";
	sge::JsonHandler json(file);
	json.set_null("nullkey").set_string("strkey", "this is string key");
	std::cout << json.to_str() << std::endl;
}


int main() {

		func2();
	return 0;
}

#endif