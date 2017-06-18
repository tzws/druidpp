#ifndef BitLength_HEADER_H 
#define BitLength_HEADER_H

#include "SQLEvalVisitor.h"
#include "SQLExpr.h"
#include "SQLMethodInvokeExpr.h"


class BitLength : virtual public Function {

	public:
		static BitLength *instance();
		virtual ~BitLength();

		virtual Object *eval(SQLEvalVisitor *visitor, SQLMethodInvokeExpr *x);
};
#endif

