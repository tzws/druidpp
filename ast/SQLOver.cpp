#include "SQLOver.h"
SQLOver::SQLOver(){

}
SQLOver::~SQLOver(){

	for(std::list<SQLExpr *>::iterator it = partitionBy.begin(); it != partitionBy.end(); ++it) 
	{
		delete *it; 
	}
	partitionBy.clear();

	if (orderBy != NULL)
	{
		
		delete orderBy;
		orderBy = NULL;
	}


}
SQLOver::SQLOver(SQLOrderBy *theOrderBy){
	setOrderBy(theOrderBy);
}

void SQLOver::accept0(SQLASTVisitor *visitor) {
	if (visitor->visit(this)) {
		acceptChild(visitor, partitionBy);
		acceptChild(visitor, orderBy);
	}
	visitor->endVisit(this);
}

SQLOrderBy *SQLOver::getOrderBy() {
	return orderBy;
}

void SQLOver::setOrderBy(SQLOrderBy *theOrderBy) {
	if (theOrderBy != NULL) {
		theOrderBy->setParent(this);
	}
	orderBy = theOrderBy;
}

std::list<SQLExpr *> &SQLOver::getPartitionBy() {
	return partitionBy;
}

//int SQLOver::hashCode() {
	//int prime = 31;
	//int result = 1;
	//result = prime * result + ((orderBy == NULL) ? 0 : orderBy.hashCode());
	//result = prime * result + ((partitionBy == NULL) ? 0 : partitionBy.hashCode());
	//return result;
//}

//bool SQLOver::equals(Object obj) {
	//if (this == obj) {
		//return true;
	//}
	//if (obj == NULL) {
		//return false;
	//}
	//if (getClass() != obj.getClass()) {
		//return false;
	//}
	//SQLOver other = (SQLOver) obj;
	//if (orderBy == NULL) {
		//if (other.orderBy != NULL) {
			//return false;
		//}
	//} else if (!orderBy.equals(other.orderBy)) {
		//return false;
	//}
	//if (partitionBy == NULL) {
		//if (other.partitionBy != NULL) {
			//return false;
		//}
	//} else if (!partitionBy.equals(other.partitionBy)) {
		//return false;
	//}
	//return true;
//}

