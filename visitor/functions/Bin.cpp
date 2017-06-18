#include "Bin.h"

Bin::~Bin()
{

}

Bin * Bin::instance()
{
	static Bin x; // Guaranteed to be destroyed.
	// Instantiated on first use.
	return &x;
}

Object *Bin::eval(SQLEvalVisitor *visitor, SQLMethodInvokeExpr *x) {
	if (x.getParameters().size() != 1) {
		return SQLEvalVisitor.EVAL_ERROR;
	}

	SQLExpr param0 = x.getParameters().get(0);
	param0.accept(visitor);

	Object param0Value = param0.getAttributes().get(EVAL_VALUE);
	if (param0Value == null) {
		return SQLEvalVisitor.EVAL_ERROR;
	}

	if (param0Value instanceof Number) {
		long longValue = ((Number) param0Value).longValue();
		String result = Long.toString(longValue, 2);
		return result;
	}
	return SQLEvalVisitor.EVAL_ERROR;
}
