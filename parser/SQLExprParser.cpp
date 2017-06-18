#include <boost/assign/list_of.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/case_conv.hpp>

#include "SQLExprParser.h"
#include "SQLSelectParser.h"
#include "EOFParserException.h"
#include "IllegalArgumentException.h"


//std::string[] SQLExprParser::AGGREGATE_FUNCTIONS = { "AVG", "COUNT", "MAX", "MIN", "STDDEV", "SUM" };

const std::vector<std::string> SQLExprParser::AGGREGATE_FUNCTIONS = boost::assign::list_of("AVG")("COUNT")("MAX")("MIN")("STDDEV")("SUM");
//std::string[]  aggregateFunctions  = AGGREGATE_FUNCTIONS;

SQLExprParser::SQLExprParser(std::string &theSql) : super(theSql), aggregateFunctions (AGGREGATE_FUNCTIONS){
	//std::cout << __FILE__ << ": " << __LINE__ << ", in SQLExprParser::SQLExprParser, constructor 1, theSql is: " << theSql << std::endl;
	//super(sql);
}

SQLExprParser::SQLExprParser(Lexer *theLexer) : super(theLexer), aggregateFunctions (AGGREGATE_FUNCTIONS){
	//std::cout << __FILE__ << ": " << __LINE__ << ", in SQLExprParser::SQLExprParser, constructor 2 " << std::endl;
	//super(lexer);
}

SQLExprParser::~SQLExprParser() {

	//std::cout << __FILE__ << ": " << __LINE__ << ", in SQLExprParser::~SQLExprParser, destructor step 1" << std::endl;

	for(std::list<SQLHint *>::iterator it = myHints.begin(); it != myHints.end(); ++it) 
	{
		//std::cout << __FILE__ << ": " << __LINE__ << ", in SQLExprParser::~SQLExprParser, destructor step 1.1" << std::endl;
		delete *it; 
	}
	myHints.clear();


}
SQLExpr *SQLExprParser::getExpr() {
	//std::cout << __FILE__ << ": " << __LINE__ << ", in SQLExprParser::getExpr, step 1 " << std::endl;
	if (lexer->getToken() == STAR) {
		//std::cout << __FILE__ << ": " << __LINE__ << ", in SQLExprParser::getExpr, step 2 " << std::endl;
		lexer->nextToken();

		SQLExpr *expr = new SQLAllColumnExpr();

		if (lexer->getToken() == DOT) {
			//std::cout << __FILE__ << ": " << __LINE__ << ", in SQLExprParser::getExpr, step 2.1 " << std::endl;
			lexer->nextToken();
			accept(STAR);
			std::string star( "*");
			return new SQLPropertyExpr(expr, star);
		}
		//std::cout << __FILE__ << ": " << __LINE__ << ", in SQLExprParser::getExpr, step 2.2 " << std::endl;

		return expr;
	}

	//std::cout << __FILE__ << ": " << __LINE__ << ", in SQLExprParser::getExpr, step 3 " << std::endl;
	SQLExpr *expr = primary();
	//std::cout << __FILE__ << ": " << __LINE__ << ", in SQLExprParser::getExpr, step 4 " << std::endl;

	if (lexer->getToken() == COMMA) {
		return expr;
	}

	//std::cout << __FILE__ << ": " << __LINE__ << ", in SQLExprParser::getExpr, step 5 " << std::endl;
	expr = exprRest(expr);
	return expr;
	//std::cout << __FILE__ << ": " << __LINE__ << ", in SQLExprParser::getExpr, step 6 " << std::endl;
}

SQLExpr *SQLExprParser::exprRest(SQLExpr *expr) {
	expr = bitXorRest(expr);
	expr = multiplicativeRest(expr);
	expr = additiveRest(expr);
	expr = shiftRest(expr);
	expr = bitAndRest(expr);
	expr = bitOrRest(expr);
	expr = inRest(expr);
	expr = relationalRest(expr);
	expr = equalityRest(expr);
	expr = andRest(expr);
	expr = orRest(expr);

	return expr;
}

SQLExpr *SQLExprParser::bitXor() {
	SQLExpr *expr = primary();
	return bitXorRest(expr);
}

SQLExpr *SQLExprParser::bitXorRest(SQLExpr *expr) {
	if (lexer->getToken() == CARET) {
		lexer->nextToken();
		SQLExpr *rightExp = primary();
		expr = new SQLBinaryOpExpr(expr, &SQLBinaryOperator::BitwiseXor, rightExp);
		expr = bitXorRest(expr);
	}

	return expr;
}

SQLExpr *SQLExprParser::multiplicative() {
	SQLExpr *expr = bitXor();
	return multiplicativeRest(expr);
}

SQLExpr *SQLExprParser::multiplicativeRest(SQLExpr *expr) {
	if (lexer->getToken() == STAR) {
		lexer->nextToken();
		SQLExpr *rightExp = bitXor();
		expr = new SQLBinaryOpExpr(expr, &SQLBinaryOperator::Multiply, rightExp);
		expr = multiplicativeRest(expr);
	} else if (lexer->getToken() == SLASH) {
		lexer->nextToken();
		SQLExpr *rightExp = bitXor();
		expr = new SQLBinaryOpExpr(expr, &SQLBinaryOperator::Divide, rightExp);
		expr = multiplicativeRest(expr);
	} else if (lexer->getToken() == PERCENT) {
		lexer->nextToken();
		SQLExpr *rightExp = bitXor();
		expr = new SQLBinaryOpExpr(expr, &SQLBinaryOperator::Modulus, rightExp);
		expr = multiplicativeRest(expr);
	}
	return expr;
}

