#include "SQLInListExpr.h"
SQLInListExpr::SQLInListExpr() : xnot(false){

}

SQLInListExpr::~SQLInListExpr() {

	for(std::list<SQLExpr *>::iterator it = targetList.begin(); it != targetList.end(); ++it) 
	{
		delete *it; 
	}
	targetList.clear();

	if (expr != NULL)
	{
		delete expr;
		expr = NULL;
	}


}
SQLInListExpr::SQLInListExpr(SQLExpr *theExpr) : expr(theExpr), xnot(false){

	//expr = theExpr;
}

SQLInListExpr::SQLInListExpr(SQLExpr *theExpr, bool theNot) : expr(theExpr), xnot(theNot) {

	//this.expr = expr;
	//this.xnot = xnot;
}

bool SQLInListExpr::isNot() {
	return xnot;
}

void SQLInListExpr::setNot(bool theNot) {
	xnot = theNot;
}

SQLExpr *SQLInListExpr::getExpr() {
	return expr;
}

void SQLInListExpr::setExpr(SQLExpr *theExpr) {
	expr = theExpr;
}

std::list<SQLExpr *> & SQLInListExpr::getTargetList() {
	return targetList;
}

void SQLInListExpr::setTargetList(std::list<SQLExpr *> & theTargetList) {
	targetList = theTargetList;
}

void SQLInListExpr::accept0(SQLASTVisitor *visitor) {
	if (visitor->visit(this)) {
		acceptChild(visitor, expr);
		acceptChild(visitor, targetList);
	}

	visitor->endVisit(this);
}

//int SQLInListExpr::hashCode() {
	//final int prime = 31;
	//int result = 1;
	//result = prime * result + ((expr == NULL) ? 0 : expr.hashCode());
	//result = prime * result + (xnot ? 1231 : 1237);
	//result = prime * result + ((targetList == NULL) ? 0 : targetList.hashCode());
	//return result;
//}

//bool SQLInListExpr::equals(Object obj) {
	//if (this == obj) {
		//return true;
	//}
	//if (obj == NULL) {
		//return false;
	//}
	//if (getClass() != obj.getClass()) {
		//return false;
	//}
	//SQLInListExpr other = (SQLInListExpr) obj;
	//if (expr == NULL) {
		//if (other.expr != NULL) {
			//return false;
		//}
	//} else if (!expr.equals(other.expr)) {
		//return false;
	//}
	//if (xnot != other.xnot) {
		//return false;
	//}
	//if (targetList == NULL) {
		//if (other.targetList != NULL) {
			//return false;
		//}
	//} else if (!targetList.equals(other.targetList)) {
		//return false;
	//}
	//return true;
//}

