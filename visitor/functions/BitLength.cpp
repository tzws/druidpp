#include "BitLength.h"

BitLength::~BitLength()
{

}

BitLength * BitLength::instance()
{
	static BitLength x; // Guaranteed to be destroyed.
	// Instantiated on first use.
	return &x;
}

Object *BitLength::eval(SQLEvalVisitor *visitor, SQLMethodInvokeExpr *x) {
	if (x.getParameters().size() != 1) {
		return SQLEvalVisitor.EVAL_ERROR;
	}

	SQLExpr param0 = x.getParameters().get(0);
	param0.accept(visitor);

	Object param0Value = param0.getAttributes().get(EVAL_VALUE);
	if (param0Value == null) {
		return SQLEvalVisitor.EVAL_ERROR;
	}

	if (param0Value instanceof String) {
		return ((String) param0Value).getBytes().length * 8;
	}
	return SQLEvalVisitor.EVAL_ERROR;
}
