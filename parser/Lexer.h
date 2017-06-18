#ifndef LEXER_HEADER_H
#define LEXER_HEADER_H

#include <boost/lexical_cast.hpp>
#include <iostream>
#include <vector>
//#include <decimal/decimal>

#include "Token.h"
#include "Keywords.h"
#include "CharTypes.h"
#include "LayoutCharacters.h"
#include "NumberFormatException.h"

#include "../ast/expr/SQLNumericLiteralExpr.h"


#include <boost/smart_ptr.hpp>

class Lexer{

	protected:
		std::string text;
		int          pos;
		int          mark;

		char         ch;
		char         tmpchar;

		char       *charBuf;
		char       *tmpBuf;
		//std::list<char> buf;

		int          bufPos;
		int  charbufLength;
		int  tmpbufLength;

		Token        token;

		Keywords     *keywods;

		std::string       stringVal;
		std::string       stringInfo;
		std::string       stringHex;

		struct {
			char * chPtr;
			int startPos;
			int endPos;

		} stringMark;

		bool      skipComment;

		class CommentHandler {
			bool handle(Token lastToken, std::string comment);
		};

	private:


		struct SavePoint {

			int   bp;
			int   sp;
			int   np;
			char  ch;
			Token token;
		};

		SavePoint savePoint;

		/*
		 * anti sql injection
		 */

		bool        allowComment;
		int            varIndex;

		static long  MULTMIN_RADIX_TEN;
		static long  N_MULTMAX_RADIX_TEN;
		static int digits[10];
		static bool _digitsInitialized;

	protected:
		CommentHandler commentHandler;

	public: 
		~Lexer();
		void keepChar();
		void restoreChar();
		static bool initDigits();
		Lexer(std::string &input); 
		Lexer(std::string &input, bool skipComment);
		Lexer(char* input, int inputLength, bool skipComment);
		Lexer::CommentHandler& getCommentHandler();
		void setCommentHandler(Lexer::CommentHandler &commentHandler);
		//inline char charAt(int index);
		inline char charAt(int index) {
			return (index >= charbufLength ) ? LayoutCharacters::EOI : charBuf[index];
		}


		//std::string &addSymbol();
		void addSymbol1() ;
		//std::string &subString(int offset, int count);
		void subString1(int offset, int count) ;
		bool isAllowComment();
		void setAllowComment(bool allowComment);
		int nextVarIndex();
		Keywords *getKeywods();
		void doMark();
		void reset();		

		bool isEOF();
		/**
		 * Return the current token, set by nextToken().
		 */
		Token& getToken();
		std::string &info();
		void nextTokenComma();
		void nextTokenLParen();
		void nextTokenValue();
		void nextToken();
		void scanSharp();
		void scanVariable();
		void scanComment();
		void scanIdentifier();
		void scanNumber();


		void scanHexaDecimal();

		std::string &hexString();

		bool isDigit(char ch);
		/**
		 * Return the current token's position: a 0-based offset from beginning of the raw input stream (before unicode
		 * translation)
		 */

		int getPos();
		/**
		 * The value of a literal token, recorded as a string. For integers, leading 0x and 'l' suffixes are suppressed.
		 */
		std::string &getStringVal();
		char * getStringVal1();

		//// QS_TODO negative number is invisible for lexer
		RNumber *integerValue();
		//int integerValue();

		int bp();

		char current();

		void reset(int mark, char markChar, Token token);

		std::string &numberString();

		//std::decimal::decimal128 decimalValue();
		RNumber *decimalValue();

		//static interface CommentHandler;

	protected: 

		void initBuff(int size);

		//void scanChar();

		inline void scanChar() {

			//std::cout << "in Lexer::scanChar, step 1 " << charBuf[0] << std::endl;
			ch = charAt(++pos);
			//std::cout << "in Lexer::scanChar, step 2 " << charBuf[0] << std::endl;
		}


		void unscan();

		/**
		 * Report an error at the given position using the provided arguments.
		 */
		void lexError(std::string &key, ...);
		void lexError(const char *key, ...);
		void scanLBracket();

		void scanString();

		/**
		 * Append a character to sbuf.
		 */
		void putChar(char ch);


	private:
		void scanOperator();

		void scanAlias();
		bool isOperator(char ch);
};
typedef boost::shared_ptr<Lexer> Lexer_ptr;
#endif

