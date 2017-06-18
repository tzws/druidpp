#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <string>
#include <vector>
#include <sys/time.h>

#include "Lexer.h"
#include "SQLParser.h"
#include "SQLExprParser.h"
#include "SQLSelectParser.h"
#include "SQLStatementParser.h"
#include "SQLDDLParser.h"
#include "SQLCreateTableParser.h"
#include "OdpsSelectParser.h"






static inline double millitime(){
	struct timeval now;
	gettimeofday(&now, NULL);
	double ret = now.tv_sec + now.tv_usec/1000.0/1000.0;
	return ret;
}


void welcome(){
	printf("benchmark tool\n");
	printf("\n");
}


std::string & testStatementParser(std::string & sql) {

	std::string out = "";
	try {
		//MySqlOutputVisitor visitor = new MySqlOutputVisitor(out);
		SQLStatementParser *parser = new SQLStatementParser(sql);
		std::list<SQLStatement *> statementList = parser->parseStatementList();
		// for (SQLStatement statement : statementList) {
		// statement.accept(visitor);
		// visitor.println();
		// }
		delete parser;
	} catch (ParserException *e) {
		std::cerr << e->what() << std::endl;
		exit(1);
	}

	return out;
}

void testExprParser (std::string & sql)
{
	//std::cout << __FILE__ << ": " << __LINE__ << ", in testExprParser, step 1 " << std::endl;
	SQLExprParser *exprParser = new SQLExprParser(sql);

	SQLBinaryOpExpr *binaryOpExpr = dynamic_cast<SQLBinaryOpExpr *>(exprParser->getExpr());
	//std::cout << (binaryOpExpr->getOperator())->getName() << std::endl;

	//Assert.assertEquals(SQLBinaryOperator.GreaterThan, binaryOpExpr.getOperator());

	SQLIdentifierExpr *left = dynamic_cast<SQLIdentifierExpr *>(binaryOpExpr->getLeft());
	//std::cout << (left->getName()) << std::endl;
	SQLIntegerExpr *right = dynamic_cast<SQLIntegerExpr *>(binaryOpExpr->getRight());
	//RNumber *n = right->getNumber();
	//int a = boost::rational_cast<int> (n);
	//std::cout << (right->intValue()) << std::endl;

	delete left;
	delete right;
	delete binaryOpExpr;

	delete exprParser;
	//std::cout << __FILE__ << ": " << __LINE__ << ", in testExprParser, step 2 " << std::endl;
}


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
			//std::cout <<  tokenStringList.at(tok) << "\t\t" << lexer->getStringVal()  <<  std::endl;
		} else if (tok == MULTI_LINE_COMMENT) {
			std::cout <<  tokenStringList.at(tok) << "\t\t" << lexer->getStringVal()  << std::endl;
		} else {
			//std::cout << tokenStringList.at(tok) << "\t\t" << lexer->getStringVal()  << std::endl;
		}

		if (tok == ENDOFFILE ) {
			break;
		}
	}
	delete lexer;

	return out;
}


void perfSql(std::string & sql) {

	double stime = millitime();
	int total = 0;

	std::string e ("AGE > 506");
	for (int i = 0; i < 1000 * 1000; ++i) {
	//for (int i = 0; i < 1 * 1; ++i) {
		//std::cout << __FILE__ << ": " << __LINE__ << ", in perfSql loop :  " << i << std::endl;
		//testStatementParser(sql);
		//testLexer(sql);
		testStatementParser(sql);
		//testExprParser(e);
		total += 1;
		//fprintf(stderr, "loop %d dones\n", i);
	}

	double etime = millitime();
	double ts = (stime == etime)? 1 : (etime - stime);
	double speed = total / ts;
	fprintf(stderr, "qps: %d, time: %.3f s\n", (int)speed, ts);
	return;
}

