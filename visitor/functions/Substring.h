#ifndef Substring_HEADER_H 
#define Substring_HEADER_H


#include "SQLEvalVisitor.h"
#include "SQLEvalVisitorUtils.h"
#include "SQLExpr.h"
#include "SQLMethodInvokeExpr.h"
#include "ParserException.h"

class Substring : virtual public Function {
 	public:
		static Substring *instance();
		virtual ~Substring();
		virtual Object *eval(SQLEvalVisitor *visitor, SQLMethodInvokeExpr *x);


};
#endif

