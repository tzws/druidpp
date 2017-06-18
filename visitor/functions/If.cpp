#include "If.h"

If::~If()
{

}

If * If::instance()
{
	static If x;
	return &x;
}


Object *If::eval(SQLEvalVisitor *visitor, SQLMethodInvokeExpr *x) {
	final List<SQLExpr> parameters = x.getParameters();
	if (parameters.size() == 0) {
		return EVAL_ERROR;
	}

	SQLExpr condition = parameters.get(0);
	condition.accept(visitor);
	Object itemValue = condition.getAttributes().get(EVAL_VALUE);
	if (Boolean.TRUE == itemValue || !SQLEvalVisitorUtils.eq(itemValue, 0)) {
		SQLExpr trueExpr = parameters.get(1);
		trueExpr.accept(visitor);
		return trueExpr.getAttributes().get(EVAL_VALUE);
	} else {
		SQLExpr falseExpr = parameters.get(2);
		falseExpr.accept(visitor);
		return falseExpr.getAttributes().get(EVAL_VALUE);
	}
}

