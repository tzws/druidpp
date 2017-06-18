#ifndef Function_HEADER_H 
#define Function_HEADER_H
#include "SQLMethodInvokeExpr.h"
#include "SQLEvalVisitor.h"


class Function {
	public: 
		virtual Object *eval(SQLEvalVisitor *visitor, SQLMethodInvokeExpr *x) = 0;
};
#endif

