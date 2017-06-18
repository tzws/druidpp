// g++ x.cpp -std=c++11
#include <iostream>
#include <vector>
#include "Lexer.h"

void test_0() {
	std::string sql = "SELECT /*mark for picman*/ * FROM WP_ALBUM WHERE MEMBER_ID = ? AND ID IN (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)";


	std::string oracle = "    SELECT  NVL(SUM(MISSIONNO), 0) DISTCNT, COUNT(DISTINCT(USERID)) USERIDCNT  FROM EVTSUPPLYHIST  WHERE EVTCODE = evtCode  AND EVTNO = evtNo  AND GIFTCODE = giftCode  AND SUPPLYDT BETWEEN TO_DATE(startDate, 'YYYY/MM/DD HH24:MI:SS')   AND TO_DATE(endDate, 'YYYY/MM/DD HH24:MI:SS')  ";

	std::string x = "SELECT e.last_name    AS name, e.commission_pct comm, e.salary * 12    Annual FROM  scott.employees AS e WHERE  e.salary > 1000 ORDER  BY e.first_name, e.last_name;";
	Lexer *lexer = new Lexer(x);

	for (;;) {

		std::cout << "in test_0, step 1" << std::endl;

		lexer->nextToken();
		std::cout << "in test_0, step 2" << std::endl;

		Token tok = lexer->getToken();
		std::cout << "in test_0, step 3, toke is: " << tok << std::endl;

		if (tok == IDENTIFIER) {
			std::cout << "\t\t" << __FILE__ << ": " << __LINE__ << ": Token is: " <<  tokenStringList.at(tok) << "\t\t, stringVal is: " << lexer->getStringVal()  << "<---- done" <<  std::endl;
		} else if (tok == MULTI_LINE_COMMENT) {
			std::cout << "\t\t" << __FILE__ << ": " << __LINE__ << ": Token is: " <<  tokenStringList.at(tok) << "\t\t, stringVal is: " << lexer->getStringVal()  << "<---- done" <<  std::endl;
		} else {
			std::cout << "\t\t" << __FILE__ << ": " << __LINE__ << ": Token is: " <<  tokenStringList.at(tok) << "\t\t, stringVal is: " << lexer->getStringVal()  << "<---- done" <<  std::endl;
		}

		if (tok == ENDOFFILE ) {
			break;
		}

	}

}

void test_lexer()  {
	//std::string sql = "SELECT * FROM T WHERE F1 = ? ORDER BY F2";
	std::string sql = "SELECT ID, NAME, AGE FROM USER WHERE ID = ?";
	Lexer *lexer = new Lexer(sql);
	for (;;) {
		lexer->nextToken();
		Token tok = lexer->getToken();

		if (tok == IDENTIFIER) {

			std::cout << "1\t\t" << __FILE__ << ": " << __LINE__ << ": Token is: " <<  tokenStringList.at(tok) << "\t\t, stringVal is: " << lexer->getStringVal()  << "<---- done" <<  std::endl;
			//System.out.println(tok.name() + "\t\t" + lexer.stringVal());
		} else if (tok == LITERAL_INT) {

			std::cout << "2\t\t" << __FILE__ << ": " << __LINE__ << ": Token is: " <<  tokenStringList.at(tok) << "\t\t, stringVal is: " << lexer->getStringVal()  << "<---- done" <<  std::endl;
			//System.out.println(tok.name() + "\t\t" + lexer.numberString());
		} else {

			std::cout << "3\t\t" << __FILE__ << ": " << __LINE__ << ": Token is: " <<  tokenStringList.at(tok) << "\t\t, stringVal is: " << lexer->getStringVal()  << "<---- done" <<  std::endl;
			//System.out.println(tok.name() + "\t\t\t" + tok.name);
		}

		if (tok == WHERE) {
			//System.out.println("where pos : " + lexer.pos());
			std::cout << "\t\t" << __FILE__ << ": " << __LINE__ << ": Token is: " <<  tokenStringList.at(tok) << "\t\t, stringVal is: " << lexer->getStringVal()  << "<---- done" <<  std::endl;

		}

		if (tok == ENDOFFILE) {
			break;
		}
	}
}




int main ()
{
	//test_0();
	test_lexer();
	return 0;
}

