#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <string>
#include <vector>

#include "Lexer.h"
#include "SQLExprParser.h"

void welcome(){
	printf("ssdb-bench - SSDB benchmark tool\n");
	printf("Copyright (c) 2013-2014 ideawu.com\n");
	printf("\n");
}


//std::string & testStatementParser(std::string & sql) {
	//std::string out = "";
	////MySqlOutputVisitor visitor = new MySqlOutputVisitor(out);
	//SQLStatementParser *parser = new SQLStatementParser(sql);
	//std::list<SQLStatement *> statementList = parser->parseStatementList();
	//// for (SQLStatement statement : statementList) {
	//// statement.accept(visitor);
	//// visitor.println();
	//// }
	//return out;
//}


std::string & testLexer(std::string & sql) {
	std::string out = "";

	Lexer *lexer = new Lexer(sql);

	for (;;) {

		//std::cout << "in test_0, step 1" << std::endl;

		lexer->nextToken();
		//std::cout << "in test_0, step 2" << std::endl;

		Token tok = lexer->getToken();
		//std::cout << "in test_0, step 3, toke is: " << tok << std::endl;

		if (tok == IDENTIFIER) {
			//std::cout << "\t\t" << __FILE__ << ": " << __LINE__ << ": Token is: " <<  tokenStringList.at(tok) << "\t\t, stringVal is: " << lexer->getStringVal()  << "<---- done" <<  std::endl;
		} else if (tok == MULTI_LINE_COMMENT) {
			//std::cout << "\t\t" << __FILE__ << ": " << __LINE__ << ": Token is: " <<  tokenStringList.at(tok) << "\t\t, stringVal is: " << lexer->getStringVal()  << "<---- done" <<  std::endl;
		} else {
			//std::cout << "\t\t" << __FILE__ << ": " << __LINE__ << ": Token is: " <<  tokenStringList.at(tok) << "\t\t, stringVal is: " << lexer->getStringVal()  << "<---- done" <<  std::endl;
		}

		if (tok == ENDOFFILE ) {
			break;
		}
	}

	return out;
}


void perfSql(std::string & sql) {

	double stime = millitime();
	int total = 0;
	for (int i = 0; i < 1000 * 1000; ++i) {
		//testStatementParser(sql);
		testLexer(sql);
		total += 1;
	}

	double etime = millitime();
	double ts = (stime == etime)? 1 : (etime - stime);
	double speed = total / ts;
	printf("qps: %d, time: %.3f s\n", (int)speed, ts);
	return;
}

public void test_pert()  {

	std::string sql = "SELECT * FROM T";
	//std::string sql = "SELECT ID, NAME, AGE FROM USER WHERE ID = ?";
	std::string e ("AGE > 506");

	for (int i = 0; i < 10; ++i) {
		//perfSql(sql);
		perfSql(e);
	}
}

int main(int argc, char **argv){

	welcome();

	printf("\n");

	return 0;
}

