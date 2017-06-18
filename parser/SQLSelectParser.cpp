#include <boost/algorithm/string.hpp>
#include "SQLSelectParser.h"
#include "SQLExprParser.h"


SQLSelectParser::SQLSelectParser(std::string &theSql) : super (theSql){
		//std::cout << __FILE__ << ": " << __LINE__ << ", in SQLSelectParser::SQLSelectParser, constructor step 1" << std::endl;
	//super(sql);
}

SQLSelectParser::SQLSelectParser(Lexer *theLexer) : super (theLexer){
		//std::cout << __FILE__ << ": " << __LINE__ << ", in SQLSelectParser::SQLSelectParser, constructor step 2" << std::endl;
	//super(lexer);
}

SQLSelectParser::SQLSelectParser(SQLExprParser *theExprParser): super(theExprParser->getLexer()), exprParser (theExprParser){
		//std::cout << __FILE__ << ": " << __LINE__ << ", in SQLSelectParser::SQLSelectParser, constructor step 3" << std::endl;
	//super(exprParser.getLexer());
	//exprParser = theExprParser;
}

SQLSelectParser::~SQLSelectParser() {
		//std::cout << __FILE__ << ": " << __LINE__ << ", in SQLSelectParser::~SQLSelectParser, destructor step 1" << std::endl;

}
SQLSelect *SQLSelectParser::select() {

	//std::cout << "\t\t" <<  __FILE__ << ": " << __LINE__ << ", in SQLSelectParser::select, step 1" << std::endl;
	SQLSelect *select = new SQLSelect();
	//std::cout << "\t\t" <<  __FILE__ << ": " << __LINE__ << ", in SQLSelectParser::select, step 2" << std::endl;

	withSubquery(select);
	//std::cout << "\t\t" <<  __FILE__ << ": " << __LINE__ << ", in SQLSelectParser::select, step 3" << std::endl;

	select->setQuery(query());
	//std::cout << "\t\t" <<  __FILE__ << ": " << __LINE__ << ", in SQLSelectParser::select, step 4" << std::endl;
	select->setOrderBy(parseOrderBy());
	//std::cout << "\t\t" <<  __FILE__ << ": " << __LINE__ << ", in SQLSelectParser::select, step 5" << std::endl;

	if (select->getOrderBy() == NULL) {
		//std::cout << "\t\t" <<  __FILE__ << ": " << __LINE__ << ", in SQLSelectParser::select, step 5.1" << std::endl;
		select->setOrderBy(parseOrderBy());
		//std::cout << "\t\t" <<  __FILE__ << ": " << __LINE__ << ", in SQLSelectParser::select, step 5.2" << std::endl;
	}

	if (lexer->getToken() == HINT) {
		//std::cout << "\t\t" <<  __FILE__ << ": " << __LINE__ << ", in SQLSelectParser::select, step 5.3" << std::endl;
		exprParser->parseHints(select->getHints());
		//std::cout << "\t\t" <<  __FILE__ << ": " << __LINE__ << ", in SQLSelectParser::select, step 5.4" << std::endl;
	}

	//std::cout << "\t\t" <<  __FILE__ << ": " << __LINE__ << ", in SQLSelectParser::select, step 6" << std::endl;
	return select;
}

SQLUnionQuery *SQLSelectParser::createSQLUnionQuery() {
	return new SQLUnionQuery();
}

SQLUnionQuery *SQLSelectParser::unionRest(SQLUnionQuery *xunion) {
	if (lexer->getToken() == ORDER) {
		SQLOrderBy *orderBy = exprParser->parseOrderBy();
		xunion->setOrderBy(orderBy);
		return unionRest(xunion);
	}
	return xunion;
}

