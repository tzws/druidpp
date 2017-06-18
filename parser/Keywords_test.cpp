//http://codereview.stackexchange.com/questions/14309/conversion-between-enum-and-string-in-c-class-header
//http://stackoverflow.com/questions/207976/how-to-easily-map-c-enums-to-strings
#include <boost/assign/list_of.hpp>
#include <boost/unordered_map.hpp>
#include <iostream>

#include <boost/algorithm/string.hpp>
#include "Keywords.h"

int main()
{

	Keywords     * keywods = Keywords::getInstance();
	std::cout << " enum SELECT = " << tokenStringList.at(TOKEN_SELECT) << std::endl;
	std::string all = "ALL";
	std::cout << " getKeywods " << keywods->getKeyword(all) << std::endl;
	std::string xxx = "xxx";
	std::cout << " getKeywods " << keywods->getKeyword(xxx) << std::endl;

	TokenMap &tkmap = keywods->getKeywords();

	TokenMap::iterator it = tkmap.begin();

	for( ; it != tkmap.end(); ++it)
	{
		std::cout<<"key:"<<it->first <<"value:"<<it->second<<std::endl;
	}

	return 0;
}


