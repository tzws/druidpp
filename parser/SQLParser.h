
#ifndef SQLParser_HEADER_H
#define SQLParser_HEADER_H

#include <boost/smart_ptr.hpp>
#include <string>
#include "Lexer.h"
#include "ParserException.h"
#include "Token.h"



class SQLParser {

	private:
		bool lexerHere;
	protected:
		Lexer *lexer;

		bool identifierEquals(std::string &text);
		bool identifierEquals(const char *);
		void acceptIdentifier(std::string &text);
		void acceptIdentifier(const char *text);

		std::string &as();

		void setErrorEndPos(int errPos);

	public:
		SQLParser(std::string& sql);

		SQLParser(Lexer* lexer);
		~SQLParser();

		Lexer *getLexer();

		void accept(Token token);

		void match(Token token);

	private:
		int errorEndPos;
		std::string alias;

};
typedef boost::shared_ptr<SQLParser> SQLParser_ptr;

#endif

