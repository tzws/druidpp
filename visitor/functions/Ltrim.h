#ifndef Ltrim_HEADER_H 
#define Ltrim_HEADER_H


#include "SQLEvalVisitor.h"
#include "SQLEvalVisitorUtils.h"
#include "SQLExpr.h"
#include "SQLMethodInvokeExpr.h"
#include "ParserException.h"

class Ltrim : virtual public Function {
	public:
		static Ltrim *instance();
		virtual ~Ltrim();
		virtual Object *eval(SQLEvalVisitor *visitor, SQLMethodInvokeExpr *x);

};
#endif

