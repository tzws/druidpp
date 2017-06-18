#include "SQLCaseExpr_Item.h"

SQLCaseExpr_Item::SQLCaseExpr_Item(){

}

SQLCaseExpr_Item::~SQLCaseExpr_Item(){


	if (conditionExpr != NULL)
	{
		
		delete conditionExpr;
		conditionExpr = NULL;
	}

	if (valueExpr != NULL)
	{
		
		delete valueExpr;
		valueExpr = NULL;
	}

}
SQLCaseExpr_Item::SQLCaseExpr_Item(SQLExpr *theConditionExpr, SQLExpr * theValueExpr){

	setConditionExpr(theConditionExpr);
	setValueExpr(theValueExpr);


}

SQLExpr *SQLCaseExpr_Item::getConditionExpr() {
	return conditionExpr;
}

void SQLCaseExpr_Item::setConditionExpr(SQLExpr *theConditionExpr) {
	if (theConditionExpr != NULL) {
		theConditionExpr->setParent(this);
	}
	conditionExpr = theConditionExpr;
}

SQLExpr *SQLCaseExpr_Item::getValueExpr() {
	return valueExpr;
}

void SQLCaseExpr_Item::setValueExpr(SQLExpr *theValueExpr) {
	if (theValueExpr != NULL) {
		theValueExpr->setParent(this);
	}
	valueExpr = theValueExpr;
}

void SQLCaseExpr_Item::accept0(SQLASTVisitor *visitor) {
	if (visitor->visit(this)) {
		acceptChild(visitor, conditionExpr);
		acceptChild(visitor, valueExpr);
	}
	visitor->endVisit(this);
}

