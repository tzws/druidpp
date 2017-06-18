
#include "Ascii.h"

//Ascii *Ascii::ins = new Ascii();
//bool Ascii::_init = Ascii::init();
//Ascii::Ascii() : instance (nullptr)
Ascii::Ascii() 
{

}

Ascii::~Ascii()
{

}

Ascii * Ascii::instance()
{
	static Ascii x; // Guaranteed to be destroyed.
	// Instantiated on first use.
	return &x;
}

//bool Ascii::init()
//{
	//if (ins == NULL)
	//{
		//ins = new Ascii();
	//}
	//return true;
//}

Object *Ascii::eval(SQLEvalVisitor *visitor, SQLMethodInvokeExpr *x) {
	if (x.getParameters().size() == 0) {
		return SQLEvalVisitor.EVAL_ERROR;
	}
	SQLExpr param = x.getParameters().get(0);
	param.accept(visitor);

	Object paramValue = param.getAttributes().get(EVAL_VALUE);
	if (paramValue == null) {
		return SQLEvalVisitor.EVAL_ERROR;
	}

	if (paramValue == EVAL_VALUE_NULL) {
		return EVAL_VALUE_NULL;
	}

	String strValue = paramValue.toString();
	if (strValue.length() == 0) {
		return 0;
	}

	int ascii = strValue.charAt(0);
	return ascii;
}
