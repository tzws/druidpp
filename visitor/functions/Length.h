#ifndef Length_HEADER_H 
#define Length_HEADER_H


#include "SQLEvalVisitor.h"
#include "SQLEvalVisitorUtils.h"
#include "SQLExpr.h"
#include "SQLMethodInvokeExpr.h"
#include "ParserException.h"

class Length : virtual public Function {
	public:
		static Length *instance();
		virtual ~Length();
		virtual Object *eval(SQLEvalVisitor *visitor, SQLMethodInvokeExpr *x);

};
#endif