SQLSelectQuery *SQLSelectParser::queryRest(SQLSelectQuery *selectQuery) {

	//std::cout << "\t\t" <<  __FILE__ << ": " << __LINE__ << ", in SQLSelectParser::queryRest, step 1" << std::endl;


	//std::cout <<  "++++\t" << __FILE__ << ": " << __LINE__ << ", in SQLSelectParser::queryRest, step 1.01 " <<   lexer->getToken() <<  " " << tokenStringList.at(lexer->getToken() ) <<  ": "  <<  lexer->getStringVal()  <<  ", pos "  <<  lexer->getPos()<< std::endl;

	if (lexer->getToken() == UNION) {
		//std::cout << "\t\t" <<  __FILE__ << ": " << __LINE__ << ", in SQLSelectParser::queryRest, step 1.1" << std::endl;
		lexer->nextToken();

		SQLUnionQuery *xunion = createSQLUnionQuery();
		xunion->setLeft(selectQuery);

		if (lexer->getToken() == ALL) {
			xunion->setOperator(&SQLUnionOperator::UNION_ALL);
			lexer->nextToken();
		} else if (lexer->getToken() == DISTINCT) {
			xunion->setOperator(&SQLUnionOperator::DISTINCT);
			lexer->nextToken();
		}
		SQLSelectQuery *right = this->query();
		xunion->setRight(right);

		return unionRest(xunion);
	}

	if (lexer->getToken() == EXCEPT) {
		//std::cout << "\t\t" <<  __FILE__ << ": " << __LINE__ << ", in SQLSelectParser::queryRest, step 1.2" << std::endl;
		lexer->nextToken();

		//std::cout << "\t\t" <<  __FILE__ << ": " << __LINE__ << ", in SQLSelectParser::queryRest, step 1.2.1 creating new SQLUnionQuery" << std::endl;
		SQLUnionQuery *xunion = new SQLUnionQuery();
		xunion->setLeft(selectQuery);

		xunion->setOperator(&SQLUnionOperator::EXCEPT);

		SQLSelectQuery *right = this->query();
		xunion->setRight(right);

		return xunion;
	}

	if (lexer->getToken() == INTERSECT) {
		//std::cout << "\t\t" <<  __FILE__ << ": " << __LINE__ << ", in SQLSelectParser::queryRest, step 1.2.2 creating new SQLUnionQuery" << std::endl;
		lexer->nextToken();

		SQLUnionQuery *xunion = new SQLUnionQuery();
		xunion->setLeft(selectQuery);

		xunion->setOperator(&SQLUnionOperator::INTERSECT);

		SQLSelectQuery *right = this->query();
		xunion->setRight(right);

		return xunion;
	}

	if (lexer->getToken() == MINUS) {
		lexer->nextToken();

		//std::cout << "\t\t" <<  __FILE__ << ": " << __LINE__ << ", in SQLSelectParser::queryRest, step 1.2.3 creating new SQLUnionQuery" << std::endl;
		SQLUnionQuery *xunion = new SQLUnionQuery();
		xunion->setLeft(selectQuery);

		xunion->setOperator(&SQLUnionOperator::MINUS);

		SQLSelectQuery *right = this->query();
		xunion->setRight(right);

		return xunion;
	}
	//std::cout << "\t\t" <<  __FILE__ << ": " << __LINE__ << ", in SQLSelectParser::queryRest, step 2" << std::endl;

	return selectQuery;
}

