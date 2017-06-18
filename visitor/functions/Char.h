#ifndef Char_HEADER_H 
#define Char_HEADER_H

//import java.math.BigDecimal;

#include "SQLEvalVisitor.h"
#include "SQLExpr.h"
#include "SQLMethodInvokeExpr.h"

class Char : virtual public Function {

	public:
		static Char *instance();
		virtual ~Char();
		virtual Object *eval(SQLEvalVisitor *visitor, SQLMethodInvokeExpr *x);
};
#endif

