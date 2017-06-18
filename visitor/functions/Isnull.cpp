#include "Isnull.h"
Isnull::~Isnull()
{

}

Isnull * Isnull::instance()
{
	static Isnull x;
	return &x;
}

Object *Isnull::eval(SQLEvalVisitor *visitor, SQLMethodInvokeExpr *x) {
	final List<SQLExpr> parameters = x.getParameters();
	if (parameters.size() == 0) {
		return EVAL_ERROR;
	}

	SQLExpr condition = parameters.get(0);
	condition.accept(visitor);
	Object itemValue = condition.getAttributes().get(EVAL_VALUE);
	if (itemValue == EVAL_VALUE_NULL) {
		return Boolean.TRUE;
	} else if (itemValue == null) {
		return null;
	} else {
		return Boolean.FALSE;
	}
}

