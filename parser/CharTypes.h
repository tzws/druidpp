// g++ x.cpp -std=c++11
#include <iostream>
#include <vector>

#ifndef CHARTYPES_HEADER_H
#define CHARTYPES_HEADER_H
#include <boost/smart_ptr.hpp>
#define HEXFLAGSLENGTH 256

class CharTypes {
	public:
		CharTypes ();
		~CharTypes ();

		static bool isHex(char c);
		static bool isDigit(char c);
		static bool isFirstIdentifierChar(char c);

		/**
		 * @return false if {@link LayoutCharacters#EOI}
		 */
		static bool isWhitespace(char c);
		static bool isWhitespace(std::string c);

		static bool isIdentifierChar(char c);

	private:
		static bool hexFlags[256];
		static bool firstIdentifierFlags[256];
		static bool identifierFlags[256];
		static bool whitespaceFlags[256];
		static bool __init;
		static bool init();

};
typedef boost::shared_ptr<CharTypes> CharTypes_ptr;

#endif

