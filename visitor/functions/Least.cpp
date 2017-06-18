#include "Least.h"
Least::~Least()
{

}

Least * Least::instance()
{
	static Least x;
	return &x;
}

Object *Least::eval(SQLEvalVisitor *visitor, SQLMethodInvokeExpr *x) {
	Object result = null;
	for (SQLExpr item : x.getParameters()) {
		item.accept(visitor);

		Object itemValue = item.getAttributes().get(EVAL_VALUE);
		if (result == null) {
			result = itemValue;
		} else {
			if (SQLEvalVisitorUtils.lt(itemValue, result)) {
				result = itemValue;
			}
		}
	}

	return result;
}

