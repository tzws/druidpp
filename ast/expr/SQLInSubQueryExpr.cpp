#include "SQLInSubQueryExpr.h"
SQLInSubQueryExpr::SQLInSubQueryExpr() : xnot(false){

}

SQLInSubQueryExpr::~SQLInSubQueryExpr() {
	if (expr != NULL)
	{
		
		delete expr;
		expr = NULL;
	}

}
bool SQLInSubQueryExpr::isNot() {
	return xnot;
}

void SQLInSubQueryExpr::setNot(bool theNot) {
	xnot = theNot;
}

SQLExpr *SQLInSubQueryExpr::getExpr() {
	return expr;
}

void SQLInSubQueryExpr::setExpr(SQLExpr *theExpr) {
	expr = theExpr;
}

SQLInSubQueryExpr::SQLInSubQueryExpr(SQLSelect *theSelect) : subQuery (theSelect), xnot(false){

	//subQuery = theSelect;
}

SQLSelect *SQLInSubQueryExpr::getSubQuery() {
	return subQuery;
}

void SQLInSubQueryExpr::setSubQuery(SQLSelect *theSubQuery) {
	if (theSubQuery != NULL) {
		theSubQuery->setParent(this);
	}
	subQuery = theSubQuery;
}

void SQLInSubQueryExpr::output(std::string & buf) {
	subQuery->output(buf);
}

void SQLInSubQueryExpr::accept0(SQLASTVisitor *visitor) {
	if (visitor->visit(this)) {
		acceptChild(visitor,expr);
		acceptChild(visitor,subQuery);
	}

	visitor->endVisit(this);
}

//int SQLInSubQueryExpr::hashCode() {
	//final int prime = 31;
	//int result = 1;
	//result = prime * result + ((expr == NULL) ? 0 : expr.hashCode());
	//result = prime * result + (xnot ? 1231 : 1237);
	//result = prime * result + ((subQuery == NULL) ? 0 : subQuery.hashCode());
	//return result;
//}

//bool SQLInSubQueryExpr::equals(Object obj) {
	//if (this == obj) {
		//return true;
	//}
	//if (obj == NULL) {
		//return false;
	//}
	//if (getClass() != obj.getClass()) {
		//return false;
	//}
	//SQLInSubQueryExpr other = (SQLInSubQueryExpr) obj;
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
	//if (subQuery == NULL) {
		//if (other.subQuery != NULL) {
			//return false;
		//}
	//} else if (!subQuery.equals(other.subQuery)) {
		//return false;
	//}
	//return true;
//}

