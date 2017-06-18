#ifndef Bin_HEADER_H 
#define Bin_HEADER_H

#include "SQLEvalVisitor.h"
#include "SQLExpr.h"
#include "SQLMethodInvokeExpr.h"

class Bin : virtual public Function {

	public:
		//static Bin instance = new Bin();

		static Bin *instance();
		virtual ~Bin();
		virtual Object *eval(SQLEvalVisitor *visitor, SQLMethodInvokeExpr *x);
};
#endif