void test_pert()  {

	//std::string sql = "SELECT * FROM T";
	std::string sql = "select id, name, age from user where id = ?";
	std::string e ("AGE > 506");
	std::string sql_upper = "SELECT ID, NAME, AGE FROM USER WHERE ID = ?";

	//std::string oracle = "    SELECT  NVL(SUM(MISSIONNO), 0) DISTCNT, COUNT(DISTINCT(USERID)) USERIDCNT  FROM EVTSUPPLYHIST  WHERE EVTCODE = #evtCode#  AND EVTNO = #evtNo#  AND GIFTCODE = #giftCode#  AND SUPPLYDT BETWEEN TO_DATE(#startDate#, 'YYYY/MM/DD HH24:MI:SS')   AND TO_DATE(#endDate#, 'YYYY/MM/DD HH24:MI:SS')  ";

	std::string oracle = "    select  nvl(sum(missionno), 0) distcnt, count(distinct(userid)) useridcnt  from evtsupplyhist  where evtcode = evtcode  and evtno = evtno  and giftcode = giftcode  and supplydt between to_date(startdate, 'yyyy/mm/dd hh24:mi:ss')   and to_date(enddate, 'yyyy/mm/dd hh24:mi:ss')  ";

	std::string x = "SELECT last_name, commission_pct FROM employees WHERE salary > 1000";
	std::string x1 = "SELECT e.last_name    AS name, e.commission_pct comm, e.salary * 12    Annual FROM  scott.employees AS e WHERE  e.salary > 1000 ORDER  BY e.first_name, e.last_name;";
	//std::string x1 = "SELECT e.last_name";
	//x1 = "SELECT last_name FROM  employees ORDER  BY first_name";

	std::string postgres1 = "UPDATE pgbench_branches SET bbalance = bbalance + :delta WHERE bid = :bid;";
	std::string postgres2 = "INSERT INTO pgbench_history (tid, bid, aid, delta, mtime) VALUES (:tid, :bid, :aid, :delta, CURRENT_TIMESTAMP);";
	fprintf(stderr, "parsing SQL: %s \n", sql_upper.c_str());
	for (int i = 0; i < 5; ++i) {
		perfSql(sql_upper);
	}

	fprintf(stderr, "parsing SQL: %s \n", sql.c_str());
	for (int i = 0; i < 5; ++i) {
		perfSql(sql);
	}



	fprintf(stderr, "parsing SQL: %s \n", x1.c_str());
	for (int i = 0; i < 5; ++i) {
		perfSql(x1);
	}

	fprintf(stderr, "parsing SQL: %s \n", oracle.c_str());
	for (int i = 0; i < 5; ++i) {
		perfSql(oracle);
	}

	fprintf(stderr, "parsing SQL: %s \n", postgres2.c_str());
	for (int i = 0; i < 10; ++i) {
		perfSql(postgres2);
	}

}

int main(int argc, char **argv){

	//welcome();
	std::string sql = "SELECT ID, NAME, AGE FROM USER WHERE ID = ? Union SeleCT ID, name, age from x";
	//std::string oracle = "    SELECT  NVL(SUM(MISSIONNO), 0) DISTCNT, COUNT(DISTINCT(USERID)) USERIDCNT  FROM EVTSUPPLYHIST  WHERE EVTCODE = evtCode  AND EVTNO = evtNo  AND GIFTCODE = giftCode  AND SUPPLYDT BETWEEN TO_DATE(startDate, 'YYYY/MM/DD HH24:MI:SS')   AND TO_DATE(endDate, 'YYYY/MM/DD HH24:MI:SS')  ";
	std::string oracle = "    SELECT  NVL(SUM(MISSIONNO), 0) DISTCNT, COUNT(DISTINCT(USERID)) USERIDCNT  FROM EVTSUPPLYHIST  WHERE EVTCODE = evtCode  AND EVTNO = evtNo  AND GIFTCODE = giftCode  AND SUPPLYDT BETWEEN TO_DATE(startDate, 'YYYY/MM/DD HH24:MI:SS')   AND TO_DATE(endDate, 'YYYY/MM/DD HH24:MI:SS')  ";
	std::string x1 = "SELECT last_name FROM  employees ORDER  BY first_name";
	//x1 = "SELECT e.last_name AS name from scott.employees e";
	test_pert();
	//testStatementParser(sql);
	//testStatementParser(oracle);
	//testStatementParser(x1);
	//testStatementParser(oracle);
	//testLexer(sql);

	printf("\n");

	return 0;
}