SQLExpr *SQLExprParser::primary() {
	SQLExpr *sqlExpr = NULL;

	Token tok = lexer->getToken();

	//std::cout <<  "++++\t" << __FILE__ << ": " << __LINE__ << ", in SQLExprParser::primary, step 1.1" <<   lexer->getToken() <<  " " << tokenStringList.at(lexer->getToken() ) <<  ": "  <<  lexer->getStringVal()  <<  ", pos "  <<  lexer->getPos()<< std::endl;
	switch (tok) {
		case LEFTPAREN:

			lexer->nextToken();
			sqlExpr = getExpr();

			if (lexer->getToken() == COMMA) {

				SQLListExpr *listExpr = new SQLListExpr();
				listExpr->getItems().push_back(sqlExpr);
				do {
					lexer->nextToken();
					listExpr->getItems().push_back(getExpr());
				} while (lexer->getToken() == COMMA);

				sqlExpr = listExpr;
			}
			accept(RPAREN);
			break;

		case TOKEN_INSERT:

			{
				lexer->nextToken();
				if (lexer->getToken() != LEFTPAREN) {
					throw new ParserException("syntax error");
				}
				std::string insert = ("INSERT");
				sqlExpr = new SQLIdentifierExpr(insert);
				break;

			}
		case IDENTIFIER:

			sqlExpr = new SQLIdentifierExpr(lexer->getStringVal());
			lexer->nextToken();
			break;

		case NEW:

			throw new ParserException("TODO");

		case LITERAL_INT:

			sqlExpr = new SQLIntegerExpr(lexer->integerValue());
			lexer->nextToken();
			break;

		case LITERAL_FLOAT:

			sqlExpr = new SQLNumberExpr(lexer->decimalValue());
			lexer->nextToken();
			break;

		case LITERAL_CHARS:

			sqlExpr = new SQLCharExpr(lexer->getStringVal());
			lexer->nextToken();
			break;

		case LITERAL_NCHARS:

			sqlExpr = new SQLNCharExpr(lexer->getStringVal());
			lexer->nextToken();
			break;

		case TOKEN_VARIANT:
			{
				SQLVariantRefExpr *varRefExpr = new SQLVariantRefExpr(lexer->getStringVal());
				lexer->nextToken();

				if (!(varRefExpr->getName()).compare(std::string("@")) && lexer->getToken() == LITERAL_CHARS) {

					std::string x = std::string("@'" )+ lexer->getStringVal() + std::string("'");
					varRefExpr->setName(x);
					lexer->nextToken();

				} else if (!(varRefExpr->getName()).compare("@@") && lexer->getToken() == LITERAL_CHARS) {

					std::string x = std::string("@@'") + lexer->getStringVal() + std::string("'");
					varRefExpr->setName(x);
					lexer->nextToken();

				}

				sqlExpr = varRefExpr;
				break;
			}

		case DEFAULT:
			{
				sqlExpr = new SQLDefaultExpr();
				lexer->nextToken();
				break;
			}

				case DUAL:
		case KEY:
		case DISTINCT:
		case LIMIT:
		case SCHEMA:
		case COLUMN:
		case IF:
		case END:
		case COMMENT:
		case COMPUTE:
		case ENABLE:
		case DISABLE:
		case INITIALLY:
		case SEQUENCE:
		case USER:
		case EXPLAIN:
		case WITH:
		case GRANT:
		case REPLACE:
		case INDEX:
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
		case FULL:
		case TO:
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

			sqlExpr = new SQLIdentifierExpr(lexer->getStringVal());
			lexer->nextToken();
			break;

		case CASE:

			{

				SQLCaseExpr *caseExpr = new SQLCaseExpr();
				lexer->nextToken();
				if (lexer->getToken() != WHEN) {
					caseExpr->setValueExpr(getExpr());
				}

				accept(WHEN);

				SQLExpr *testExpr = getExpr();
				accept(THEN);
				SQLExpr *valueExpr = getExpr();

				SQLCaseExpr_Item *caseItem = new SQLCaseExpr_Item(testExpr, valueExpr);
				caseExpr->addItem(caseItem);

				while (lexer->getToken() == WHEN) {
					lexer->nextToken();
					testExpr = getExpr();
					accept(THEN);
					valueExpr = getExpr();
					caseItem = new SQLCaseExpr_Item(testExpr, valueExpr);
					caseExpr->getItems().push_back(caseItem);
				}

				if (lexer->getToken() == ELSE) {
					lexer->nextToken();
					caseExpr->setElseExpr(getExpr());
				}

				accept(END);

				sqlExpr = caseExpr;
				break;


			}
		case EXISTS:

			lexer->nextToken();
			accept(LEFTPAREN);
			sqlExpr = new SQLExistsExpr(createSelectParser()->select());
			accept(RPAREN);
			break;

		case NOT:

			//std::cout <<  "++++\t" << __FILE__ << ": " << __LINE__ << ", in SQLExprParser::primary, case NOT::" <<   lexer->getToken() <<  " " << tokenStringList.at(lexer->getToken() ) <<  ": "  <<  lexer->getStringVal()  <<  ", pos "  <<  lexer->getPos()<< std::endl;
			lexer->nextToken();
			if (lexer->getToken() == EXISTS) {
				lexer->nextToken();
				accept(LEFTPAREN);
				sqlExpr = new SQLExistsExpr(createSelectParser()->select(), true);
				accept(RPAREN);

			} else if (lexer->getToken() == LEFTPAREN) {
				lexer->nextToken();

				SQLExpr *notTarget = getExpr();

				accept(RPAREN);
				notTarget = exprRest(notTarget);

				sqlExpr = new SQLNotExpr(notTarget);

				//std::cout <<  "++++\t" << __FILE__ << ": " << __LINE__ << ", in SQLExprParser::primary, case NOT 1.1::" <<   lexer->getToken() <<  " " << tokenStringList.at(lexer->getToken() ) <<  ": "  <<  lexer->getStringVal()  <<  ", pos "  <<  lexer->getPos()<< std::endl;
				return primaryRest(sqlExpr);
			} else {
				SQLExpr *restExpr = relational();
				sqlExpr = new SQLNotExpr(restExpr);
			}
			break;

		case TOKEN_SELECT:

			{

				SQLQueryExpr *queryExpr = new SQLQueryExpr(createSelectParser()->select());
				sqlExpr = queryExpr;
				break;
			}

		case CAST:

			{
				lexer->nextToken();
				accept(LEFTPAREN);

				SQLCastExpr *cast = new SQLCastExpr();
				cast->setExpr(getExpr());
				accept(AS);
				cast->setDataType(parseDataType());
				accept(RPAREN);

				sqlExpr = cast;
				break;


			}
		case SUB:

			lexer->nextToken();
			switch (lexer->getToken()) {

				case LITERAL_INT:
					{
						RNumber *integerValue = lexer->integerValue();

						//if (integerValue instanceof Integer) {

							//int intVal = ((Integer) integerValue).intValue();
							//if (intVal == Integer.MIN_VALUE) {
								//integerValue = Long.valueOf(((long) intVal) * -1);
							//} else {
								//integerValue = Integer.valueOf(intVal * -1);
							//}

						//} else if (integerValue instanceof Long) {

							//long longVal = ((Long) integerValue).longValue();
							//if (longVal == 2147483648L) {
								//integerValue = Integer.valueOf((int) (((long) longVal) * -1));
							//} else {
								//integerValue = Long.valueOf(longVal * -1);
							//}

						//} else {

							//integerValue = ((BigInteger) integerValue).negate();

						//}
						
						sqlExpr = new SQLIntegerExpr(integerValue);
						lexer->nextToken();
						break;
					}

				case LITERAL_FLOAT:

					//sqlExpr = new SQLNumberExpr(lexer->decimalValue().negate());
					sqlExpr = new SQLNumberExpr(lexer->decimalValue());
					lexer->nextToken();
					break;

				case IDENTIFIER: // 当负号后面为字段的情况

					sqlExpr = new SQLIdentifierExpr(lexer->getStringVal());
					//SQLIdentifierExpr* sqlExpr = dynamic_cast<SQLExpr *>(expr);
					sqlExpr = new SQLUnaryExpr(&SQLUnaryOperator::Negative, sqlExpr);
					lexer->nextToken();
					break;

				case QUES:

					{

						std::string q("?");
						sqlExpr = new SQLUnaryExpr(&SQLUnaryOperator::Negative, new SQLVariantRefExpr(q));
						lexer->nextToken();
						break;
					}

				case LEFTPAREN:

					lexer->nextToken();
					sqlExpr = getExpr();
					accept(RPAREN);
					sqlExpr = new SQLUnaryExpr(&SQLUnaryOperator::Negative, sqlExpr);
					break;

				default:
					throw new ParserException("TODO : " + lexer->getToken());
			}
			break;

		case PLUS:

			lexer->nextToken();
			switch (lexer->getToken()) {

				case LITERAL_INT:

					sqlExpr = new SQLIntegerExpr(lexer->integerValue());
					lexer->nextToken();
					break;

				case LITERAL_FLOAT:

					sqlExpr = new SQLNumberExpr(lexer->decimalValue());
					lexer->nextToken();
					break;

				case LEFTPAREN:

					lexer->nextToken();
					sqlExpr = getExpr();
					accept(RPAREN);
					sqlExpr = new SQLUnaryExpr(&SQLUnaryOperator::Plus, sqlExpr);
					break;

				default:
					throw new ParserException("TODO");
			}
			break;

		case TILDE:
			{

				lexer->nextToken();
				SQLExpr *unaryValueExpr = getExpr();
				SQLUnaryExpr *unary = new SQLUnaryExpr(&SQLUnaryOperator::Compl, unaryValueExpr);
				sqlExpr = unary;
				break;
			}


		case QUES:
			{
				lexer->nextToken();
				std::string q("?");
				SQLVariantRefExpr *quesVarRefExpr = new SQLVariantRefExpr(q);
				quesVarRefExpr->setIndex(lexer->nextVarIndex());
				sqlExpr = quesVarRefExpr;
				break;
			}


		case LEFT:
			{
				std::string l("LEFT");
				sqlExpr = new SQLIdentifierExpr(l);
				lexer->nextToken();
				break;
			}


		case RIGHT:
			{
				std::string r("RIGHT");
				sqlExpr = new SQLIdentifierExpr(r);
				lexer->nextToken();
				break;
			}


		case DATABASE:
			{
				std::string d("DATABASE");
				sqlExpr = new SQLIdentifierExpr(d);
				lexer->nextToken();
				break;
			}

		case LOCK:
			{
				std::string l("LOCK");
				sqlExpr = new SQLIdentifierExpr(l);
				lexer->nextToken();
				break;
			}

		case XNULL:

			sqlExpr = new SQLNullExpr();
			lexer->nextToken();
			break;

		case BANG:
			{
				lexer->nextToken();
				SQLExpr *bangExpr = getExpr();
				sqlExpr = new SQLUnaryExpr(&SQLUnaryOperator::Not, bangExpr);
				break;
			}

		case LITERAL_HEX:
			{
				std::string hex = lexer->hexString();
				sqlExpr = new SQLHexExpr(hex);
				lexer->nextToken();
				break;
			}

		case INTERVAL:

			sqlExpr = parseInterval();
			break;

		case COLON:
			{
				lexer->nextToken();
				if (lexer->getToken() == LITERAL_ALIAS) {
					std::string x = std::string(":\"") + lexer->getStringVal() + std::string("\"");
					sqlExpr = new SQLVariantRefExpr(x);
					lexer->nextToken();
				}
				break;
			}

		case ANY:
			{

				lexer->nextToken();
				if (lexer->getToken() == LEFTPAREN) {

					SQLAnyExpr *anyExpr = new SQLAnyExpr();

					accept(LEFTPAREN);
					SQLSelect *anySubQuery = createSelectParser()->select();
					anyExpr->setSubQuery(anySubQuery);
					accept(RPAREN);

					anySubQuery->setParent(anyExpr);

					sqlExpr = anyExpr;
				} else {

					std::string x ("ANY");
					sqlExpr = new SQLIdentifierExpr(x);
				}
				break;
			}
		case SOME:
			{

				lexer->nextToken();
				SQLSomeExpr *someExpr = new SQLSomeExpr();

				accept(LEFTPAREN);
				SQLSelect *someSubQuery = createSelectParser()->select();
				someExpr->setSubQuery(someSubQuery);
				accept(RPAREN);

				someSubQuery->setParent(someExpr);

				sqlExpr = someExpr;

				break;

			}
		case ALL:
			{
				lexer->nextToken();
				SQLAllExpr *allExpr = new SQLAllExpr();

				accept(LEFTPAREN);
				SQLSelect *allSubQuery = createSelectParser()->select();
				allExpr->setSubQuery(allSubQuery);
				accept(RPAREN);

				allSubQuery->setParent(allExpr);

				sqlExpr = allExpr;
				break;

			}
		case LITERAL_ALIAS:
			{
				std::string x = '"' + lexer->getStringVal() + '"';
				sqlExpr = new SQLIdentifierExpr(x);
				lexer->nextToken();
				break;
			}

		case ENDOFFILE:
			throw new EOFParserException();
		default:
			{

				std::stringstream stream;
				//stream << "syntax error, expect " <<  text <<  ", actual " <<  lexer->getToken();
				stream << "ERROR. token : " <<  tok <<  ", string : " << tokenStringList.at(tok)  <<  ", pos : " <<   lexer->getPos();

				throw new ParserException(stream.str());
				//throw new ParserException(std::string("ERROR. token : ") + tok + std::string(", pos : ") + lexer->pos());
			}
	}

	//std::cout <<  "++++\t" << __FILE__ << ": " << __LINE__ << ", in SQLExprParser::primary, step 2" <<   lexer->getToken() <<  " " << tokenStringList.at(lexer->getToken() ) <<  ": "  <<  lexer->getStringVal()  <<  ", pos "  <<  lexer->getPos()<< std::endl;
	return primaryRest(sqlExpr);
}

