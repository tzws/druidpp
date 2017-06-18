#ifndef Left_HEADER_H 
#define Left_HEADER_H


#include "SQLEvalVisitor.h"
#include "SQLEvalVisitorUtils.h"
#include "SQLExpr.h"
#include "SQLMethodInvokeExpr.h"
#include "ParserException.h"

class Left : virtual public Function {
	public:
		static Left *instance();
		virtual ~Left();
		virtual Object *eval(SQLEvalVisitor *visitor, SQLMethodInvokeExpr *x);

};
#endif

