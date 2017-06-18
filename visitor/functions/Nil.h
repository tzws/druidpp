#ifndef Nil_HEADER_H 
#define Nil_HEADER_H


#include "SQLEvalVisitor.h"
#include "SQLEvalVisitorUtils.h"
#include "SQLExpr.h"
#include "SQLMethodInvokeExpr.h"
#include "ParserException.h"

class Nil : virtual public Function {
	public:
		static Nil *instance();
		virtual ~Nil();
		virtual Object *eval(SQLEvalVisitor *visitor, SQLMethodInvokeExpr *x);

};
#endif

