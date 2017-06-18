#include "Reverse.h"    
Reverse::~Reverse()
{

}

Reverse * Reverse::instance()
{
	static Reverse x;
	return &x;
}

Object *Reverse::eval(SQLEvalVisitor *visitor, SQLMethodInvokeExpr *x) {
	if (x.getParameters().size() != 1) {
		return SQLEvalVisitor.EVAL_ERROR;
	}

	SQLExpr param0 = x.getParameters().get(0);
	param0.accept(visitor);

	Object param0Value = param0.getAttributes().get(EVAL_VALUE);
	if (param0Value == null) {
		return SQLEvalVisitor.EVAL_ERROR;
	}

	std::string strValue = param0Value.toString();

	StringBuilder buf = new StringBuilder();
	for (int i = strValue.length() - 1; i >= 0; --i) {
		buf.append(strValue.charAt(i));
	}
	std::string result = buf.toString();
	return result;
}

