#include <boost/algorithm/string.hpp>
#include <string>
#include <sstream>
#include <iostream>

#include "SQLParser.h"

bool SQLParser::identifierEquals(std::string& text) {
	return lexer->getToken() == IDENTIFIER && (boost::iequals(lexer->getStringVal(), text));
	//return lexer->getToken() == IDENTIFIER && (strcasecmp((lexer->getStringVal()).c_str(), text.c_str()));
}

bool SQLParser::identifierEquals(const char * text) {

	//return lexer->getToken() == IDENTIFIER && (strcasecmp((lexer->getStringVal()).c_str(), text));


	//std::string newstr = boost::to_upper_copy(std::string(lexer->getStringVal()));
	//return lexer->getToken() == IDENTIFIER && (strcmp(newstr.c_str(), text));

	//return lexer->getToken() == IDENTIFIER && (boost::iequals((lexer->getStringVal()), std::string(text)));


	lexer->keepChar();
	return lexer->getToken() == IDENTIFIER && (bsd_strcmp_u((lexer->getStringVal1()), text));
	lexer->restoreChar();


	
}
SQLParser::~SQLParser() {

	//std::cout << __FILE__ << ": " << __LINE__ << ", in SQLParser::~SQLParser, destructor step 1" << std::endl;
	if (lexerHere && lexer != NULL)
	{
		//std::cout << __FILE__ << ": " << __LINE__ << ", in SQLParser::~SQLParser, destructor step 1.1" << std::endl;
		delete lexer;
	}
	//std::cout << __FILE__ << ": " << __LINE__ << ", in SQLParser::~SQLParser, destructor step 2" << std::endl;
}


void SQLParser::acceptIdentifier(std::string &text) {
	if (identifierEquals(text)) {
		lexer->nextToken();
	} else {
		setErrorEndPos(lexer->getPos());

		std::stringstream stream;
		stream << "syntax error, expect " <<  text <<  ", actual " <<  lexer->getToken();

		throw new ParserException(stream.str());
	}
}
void SQLParser::acceptIdentifier(const char * text) {
	if (identifierEquals(text)) {
		lexer->nextToken();
	} else {
		setErrorEndPos(lexer->getPos());

		std::stringstream stream;
		stream << "syntax error, expect " <<  text <<  ", actual " <<  lexer->getToken();

		throw new ParserException(stream.str());
	}
}

std::string &SQLParser::as() {
	//http://stackoverflow.com/questions/3903587/how-to-check-if-a-stdstring-is-set-or-not
	alias = "";

	if (lexer->getToken() == AS) {
		lexer->nextToken();

		if (lexer->getToken() == LITERAL_ALIAS) {
			alias = '"' + lexer->getStringVal() + '"';
			lexer->nextToken();
		} else if (lexer->getToken() == IDENTIFIER) {
			alias = lexer->getStringVal();
			lexer->nextToken();
		} else if (lexer->getToken() == LITERAL_CHARS) {
			alias = "'" + lexer->getStringVal() + "'";
			lexer->nextToken();
		} else {
			switch (lexer->getToken()) {
				case KEY:
				case INDEX:
				case CASE:
				case MODEL:
				case PCTFREE:
				case INITRANS:
				case MAXTRANS:
				case SEGMENT:
				case CREATION:
				case IMMEDIATE:
				case DEFERRED:
				case STORAGE:
				case NEXT:
				case MINEXTENTS:
				case MAXEXTENTS:
				case MAXSIZE:
				case PCTINCREASE:
				case FLASH_CACHE:
				case CELL_FLASH_CACHE:
				case KEEP:
				case NONE:
				case LOB:
				case STORE:
				case ROW:
				case CHUNK:
				case CACHE:
				case NOCACHE:
				case LOGGING:
				case NOCOMPRESS:
				case KEEP_DUPLICATES:
				case EXCEPTIONS:
				case PURGE:
				case INITIALLY:
				case END:
				case COMMENT:
				case ENABLE:
				case DISABLE:
				case SEQUENCE:
				case USER:
				case ANALYZE:
				case OPTIMIZE:
				case GRANT:
				case FULL:
				case TO:
				case NEW:
				case INTERVAL:
				case LOCK:
				case LIMIT:
				case IDENTIFIED:
				case PASSWORD:
				case BINARY:
				case WINDOW:
				case OFFSET:
				case SHARE:
				case START:
				case CONNECT:
				case MATCHED:
				case ERRORS:
				case REJECT:
				case UNLIMITED:
				case BEGIN:
				case EXCLUSIVE:
				case MODE:
				case ADVISE:
					alias = lexer->getStringVal();
					lexer->nextToken();
					return alias;
				case QUES:
					alias = "?";
					lexer->nextToken();
				default:
					break;
			}
		}

		if (!alias.empty()) {
			while (lexer->getToken() == DOT) {
				lexer->nextToken();
				alias += ('.' + tokenStringList.at(lexer->getToken()));
				lexer->nextToken();
			}

			return alias;
		}

		if (lexer->getToken() == LEFTPAREN) {
			//return null;
			alias = "";
			return alias;
		}

		throw new ParserException("Error : " + lexer->getToken());
	}

	if (lexer->getToken() == LITERAL_ALIAS) {
		alias = '"' + lexer->getStringVal() + '"';
		lexer->nextToken();
	} else if (lexer->getToken() == IDENTIFIER) {
		alias = lexer->getStringVal();
		lexer->nextToken();
	} else if (lexer->getToken() == LITERAL_CHARS) {
		alias = "'" + lexer->getStringVal() + "'";
		lexer->nextToken();
	} else if (lexer->getToken() == CASE) {
		alias = tokenStringList.at(lexer->getToken());
		lexer->nextToken();
	}

	switch (lexer->getToken()) {
		case KEY:
		case INTERVAL:
			alias = tokenStringList.at(lexer->getToken());
			lexer->nextToken();
			return alias;
		default:
			break;
	}

	return alias;
}

void SQLParser::setErrorEndPos(int errPos) {
	if (errPos > errorEndPos) {
		errorEndPos = errPos;
	}
}

SQLParser::SQLParser(std::string &sql) : lexerHere(true), lexer((new Lexer(sql))), errorEndPos(-1) {

	//std::cout << __FILE__ << ": " << __LINE__ << ", in SQLParser::SQLParser, constructor 1 " << std::endl;
	//this(new Lexer(sql));
	//this.lexer->nextToken();
	//Lexer *theLexer = new Lexer(sql);
	//lexer = *theLexer;
	lexer->nextToken();
}

SQLParser::SQLParser(Lexer* theLexer): lexerHere(false), lexer(theLexer), errorEndPos(-1) {
	//std::cout << __FILE__ << ": " << __LINE__ << ", in SQLParser::SQLParser, constructor 2 " << std::endl;
	//lexer = theLexer;
	//errorEndPos = -1;
}

Lexer *SQLParser::getLexer() {
	return lexer;
}

void SQLParser::accept(Token token) {
	if (lexer->getToken() == token) {
		lexer->nextToken();
	} else {
		setErrorEndPos(lexer->getPos());
		std::stringstream stream;
		stream << "syntax error, expect " <<  token <<  ", actual " <<  lexer->getToken() <<  " "
			<<  lexer->getStringVal() <<  ", pos " <<  lexer->getPos();

		throw new ParserException(stream.str());
	}
}

void SQLParser::match(Token token) {
	if (lexer->getToken() != token) {
		std::stringstream stream;
		stream << "syntax error, expect " <<  token <<  ", actual " <<  lexer->getToken() <<  " " <<  lexer->getStringVal();
		throw new ParserException(stream.str());
	}
}