SQLSelectQuery *SQLSelectParser::query() {

	//std::cout << "\t\t" <<  __FILE__ << ": " << __LINE__ << ", in SQLSelectParser::query, step 1" << std::endl;
	if (lexer->getToken() == LEFTPAREN) {
		//std::cout << "\t\t" <<  __FILE__ << ": " << __LINE__ << ", in SQLSelectParser::query, step 1.1" << std::endl;
		lexer->nextToken();

		SQLSelectQuery *select = query();
		accept(RPAREN);

		return queryRest(select);
	}
	//std::cout << "\t\t" <<  __FILE__ << ": " << __LINE__ << ", in SQLSelectParser::query, step 2" << std::endl;

	accept(TOKEN_SELECT);
	//std::cout << "\t\t" <<  __FILE__ << ": " << __LINE__ << ", in SQLSelectParser::query, step 3" << std::endl;

	if (lexer->getToken() == COMMENT) {
		//std::cout << "\t\t" <<  __FILE__ << ": " << __LINE__ << ", in SQLSelectParser::query, step 3.1" << std::endl;
		lexer->nextToken();
	}
	//std::cout << "\t\t" <<  __FILE__ << ": " << __LINE__ << ", in SQLSelectParser::query, step 4, creating new SQLSelectQueryBlock" << std::endl;

	SQLSelectQueryBlock *queryBlock = new SQLSelectQueryBlock();
	//std::cout << "\t\t" <<  __FILE__ << ": " << __LINE__ << ", in SQLSelectParser::query, step 5" << std::endl;

	if (lexer->getToken() == DISTINCT) {

		//std::cout << "\t\t" <<  __FILE__ << ": " << __LINE__ << ", in SQLSelectParser::query, step 5.1" << std::endl;
		queryBlock->setDistionOption(SQLSetQuantifier::DISTINCT);
		//std::cout << "\t\t" <<  __FILE__ << ": " << __LINE__ << ", in SQLSelectParser::query, step 5.2" << std::endl;
		lexer->nextToken();

	} else if (lexer->getToken() == UNIQUE) {
		//std::cout << "\t\t" <<  __FILE__ << ": " << __LINE__ << ", in SQLSelectParser::query, step 5.3" << std::endl;

		queryBlock->setDistionOption(SQLSetQuantifier::UNIQUE);
		lexer->nextToken();

	} else if (lexer->getToken() == ALL) {
		//std::cout << "\t\t" <<  __FILE__ << ": " << __LINE__ << ", in SQLSelectParser::query, step 5.4" << std::endl;

		queryBlock->setDistionOption(SQLSetQuantifier::ALL);
		lexer->nextToken();

	}
	//std::cout << "\t\t" <<  __FILE__ << ": " << __LINE__ << ", in SQLSelectParser::query, step 6" << std::endl;

	parseSelectList(queryBlock);
	//std::cout << "\t\t" <<  __FILE__ << ": " << __LINE__ << ", in SQLSelectParser::query, step 7" << std::endl;

	parseFrom(queryBlock);
	//std::cout << "\t\t" <<  __FILE__ << ": " << __LINE__ << ", in SQLSelectParser::query, step 8" << std::endl;

	parseWhere(queryBlock);
	//std::cout << "\t\t" <<  __FILE__ << ": " << __LINE__ << ", in SQLSelectParser::query, step 9" << std::endl;
	//std::cout <<  "++++\t" << __FILE__ << ": " << __LINE__ << ", in SQLSelectParser::query, step 9.1 " <<   lexer->getToken() <<  " " << tokenStringList.at(lexer->getToken() ) <<  ": "  <<  lexer->getStringVal()  <<  ", pos "  <<  lexer->getPos()<< std::endl;

	parseGroupBy(queryBlock);
	//std::cout << "\t\t" <<  __FILE__ << ": " << __LINE__ << ", in SQLSelectParser::query, step 10" << std::endl;
	//std::cout <<  "++++\t" << __FILE__ << ": " << __LINE__ << ", in SQLSelectParser::query, step 10.1 " <<   lexer->getToken() <<  " " << tokenStringList.at(lexer->getToken() ) <<  ": "  <<  lexer->getStringVal()  <<  ", pos "  <<  lexer->getPos()<< std::endl;

	return queryRest(queryBlock);
}

