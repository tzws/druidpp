#include "SQLNotExpr.h"
SQLNotExpr::SQLNotExpr(){

}
SQLNotExpr::~SQLNotExpr(){
	if (expr != NULL)
	{
		delete expr;
		expr = NULL;
	}

}
SQLNotExpr::SQLNotExpr(SQLExpr * theExpr){

	expr = theExpr;
}

SQLExpr *SQLNotExpr::getExpr() {
	return expr;
}

void SQLNotExpr::setExpr(SQLExpr *theExpr) {
	expr = theExpr;
}

void SQLNotExpr::output(std::string & buf) {
	buf += " NOT ";
	expr->output(buf);
}

void SQLNotExpr::accept0(SQLASTVisitor *visitor) {
	if (visitor->visit(this)) {
		acceptChild(visitor, expr);
	}

	visitor->endVisit(this);
}

//int hashCode() {
	//final int prime = 31;
	//int result = 1;
	//result = prime * result + ((expr == NULL) ? 0 : expr.hashCode());
	//return result;
//}

//bool equals(Object obj) {
	//if (this == obj) {
		//return true;
	//}
	//if (obj == NULL) {
		//return false;
	//}
	//if (getClass() != obj.getClass()) {
		//return false;
	//}
	//SQLNotExpr other = (SQLNotExpr) obj;
	//if (expr == NULL) {
		//if (other.expr != NULL) {
			//return false;
		//}
	//} else if (!expr.equals(other.expr)) {
		//return false;
	//}
	//return true;
//}

