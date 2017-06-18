#include "Left.h"
Left::~Left()
{

}

Left * Left::instance()
{
	static Left x;
	return &x;
}

Object * Left::eval(SQLEvalVisitor *visitor, SQLMethodInvokeExpr *x) {
	if (x.getParameters().size() != 2) {
		return SQLEvalVisitor.EVAL_ERROR;
	}

	SQLExpr param0 = x.getParameters().get(0);
	SQLExpr param1 = x.getParameters().get(1);
	param0.accept(visitor);
	param1.accept(visitor);

	Object param0Value = param0.getAttributes().get(EVAL_VALUE);
	Object param1Value = param1.getAttributes().get(EVAL_VALUE);
	if (param0Value == null || param1Value == null) {
		return SQLEvalVisitor.EVAL_ERROR;
	}

	std::string strValue = param0Value.toString();
	int intValue = SQLEvalVisitorUtils.castToInteger(param1Value);

	if (intValue > strValue.length()) {
		return SQLEvalVisitor.EVAL_ERROR;
	}

	std::string result = strValue.substring(0, intValue);

	return result;
}

