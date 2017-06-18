#ifndef Reverse_HEADER_H 
#define Reverse_HEADER_H


#include "SQLEvalVisitor.h"
#include "SQLEvalVisitorUtils.h"
#include "SQLExpr.h"
#include "SQLMethodInvokeExpr.h"
#include "ParserException.h"

class Reverse : virtual public Function {
 	public:
		static Reverse *instance();
		virtual ~Reverse();
		virtual Object *eval(SQLEvalVisitor *visitor, SQLMethodInvokeExpr *x);
   
};
#endif

