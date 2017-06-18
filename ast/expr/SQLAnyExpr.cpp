#include "SQLAnyExpr.h"

SQLAnyExpr::SQLAnyExpr(){

}

SQLAnyExpr::~SQLAnyExpr(){
	if (subQuery != NULL)
	{
		delete subQuery;
		subQuery = NULL;
		
	}
}
SQLAnyExpr::SQLAnyExpr(SQLSelect *theSelect){

	subQuery = theSelect;
}

SQLSelect *SQLAnyExpr::getSubQuery() {
	return subQuery;
}

void SQLAnyExpr::setSubQuery(SQLSelect * theSubQuery) {
	subQuery = theSubQuery;
}

void SQLAnyExpr::output(std::string & buf) {
	//this.subQuery.output(buf);
	subQuery->output(buf);
}

void SQLAnyExpr::accept0(SQLASTVisitor *visitor) {
	if (visitor->visit(this)) {
		acceptChild(visitor, subQuery);
	}

	visitor->endVisit(this);
}

//int SQLAnyExpr::hashCode() {
	//final int prime = 31;
	//int result = 1;
	//result = prime * result + ((subQuery == null) ? 0 : subQuery.hashCode());
	//return result;
//}

//bool SQLAnyExpr::equals(Object obj) {
	//if (this == obj) {
		//return true;
	//}
	//if (obj == null) {
		//return false;
	//}
	//if (getClass() != obj.getClass()) {
		//return false;
	//}
	//SQLAnyExpr other = (SQLAnyExpr) obj;
	//if (subQuery == null) {
		//if (other.subQuery != null) {
			//return false;
		//}
	//} else if (!subQuery.equals(other.subQuery)) {
		//return false;
	//}
	//return true;
//}

