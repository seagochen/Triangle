#include <iostream>
#include <Core/Core.hpp>
#include <CPPCore/CPPCore.hpp>
#include <string>

using namespace std;

int main(int argc, char* argv[])
{
	list* list = search_files(".", "\\.dll$");
	StringContainer container(list);

	for (Iterator<string>* itr = container.iterator(); itr->has_next(); itr->next()) {
		string* pstr = itr->ptr();
		cout << *pstr << endl;
	}
	
	return 0;
}