SQLExpr *SQLExprParser::parseInterval() {
	throw new ParserException("TODO");
}

SQLSelectParser *SQLExprParser::createSelectParser() {
	return new SQLSelectParser(this);
}

SQLExpr *SQLExprParser::primaryRest(SQLExpr *expr) {
	if (expr == NULL) {
		throw new IllegalArgumentException("expr");
	}

	//std::cout <<  "++++\t" << __FILE__ << ": " << __LINE__ << ", in SQLExprParser::primaryRest, step 1 " <<   lexer->getToken() <<  " " << tokenStringList.at(lexer->getToken() ) <<  ": "  <<  lexer->getStringVal()  <<  ", pos "  <<  lexer->getPos()<< std::endl;
	if (lexer->getToken() == OF) {
		//std::cout <<  "++++\t" << __FILE__ << ": " << __LINE__ << ", in SQLExprParser::primaryRest, step 1.1 " <<   lexer->getToken() <<  " " << tokenStringList.at(lexer->getToken() ) <<  ": "  <<  lexer->getStringVal()  <<  ", pos "  <<  lexer->getPos()<< std::endl;

		//if (expr instanceof SQLIdentifierExpr) {
		SQLIdentifierExpr* v = dynamic_cast<SQLIdentifierExpr *>(expr);
		if(v != 0) {

			std::string name = v->getName();

			if (boost::iequals(std::string("CURRENT"), name))
			{
				lexer->nextToken();
				SQLName *cursorName = getName();
				delete expr;
				return new SQLCurrentOfCursorExpr(cursorName);
			}

			//if (std::string("CURRENT").equalsIgnoreCase(name)) {
			//}
		}

	}

	if (lexer->getToken() == DOT) {
		//std::cout <<  "++++\t" << __FILE__ << ": " << __LINE__ << ", in SQLExprParser::primaryRest, step 1.2 " <<   lexer->getToken() <<  " " << tokenStringList.at(lexer->getToken() ) <<  ": "  <<  lexer->getStringVal()  <<  ", pos "  <<  lexer->getPos()<< std::endl;
		lexer->nextToken();

		//if (expr instanceof SQLCharExpr) {

		SQLCharExpr* v = dynamic_cast<SQLCharExpr *>(expr);
		if(v != 0) {
			std::string text = v->getText();
			SQLExpr * x = expr;
			delete expr;
			expr = new SQLIdentifierExpr(text);

		}

		expr = dotRest(expr);
		//std::cout <<  "++++\t" << __FILE__ << ": " << __LINE__ << ", in SQLExprParser::primaryRest, step 1.3 " <<   lexer->getToken() <<  " " << tokenStringList.at(lexer->getToken() ) <<  ": "  <<  lexer->getStringVal()  <<  ", pos "  <<  lexer->getPos()<< std::endl;
		return primaryRest(expr);
	} else {
		//std::cout <<  "++++\t" << __FILE__ << ": " << __LINE__ << ", in SQLExprParser::primaryRest, step 1.4 " <<   lexer->getToken() <<  " " << tokenStringList.at(lexer->getToken() ) <<  ": "  <<  lexer->getStringVal()  <<  ", pos "  <<  lexer->getPos()<< std::endl;
		if (lexer->getToken() == LEFTPAREN) {
			//std::cout <<  "++++\t" << __FILE__ << ": " << __LINE__ << ", in SQLExprParser::primaryRest, step 1.5 " <<   lexer->getToken() <<  " " << tokenStringList.at(lexer->getToken() ) <<  ": "  <<  lexer->getStringVal()  <<  ", pos "  <<  lexer->getPos()<< std::endl;
			return methodRest(expr, true);
		}
	}

	//std::cout <<  "++++\t" << __FILE__ << ": " << __LINE__ << ", in SQLExprParser::primaryRest, step 2 " <<   lexer->getToken() <<  " " << tokenStringList.at(lexer->getToken() ) <<  ": "  <<  lexer->getStringVal()  <<  ", pos "  <<  lexer->getPos()<< std::endl;
	return expr;
}

