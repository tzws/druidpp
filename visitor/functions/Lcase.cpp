#include "Lcase.h"    
Lcase::~Lcase()
{

}

Lcase * Lcase::instance()
{
	static Lcase x;
	return &x;
}

Object *Lcase::eval(SQLEvalVisitor *visitor, SQLMethodInvokeExpr *x) {
	if (x.getParameters().size() != 1) {
		return SQLEvalVisitor.EVAL_ERROR;
	}

	SQLExpr param0 = x.getParameters().get(0);
	param0.accept(visitor);

	Object param0Value = param0.getAttributes().get(EVAL_VALUE);
	if (param0Value == null) {
		return SQLEvalVisitor.EVAL_ERROR;
	}

	std::string strValue = param0Value.toString();

	std::string result = strValue.toLowerCase();

	return result;
}

