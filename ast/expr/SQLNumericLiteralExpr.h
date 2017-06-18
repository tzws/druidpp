#ifndef SQLNumericLiteralExpr_HEADER_H
#define SQLNumericLiteralExpr_HEADER_H

#include <boost/smart_ptr.hpp>
#include <boost/rational.hpp>

#include "../SQLExprImpl.h"
//#include "../../visitor/SQLASTVisitor.h"

#include "SQLLiteralExpr.h"
using boost::rational;
typedef rational<double> RNumber;

class SQLNumericLiteralExpr : virtual public SQLExprImpl, virtual public SQLLiteralExpr {

	public:
		SQLNumericLiteralExpr(){

		}

		virtual ~SQLNumericLiteralExpr(){

		}


		virtual RNumber *getNumber() = 0;

		virtual void setNumber(RNumber *number) = 0;
};
typedef boost::shared_ptr<SQLNumericLiteralExpr> SQLNumericLiteralExpr_ptr;
#endif

