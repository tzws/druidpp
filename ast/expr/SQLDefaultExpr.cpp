#include "SQLDefaultExpr.h"

SQLDefaultExpr::SQLDefaultExpr() {
	
}

SQLDefaultExpr::~SQLDefaultExpr() {
	
}
//bool SQLDefaultExpr::equals(Object o) {
	//return o instanceof SQLDefaultExpr;
//}

//int SQLDefaultExpr::hashCode() {
	//return 0;
//}

void SQLDefaultExpr::accept0(SQLASTVisitor *visitor) {
	visitor->visit(this);
	visitor->endVisit(this);
}

//std::string &SQLDefaultExpr::toString() {
	//std::string *defalt = new std::string( "DEFAULT");
	//return *defalt;
//}

