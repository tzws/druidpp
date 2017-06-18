#include "SQLAllExpr.h"

SQLAllExpr::SQLAllExpr(){

}
SQLAllExpr::~SQLAllExpr(){
	if (subQuery != NULL)
	{
		delete subQuery;
		subQuery = NULL;
		
	}
}
SQLAllExpr::SQLAllExpr(SQLSelect  * theSelect){

	subQuery = theSelect;
}

SQLSelect *SQLAllExpr::getSubQuery() {
	return subQuery;
}

void SQLAllExpr::setSubQuery(SQLSelect *theSubQuery) {
	subQuery = theSubQuery;
}

void SQLAllExpr::output(std::string & buf) {
	//this.subQuery.output(buf);
	subQuery->output(buf);
}

void SQLAllExpr::accept0(SQLASTVisitor *visitor) {
	if (visitor->visit(this)) {
		acceptChild(visitor, subQuery);
	}

	visitor->endVisit(this);
}

//int SQLAllExpr::hashCode() {
	//final int prime = 31;
	//int result = 1;
	//result = prime * result + ((subQuery == null) ? 0 : subQuery.hashCode());
	//return result;
//}

//bool SQLAllExpr::equals(Object obj) {
	//if (this == obj) {
		//return true;
	//}
	//if (obj == null) {
		//return false;
	//}
	//if (getClass() != obj.getClass()) {
		//return false;
	//}
	//SQLAllExpr other = (SQLAllExpr) obj;
	//if (subQuery == null) {
		//if (other.subQuery != null) {
			//return false;
		//}
	//} else if (!subQuery.equals(other.subQuery)) {
		//return false;
	//}
	//return true;
//}

