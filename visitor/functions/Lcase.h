#ifndef Lcase_HEADER_H 
#define Lcase_HEADER_H


#include "SQLEvalVisitor.h"
#include "SQLEvalVisitorUtils.h"
#include "SQLExpr.h"
#include "SQLMethodInvokeExpr.h"
#include "ParserException.h"

class Lcase : virtual public Function {
	public:
		static Lcase *instance();
		virtual ~Lcase();
		virtual Object *eval(SQLEvalVisitor *visitor, SQLMethodInvokeExpr *x);

};
#endif

