#ifndef Hex_HEADER_H 
#define Hex_HEADER_H


#include "SQLEvalVisitor.h"
#include "SQLExpr.h"
#include "SQLMethodInvokeExpr.h"
#include "ParserException.h"
#include "HexBin.h"


class Hex : virtual public Function {


	public:
		static Hex *instance();
		virtual ~Hex();
		virtual Object *eval(SQLEvalVisitor *visitor, SQLMethodInvokeExpr *x);
};
#endif

