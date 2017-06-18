#include "SQLCreateTableParser.h"
SQLCreateTableParser::SQLCreateTableParser(std::string & theSql) : SQLDDLParser(theSql){
	//super(sql);
}

SQLCreateTableParser::SQLCreateTableParser(SQLExprParser * theExprParser) : SQLDDLParser(theExprParser){
	//super(exprParser);
}

SQLCreateTableParser::~SQLCreateTableParser(){

}
SQLCreateTableStatement *SQLCreateTableParser::parseCrateTable() {
	return parseCrateTable(true);
}

SQLCreateTableStatement *SQLCreateTableParser::parseCrateTable(bool theAcceptCreate) {
	if (theAcceptCreate) {
		accept(CREATE);
	}

	SQLCreateTableStatement *createTable = newCreateStatement();

	if (identifierEquals("GLOBAL")) {
		lexer->nextToken();

		if (identifierEquals("TEMPORARY")) {

			lexer->nextToken();
			createTable->setType(SQLCreateTableStatement::GLOBAL_TEMPORARY);

		} else {

			std::stringstream stream;
			stream << "TODO " <<  lexer->getToken() <<  " "  <<  lexer->getStringVal();
			throw new ParserException(stream.str());
			//throw new ParserException("syntax error " + lexer->getToken() + " " + lexer->getStringVal());

		}
	} else if (lexer->getToken() == IDENTIFIER && boost::iequals(lexer->getStringVal(), std::string("LOCAL"))) {

		lexer->nextToken();
		//if (lexer->getToken() == IDENTIFIER && lexer->getStringVal().equalsIgnoreCase("TEMPORAY")) {
		if (lexer->getToken() == IDENTIFIER && boost::iequals(lexer->getStringVal(), std::string("TEMPORARY"))) {

			lexer->nextToken();
			createTable->setType(SQLCreateTableStatement::LOCAL_TEMPORARY);

		} else {

			throw new ParserException("syntax error");

		}
	}

	accept(TABLE);

	createTable->setName(this->exprParser->getName());

	if (lexer->getToken() == LEFTPAREN) {
		lexer->nextToken();

		for (;;) {
			if (lexer->getToken() == IDENTIFIER //
					|| lexer->getToken() == LITERAL_ALIAS) {

				SQLColumnDefinition *column = this->exprParser->parseColumn();
				createTable->getTableElementList().push_back(column);

			} else if (lexer->getToken() == PRIMARY //
					|| lexer->getToken() == UNIQUE //
					|| lexer->getToken() == CHECK //
					|| lexer->getToken() == CONSTRAINT) {

				SQLConstaint *constraint = this->exprParser->parseConstaint();
				constraint->setParent(createTable);

				SQLTableElement* xxx = dynamic_cast<SQLTableElement *>(constraint);
				createTable->getTableElementList().push_back(xxx);

			} else if (lexer->getToken() == TABLESPACE) {

				throw new ParserException("TODO " + lexer->getToken());

			} else {

				SQLColumnDefinition *column = this->exprParser->parseColumn();
				createTable->getTableElementList().push_back(column);

			}

			if (lexer->getToken() == COMMA) {
				lexer->nextToken();

				if (lexer->getToken() == RPAREN) { // compatible for sql server
					break;
				}
				continue;
			}

			break;
		}

		// while
		// (this->tokenList.current().equals(OracleConstraintToken)) {
		// parseConstaint(table.getConstaints());
		//
		// if (this->tokenList.current().equals(OracleCommaToken))
		// ;
		// lexer->nextToken();
		// }

		accept(RPAREN);

	}

	return createTable;
}

SQLCreateTableStatement *SQLCreateTableParser::newCreateStatement() {
	return new SQLCreateTableStatement();
}