SQLExpr *SQLExprParser::methodRest(SQLExpr *expr, bool acceptLEFTPAREN) {

	//std::cout <<  "++++\t" << __FILE__ << ": " << __LINE__ << ", in SQLExprParser::methodRest, step 1 " <<   lexer->getToken() <<  " " << tokenStringList.at(lexer->getToken() ) <<  ": "  <<  lexer->getStringVal()  <<  ", pos "  <<  lexer->getPos()<< std::endl;
	if (acceptLEFTPAREN) {
		accept(LEFTPAREN);
	}


	SQLName* n = dynamic_cast<SQLName *>(expr);
	SQLDefaultExpr* d = dynamic_cast<SQLDefaultExpr *>(expr);
	//std::cout <<  "++++\t" << __FILE__ << ": " << __LINE__ << ", in SQLExprParser::methodRest, step 2 " <<   lexer->getToken() <<  " " << tokenStringList.at(lexer->getToken() ) <<  ": "  <<  lexer->getStringVal()  <<  ", pos "  <<  lexer->getPos()<< std::endl;
	//if (expr instanceof SQLName || expr instanceof SQLDefaultExpr) {
	if(n != 0 || d != 0) {
		//std::cout <<  "++++\t" << __FILE__ << ": " << __LINE__ << ", in SQLExprParser::methodRest, step 3 " <<   lexer->getToken() <<  " " << tokenStringList.at(lexer->getToken() ) <<  ": "  <<  lexer->getStringVal()  <<  ", pos "  <<  lexer->getPos()<< std::endl;
		std::string methodName;

		SQLMethodInvokeExpr *methodInvokeExpr;
		methodInvokeExpr = NULL;
		SQLObject *theExpr;

		SQLPropertyExpr* p = dynamic_cast<SQLPropertyExpr *>(expr);

		//if (expr instanceof SQLPropertyExpr) {
		if(p != 0 ) {
			//std::cout <<  "++++\t" << __FILE__ << ": " << __LINE__ << ", in SQLExprParser::methodRest, step 4 " <<   lexer->getToken() <<  " " << tokenStringList.at(lexer->getToken() ) <<  ": "  <<  lexer->getStringVal()  <<  ", pos "  <<  lexer->getPos()<< std::endl;
			methodName = p->getName();
			methodInvokeExpr = new SQLMethodInvokeExpr(methodName);

			//std::cout << "\t\t" <<  __FILE__ << ": " << __LINE__ << ", SQLExprParser::methodRest, occurs 1" << std::endl;

			methodInvokeExpr->setOwner(p->getOwner());
			//delete p;
		} else {
			methodName = expr->toString();
			//std::cout <<  "++++\t" << __FILE__ << ": " << __LINE__ << ", in SQLExprParser::methodRest, step 5 " <<   lexer->getToken() <<  " " << tokenStringList.at(lexer->getToken() ) <<  ": "  <<  lexer->getStringVal()  <<  ", pos "  <<  lexer->getPos()<< ", methodName is: " << methodName <<  std::endl;
			methodInvokeExpr = new SQLMethodInvokeExpr(methodName);
			delete n;
		}

		if (isAggreateFunction(methodName)) {
			//std::cout <<  "++++\t" << __FILE__ << ": " << __LINE__ << ", in SQLExprParser::methodRest, step 6 " <<   lexer->getToken() <<  " " << tokenStringList.at(lexer->getToken() ) <<  ": "  <<  lexer->getStringVal()  <<  ", pos "  <<  lexer->getPos()<< std::endl;
			SQLAggregateExpr *aggregateExpr = parseAggregateExpr(methodName);

			// here the methodInvokeExpr created above will be lost.
			if (methodInvokeExpr != NULL)
			{
				delete methodInvokeExpr;
			}

			return aggregateExpr;
		}

		if (lexer->getToken() != RPAREN) {

			//std::cout <<  "++++\t" << __FILE__ << ": " << __LINE__ << ", in SQLExprParser::methodRest, step 7 " <<   lexer->getToken() <<  " " << tokenStringList.at(lexer->getToken() ) <<  ": "  <<  lexer->getStringVal()  <<  ", pos "  <<  lexer->getPos()<< std::endl;
			theExpr = methodInvokeExpr;
			exprList(methodInvokeExpr->getParameters(), theExpr);
		}

		accept(RPAREN);

		//std::cout <<  "++++\t" << __FILE__ << ": " << __LINE__ << ", in SQLExprParser::methodRest, step 8 " <<   lexer->getToken() <<  " " << tokenStringList.at(lexer->getToken() ) <<  ": "  <<  lexer->getStringVal()  <<  ", pos "  <<  lexer->getPos()<< std::endl;
		return primaryRest(methodInvokeExpr);
	}
	throw new ParserException(std::string("not support token:" ) + tokenStringList.at(lexer->getToken()) );
}

SQLExpr *SQLExprParser::dotRest(SQLExpr *expr) {
	if (lexer->getToken() == STAR) {
		lexer->nextToken();

		std::string star( "*");
		expr = new SQLPropertyExpr(expr, star);
	} else {
		std::string name;

		if (lexer->getToken() == IDENTIFIER || lexer->getToken() == LITERAL_CHARS
				|| lexer->getToken() == LITERAL_ALIAS) {

			name = lexer->getStringVal();
			lexer->nextToken();

		} else if (lexer->getKeywods()->containsValue(lexer->getToken())) {

			name = lexer->getStringVal();
			lexer->nextToken();

		} else {

			throw new ParserException("error : " + lexer->getStringVal());
		}

		if (lexer->getToken() == LEFTPAREN) {

			lexer->nextToken();

			SQLMethodInvokeExpr *methodInvokeExpr = new SQLMethodInvokeExpr(name);
			//std::cout << "\t\t" <<  __FILE__ << ": " << __LINE__ << ", SQLExprParser::methodRest, occurs 2" << std::endl;
			methodInvokeExpr->setOwner(expr);

			if (lexer->getToken() == RPAREN) {
				lexer->nextToken();
			} else {

				if (lexer->getToken() == PLUS) {
					std::string plus1("*");
					methodInvokeExpr->addParameter(new SQLIdentifierExpr(plus1));
					lexer->nextToken();

				} else {

					exprList(methodInvokeExpr->getParameters(), methodInvokeExpr);

				}

				accept(RPAREN);
			}
			expr = methodInvokeExpr;
		} else {
			expr = new SQLPropertyExpr(expr, name);
		}
	}

	expr = primaryRest(expr);
	return expr;
}

SQLExpr *SQLExprParser::groupComparisionRest(SQLExpr *expr) {
	return expr;
}

void SQLExprParser::getNames(std::list<SQLName *> & exprCol) {
	getNames(exprCol, NULL);
}

void SQLExprParser::getNames(std::list<SQLName *> &exprCol, SQLObject *parent) {
	if (lexer->getToken() == RBRACE) {
		return;
	}

	if (lexer->getToken() == ENDOFFILE) {
		return;
	}

	SQLName *name = getName();
	name->setParent(parent);
	exprCol.push_back(name);

	while (lexer->getToken() == COMMA) {
		lexer->nextToken();

		name = getName();
		name->setParent(parent);
		exprCol.push_back(name);
	}
}

void SQLExprParser::exprList(std::list<SQLExpr *> & exprCol) {
	exprList(exprCol, NULL);
}

void SQLExprParser::exprList(std::list<SQLExpr *> & exprCol, SQLObject *parent) {
	if (lexer->getToken() == RPAREN || lexer->getToken() == RBRACKET) {
		return;
	}

	if (lexer->getToken() == ENDOFFILE) {
		return;
	}

	SQLExpr *expr = getExpr();
	expr->setParent(parent);
	exprCol.push_back(expr);

	while (lexer->getToken() == COMMA) {

		lexer->nextToken();
		expr = getExpr();
		expr->setParent(parent);
		exprCol.push_back(expr);

	}
}

