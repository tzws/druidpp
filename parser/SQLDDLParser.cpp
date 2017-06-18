#include "SQLDDLParser.h"
SQLDDLParser::SQLDDLParser(std::string &theSql) : SQLStatementParser(theSql){
	//super(sql);
}

SQLDDLParser::SQLDDLParser(SQLExprParser *theExprParser) : SQLStatementParser(theExprParser){
	//super(exprParser);
}

SQLDDLParser::~SQLDDLParser(){

}
SQLTableConstaint *SQLDDLParser::parseConstraint() {
	if (lexer->getToken() == CONSTRAINT) {
		lexer->nextToken();
	}

	if (lexer->getToken() == IDENTIFIER) {
		this->exprParser->getName();
		throw new ParserException("TODO");
	}

	if (lexer->getToken() == PRIMARY) {
		lexer->nextToken();
		accept(KEY);

		throw new ParserException("TODO");
	}

	throw new ParserException("TODO");
}

