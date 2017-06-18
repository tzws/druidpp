#include "SQLCaseExpr.h"
SQLCaseExpr::SQLCaseExpr(){

}
SQLCaseExpr::~SQLCaseExpr(){

	for(std::list<SQLCaseExpr_Item *>::iterator it = items.begin(); it != items.end(); ++it) 
	{
		delete *it; 
	}
	items.clear();


	if (elseExpr != NULL)
	{
		
		delete elseExpr;
		elseExpr = NULL;
	}

	if (valueExpr != NULL)
	{
		
		delete valueExpr;
		valueExpr = NULL;
	}

}
SQLExpr *SQLCaseExpr::getValueExpr() {
	return valueExpr;
}

void SQLCaseExpr::setValueExpr(SQLExpr *theValueExpr) {
	if (theValueExpr != NULL) {
		theValueExpr->setParent(this);
	}
	valueExpr = theValueExpr;
}

SQLExpr *SQLCaseExpr::getElseExpr() {
	return elseExpr;
}

void SQLCaseExpr::setElseExpr(SQLExpr * theElseExpr) {
	if (theElseExpr != NULL) {
		theElseExpr->setParent(this);
	}
	elseExpr = theElseExpr;
}

std::list<SQLCaseExpr_Item *> & SQLCaseExpr::getItems() {
	return items;
}

void SQLCaseExpr::addItem(SQLCaseExpr_Item * theItem) {
	if (theItem != NULL) {
		theItem->setParent(this);
		items.push_back(theItem);
	}
}

void SQLCaseExpr::accept0(SQLASTVisitor *visitor) {
	if (visitor->visit(this)) {
		acceptChild(visitor, valueExpr);
		acceptChild(visitor, items);
		acceptChild(visitor, elseExpr);
	}
	visitor->endVisit(this);
}

void SQLCaseExpr::acceptChild(SQLASTVisitor *visitor, std::list<SQLCaseExpr_Item *> &children)
{
	
	if (children.empty()) {
		return;
	}

	std::list<SQLCaseExpr_Item *>::iterator iStart = children.begin() ;
	std::list<SQLCaseExpr_Item *>::iterator iEnd = children.end() ;
	std::list<SQLCaseExpr_Item *>::iterator  it;
	for (it=iStart ;it!=iEnd;++it)
	{
		(*it)->accept(visitor);
		//acceptChild(visitor, *it);
	}

}

void SQLCaseExpr::acceptChild(SQLASTVisitor *visitor, SQLExpr * child)
{
	if (child == NULL) {
		return;
	}

	child->accept(visitor);
}