void SQLSelectParser::withSubquery(SQLSelect *theSelect) {
	//std::cout << "\t\t" <<  __FILE__ << ": " << __LINE__ << ", in SQLSelectParser::withSubquery, step 1" << std::endl;
	if (lexer->getToken() == WITH) {
		//std::cout << "\t\t" <<  __FILE__ << ": " << __LINE__ << ", in SQLSelectParser::withSubquery, step 1.1" << std::endl;
		lexer->nextToken();

		SQLWithSubqueryClause *withQueryClause = new SQLWithSubqueryClause();

		if (lexer->getToken() == RECURSIVE || identifierEquals("RECURSIVE")) {
			lexer->nextToken();
			withQueryClause->setRecursive(true);
		}

		for (;;) {
			SQLWithSubqueryClause_Entry *entry = new SQLWithSubqueryClause_Entry();

			SQLIdentifierExpr* v = dynamic_cast<SQLIdentifierExpr *>(exprParser->getName());
			entry->setName(v);

			if (lexer->getToken() == LEFTPAREN) {
				lexer->nextToken();
				exprParser->getNames(entry->getColumns());
				accept(RPAREN);
			}

			accept(AS);
			accept(LEFTPAREN);
			entry->setSubQuery(select());
			accept(RPAREN);

			withQueryClause->getEntries().push_back(entry);

			if (lexer->getToken() == COMMA) {
				lexer->nextToken();
				continue;
			}

			break;
		}

		theSelect->setWithSubQuery(withQueryClause);
	}
	//std::cout << "\t\t" <<  __FILE__ << ": " << __LINE__ << ", in SQLSelectParser::withSubquery, step 2" << std::endl;
}

void SQLSelectParser::parseWhere(SQLSelectQueryBlock *queryBlock) {

	//std::cout << "\t\t" <<  __FILE__ << ": " << __LINE__ << ", in SQLSelectParser::parseWhere, step 1" << std::endl;
	//std::cout <<  "++++\t" << __FILE__ << ": " << __LINE__ << ", in SQLSelectParser::parseWhere, step 1.01 " <<   lexer->getToken() <<  " " << tokenStringList.at(lexer->getToken() ) <<  ": "  <<  lexer->getStringVal()  <<  ", pos "  <<  lexer->getPos()<< std::endl;
	if (lexer->getToken() == WHERE) {
		//std::cout << "\t\t" <<  __FILE__ << ": " << __LINE__ << ", in SQLSelectParser::parseWhere, step 1.1" << std::endl;
		lexer->nextToken();

		queryBlock->setWhere(expr());
	}
	//std::cout << "\t\t" <<  __FILE__ << ": " << __LINE__ << ", in SQLSelectParser::parseWhere, step 2" << std::endl;
}

void SQLSelectParser::parseGroupBy(SQLSelectQueryBlock *queryBlock) {
	//std::cout << "\t\t" <<  __FILE__ << ": " << __LINE__ << ", in SQLSelectParser::parseGroupBy, step 1" << std::endl;
	if (lexer->getToken() == GROUP) {

		lexer->nextToken();
		accept(BY);

		//std::cout << "\t\t" <<  __FILE__ << ": " << __LINE__ << ", in SQLSelectParser::parseGroupBy, step 1.1, creating new SQLSelectGroupByClause" << std::endl;
		SQLSelectGroupByClause *groupBy = new SQLSelectGroupByClause();
		while (true) {

			groupBy->getItems().push_back(expr());
			if (lexer->getToken() != COMMA) {
				break;
			}

			lexer->nextToken();
		}

		if (lexer->getToken() == HAVING) {
			lexer->nextToken();

			groupBy->setHaving(expr());
		}

		queryBlock->setGroupBy(groupBy);

	} else if (lexer->getToken() == (HAVING)) {
		//std::cout << "\t\t" <<  __FILE__ << ": " << __LINE__ << ", in SQLSelectParser::parseGroupBy, step 1.2, creating new SQLSelectGroupByClause" << std::endl;
		lexer->nextToken();

		SQLSelectGroupByClause *groupBy = new SQLSelectGroupByClause();

		groupBy->setHaving(this->expr());
		queryBlock->setGroupBy(groupBy);
	}
	//std::cout << "\t\t" <<  __FILE__ << ": " << __LINE__ << ", in SQLSelectParser::parseGroupBy, step 3, creating new SQLSelectGroupByClause" << std::endl;
}

