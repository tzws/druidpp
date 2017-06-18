#ifndef Right_HEADER_H 
#define Right_HEADER_H


#include "SQLEvalVisitor.h"
#include "SQLEvalVisitorUtils.h"
#include "SQLExpr.h"
#include "SQLMethodInvokeExpr.h"
#include "ParserException.h"

class Right : virtual public Function {
 	public:
		static Right *instance();
		virtual ~Right();
		virtual Object *eval(SQLEvalVisitor *visitor, SQLMethodInvokeExpr *x);


};
#endif

