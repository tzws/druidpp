// g++ x.cpp -std=c++11
#include <iostream>
#include <vector>
#include "Lexer.h"
#include "SQLExprParser.h"

int main ()
{

	try {

		std::string e ("AGE > 506");
		SQLExprParser *exprParser = new SQLExprParser(e);
		SQLBinaryOpExpr *binaryOpExpr = dynamic_cast<SQLBinaryOpExpr *>(exprParser->getExpr());
		std::cout << (binaryOpExpr->getOperator())->getName() << std::endl;

		//Assert.assertEquals(SQLBinaryOperator.GreaterThan, binaryOpExpr.getOperator());

		SQLIdentifierExpr *left = dynamic_cast<SQLIdentifierExpr *>(binaryOpExpr->getLeft());
		std::cout << (left->getName()) << std::endl;
		SQLIntegerExpr *right = dynamic_cast<SQLIntegerExpr *>(binaryOpExpr->getRight());
		//RNumber *n = right->getNumber();
		//int a = boost::rational_cast<int> (n);
		std::cout << (right->intValue()) << std::endl;

		//Assert.assertEquals("AGE", left.getName());
		//Assert.assertEquals(5, right.getNumber().intValue());
		//
		//

		std::string sql ( "a > b");
		std::string sql_c  ("a > 2");

		SQLBinaryOpExpr *exprA, *exprB, *exprC;
		{
			SQLExprParser *parser = new SQLExprParser(sql);
			SQLBinaryOpExpr *exprA = dynamic_cast<SQLBinaryOpExpr *>(parser->getExpr());
		}
		{
			SQLExprParser *parser = new SQLExprParser(sql);
			SQLBinaryOpExpr *exprB = dynamic_cast<SQLBinaryOpExpr *>(parser->getExpr());
		}
		{
			SQLExprParser *parser = new SQLExprParser(sql);
			SQLBinaryOpExpr *exprC = dynamic_cast<SQLBinaryOpExpr *>(parser->getExpr());
		}
	} catch (ParserException *e) {
		std::cout << e->what() << std::endl;
	}


	return 0;
}

