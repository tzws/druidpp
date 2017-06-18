#include "Char.h"

Char::~Char()
{

}

Char * Char::instance()
{
	static Char x;
	return &x;
}

Object *Char::eval(SQLEvalVisitor *visitor, SQLMethodInvokeExpr *x) {
	if (x.getParameters().size() == 0) {
		return SQLEvalVisitor.EVAL_ERROR;
	}

	StringBuffer buf = new StringBuffer(x.getParameters().size());
	for (SQLExpr param : x.getParameters()) {
		param.accept(visitor);

		Object paramValue = param.getAttributes().get(EVAL_VALUE);

		if (paramValue instanceof Number) {
			int charCode = ((Number) paramValue).intValue();
			buf.append((char) charCode);
		} else if (paramValue instanceof String) {
			int charCode = new BigDecimal((String)paramValue).intValue();
			buf.append((char) charCode);
		} else {
			return SQLEvalVisitor.EVAL_ERROR;
		}
	}

	return buf.toString();
}
