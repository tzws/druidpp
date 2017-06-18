#include "Concat.h"

Concat::~Concat()
{

}

Concat * Concat::instance()
{
	static Concat x;
	return &x;
}

Object *Concat::eval(SQLEvalVisitor *visitor, SQLMethodInvokeExpr *x) {
	StringBuilder buf = new StringBuilder();

	for (SQLExpr item : x.getParameters()) {
		item.accept(visitor);

		Object itemValue = item.getAttributes().get(EVAL_VALUE);
		if (itemValue == null) {
			return null;
		}
		buf.append(itemValue.toString());
	}

	return buf.toString();
}
