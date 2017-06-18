#ifndef Instr_HEADER_H 
#define Instr_HEADER_H


#include "SQLEvalVisitor.h"
#include "SQLEvalVisitorUtils.h"
#include "SQLExpr.h"
#include "SQLMethodInvokeExpr.h"
#include "ParserException.h"

class Instr : virtual public Function {
    
	public:
		static Instr *instance();
		virtual ~Instr();
		virtual Object *eval(SQLEvalVisitor *visitor, SQLMethodInvokeExpr *x);
};
#endif

