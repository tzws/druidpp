#ifndef Unhex_HEADER_H 
#define Unhex_HEADER_H


#include "SQLEvalVisitor.h"
#include "SQLEvalVisitorUtils.h"
#include "SQLExpr.h"
#include "SQLMethodInvokeExpr.h"
#include "ParserException.h"

//import java.io.UnsupportedEncodingException;

//import com.alibaba.druid.util.HexBin;

class Unhex : virtual public Function {

	public:
		static Unhex *instance();
		virtual ~Unhex();
		virtual Object *eval(SQLEvalVisitor *visitor, SQLMethodInvokeExpr *x);

};
#endif