SQLName *SQLExprParser::getName() {

	std::string identName;

	if (lexer->getToken() == LITERAL_ALIAS) {

		identName = std::string("\"") + lexer->getStringVal() + std::string("\"");
		lexer->nextToken();

	} else if (lexer->getToken() == IDENTIFIER) {

		identName = lexer->getStringVal();

		lexer->nextToken();

	} else if (lexer->getToken() == LITERAL_CHARS) {

		identName = std::string("\'") + lexer->getStringVal() + std::string("\'");
		lexer->nextToken();

	} else if (lexer->getToken() == TOKEN_VARIANT) {

		identName = lexer->getStringVal();
		lexer->nextToken();

	} else {

		switch (lexer->getToken()) {

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
				identName = lexer->getStringVal();
				lexer->nextToken();
				break;
			default:

				std::stringstream stream;
				stream << "error  " << __FILE__ << ": " << __LINE__ << ": " <<  lexer->getToken() <<  ": " << tokenStringList.at(lexer->getToken() )   <<  ": stringVal is: " <<  lexer->getStringVal();

				//std::cout << "===>\t" <<  stream.str() << std::endl;
				throw new ParserException(stream.str());
				//throw new ParserException("error " + lexer->getToken());
		}
	}

	SQLName *name = new SQLIdentifierExpr(identName);

	name = nameRest(name);

	return name;
}

SQLName *SQLExprParser::nameRest(SQLName *name) {
	if (lexer->getToken() == DOT) {
		lexer->nextToken();

		if (lexer->getToken() == KEY) {
			std::string key1 ("KEY");
			name = new SQLPropertyExpr(name, key1);
			lexer->nextToken();
			return name;
		}

		if (lexer->getToken() != LITERAL_ALIAS && lexer->getToken() != IDENTIFIER
				&& (!lexer->getKeywods()->containsValue(lexer->getToken()))) {

			throw new ParserException(std::string("error, ") + tokenStringList.at(lexer->getToken()) );
		}

		if (lexer->getToken() == LITERAL_ALIAS) {
			std::string x = std::string("\"") + lexer->getStringVal() + std::string("\"");
			name = new SQLPropertyExpr(name, x);
		} else {
			name = new SQLPropertyExpr(name, lexer->getStringVal());
		}

		lexer->nextToken();
		name = nameRest(name);
	}

	return name;
}

bool SQLExprParser::isAggreateFunction(std::string &word) {

	//for (int i = 0; i < aggregateFunctions.length; ++i) {
		//if (aggregateFunctions[i].compareToIgnoreCase(word) == 0) {
			//return true;
		//}
	//}
/*	
	std::string newstr = boost::to_upper_copy(word);
	if(binary_search(aggregateFunctions.begin(), aggregateFunctions.end(), newstr)){
	     // Find the item
		 return true;
	}
*/
	
	for (std::vector<std::string>::const_iterator it = aggregateFunctions.begin(); it != aggregateFunctions.end(); ++it)
	{
		if (boost::iequals((*it), word))
		{
			return true;
		}
	}

	return false;
}

SQLAggregateExpr *SQLExprParser::parseAggregateExpr(std::string &methodName) {
	//methodName = methodName.toUpperCase();
	boost::algorithm::to_upper(methodName);

	SQLAggregateExpr *aggregateExpr;

	if (lexer->getToken() == ALL) {

		aggregateExpr = new SQLAggregateExpr(methodName, SQLAggregateExpr::ALL);
		lexer->nextToken();

	} else if (lexer->getToken() == DISTINCT) {

		aggregateExpr = new SQLAggregateExpr(methodName, SQLAggregateExpr::DISTINCT);
		lexer->nextToken();

	} else {

		aggregateExpr = new SQLAggregateExpr(methodName);
	}

	exprList(aggregateExpr->getArguments(), aggregateExpr);

	parseAggregateExprRest(aggregateExpr);

	accept(RPAREN);

	if (lexer->getToken() == OVER) {

		//std::cout <<  "++++\t" << __FILE__ << ": " << __LINE__ << ", in SQLExprParser::parseAggregateExpr, for over" <<   lexer->getToken() <<  " " << tokenStringList.at(lexer->getToken() ) <<  ": "  <<  lexer->getStringVal()  <<  ", pos "  <<  lexer->getPos()<< std::endl;
		lexer->nextToken();
		SQLOver *over = new SQLOver();
		accept(LEFTPAREN);

		if (lexer->getToken() == PARTITION || identifierEquals("PARTITION")) {
			lexer->nextToken();
			accept(BY);

			if (lexer->getToken() == (LEFTPAREN)) {
				lexer->nextToken();
				exprList(over->getPartitionBy());
				accept(RPAREN);
			} else {
				exprList(over->getPartitionBy());
			}
		}

		over->setOrderBy(parseOrderBy());

		accept(RPAREN);
		aggregateExpr->setOver(over);

	}

	return aggregateExpr;
}

SQLAggregateExpr *SQLExprParser::parseAggregateExprRest(SQLAggregateExpr *aggregateExpr) {
	return aggregateExpr;
}

SQLOrderBy *SQLExprParser::parseOrderBy() {
	//std::cout <<  "++++\t" << __FILE__ << ": " << __LINE__ << ", in SQLExprParser::parseOrderBy, step 1 " <<   lexer->getToken() <<  " " << tokenStringList.at(lexer->getToken() ) <<  ": "  <<  lexer->getStringVal()  <<  ", pos "  <<  lexer->getPos()<< std::endl;
	if (lexer->getToken() == ORDER) {
		//std::cout <<  "++++\t" << __FILE__ << ": " << __LINE__ << ", in SQLExprParser::parseOrderBy, step 1.1 " <<   lexer->getToken() <<  " " << tokenStringList.at(lexer->getToken() ) <<  ": "  <<  lexer->getStringVal()  <<  ", pos "  <<  lexer->getPos()<< std::endl;
		SQLOrderBy *orderBy = new SQLOrderBy();

		lexer->nextToken();

		accept(BY);

		orderBy->getItems().push_back(parseSelectOrderByItem());

		while (lexer->getToken() == COMMA) {

			lexer->nextToken();
			orderBy->getItems().push_back(parseSelectOrderByItem());
		}

		//std::cout <<  "++++\t" << __FILE__ << ": " << __LINE__ << ", in SQLExprParser::parseOrderBy, step 1.2 " <<   lexer->getToken() <<  " " << tokenStringList.at(lexer->getToken() ) <<  ": "  <<  lexer->getStringVal()  <<  ", pos "  <<  lexer->getPos()<< std::endl;
		return orderBy;
	}

	//std::cout <<  "++++\t" << __FILE__ << ": " << __LINE__ << ", in SQLExprParser::parseOrderBy, step 2 " <<   lexer->getToken() <<  " " << tokenStringList.at(lexer->getToken() ) <<  ": "  <<  lexer->getStringVal()  <<  ", pos "  <<  lexer->getPos()<< std::endl;
	return NULL;
}

SQLSelectOrderByItem *SQLExprParser::parseSelectOrderByItem() {
	//return NULL;

	//std::cout <<  "++++\t" << __FILE__ << ": " << __LINE__ << ", in SQLExprParser::parseSelectOrderByItem, step 1 " <<   lexer->getToken() <<  " " << tokenStringList.at(lexer->getToken() ) <<  ": "  <<  lexer->getStringVal()  <<  ", pos "  <<  lexer->getPos()<< std::endl;
	SQLSelectOrderByItem *item = new SQLSelectOrderByItem();

	SQLExpr *x = getExpr();

	item->setExpr(x);

	//std::cout <<  "++++\t" << __FILE__ << ": " << __LINE__ << ", in SQLExprParser::parseSelectOrderByItem, step 2 " <<   lexer->getToken() <<  " " << tokenStringList.at(lexer->getToken() ) <<  ": "  <<  lexer->getStringVal()  <<  ", pos "  <<  lexer->getPos()<< std::endl;
	if (lexer->getToken() == ASC) {

		lexer->nextToken();

		item->setType(&SQLOrderingSpecification::ASC);

	} else if (lexer->getToken() == DESC) {

		lexer->nextToken();
		item->setType(&SQLOrderingSpecification::DESC);
	}

	return item;
}

SQLExpr *SQLExprParser::bitAnd() {
	SQLExpr *expr = shift();
	return bitAndRest(expr);
}

SQLExpr *SQLExprParser::bitAndRest(SQLExpr *expr) {

	while (lexer->getToken() == AMP) {
		lexer->nextToken();
		SQLExpr *rightExp = shift();
		expr = new SQLBinaryOpExpr(expr, &SQLBinaryOperator::BitwiseAnd, rightExp);
	}
	return expr;
}

