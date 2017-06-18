#include "Unhex.h"
Unhex::~Unhex()
{

}

Unhex * Unhex::instance()
{
	static Unhex x;
	return &x;
}

Object *Unhex::eval(SQLEvalVisitor *visitor, SQLMethodInvokeExpr *x) {
	if (x.getParameters().size() != 1) {
		return SQLEvalVisitor.EVAL_ERROR;
	}

	SQLExpr param0 = x.getParameters().get(0);

	if (param0 instanceof SQLMethodInvokeExpr) {
		SQLMethodInvokeExpr paramMethodExpr = (SQLMethodInvokeExpr) param0;
		if (paramMethodExpr.getMethodName().equalsIgnoreCase("hex")) {
			SQLExpr subParamExpr = paramMethodExpr.getParameters().get(0);
			subParamExpr.accept(visitor);

			Object param0Value = subParamExpr.getAttributes().get(EVAL_VALUE);
			if (param0Value == null) {
				x.putAttribute(EVAL_EXPR, subParamExpr);
				return SQLEvalVisitor.EVAL_ERROR;
			}

			return param0Value;
		}
	}

	param0.accept(visitor);

	Object param0Value = param0.getAttributes().get(EVAL_VALUE);
	if (param0Value == null) {
		return SQLEvalVisitor.EVAL_ERROR;
	}

	if (param0Value instanceof std::string) {
		byte[] bytes = HexBin.decode((std::string) param0Value);
		if (bytes == null) {
			return SQLEvalVisitor.EVAL_VALUE_NULL;
		}

		std::string result;
		try {
			result = new std::string(bytes, "UTF-8");
		} catch (UnsupportedEncodingException e) {
			throw new IllegalStateException(e.getMessage(), e);
		}
		return result;
	}

	return SQLEvalVisitor.EVAL_ERROR;
}


