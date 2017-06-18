#ifndef Least_HEADER_H 
#define Least_HEADER_H


#include "SQLEvalVisitor.h"
#include "SQLEvalVisitorUtils.h"
#include "SQLExpr.h"
#include "SQLMethodInvokeExpr.h"
#include "ParserException.h"

class Least : virtual public Function {
	public:
		static Least *instance();
		virtual ~Least();
		virtual Object *eval(SQLEvalVisitor *visitor, SQLMethodInvokeExpr *x);

};
#endif

