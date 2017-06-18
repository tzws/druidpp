#include "SQLUnaryExpr.h"
SQLUnaryExpr::SQLUnaryExpr(){

}

SQLUnaryExpr::~SQLUnaryExpr(){
	if (expr != NULL)
	{
		delete expr;
		expr = NULL;
	}

	//if (xoperator != NULL)
	//{
		//delete xoperator;
		//xoperator = NULL;
	//}



}
SQLUnaryExpr::SQLUnaryExpr(SQLUnaryOperator *theXoperator, SQLExpr *theExpr) : xoperator (theXoperator), expr (theExpr){
	//this.xoperator = xoperator;
	//this.expr = expr;
}

SQLUnaryOperator *SQLUnaryExpr::getOperator() {
	return xoperator;
}

void SQLUnaryExpr::setOperator(SQLUnaryOperator *theXoperator) {
	xoperator = theXoperator;
}

SQLExpr *SQLUnaryExpr::getExpr() {
	return expr;
}

void SQLUnaryExpr::setExpr(SQLExpr *theExpr) {
	expr = theExpr;
}

void SQLUnaryExpr::accept0(SQLASTVisitor *visitor) {
	if (visitor->visit(this)) {
		acceptChild(visitor, expr);
	}

	visitor->endVisit(this);
}

//int SQLUnaryExpr::hashCode() {
	//int prime = 31;
	//int result = 1;
	//result = prime * result + ((expr == null) ? 0 : expr.hashCode());
	//result = prime * result + ((xoperator == null) ? 0 : xoperator.hashCode());
	//return result;
//}

//bool SQLUnaryExpr::equals(Object obj) {
	//if (this == obj) {
		//return true;
	//}
	//if (obj == null) {
		//return false;
	//}
	//if (getClass() != obj.getClass()) {
		//return false;
	//}
	//SQLUnaryExpr other = (SQLUnaryExpr) obj;
	//if (expr == null) {
		//if (other.expr != null) {
			//return false;
		//}
	//} else if (!expr.equals(other.expr)) {
		//return false;
	//}
	//if (xoperator != other.xoperator) {
		//return false;
	//}
	//return true;
//}

