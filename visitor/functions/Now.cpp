#include "Now.h"    
Now::~Now()
{

}

Now * Now::instance()
{
	static Now x;
	return &x;
}

Object *Now::eval(SQLEvalVisitor *visitor, SQLMethodInvokeExpr *x) {
	return new Date();
}


