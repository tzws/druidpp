#include "SQLExistsExpr.h"
SQLExistsExpr::SQLExistsExpr() : xnot (false){

}

SQLExistsExpr::~SQLExistsExpr() {
	if (subQuery != NULL)
	{
		delete subQuery;
		subQuery = NULL;
		
	}

}
SQLExistsExpr::SQLExistsExpr(SQLSelect *theSubQuery) : subQuery(theSubQuery), xnot(false){
	//this.setSubQuery(subQuery);
}

SQLExistsExpr::SQLExistsExpr(SQLSelect *theSubQuery, bool theNot) : subQuery(theSubQuery), xnot (theNot){ 
	//this.setSubQuery(subQuery);
	//this.xnot = xnot;
}

bool SQLExistsExpr::isNot() {
	return xnot;
}

void SQLExistsExpr::setNot(bool theNot) {
	xnot = theNot;
}

SQLSelect *SQLExistsExpr::getSubQuery() {
	return subQuery;
}

void SQLExistsExpr::setSubQuery(SQLSelect *theSubQuery) {
	if (theSubQuery != NULL) {
		theSubQuery->setParent(this);
	}
	subQuery = theSubQuery;
}

void SQLExistsExpr::accept0(SQLASTVisitor *visitor) {
	if (visitor->visit(this)) {
		acceptChild(visitor, subQuery);
	}

	visitor->endVisit(this);
}

//int SQLExistsExpr::hashCode() {
	//final int prime = 31;
	//int result = 1;
	//result = prime * result + (xnot ? 1231 : 1237);
	//result = prime * result + ((subQuery == null) ? 0 : subQuery.hashCode());
	//return result;
//}

//bool SQLExistsExpr::equals(Object obj) {
	//if (this == obj) {
		//return true;
	//}
	//if (obj == null) {
		//return false;
	//}
	//if (getClass() != obj.getClass()) {
		//return false;
	//}
	//SQLExistsExpr other = (SQLExistsExpr) obj;
	//if (xnot != other.xnot) {
		//return false;
	//}
	//if (subQuery == null) {
		//if (other.subQuery != null) {
			//return false;
		//}
	//} else if (!subQuery.equals(other.subQuery)) {
		//return false;
	//}
	//return true;
//}