void SQLSelectParser::parseSelectList(SQLSelectQueryBlock *queryBlock) {

	//std::cout << "\t\t" <<  __FILE__ << ": " << __LINE__ << ", in SQLSelectParser::parseSelectList, step 1" << std::endl;
	std::list<SQLSelectItem *> &selectList = queryBlock->getSelectList();
	for (;;) {
		//std::cout << "\t\t" <<  __FILE__ << ": " << __LINE__ << ", in SQLSelectParser::parseSelectList, step 2" << std::endl;
		SQLSelectItem * selectItem = parseSelectItem();
		selectList.push_back(selectItem);

		if (lexer->getToken() != COMMA) {
			break;
		}

		lexer->nextToken();
	}
}

SQLSelectItem *SQLSelectParser::parseSelectItem() {
	//std::cout << "\t\t" <<  __FILE__ << ": " << __LINE__ << ", in SQLSelectParser::parseSelectItem, step 1" << std::endl;
	SQLExpr *theExpr;
	if (lexer->getToken() == IDENTIFIER) {

		//std::cout << "\t\t" <<  __FILE__ << ": " << __LINE__ << ", in SQLSelectParser::parseSelectItem, step 2, creating new SQLIdentifierExpr" << std::endl;
		theExpr = new SQLIdentifierExpr(lexer->getStringVal());
		SQLExpr *tmp = theExpr;

		lexer->nextTokenComma();

		if (lexer->getToken() != COMMA) {
			//std::cout << "\t\t" <<  __FILE__ << ": " << __LINE__ << ", in SQLSelectParser::parseSelectItem, step 2.2, creating new SQLIdentifierExpr" << std::endl;
			theExpr = exprParser->primaryRest(theExpr);
			//std::cout << "\t\t" <<  __FILE__ << ": " << __LINE__ << ", in SQLSelectParser::parseSelectItem, step 2.3, creating new SQLIdentifierExpr" << std::endl;
			theExpr = exprParser->exprRest(theExpr);
		}
		//delete tmp;
	} else {
		//std::cout << "\t\t" <<  __FILE__ << ": " << __LINE__ << ", in SQLSelectParser::parseSelectItem, step 3" << std::endl;
		theExpr = expr();
	}
	std::string &alias = as();

	//std::cout << "\t\t" <<  __FILE__ << ": " << __LINE__ << ", in SQLSelectParser::parseSelectItem, step 4" << std::endl;
	return new SQLSelectItem(theExpr, alias);
}

void SQLSelectParser::parseFrom(SQLSelectQueryBlock *queryBlock) {

	//std::cout << "\t\t" <<  __FILE__ << ": " << __LINE__ << ", in SQLSelectParser::parseFrom, step 1" << std::endl;
	if (lexer->getToken() != FROM) {
		return;
	}

	lexer->nextToken();

	queryBlock->setFrom(parseTableSource());

	//std::cout << "\t\t" <<  __FILE__ << ": " << __LINE__ << ", in SQLSelectParser::parseFrom, step 2" << std::endl;
}

SQLTableSource *SQLSelectParser::parseTableSource() {

	if (lexer->getToken() == LEFTPAREN) {

		lexer->nextToken();
		SQLTableSource *tableSource;

		if (lexer->getToken() == TOKEN_SELECT || lexer->getToken() == WITH) {

			SQLSelect *theSelect = select();
			accept(RPAREN);
			queryRest(theSelect->getQuery());
			tableSource = new SQLSubqueryTableSource(theSelect);

		} else if (lexer->getToken() == LEFTPAREN) {

			tableSource = parseTableSource();
			accept(RPAREN);

		} else {

			tableSource = parseTableSource();
			accept(RPAREN);
		}

		return parseTableSourceRest(tableSource);
	}

	if (lexer->getToken() == TOKEN_SELECT) {
		throw new ParserException("TODO");
	}

	SQLExprTableSource *tableReference = new SQLExprTableSource();

	parseTableSourceQueryTableExpr(tableReference);

	return parseTableSourceRest(tableReference);
}

void SQLSelectParser::parseTableSourceQueryTableExpr(SQLExprTableSource *tableReference) {

	if (lexer->getToken() == LITERAL_ALIAS || lexer->getToken() == IDENTIFIED
			|| lexer->getToken() == LITERAL_CHARS) {

		tableReference->setExpr(exprParser->getName());
		return;
	}

	tableReference->setExpr(expr());
}

