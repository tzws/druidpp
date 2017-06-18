#ifndef Lpad_HEADER_H 
#define Lpad_HEADER_H


#include "SQLEvalVisitor.h"
#include "SQLEvalVisitorUtils.h"
#include "SQLExpr.h"
#include "SQLMethodInvokeExpr.h"
#include "ParserException.h"

class Lpad : virtual public Function {
	public:
		static Lpad *instance();
		virtual ~Lpad();
		virtual Object *eval(SQLEvalVisitor *visitor, SQLMethodInvokeExpr *x);

};
#endif

