#include "Insert.h"
Insert::~Insert()
{

}

Insert * Insert::instance()
{
	static Insert x;
	return &x;
}


Object *Insert::eval(SQLEvalVisitor *visitor, SQLMethodInvokeExpr *x) {
	if (x.getParameters().size() != 4) {
		return SQLEvalVisitor.EVAL_ERROR;
	}

	SQLExpr param0 = x.getParameters().get(0);
	SQLExpr param1 = x.getParameters().get(1);
	SQLExpr param2 = x.getParameters().get(2);
	SQLExpr param3 = x.getParameters().get(3);
	param0.accept(visitor);
	param1.accept(visitor);
	param2.accept(visitor);
	param3.accept(visitor);

	Object param0Value = param0.getAttributes().get(EVAL_VALUE);
	Object param1Value = param1.getAttributes().get(EVAL_VALUE);
	Object param2Value = param2.getAttributes().get(EVAL_VALUE);
	Object param3Value = param3.getAttributes().get(EVAL_VALUE);

	if (!(param0Value instanceof String)) {
		return SQLEvalVisitor.EVAL_ERROR;
	}
	if (!(param1Value instanceof Number)) {
		return SQLEvalVisitor.EVAL_ERROR;
	}
	if (!(param2Value instanceof Number)) {
		return SQLEvalVisitor.EVAL_ERROR;
	}
	if (!(param3Value instanceof String)) {
		return SQLEvalVisitor.EVAL_ERROR;
	}

	String str = (String) param0Value;
	int pos = ((Number) param1Value).intValue();
	int len = ((Number) param2Value).intValue();
	String newstr = (String) param3Value;

	if (pos <= 0) {
		return str;
	}

	if (pos == 1) {
		if (len > str.length()) {
			return newstr;
		}
		return newstr + str.substring(len);
	}

	String first = str.substring(0, pos - 1);
	if (pos + len - 1 > str.length()) {
		return first + newstr;
	}

	return first + newstr + str.substring(pos + len - 1);
}
