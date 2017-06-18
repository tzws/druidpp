#include "OdpsSelectParser.h"
OdpsSelectParser::~OdpsSelectParser()
{

}
OdpsSelectParser::OdpsSelectParser(SQLExprParser *theExprParser)
	: 
		SQLSelectParser(theExprParser)
		//, exprParser(theExprParser)
{
	//super(exprParser->getLexer());
	//exprParser = exprParser;
}

SQLSelectItem *OdpsSelectParser::parseSelectItem() {
	SQLExpr *theExpr;
	if (lexer->getToken() == IDENTIFIER) {
		theExpr = new SQLIdentifierExpr(lexer->getStringVal());
		lexer->nextTokenComma();

		if (lexer->getToken() != COMMA) {
			theExpr = this->exprParser->primaryRest(theExpr);
			theExpr = this->exprParser->exprRest(theExpr);
		}
	} else {
		theExpr = expr();
	}

	if (lexer->getToken() == AS) {
		lexer->nextToken();

		if (lexer->getToken() == LEFTPAREN) {
			lexer->nextToken();

			OdpsUDTFSQLSelectItem *selectItem = new OdpsUDTFSQLSelectItem();

			selectItem->setExpr(theExpr);

			for (;;) {
				std::string alias = lexer->getStringVal();
				lexer->nextToken();

				selectItem->getAliasList().push_back(alias);

				if (lexer->getToken() == COMMA) {
					lexer->nextToken();
					continue;
				}
				break;
			}

			accept(RPAREN);

			return selectItem;
		}
	}

	std::string alias = as();

	return new SQLSelectItem(theExpr, alias);
}
