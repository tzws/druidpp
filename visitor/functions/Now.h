#ifndef Now_HEADER_H 
#define Now_HEADER_H


#include "SQLEvalVisitor.h"
#include "SQLEvalVisitorUtils.h"
#include "SQLExpr.h"
#include "SQLMethodInvokeExpr.h"
#include "ParserException.h"

class Now : virtual public Function {
	public:
		static Now *instance();
		virtual ~Now();
		virtual Object *eval(SQLEvalVisitor *visitor, SQLMethodInvokeExpr *x);
    
};
#endif

