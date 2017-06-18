#include "ExportParameterVisitorUtils.h"

//here, the list std::list<Object *>, it's original java version will put String, int, double, etc... in this list. However only the size of the list is used, the elements in the list is not used at all. so, 
	//one way is to find a generic list in c++;
	//the other way in create a base class, and some wrapper class entends base for std::string, int, double ...
	//or, just keep the number of the parameters, not using the list at all.


bool ExportParameterVisitorUtils::exportParamterAndAccept(int &size, std::list<SQLExpr *> &list) {

	for (std::list<SQLExpr *>::iterator it = list.begin(); it != list.end(); it++)
	{
		SQLExpr *param = *it;

		SQLExpr *result = exportParameter(size, param);
		if (result != param) {

			delete (*it);

			(*it) = result;
		}
	}

	return false;
}

SQLExpr *ExportParameterVisitorUtils::exportParameter(int &size, SQLExpr *param) {

	SQLCharExpr* n = dynamic_cast<SQLCharExpr *>(param);
	if (n != 0)
	{
		//Object * value = n->getText();
		//parameters.add(value);
		size++;
		return new SQLVariantRefExpr("?");
		//return new SQLVariantRefExpr(std::string("?"));
	}

	//MySqlBooleanExpr* n1 = dynamic_cast<MySqlBooleanExpr *>(param);
	//if (n1 != 0)
	//{
		//size++;
		//return new SQLVariantRefExpr("?");
		//return new SQLVariantRefExpr(std::string("?"));
	//}


	SQLNumericLiteralExpr* n2 = dynamic_cast<SQLNumericLiteralExpr *>(param);
	if (n2 != 0)
	{
		size++;
		return new SQLVariantRefExpr("?");
		//return new SQLVariantRefExpr(std::string("?"));
	}

	return param;
}

void ExportParameterVisitorUtils::exportParameter(int &size, SQLBinaryOpExpr *x) {

	SQLLiteralExpr * left = dynamic_cast<SQLLiteralExpr *>(x->getLeft() );
	SQLLiteralExpr * right = dynamic_cast<SQLLiteralExpr *>(x->getRight() );

	if (left != NULL  
			&& right != NULL 
			&& x->getOperator()->isRelational()) 
	{
		return;
	}

	{
		SQLExpr *leftResult = ExportParameterVisitorUtils::exportParameter(size, x->getLeft());
		if (leftResult != x->getLeft()) {
			x->setLeft(leftResult);
		}
	}

	{
		SQLExpr *rightResult = exportParameter(size, x->getRight());
		if (rightResult != x->getRight()) {
			x->setRight(rightResult);
		}
	}
}

void ExportParameterVisitorUtils::exportParameter(int &size, SQLBetweenExpr *x) {
	{
		SQLExpr *result = exportParameter(size, x->getBeginExpr());
		if (result != x->getBeginExpr()) {
			x->setBeginExpr(result);
		}
	}

	{
		SQLExpr *result = exportParameter(size, x->getEndExpr());
		if (result != x->getBeginExpr()) {
			x->setEndExpr(result);
		}
	}

}

