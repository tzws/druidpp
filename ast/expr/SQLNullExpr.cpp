#include "SQLNullExpr.h"
SQLNullExpr::SQLNullExpr(){

}
SQLNullExpr::~SQLNullExpr(){

}

void SQLNullExpr::output(std::string & buf) {
	buf += "NULL";
}

void SQLNullExpr::accept0(SQLASTVisitor *visitor) {
	visitor->visit(this);

	visitor->endVisit(this);
}

//int SQLNullExpr::hashCode() {
	//return 0;
//}

//bool SQLNullExpr::equals(Object o) {
	//return o instanceof SQLNullExpr;
//}

