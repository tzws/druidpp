#include "Substring.h"
Substring::~Substring()
{

}

Substring * Substring::instance()
{
	static Substring x;
	return &x;
}

Object *Substring::eval(SQLEvalVisitor *visitor, SQLMethodInvokeExpr *x) {
	List<SQLExpr> params = x.getParameters();
	int paramSize = params.size();
	if (paramSize != 2 && paramSize != 3) {
		return SQLEvalVisitor.EVAL_ERROR;
	}

	SQLExpr param0 = params.get(0);
	SQLExpr param1 = params.get(1);
	param0.accept(visitor);
	param1.accept(visitor);

	Object param0Value = param0.getAttributes().get(EVAL_VALUE);
	Object param1Value = param1.getAttributes().get(EVAL_VALUE);
	if (param0Value == null || param1Value == null) {
		return SQLEvalVisitor.EVAL_ERROR;
	}

	std::string str = param0Value.toString();
	int index = ((Number) param1Value).intValue();

	if (paramSize == 2) {

		if (index < 0) {
			int lastIndex = str.length() + index;
			return str.substring(lastIndex);
		}

		return str.substring(index - 1);
	}

	SQLExpr param2 = params.get(2);
	param2.accept(visitor);
	Object param2Value = param2.getAttributes().get(EVAL_VALUE);
	if (param2Value == null) {
		return SQLEvalVisitor.EVAL_ERROR;
	}

	int len = ((Number) param2Value).intValue();

	std::string result;
	if (index < 0) {
		int lastIndex = str.length() + index;
		result = str.substring(lastIndex);
	} else {
		result = str.substring(index - 1);
	}

	if (len > result.length()) {
		return result;
	}
	return result.substring(0, len);
}


