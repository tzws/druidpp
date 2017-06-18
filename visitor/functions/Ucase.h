#ifndef Ucase_HEADER_H 
#define Ucase_HEADER_H


#include "SQLEvalVisitor.h"
#include "SQLEvalVisitorUtils.h"
#include "SQLExpr.h"
#include "SQLMethodInvokeExpr.h"
#include "ParserException.h"

class Ucase : virtual public Function {
	public:
		static Ucase *instance();
		virtual ~Ucase();
		virtual Object *eval(SQLEvalVisitor *visitor, SQLMethodInvokeExpr *x);


};
#endif

