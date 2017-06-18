#ifndef Isnull_HEADER_H 
#define Isnull_HEADER_H


#include "SQLEvalVisitor.h"
#include "SQLEvalVisitorUtils.h"
#include "SQLExpr.h"
#include "SQLMethodInvokeExpr.h"
#include "ParserException.h"

public class Isnull : virtual public Function {

	public:
		static Isnull *instance();
		virtual ~Isnull();
		virtual Object *eval(SQLEvalVisitor *visitor, SQLMethodInvokeExpr *x);

};
#endif

