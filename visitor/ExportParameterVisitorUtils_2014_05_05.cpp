#include "ExportParameterVisitorUtils.h"

//here, the list std::list<Object *>, it's original java version will put String, int, double, etc... in this list. However only the size of the list is used, the elements in the list is not used at all. so, 
	//one way is to find a generic list in c++;
	//the other way in create a base class, and some wrapper class entends base for std::string, int, double ...
	//or, just keep the number of the parameters, not using the list at all.


bool ExportParameterVisitorUtils::exportParamterAndAccept(std::list<Object *> & parameters, std::list<SQLExpr *> &list) {

	for (std::list<SQLExpr *>::iterator it = list.begin(); it != list.end(); it++)
	{
		SQLExpr *param = *it;

		SQLExpr *result = exportParameter(parameters, param);
		if (result != param) {

			delete (*it);

			(*it) = result;
		}
	}

	return false;
}

SQLExpr *ExportParameterVisitorUtils::exportParameter(std::list<Object *> &parameters, SQLExpr *param) {

	SQLCharExpr* n = dynamic_cast<SQLCharExpr *>(param);
	if (n != 0)
	{
		Object * value = n->getText();
		parameters.add(value);
		return new SQLVariantRefExpr("?");
	}

	if (param instanceof SQLCharExpr) {
		Object * value = ((SQLCharExpr) param).getText();
		parameters.add(value);
		return new SQLVariantRefExpr("?");
	}

	if (param instanceof MySqlBooleanExpr) {
		Object * value = ((MySqlBooleanExpr) param).getValue();
		parameters.add(value);
		return new SQLVariantRefExpr("?");
	}

	if (param instanceof SQLNumericLiteralExpr) {
		Object * value = ((SQLNumericLiteralExpr) param).getNumber();
		parameters.add(value);
		return new SQLVariantRefExpr("?");
	}

	return param;
}

void ExportParameterVisitorUtils::exportParameter(std::list<Object *> &parameters, SQLBinaryOpExpr *x) {
	if (x.getLeft() instanceof SQLLiteralExpr 
			&& x.getRight() instanceof SQLLiteralExpr 
			&& x.getOperator().isRelational()) 
	{
		return;
	}

	{
		SQLExpr leftResult = ExportParameterVisitorUtils.exportParameter(parameters, x.getLeft());
		if (leftResult != x.getLeft()) {
			x.setLeft(leftResult);
		}
	}

	{
		SQLExpr rightResult = exportParameter(parameters, x.getRight());
		if (rightResult != x.getRight()) {
			x.setRight(rightResult);
		}
	}
}

void ExportParameterVisitorUtils::exportParameter(std::list<Object *> &parameters, SQLBetweenExpr *x) {
	{
		SQLExpr result = exportParameter(parameters, x.getBeginExpr());
		if (result != x.getBeginExpr()) {
			x.setBeginExpr(result);
		}
	}

	{
		SQLExpr result = exportParameter(parameters, x.getEndExpr());
		if (result != x.getBeginExpr()) {
			x.setEndExpr(result);
		}
	}

}

