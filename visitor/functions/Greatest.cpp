#$include "Greatest.h"

Greatest::~Greatest()
{

}

Greatest * Greatest::instance()
{
	static Greatest x;
	return &x;
}

Object *Greatest::eval(SQLEvalVisitor *visitor, SQLMethodInvokeExpr *x) {
	Object result = null;
	for (SQLExpr item : x.getParameters()) {
		item.accept(visitor);

		Object itemValue = item.getAttributes().get(EVAL_VALUE);
		if (result == null) {
			result = itemValue;
		} else {
			if (SQLEvalVisitorUtils.gt(itemValue, result)) {
				result = itemValue;
			}
		}
	}

	return result;
}

