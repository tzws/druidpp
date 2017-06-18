//http://codereview.stackexchange.com/questions/14309/conversion-between-enum-and-string-in-c-class-header
//http://stackoverflow.com/questions/207976/how-to-easily-map-c-enums-to-strings
#include <boost/assign/list_of.hpp>
#include <boost/unordered_map.hpp>
#include <iostream>

#include <boost/algorithm/string.hpp>
#include "Keywords.h"



int my_strcmp(const char* s1, const char* s2)
{
	while(*s1 && (*s1==*s2))
		s1++,s2++;
	return *(const unsigned char*)s1-*(const unsigned char*)s2;
}


int bsd_strcmp(register const char *s1, register const char *s2)
{
	while (*s1 == *s2++)
		if (*s1++ == 0)
			return (0);
	return (*(const unsigned char *)s1 - *(const unsigned char *)(s2 - 1));
}


int bsd_strcmp_u(register const char *s1, register const char *s2)
{
	while (toupper(*s1) == *s2++)
		if (*s1++ == 0)
			return (0);
	return (*(const unsigned char *)(toupper(*s1)) - *(const unsigned char *)(s2 - 1));
}

int apple_strcmp(const char *s1, const char *s2)
{
	for ( ; *s1 == *s2; s1++, s2++)
		if (*s1 == '\0')
			return 0;
	return ((*(unsigned char *)s1 < *(unsigned char *)s2) ? -1 : +1);
}


void convertToUpperCase(char *sPtr)
{
	while(*sPtr != '\0')
	{
		//if (islower(*sPtr))
			*sPtr = toupper((unsigned char)*sPtr);
			//*sPtr = toupper(*sPtr);
		sPtr++;
	}
}





Keywords* Keywords::getInstance()
{
	static Keywords DEFAULT_KEYWORDS; // Guaranteed to be destroyed.
	// Instantiated on first use.
	return &DEFAULT_KEYWORDS;
}

//http://stackoverflow.com/questions/535317/checking-value-exist-in-a-stdmap-c
//You can use boost::multi_index to create a bidirectional map - you can use either value of the pair as a key to do a quick lookup.
bool Keywords::containsValue(Token &token) 
{
	bool found = false;

	////std::map<std::string, Token>::iterator it = keywords.begin();
	////TokenMap::iterator it = keywords.begin();
	//UMap::iterator it = theMap.begin();
	////while(it != keywords.end())
	//while(it != theMap.end())
	//{
		//found = (it->second == token);
		//if(found)
			//break;
		//++it;
	//}
	//return found;


	HMap::iterator it = hmap.begin();
	while(it != hmap.end())
	{
		found = (it->second == token);
		if(found)
			break;
		++it;
	}
	return found;

}

Token& Keywords::getKeyword(std::string &key) {




	//std::string newstr = boost::to_upper_copy(key);
	//if ( keywords.find(newstr) == keywords.end() ) {
		//std::string x = "NO_EXISTING_TOKEN";
		//return keywords.at(x);
	//} else {
		//return keywords.at(newstr);
	//}



	boost::to_upper(key);
	//std::cout << __FILE__ << ": " << __LINE__  << ", in Keywords::getKeyword" << std::endl;
	HMap::iterator it = hmap.find(key.c_str());
	//std::cout << __FILE__ << ": " << __LINE__  << ", in Keywords::getKeyword" << std::endl;
	if (it == hmap.end())
	{
		return hmap.at("NO_EXISTING_TOKEN");
	} else {
		//std::cout << "found" << it->second << std::endl;
		return hmap.at(key.c_str());
	}

}

Token& Keywords::getKeyword(const char * key) {

	//UMap::iterator it = theMap.find(key);
	//if (it == theMap.end())
	//{
		//return theMap.at("NO_EXISTING_TOKEN");
	//} else {
		//return theMap.at(key);
	//}


	std::string newstr = boost::to_upper_copy(std::string(key));

	HMap::iterator it = hmap.find(newstr.c_str());
	if (it == hmap.end())
	{
		return hmap.at("NO_EXISTING_TOKEN");
	} else {
		return hmap.at(newstr.c_str());
	}
}

Token& Keywords::getKeyword(char * key) {

	//UMap::iterator it = theMap.find(key);
	//if (it == theMap.end())
	//{
		//return theMap.at("NO_EXISTING_TOKEN");
	//} else {
		//return theMap.at(key);
	//}


	char * tmpBuf = new char[strlen(key) + 1];
	memcpy (tmpBuf,key, strlen(key) + 1);
	convertToUpperCase(tmpBuf);

	HMap::iterator it = hmap.find(tmpBuf);
	if (it == hmap.end())
	{
		delete[] tmpBuf;
		return hmap.at("NO_EXISTING_TOKEN");
	} else {
		tok = hmap.at(tmpBuf);
		delete[] tmpBuf;
		return tok;
	}

}

TokenMap& Keywords::getKeywords() {
	return keywords;
}

