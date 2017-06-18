#include "SQLQueryExpr.h"
SQLQueryExpr::SQLQueryExpr(){

}

SQLQueryExpr::~SQLQueryExpr(){
	if (subQuery != NULL)
	{
		delete subQuery;
		subQuery = NULL;
		
	}
}
SQLQueryExpr::SQLQueryExpr(SQLSelect * theSelect){
	setSubQuery(theSelect);
}

SQLSelect *SQLQueryExpr::getSubQuery() {
	return subQuery;
}

void SQLQueryExpr::setSubQuery(SQLSelect * theSubQuery) {
	if (theSubQuery != NULL) {
		theSubQuery->setParent(this);
	}
	subQuery = theSubQuery;
}

void SQLQueryExpr::output(std::string & buf) {
	subQuery->output(buf);
}

void SQLQueryExpr::accept0(SQLASTVisitor *visitor) {
	if (visitor->visit(this)) {
		acceptChild(visitor, subQuery);
	}

	visitor->endVisit(this);
}

//int SQLQueryExpr::hashCode() {
	//final int prime = 31;
	//int result = 1;
	//result = prime * result + ((subQuery == NULL) ? 0 : subQuery.hashCode());
	//return result;
//}

//bool SQLQueryExpr::equals(Object obj) {
	//if (this == obj) {
		//return true;
	//}
	//if (obj == NULL) {
		//return false;
	//}
	//if (getClass() != obj.getClass()) {
		//return false;
	//}
	//SQLQueryExpr other = (SQLQueryExpr) obj;
	//if (subQuery == NULL) {
		//if (other.subQuery != NULL) {
			//return false;
		//}
	//} else if (!subQuery.equals(other.subQuery)) {
		//return false;
	//}
	//return true;
//}

