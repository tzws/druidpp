#include "SQLAllColumnExpr.h"

SQLAllColumnExpr::SQLAllColumnExpr(){

}

SQLAllColumnExpr::~SQLAllColumnExpr(){

}
void SQLAllColumnExpr::output(std::string & buf) {
	//buf.append("*");
	buf += "*";
}

void SQLAllColumnExpr::accept0(SQLASTVisitor *visitor) {
	visitor->visit(this);
	visitor->endVisit(this);
}

