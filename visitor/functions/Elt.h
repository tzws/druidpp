#ifndef Elt_HEADER_H 
#define Elt_HEADER_H


#include "SQLEvalVisitor.h"
#include "SQLExpr.h"
#include "SQLMethodInvokeExpr.h"

class Elt : virtual  Function {


	public:
		static Elt *instance();
		virtual ~Elt();
		virtual Object *eval(SQLEvalVisitor *visitor, SQLMethodInvokeExpr *x);
};
#endif