SQLExpr *SQLExprParser::bitOr() {
	SQLExpr *expr = bitAnd();
	return bitOrRest(expr);
}

SQLExpr *SQLExprParser::bitOrRest(SQLExpr *expr) {
	if (lexer->getToken() == BAR) {
		lexer->nextToken();
		SQLExpr *rightExp = bitAnd();
		expr = new SQLBinaryOpExpr(expr, &SQLBinaryOperator::BitwiseOr, rightExp);
		expr = bitAndRest(expr);
	}
	return expr;
}

SQLExpr *SQLExprParser::equality() {
	SQLExpr *expr = bitOr();
	return equalityRest(expr);
}

SQLExpr *SQLExprParser::equalityRest(SQLExpr *expr) {

	SQLExpr *rightExp;
	if (lexer->getToken() == EQ) {
		lexer->nextToken();
		try {
			rightExp = bitOr();
		} catch (EOFParserException e) {

			std::stringstream stream;
			stream << "EOF, "  <<  expr <<  "="  <<   e.what();
			throw new ParserException(stream.str());
		}
		rightExp = equalityRest(rightExp);

		expr = new SQLBinaryOpExpr(expr, &SQLBinaryOperator::Equality, rightExp);
	} else if (lexer->getToken() == BANGEQ) {
		lexer->nextToken();
		rightExp = bitOr();

		rightExp = equalityRest(rightExp);

		expr = new SQLBinaryOpExpr(expr, &SQLBinaryOperator::NotEqual, rightExp);
	} else if (lexer->getToken() == COLONEQ) {
		lexer->nextToken();
		rightExp = getExpr();
		expr = new SQLBinaryOpExpr(expr, &SQLBinaryOperator::Assignment, rightExp);
	}

	return expr;
}

SQLExpr *SQLExprParser::inRest(SQLExpr *expr) {

	if (lexer->getToken() == TOKEN_IN) {
		lexer->nextToken();

		SQLInListExpr *inListExpr = new SQLInListExpr(expr);
		if (lexer->getToken() == LEFTPAREN) {

			lexer->nextToken();
			exprList(inListExpr->getTargetList(), inListExpr);
			accept(RPAREN);
			expr = inListExpr;

		} else {

			SQLExpr *itemExpr = primary();
			itemExpr->setParent(inListExpr);
			inListExpr->getTargetList().push_back(itemExpr);
		}

		expr = inListExpr;

		if (inListExpr->getTargetList().size() == 1) {
			//SQLExpr targetExpr = (inListExpr->getTargetList()).get(0);
			SQLExpr *targetExpr = (inListExpr->getTargetList()).front();

			SQLQueryExpr* q = dynamic_cast<SQLQueryExpr *>(targetExpr);
			//if (targetExpr instanceof SQLQueryExpr) {
			if (q != 0) {

				SQLInSubQueryExpr *inSubQueryExpr = new SQLInSubQueryExpr();
				inSubQueryExpr->setExpr(inListExpr->getExpr());

				inSubQueryExpr->setSubQuery(q->getSubQuery());
				expr = inSubQueryExpr;

			}
		}
	}

	return expr;
}

SQLExpr *SQLExprParser::additive() {
	SQLExpr *expr = multiplicative();
	return additiveRest(expr);
}

SQLExpr *SQLExprParser::additiveRest(SQLExpr *expr) {

	if (lexer->getToken() == PLUS) {

		lexer->nextToken();
		SQLExpr *rightExp = multiplicative();

		expr = new SQLBinaryOpExpr(expr, &SQLBinaryOperator::Add, rightExp);
		expr = additiveRest(expr);

	} else if (lexer->getToken() == BARBAR) {

		lexer->nextToken();
		SQLExpr *rightExp = multiplicative();
		expr = new SQLBinaryOpExpr(expr, &SQLBinaryOperator::Concat, rightExp);
		expr = additiveRest(expr);

	} else if (lexer->getToken() == SUB) {

		lexer->nextToken();
		SQLExpr *rightExp = multiplicative();

		expr = new SQLBinaryOpExpr(expr, &SQLBinaryOperator::Subtract, rightExp);
		expr = additiveRest(expr);
	}

	return expr;
}

SQLExpr *SQLExprParser::shift() {
	SQLExpr *expr = additive();
	return shiftRest(expr);
}

SQLExpr *SQLExprParser::shiftRest(SQLExpr *expr) {

	if (lexer->getToken() == LTLT) {

		lexer->nextToken();
		SQLExpr *rightExp = additive();

		expr = new SQLBinaryOpExpr(expr, &SQLBinaryOperator::LeftShift, rightExp);
		expr = shiftRest(expr);

	} else if (lexer->getToken() == GTGT) {

		lexer->nextToken();
		SQLExpr *rightExp = additive();

		expr = new SQLBinaryOpExpr(expr, &SQLBinaryOperator::RightShift, rightExp);
		expr = shiftRest(expr);
	}

	return expr;
}

SQLExpr *SQLExprParser::getAnd() {
	SQLExpr *expr = relational();
	return andRest(expr);
}

SQLExpr *SQLExprParser::andRest(SQLExpr *expr) {
	for (;;) {

		if (lexer->getToken() == AND || lexer->getToken() == AMPAMP) {
			lexer->nextToken();
			SQLExpr *rightExp = relational();

			expr = new SQLBinaryOpExpr(expr, &SQLBinaryOperator::BooleanAnd, rightExp);
		} else {
			break;
		}
	}

	return expr;
}

SQLExpr *SQLExprParser::getOr() {
	SQLExpr *expr = getAnd();
	return orRest(expr);
}

SQLExpr *SQLExprParser::orRest(SQLExpr *expr) {

	for (;;) {
		if (lexer->getToken() == OR) {
			lexer->nextToken();
			SQLExpr *rightExp = getAnd();

			expr = new SQLBinaryOpExpr(expr, &SQLBinaryOperator::BooleanOr, rightExp);
		} else if (lexer->getToken() == XOR) {
			lexer->nextToken();
			SQLExpr *rightExp = getAnd();

			expr = new SQLBinaryOpExpr(expr, &SQLBinaryOperator::BooleanXor, rightExp);
		} else {
			break;
		}
	}

	return expr;
}

SQLExpr *SQLExprParser::relational() {
	SQLExpr *expr = equality();

	return relationalRest(expr);
}

