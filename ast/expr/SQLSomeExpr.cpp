#include "SQLSomeExpr.h"
SQLSomeExpr::SQLSomeExpr(){

}

SQLSomeExpr::~SQLSomeExpr(){
	if (subQuery != NULL)
	{
		delete subQuery;
		subQuery = NULL;
		
	}
}
SQLSomeExpr::SQLSomeExpr(SQLSelect * theSelect){

	subQuery = theSelect;
}

SQLSelect *SQLSomeExpr::getSubQuery() {
	return subQuery;
}

void SQLSomeExpr::setSubQuery(SQLSelect * theSubQuery) {
	subQuery = theSubQuery;
}

void SQLSomeExpr::output(std::string & buf) {
	subQuery->output(buf);
}

void SQLSomeExpr::accept0(SQLASTVisitor *visitor) {
	if (visitor->visit(this)) {
		acceptChild(visitor, subQuery);
	}

	visitor->endVisit(this);
}

//int SQLSomeExpr::hashCode() {
	//final int prime = 31;
	//int result = 1;
	//result = prime * result + ((subQuery == null) ? 0 : subQuery.hashCode());
	//return result;
//}

//bool SQLSomeExpr::equals(Object obj) {
	//if (this == obj) {
		//return true;
	//}
	//if (obj == null) {
		//return false;
	//}
	//if (getClass() != obj.getClass()) {
		//return false;
	//}
	//SQLSomeExpr other = (SQLSomeExpr) obj;
	//if (subQuery == null) {
		//if (other.subQuery != null) {
			//return false;
		//}
	//} else if (!subQuery.equals(other.subQuery)) {
		//return false;
	//}
	//return true;
//}

