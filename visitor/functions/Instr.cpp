#include "Instr.h"
Instr::~Instr()
{

}

Instr * Instr::instance()
{
	static Instr x;
	return &x;
}

Object *Instr::eval(SQLEvalVisitor *visitor, SQLMethodInvokeExpr *x) {
	if (x.getParameters().size() != 2) {
		return SQLEvalVisitor.EVAL_ERROR;
	}

	SQLExpr param0 = x.getParameters().get(0);
	SQLExpr param1 = x.getParameters().get(1);
	param0.accept(visitor);
	param1.accept(visitor);

	Object param0Value = param0.getAttributes().get(EVAL_VALUE);
	Object param1Value = param1.getAttributes().get(EVAL_VALUE);
	if (param0Value == null || param1Value == null) {
		return SQLEvalVisitor.EVAL_ERROR;
	}

	String strValue0 = param0Value.toString();
	String strValue1 = param1Value.toString();

	int result = strValue0.indexOf(strValue1) + 1;
	return result;
}

