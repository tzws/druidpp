#include "SQLAggregateExpr.h"

SQLAggregateExpr::SQLAggregateExpr(std::string & theMethodName): over(NULL), methodName(theMethodName){

	//methodName = theMethodName;
}

SQLAggregateExpr::~SQLAggregateExpr(){


	for(std::list<SQLExpr *>::iterator it = arguments.begin(); it != arguments.end(); ++it) 
	{
		delete *it; 
	}
	arguments.clear();

	if (over != NULL)
	{
		delete over;
		over = NULL;
	}


}
SQLAggregateExpr::SQLAggregateExpr(std::string & theMethodName, Option theOption): over(NULL), methodName(theMethodName), option (theOption){
	//methodName = theMethodName;
	//option = theOption;
}

std::string &SQLAggregateExpr::getMethodName() {
	return methodName;
}

void SQLAggregateExpr::setMethodName(std::string &theMethodName) {
	methodName = theMethodName;
}

SQLAggregateExpr::Option SQLAggregateExpr::getOption() {
	return option;
}

void SQLAggregateExpr::setOption(Option theOption) {
	option = theOption;
}

std::list<SQLExpr *> & SQLAggregateExpr::getArguments() {
	return arguments;
}

SQLOver *SQLAggregateExpr::getOver() {
	return over;
}

void SQLAggregateExpr::setOver(SQLOver * theOver) {
	over = theOver;
}

void SQLAggregateExpr::accept0(SQLASTVisitor *visitor) {

	if (visitor->visit(this)) {
		acceptChild(visitor, arguments);
		acceptChild(visitor, over);
	}

	visitor->endVisit(this);
}

void SQLAggregateExpr::acceptChild(SQLASTVisitor *visitor, SQLOver * child)
{
	if (child == NULL) {
		return;
	}

	child->accept(visitor);
}

void SQLAggregateExpr::acceptChild(SQLASTVisitor *visitor, std::list<SQLExpr *> &children)
{
	
	if (children.empty()) {
		return;
	}

	std::list<SQLExpr *>::iterator iStart = children.begin() ;
	std::list<SQLExpr *>::iterator iEnd = children.end() ;
	std::list<SQLExpr *>::iterator  it;
	for (it=iStart ;it!=iEnd;++it)
	{
		(*it)->accept(visitor);
		//acceptChild(visitor, *it);
	}

}


