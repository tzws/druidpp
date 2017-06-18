#include "SQLBinaryOpExpr.h"
SQLBinaryOpExpr::SQLBinaryOpExpr() : left(NULL), right(NULL), xoperator(NULL){

}
SQLBinaryOpExpr::~SQLBinaryOpExpr(){

	//std::cout << __FILE__ << ": " << __LINE__ << ", in SQLBinaryOpExpr::~SQLBinaryOpExpr, step 1 " << std::endl;
	if (left)
	{
		delete left;
		left = 0;
	}

	if (right != NULL)
	{
		delete right;
		right = NULL;
	}

	//if (xoperator != NULL)
	//{
		//delete xoperator;
		//xoperator = NULL;

	//}

	//std::cout << __FILE__ << ": " << __LINE__ << ", in SQLBinaryOpExpr::~SQLBinaryOpExpr, step 2 " << std::endl;
}
SQLBinaryOpExpr::SQLBinaryOpExpr(SQLExpr *theLeft, SQLBinaryOperator *theXoperator, SQLExpr *theRight){

	setLeft(theLeft);
	setRight(theRight);
	this->xoperator = theXoperator;
}

SQLBinaryOpExpr::SQLBinaryOpExpr(SQLExpr *theLeft, SQLExpr *theRight, SQLBinaryOperator *theXoperator){

	setLeft(theLeft);
	setRight(theRight);
	this->xoperator = theXoperator;
}

SQLExpr *SQLBinaryOpExpr::getLeft() {
	return this->left;
}

void SQLBinaryOpExpr::setLeft(SQLExpr *theLeft) {
	if (theLeft!= NULL) {
		theLeft->setParent(this);
	}
	this->left = theLeft;
}

SQLExpr *SQLBinaryOpExpr::getRight() {
	return this->right;
}

void SQLBinaryOpExpr::setRight(SQLExpr *theRight) {
	if (theRight != NULL) {
		theRight->setParent(this);
	}
	this->right = theRight;
}

SQLBinaryOperator *SQLBinaryOpExpr::getOperator() {
	return this->xoperator;
}

void SQLBinaryOpExpr::setOperator(SQLBinaryOperator *theXoperator) {
	this->xoperator = theXoperator;
}

void SQLBinaryOpExpr::accept0(SQLASTVisitor *visitor) {
	if (visitor->visit(this)) {
		acceptChild(visitor, this->left);
		acceptChild(visitor, this->right);
	}

	visitor->endVisit(this);
}

//int hashCode() {
	//int prime = 31;
	//int result = 1;
	//result = prime * result + ((left == NULL) ? 0 : left.hashCode());
	//result = prime * result + ((xoperator == NULL) ? 0 : xoperator.hashCode());
	//result = prime * result + ((right == NULL) ? 0 : right.hashCode());
	//return result;
//}

//bool equals(Object obj) {
	//if (this == obj) {
		//return true;
	//}
	//if (obj == NULL) {
		//return false;
	//}
	//if (!(obj instanceof SQLBinaryOpExpr)) {
		//return false;
	//}
	//SQLBinaryOpExpr other = (SQLBinaryOpExpr) obj;
	//if (left == NULL) {
		//if (other.left != NULL) {
			//return false;
		//}
	//} else if (!left.equals(other.left)) {
		//return false;
	//}
	//if (xoperator != other.xoperator) {
		//return false;
	//}
	//if (right == NULL) {
		//if (other.right != NULL) {
			//return false;
		//}
	//} else if (!right.equals(other.right)) {
		//return false;
	//}
	//return true;
//}