SQLExpr *SQLExprParser::relationalRest(SQLExpr *expr) {
	SQLExpr *rightExp;

	if (lexer->getToken() == LT) {
		SQLBinaryOperator *op = &SQLBinaryOperator::LessThan;

		lexer->nextToken();
		if (lexer->getToken() == EQ) {
			lexer->nextToken();
			op = &SQLBinaryOperator::LessThanOrEqual;
		}

		rightExp = bitOr();
		expr = new SQLBinaryOpExpr(expr, op, rightExp);
		// expr = relationalRest(expr);
	} else if (lexer->getToken() == LTEQ) {
		lexer->nextToken();
		rightExp = bitOr();

		// rightExp = relationalRest(rightExp);

		expr = new SQLBinaryOpExpr(expr, &SQLBinaryOperator::LessThanOrEqual, rightExp);
	} else if (lexer->getToken() == LTEQGT) {
		lexer->nextToken();
		rightExp = bitOr();

		expr = new SQLBinaryOpExpr(expr, &SQLBinaryOperator::LessThanOrEqualOrGreaterThan, rightExp);
	} else if (lexer->getToken() == GT) {
		SQLBinaryOperator *op = &SQLBinaryOperator::GreaterThan;

		lexer->nextToken();

		if (lexer->getToken() == EQ) {
			lexer->nextToken();
			op = &SQLBinaryOperator::GreaterThanOrEqual;
		}

		rightExp = bitOr();

		expr = new SQLBinaryOpExpr(expr, op, rightExp);

	} else if (lexer->getToken() == GTEQ) {

		lexer->nextToken();
		rightExp = bitOr();

		// rightExp = relationalRest(rightExp);

		expr = new SQLBinaryOpExpr(expr, &SQLBinaryOperator::GreaterThanOrEqual, rightExp);
	} else if (lexer->getToken() == BANGLT) {

		lexer->nextToken();
		rightExp = bitOr();

		// rightExp = relationalRest(rightExp);

		expr = new SQLBinaryOpExpr(expr, &SQLBinaryOperator::NotLessThan, rightExp);
	} else if (lexer->getToken() == BANGGT) {

		lexer->nextToken();
		rightExp = bitOr();

		rightExp = relationalRest(rightExp);

		expr = new SQLBinaryOpExpr(expr, &SQLBinaryOperator::NotGreaterThan, rightExp);

	} else if (lexer->getToken() == LTGT) {

		lexer->nextToken();
		rightExp = bitOr();

		// rightExp = relationalRest(rightExp);

		expr = new SQLBinaryOpExpr(expr, &SQLBinaryOperator::LessThanOrGreater, rightExp);
	} else if (lexer->getToken() == LIKE) {
		lexer->nextToken();
		rightExp = bitOr();

		// rightExp = relationalRest(rightExp);

		expr = new SQLBinaryOpExpr(expr, &SQLBinaryOperator::Like, rightExp);

		if (lexer->getToken() == ESCAPE) {

			lexer->nextToken();
			rightExp = primary();
			expr = new SQLBinaryOpExpr(expr, &SQLBinaryOperator::Escape, rightExp);
		}
	} else if (lexer->getToken() == (NOT)) {

		lexer->nextToken();
		expr = notRationalRest(expr);

	} else if (lexer->getToken() == (BETWEEN)) {

		lexer->nextToken();
		SQLExpr *beginExpr = bitOr();
		accept(AND);
		SQLExpr *endExpr = bitOr();
		expr = new SQLBetweenExpr(expr, beginExpr, endExpr);

	} else if (lexer->getToken() == (IS)) {

		lexer->nextToken();

		if (lexer->getToken() == (NOT)) {

			lexer->nextToken();
			SQLExpr *rightExpr = primary();
			expr = new SQLBinaryOpExpr(expr, &SQLBinaryOperator::IsNot, rightExpr);

		} else {
			SQLExpr *rightExpr = primary();
			expr = new SQLBinaryOpExpr(expr, &SQLBinaryOperator::Is, rightExpr);
		}
	} else if (lexer->getToken() == TOKEN_IN) {
		expr = inRest(expr);
	}

	return expr;
}

SQLExpr *SQLExprParser::notRationalRest(SQLExpr *expr) {

	if (lexer->getToken() == (LIKE)) {
		lexer->nextToken();

		SQLExpr *rightExp = equality();

		rightExp = relationalRest(rightExp);

		expr = new SQLBinaryOpExpr(expr, &SQLBinaryOperator::NotLike, rightExp);

		if (lexer->getToken() == ESCAPE) {
			lexer->nextToken();
			rightExp = getExpr();
			expr = new SQLBinaryOpExpr(expr, &SQLBinaryOperator::Escape, rightExp);
		}
	} else if (lexer->getToken() == TOKEN_IN) {

		lexer->nextToken();
		accept(LEFTPAREN);

		SQLInListExpr *inListExpr = new SQLInListExpr(expr, true);
		exprList(inListExpr->getTargetList(), inListExpr);
		expr = inListExpr;

		accept(RPAREN);

		if (inListExpr->getTargetList().size() == 1) {

			//SQLExpr targetExpr = inListExpr.getTargetList().get(0);
			SQLExpr *targetExpr = inListExpr->getTargetList().front();

			SQLQueryExpr* v = dynamic_cast<SQLQueryExpr *>(targetExpr);

			//if (targetExpr instanceof SQLQueryExpr) {
			if (v != 0 ) {

				SQLInSubQueryExpr *inSubQueryExpr = new SQLInSubQueryExpr();
				inSubQueryExpr->setNot(true);
				inSubQueryExpr->setExpr(inListExpr->getExpr());
				inSubQueryExpr->setSubQuery(v->getSubQuery());
				expr = inSubQueryExpr;

			}
		}

		expr = relationalRest(expr);
		return expr;
	} else if (lexer->getToken() == (BETWEEN)) {
		lexer->nextToken();
		SQLExpr *beginExpr = bitOr();
		accept(AND);
		SQLExpr *endExpr = bitOr();

		expr = new SQLBetweenExpr(expr, true, beginExpr, endExpr);

		return expr;
	} else {
		throw new ParserException("TODO " + lexer->getToken());
	}
	return expr;
}

SQLDataType *SQLExprParser::parseDataType() {

	if (lexer->getToken() == DEFAULT || lexer->getToken() == NOT || lexer->getToken() == XNULL) {
		return NULL;
	}

	SQLName *typeExpr = getName();
	std::string typeName = typeExpr->toString();

	if (isCharType(typeName)) {

		SQLCharactorDataType *charType = new SQLCharactorDataType(typeName);

		if (lexer->getToken() == LEFTPAREN) {
			lexer->nextToken();
			SQLExpr *arg = getExpr();
			arg->setParent(charType);
			charType->getArguments().push_back(arg);
			accept(RPAREN);
		}

		return parseCharTypeRest(charType);
	}

	if (boost::iequals(std::string("character"), typeName) && boost::iequals(std::string ("varying"), lexer->getStringVal()) )
	{
		typeName += ' ' + lexer->getStringVal();
		lexer->nextToken();
	}

	//if ("character".equalsIgnoreCase(typeName) && "varying".equalsIgnoreCase(lexer->getStringVal())) {
	//}

	SQLDataType *dataType = new SQLDataTypeImpl(typeName);
	return parseDataTypeRest(dataType);
}

SQLDataType *SQLExprParser::parseDataTypeRest(SQLDataType *dataType) {
	if (lexer->getToken() == LEFTPAREN) {
		lexer->nextToken();

		SQLDataTypeImpl* v = dynamic_cast<SQLDataTypeImpl *>(dataType);
		if (v != NULL)
		{
			exprList(v->getArguments(), dataType);
			accept(RPAREN);
		}
	}

	return dataType;
}

bool SQLExprParser::isCharType(std::string &dataTypeName) {
	return 
	boost::iequals(std::string("char"), dataTypeName)
	|| boost::iequals(std::string("varchar"), dataTypeName)
	|| boost::iequals (std::string("nchar"), dataTypeName)
	|| boost::iequals(std::string("nvarchar"), dataTypeName)
	|| boost::iequals(std::string("tinytext"), dataTypeName)
	|| boost::iequals(std::string("text"), dataTypeName)
	|| boost::iequals (std::string("mediumtext"), dataTypeName)
	|| boost::iequals (std::string("longtext"), dataTypeName)
	;
		
		//"char".equalsIgnoreCase(dataTypeName) //
		//|| "varchar".equalsIgnoreCase(dataTypeName)
		//|| "nchar".equalsIgnoreCase(dataTypeName)
		//|| "nvarchar".equalsIgnoreCase(dataTypeName)
		//|| "tinytext".equalsIgnoreCase(dataTypeName)
		//|| "text".equalsIgnoreCase(dataTypeName)
		//|| "mediumtext".equalsIgnoreCase(dataTypeName)
		//|| "longtext".equalsIgnoreCase(dataTypeName)
		////
		//;

}

SQLDataType *SQLExprParser::parseCharTypeRest(SQLCharactorDataType *charType) {
	if (identifierEquals("CHARACTER")) {
		lexer->nextToken();

		accept(SET);

		if (lexer->getToken() != IDENTIFIER && lexer->getToken() != LITERAL_CHARS) {
			throw new ParserException();
		}
		charType->setCharSetName(lexer->getStringVal());
		lexer->nextToken();

		if (lexer->getToken() == IDENTIFIER) {

	
			if (boost::iequals(lexer->getStringVal(), std::string("COLLATE"))) {
				lexer->nextToken();

				if (lexer->getToken() != IDENTIFIER) {
					throw new ParserException();
				}
				charType->setCollate(lexer->getStringVal());
				lexer->nextToken();
			}
		}
	}
	return charType;
}