SQLTableSource *SQLSelectParser::parseTableSourceRest(SQLTableSource *tableSource) {

	if ((tableSource->getAlias() == "") || (tableSource->getAlias().length() == 0)) {

		if (lexer->getToken() != LEFT && lexer->getToken() != RIGHT && lexer->getToken() != FULL) {

			std::string &alias = as();
			if (alias != "") {

				tableSource->setAlias(alias);
				return parseTableSourceRest(tableSource);
			}
		}
	}

	SQLJoinTableSource::JoinType *joinType = &SQLJoinTableSource::JoinType::LEFT_OUTER_JOIN;
	bool xIsNull = true;


	if (lexer->getToken() == LEFT) {
		lexer->nextToken();
		if (lexer->getToken() == OUTER) {
			lexer->nextToken();
		}

		accept(JOIN);
		joinType = &SQLJoinTableSource::JoinType::LEFT_OUTER_JOIN;
		xIsNull = false;

	} else if (lexer->getToken() == RIGHT) {

		lexer->nextToken();

		if (lexer->getToken() == OUTER) {
			lexer->nextToken();
		}

		accept(JOIN);
		joinType = &SQLJoinTableSource::JoinType::RIGHT_OUTER_JOIN;
		xIsNull = false;

	} else if (lexer->getToken() == FULL) {

		lexer->nextToken();
		if (lexer->getToken() == OUTER) {
			lexer->nextToken();
		}
		accept(JOIN);
		joinType = &SQLJoinTableSource::JoinType::FULL_OUTER_JOIN;
		xIsNull = false;

	} else if (lexer->getToken() == INNER) {

		lexer->nextToken();
		accept(JOIN);
		joinType = &SQLJoinTableSource::JoinType::INNER_JOIN;
		xIsNull = false;

	} else if (lexer->getToken() == JOIN) {

		lexer->nextToken();
		joinType = &SQLJoinTableSource::JoinType::JOIN;
		xIsNull = false;

	} else if (lexer->getToken() == COMMA) {

		lexer->nextToken();
		joinType = &SQLJoinTableSource::JoinType::COMMA;
		xIsNull = false;

	} else if (identifierEquals("STRAIGHT_JOIN")) {

		lexer->nextToken();
		joinType = &SQLJoinTableSource::JoinType::STRAIGHT_JOIN;
		xIsNull = false;

	} else if (identifierEquals("CROSS")) {

		lexer->nextToken();
		accept(JOIN);
		joinType = &SQLJoinTableSource::JoinType::CROSS_JOIN;
		xIsNull = false;
	}

	//if (joinType != NULL) {
	if (!xIsNull) {
		SQLJoinTableSource *join = new SQLJoinTableSource();
		join->setLeft(tableSource);
		join->setJoinType(joinType);
		join->setRight(parseTableSource());


		if (lexer->getToken() == ON) {

			lexer->nextToken();
			join->setCondition(expr());

		} else if (identifierEquals("USING")) {

			lexer->nextToken();
			if (lexer->getToken() == LEFTPAREN) {
				lexer->nextToken();
				exprParser->exprList(join->getUsing());
				accept(RPAREN);
			} else {
				join->getUsing().push_back(expr());
			}
		}

		return parseTableSourceRest(join);
	}

	return tableSource;
}

SQLExpr *SQLSelectParser::expr() {
	return exprParser->getExpr();
}

SQLOrderBy *SQLSelectParser::parseOrderBy() {
	return exprParser->parseOrderBy();
}

void SQLSelectParser::acceptKeyword(std::string &ident) {

	if (lexer->getToken() == IDENTIFIER && boost::iequals(ident, lexer->getStringVal()) ) {
		lexer->nextToken();
	} else {
		setErrorEndPos(lexer->getPos());

		std::stringstream stream;
		stream << "syntax error, expect " <<  ident  <<  ", actual "  <<  tokenStringList.at(lexer->getToken());

		throw new ParserException(stream.str());
	}
}


