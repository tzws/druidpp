#include "Lpad.h"
Lpad::~Lpad()
{

}

Lpad * Lpad::instance()
{
	static Lpad x;
	return &x;
}

Object *Lpad::eval(SQLEvalVisitor *visitor, SQLMethodInvokeExpr *x) {
	List<SQLExpr> params = x.getParameters();
	int paramSize = params.size();
	if (paramSize != 3) {
		return SQLEvalVisitor.EVAL_ERROR;
	}

	SQLExpr param0 = params.get(0);
	SQLExpr param1 = params.get(1);
	SQLExpr param2 = params.get(2);

	param0.accept(visitor);
	param1.accept(visitor);
	param2.accept(visitor);

	Object param0Value = param0.getAttributes().get(EVAL_VALUE);
	Object param1Value = param1.getAttributes().get(EVAL_VALUE);
	Object param2Value = param2.getAttributes().get(EVAL_VALUE);
	if (param0Value == null || param1Value == null || param2Value == null) {
		return SQLEvalVisitor.EVAL_ERROR;
	}

	std::string strValue0 = param0Value.toString();
	int len = ((Number) param1Value).intValue();
	std::string strValue1 = param2Value.toString();

	std::string result = strValue0;
	if (result.length() > len) {
		return result.substring(0, len);
	}

	while (result.length() < len) {
		result = strValue1 + result;
	}

	return result;
}

