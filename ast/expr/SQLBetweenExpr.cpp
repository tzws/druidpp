#include "SQLBetweenExpr.h"

SQLBetweenExpr::SQLBetweenExpr(){

}
SQLBetweenExpr::~SQLBetweenExpr(){
	if (testExpr != NULL)
	{
		delete testExpr;
		testExpr = NULL;
	}

	if (beginExpr != NULL)
	{
		delete beginExpr;
		beginExpr = NULL;
	}

	if (endExpr != NULL)
	{
		delete endExpr;
		endExpr = NULL;
	}



}
SQLBetweenExpr::SQLBetweenExpr(SQLExpr *theTestExpr, SQLExpr *theBeginExpr, SQLExpr *theEndExpr)
	:

		testExpr(theTestExpr), beginExpr(theBeginExpr), endExpr (theEndExpr)
{
	//setTestExpr(testExpr);
	//setBeginExpr(beginExpr);
	//setEndExpr(endExpr);
}

SQLBetweenExpr::SQLBetweenExpr(SQLExpr *theTestExpr, bool theXnot, SQLExpr *theBeginExpr, SQLExpr *theEndExpr) :
	testExpr(theTestExpr), beginExpr(theBeginExpr), endExpr (theEndExpr) , xnot (theXnot)

{
	//this(testExpr, beginExpr, endExpr);
	//this.xnot = xnot;
}

void SQLBetweenExpr::accept0(SQLASTVisitor *visitor) {
	if (visitor->visit(this)) {
		acceptChild(visitor, testExpr);
		acceptChild(visitor, beginExpr);
		acceptChild(visitor, endExpr);
	}
	visitor->endVisit(this);
}

SQLExpr *SQLBetweenExpr::getTestExpr() {
	return testExpr;
}

void SQLBetweenExpr::setTestExpr(SQLExpr *theTestExpr) {
	if (theTestExpr != NULL) {
		theTestExpr->setParent(this);
	}
	testExpr = theTestExpr;
}

bool SQLBetweenExpr::isNot() {
	return xnot;
}

void SQLBetweenExpr::setNot(bool theXnot) {
	xnot = theXnot;
}

SQLExpr *SQLBetweenExpr::getBeginExpr() {
	return beginExpr;
}

void SQLBetweenExpr::setBeginExpr(SQLExpr *theBeginExpr) {
	if (theBeginExpr != NULL) {
		theBeginExpr->setParent(this);
	}
	beginExpr = theBeginExpr;
}

SQLExpr *SQLBetweenExpr::getEndExpr() {
	return endExpr;
}

void SQLBetweenExpr::setEndExpr(SQLExpr *theEndExpr) {
	if (theEndExpr != NULL) {
		theEndExpr->setParent(this);
	}
	endExpr = theEndExpr;
}

//int SQLBetweenExpr::hashCode() {
	//int prime = 31;
	//int result = 1;
	//result = prime * result + ((beginExpr == NULL) ? 0 : beginExpr.hashCode());
	//result = prime * result + ((endExpr == NULL) ? 0 : endExpr.hashCode());
	//result = prime * result + (xnot ? 1231 : 1237);
	//result = prime * result + ((testExpr == NULL) ? 0 : testExpr.hashCode());
	//return result;
//}

//bool SQLBetweenExpr::equals(Object obj) {
	//if (this == obj) {
		//return true;
	//}
	//if (obj == NULL) {
		//return false;
	//}
	//if (getClass() != obj.getClass()) {
		//return false;
	//}
	//SQLBetweenExpr other = (SQLBetweenExpr) obj;
	//if (beginExpr == NULL) {
		//if (other.beginExpr != NULL) {
			//return false;
		//}
	//} else if (!beginExpr.equals(other.beginExpr)) {
		//return false;
	//}
	//if (endExpr == NULL) {
		//if (other.endExpr != NULL) {
			//return false;
		//}
	//} else if (!endExpr.equals(other.endExpr)) {
		//return false;
	//}
	//if (xnot != other.xnot) {
		//return false;
	//}
	//if (testExpr == NULL) {
		//if (other.testExpr != NULL) {
			//return false;
		//}
	//} else if (!testExpr.equals(other.testExpr)) {
		//return false;
	//}
	//return true;
//}

