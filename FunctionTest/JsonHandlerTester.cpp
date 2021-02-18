#include "FunctionTest.h"

#ifdef FUNC_TEST_2
#define FUNCTION_UNIT_TEST
#endif

#include <JXml/JXML.h>
#include <iostream>
#include <vector>
#include <string>

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


void test_func3(sge::JsonHandler& json)
{
	std::string str = "{\"project\":\"rapidjson\",\"stars\":10}";
	json.set_json("json", str);

	// print out new string
	std::cout << json.to_str(TRUE) << std::endl;

	std::string substr = json.get_json("json");
	std::cout << substr << std::endl;
}


void test_func4(sge::JsonHandler& json)
{
	using namespace sge;

	std::vector<std::string> keys = json.keys();
	for (auto k : keys) {
		std::cout << k << " is ";

		switch (json.item_type(k)) {
		case JsonHandler::ValueType::NoneEntity:
			std::cout << "NoneEntity" << std::endl;
			break;

		case JsonHandler::ValueType::VaccumValue:
			std::cout << "VaccumValue" << std::endl;
			break;

		case JsonHandler::ValueType::BooleanValue:
			std::cout << "BooleanValue" << std::endl;
			break;
				
		case JsonHandler::ValueType::IntegerValue:
			std::cout << "IntegerValue" << std::endl;
			break;

		case JsonHandler::ValueType::DoubleValue:
			std::cout << "DoubleValue" << std::endl;
			break;
				
		case JsonHandler::ValueType::StringValue:
			std::cout << "StringValue" << std::endl;
			break;

		case JsonHandler::ValueType::EmptyList:
			std::cout << "EmptyList" << std::endl;
			break;

		case JsonHandler::ValueType::VaccumList:
			std::cout << "VaccumList" << std::endl;
			break;

		case JsonHandler::ValueType::BooleanList:
			std::cout << "BooleanList" << std::endl;
			break;

		case JsonHandler::ValueType::IntegerList:
			std::cout << "IntegerList" << std::endl;
			break;

		case JsonHandler::ValueType::DoubleList:
			std::cout << "DoubleList" << std::endl;
			break;

		case JsonHandler::ValueType::StringList:
			std::cout << "StringList" << std::endl;
			break;

		case JsonHandler::ValueType::JsonObject:
			std::cout << "JsonObject" << std::endl;
			break;

		default:
			break;
		}
	}
}


int main() {

	std::string file = "D:\\Repositories\\Repo\\Triangle\\FunctionTest\\test.json";
	sge::JsonHandler json(file);

	// add values to json object
	test_func1(json);

	std::cout << "--------------------------------" << std::endl;

	// modify some values
	test_func2(json);

	std::cout << "--------------------------------" << std::endl;

	// add sub json
	test_func3(json);

	std::cout << "--------------------------------" << std::endl;

	// type check
	test_func4(json);

	return 0;
}

#endif