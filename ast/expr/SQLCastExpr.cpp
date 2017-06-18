#include "SQLCastExpr.h"

SQLCastExpr::SQLCastExpr(){

}

SQLCastExpr::~SQLCastExpr(){
	if (expr != NULL)
	{
		delete expr;
		expr = NULL;
	}

	if (dataType != NULL)
	{
		delete dataType;
		dataType = NULL;
	}

}
SQLExpr *SQLCastExpr::getExpr() {
	return expr;
}

void SQLCastExpr::setExpr(SQLExpr *theExpr) {
	if (theExpr != NULL) {
		theExpr->setParent(this);
	}
	expr = theExpr;
}

SQLDataType *SQLCastExpr::getDataType() {
	return dataType;
}

void SQLCastExpr::setDataType(SQLDataType *theDataType) {
	dataType = theDataType;
}

void SQLCastExpr::accept0(SQLASTVisitor *visitor) {
	if (visitor->visit(this)) {
		acceptChild(visitor, expr);
		acceptChild(visitor, dataType);
	}
	visitor->endVisit(this);
}

//int SQLCastExpr::hashCode() {
	//final int prime = 31;
	//int result = 1;
	//result = prime * result + ((dataType == NULL) ? 0 : dataType.hashCode());
	//result = prime * result + ((expr == NULL) ? 0 : expr.hashCode());
	//return result;
//}

//bool SQLCastExpr::equals(Object obj) {
	//if (this == obj) {
		//return true;
	//}
	//if (obj == NULL) {
		//return false;
	//}
	//if (getClass() != obj.getClass()) {
		//return false;
	//}
	//SQLCastExpr other = (SQLCastExpr) obj;
	//if (dataType == NULL) {
		//if (other.dataType != NULL) {
			//return false;
		//}
	//} else if (!dataType.equals(other.dataType)) {
		//return false;
	//}
	//if (expr == NULL) {
		//if (other.expr != NULL) {
			//return false;
		//}
	//} else if (!expr.equals(other.expr)) {
		//return false;
	//}
	//return true;
//}

