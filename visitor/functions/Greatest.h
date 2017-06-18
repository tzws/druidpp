#ifndef Greatest_HEADER_H 
#define Greatest_HEADER_H


#include "SQLEvalVisitor.h"
#include "SQLExpr.h"
#include "SQLMethodInvokeExpr.h"
#include "SQLEvalVisitorUtils.h"


class Greatest : virtual public Function {


	public:
		static Greatest *instance();
		virtual ~Greatest();
		virtual Object *eval(SQLEvalVisitor *visitor, SQLMethodInvokeExpr *x);
};
#endif

