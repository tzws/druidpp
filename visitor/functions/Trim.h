#ifndef Trim_HEADER_H 
#define Trim_HEADER_H


#include "SQLEvalVisitor.h"
#include "SQLEvalVisitorUtils.h"
#include "SQLExpr.h"
#include "SQLMethodInvokeExpr.h"
#include "ParserException.h"

class Trim : virtual public Function {
 	public:
		static Trim *instance();
		virtual ~Trim();
		virtual Object *eval(SQLEvalVisitor *visitor, SQLMethodInvokeExpr *x);


};
#endif