void SQLExprParser::accept(Token token) {
	if (lexer->getToken() == token) {
		lexer->nextToken();
	} else {

		throw new ParserException(std::string("syntax error, expect ") + tokenStringList.at(token)  + std::string(", actual " ) + tokenStringList.at(lexer->getToken())  + std::string(" ")
				+ lexer->getStringVal());
	}
}

SQLColumnDefinition *SQLExprParser::parseColumn() {
	SQLColumnDefinition *column = createColumnDefinition();
	column->setName(getName());
	column->setDataType(parseDataType());

	return parseColumnRest(column);
}

SQLColumnDefinition *SQLExprParser::createColumnDefinition() {
	SQLColumnDefinition *column = new SQLColumnDefinition();
	return column;
}

SQLColumnDefinition *SQLExprParser::parseColumnRest(SQLColumnDefinition *column) {
	if (lexer->getToken() == DEFAULT) {
		lexer->nextToken();
		column->setDefaultExpr(bitOr());
		return parseColumnRest(column);
	}

	if (lexer->getToken() == NOT) {
		lexer->nextToken();
		accept(XNULL);
		column->getConstaints().push_back(new NotNullConstraint());
		return parseColumnRest(column);
	}

	if (lexer->getToken() == XNULL) {
		lexer->nextToken();
		column->setDefaultExpr(new SQLNullExpr());
		return parseColumnRest(column);
	}

	if (lexer->getToken() == PRIMARY) {
		lexer->nextToken();
		accept(KEY);
		column->getConstaints().push_back(new SQLColumnPrimaryKey());
		return parseColumnRest(column);
	}

	if (lexer->getToken() == UNIQUE) {
		lexer->nextToken();
		if (lexer->getToken() == KEY) {
			lexer->nextToken();
		}
		column->getConstaints().push_back(new SQLColumnPrimaryKey());
		return parseColumnRest(column);
	}

	if (lexer->getToken() == CONSTRAINT) {
		lexer->nextToken();

		SQLName *name = getName();

		if (lexer->getToken() == PRIMARY) {
			lexer->nextToken();
			accept(KEY);
			SQLColumnPrimaryKey *pk = new SQLColumnPrimaryKey();
			pk->setName(name);
			column->getConstaints().push_back(pk);
			return parseColumnRest(column);
		}

		if (lexer->getToken() == UNIQUE) {
			lexer->nextToken();
			SQLColumnUniqueKey *uk = new SQLColumnUniqueKey();
			uk->setName(name);
			column->getConstaints().push_back(uk);
			return parseColumnRest(column);
		}

		if (lexer->getToken() == REFERENCES) {
			lexer->nextToken();
			SQLColumnReference *ref = new SQLColumnReference();
			ref->setName(name);
			ref->setTable(getName());
			accept(LEFTPAREN);
			getNames(ref->getColumns(), ref);
			accept(RPAREN);
			column->getConstaints().push_back(ref);
			return parseColumnRest(column);
		}

		if (lexer->getToken() == NOT) {
			lexer->nextToken();
			accept(XNULL);
			NotNullConstraint *notNull = new NotNullConstraint();
			notNull->setName(name);
			column->getConstaints().push_back(notNull);
			return parseColumnRest(column);
		}

		if (lexer->getToken() == CHECK) {
			SQLColumnCheck *check = parseColumnCheck();
			check->setName(name);
			check->setParent(column);
			column->getConstaints().push_back(check);
			return parseColumnRest(column);
		}

		if (lexer->getToken() == DEFAULT) {
			lexer->nextToken();
			SQLExpr *expr = getExpr();
			column->setDefaultExpr(expr);
			return parseColumnRest(column);
		}

		throw new ParserException(std::string("TODO : ") + tokenStringList.at(lexer->getToken())  + std::string(" ") + lexer->getStringVal());
	}

	if (lexer->getToken() == CHECK) {
		SQLColumnCheck *check = parseColumnCheck();
		column->getConstaints().push_back(check);
		return parseColumnRest(column);
	}

	if (lexer->getToken() == COMMENT) {
		lexer->nextToken();
		column->setComment(primary());
	}

	return column;
}

SQLColumnCheck *SQLExprParser::parseColumnCheck() {
	lexer->nextToken();
	SQLExpr *expr = getExpr();
	SQLColumnCheck *check = new SQLColumnCheck(expr);

	if (lexer->getToken() == DISABLE) {
		lexer->nextToken();
		check->setEnable(false);
	} else if (lexer->getToken() == ENABLE) {
		lexer->nextToken();
		check->setEnable(true);
	}
	return check;
}

SQLPrimaryKey *SQLExprParser::parsePrimaryKey() {
	accept(PRIMARY);
	accept(KEY);

	SQLPrimaryKeyImpl *pk = new SQLPrimaryKeyImpl();
	accept(LEFTPAREN);
	exprList(pk->getColumns());
	accept(RPAREN);

	return pk;
}

SQLUnique *SQLExprParser::parseUnique() {
	accept(UNIQUE);

	SQLUnique *unique = new SQLUnique();
	accept(LEFTPAREN);
	exprList(unique->getColumns());
	accept(RPAREN);

	return unique;
}

SQLAssignItem *SQLExprParser::parseAssignItem() {
	SQLAssignItem *item = new SQLAssignItem();

	SQLExpr *var = primary();

	SQLIdentifierExpr* v = dynamic_cast<SQLIdentifierExpr *>(var);
	//if (var instanceof SQLIdentifierExpr) {
	if (v != 0) {

		//var = new SQLVariantRefExpr(((SQLIdentifierExpr) var).getName());
		var = new SQLVariantRefExpr(v->getName());
	}
	item->setTarget(var);
	if (lexer->getToken() == COLONEQ) {
		lexer->nextToken();
	} else {
		accept(EQ);
	}
	item->setValue(getExpr());

	return item;
}

std::list<SQLHint *> & SQLExprParser::parseHints() {
	//std::list<SQLCommentHint *> hints = new ArrayList<SQLCommentHint>();
	parseHints(myHints);
	return myHints;
}

void SQLExprParser::parseHints(std::list<SQLHint *> & hints) {
	if (lexer->getToken() == HINT) {
		hints.push_back(new SQLCommentHint(lexer->getStringVal()));
		lexer->nextToken();
	}
}

SQLConstaint *SQLExprParser::parseConstaint() {
	SQLName *name = NULL;

	if (lexer->getToken() == CONSTRAINT) {
		lexer->nextToken();
		name = getName();
	}

	SQLConstaint *constraint;
	if (lexer->getToken() == PRIMARY) {

		constraint = parsePrimaryKey();

	} else if (lexer->getToken() == UNIQUE) {

		constraint = parseUnique();

	} else if (lexer->getToken() == FOREIGN) {

		constraint = parseForeignKey();

	} else if (lexer->getToken() == CHECK) {

		constraint = parseCheck();

	} else {

		throw new ParserException(std::string("TODO : ") + tokenStringList.at(lexer->getToken()) + std::string(" ") + lexer->getStringVal());
	}

	constraint->setName(name);

	return constraint;
}

SQLCheck *SQLExprParser::parseCheck() {
	accept(CHECK);
	SQLCheck *check = createCheck();
	accept(LEFTPAREN);
	check->setExpr(getExpr());
	accept(RPAREN);
	return check;
}

SQLCheck *SQLExprParser::createCheck() {
	return new SQLCheck();
}

SQLForeignKeyConstraint *SQLExprParser::parseForeignKey() {
	accept(FOREIGN);
	accept(KEY);

	SQLForeignKeyConstraint *fk = createForeignKey();

	accept(LEFTPAREN);
	getNames(fk->getReferencingColumns());
	accept(RPAREN);

	accept(REFERENCES);

	fk->setReferencedTableName(getName());

	accept(LEFTPAREN);
	getNames(fk->getReferencedColumns());
	accept(RPAREN);
	return fk;
}

SQLForeignKeyConstraint *SQLExprParser::createForeignKey() {
	return new SQLForeignKeyImpl();
}

