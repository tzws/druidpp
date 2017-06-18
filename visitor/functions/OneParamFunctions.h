#ifndef OneParamFunctions_HEADER_H 
#define OneParamFunctions_HEADER_H


#include "SQLEvalVisitor.h"
#include "SQLEvalVisitorUtils.h"
#include "SQLExpr.h"
#include "SQLMethodInvokeExpr.h"
#include "ParserException.h"

//import java.math.BigDecimal;
//import java.math.BigInteger;


//import com.alibaba.druid.util.Utils;

class OneParamFunctions : virtual public Function {
	public:
		static OneParamFunctions *instance();
		virtual ~OneParamFunctions();
		virtual Object *eval(SQLEvalVisitor *visitor, SQLMethodInvokeExpr *x);

		static std::string soundex(std::string str);

		static std::string clean(std::string str);

	private:
		static char getMappingCode(std::string str, int index);

		static char map(char ch);


};
#endif

