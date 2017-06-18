#ifndef SQLNumberExpr_HEADER_H
#define SQLNumberExpr_HEADER_H

#include <boost/smart_ptr.hpp>

#include <string>

#include "../SQLExprImpl.h"
#include "../../visitor/SQLASTVisitor.h"
#include "SQLNumericLiteralExpr.h"


class SQLNumberExpr : virtual public SQLNumericLiteralExpr {

	private:
		RNumber *number;

	public:
		SQLNumberExpr();
		virtual ~SQLNumberExpr();

		SQLNumberExpr(RNumber *number);

		RNumber *getNumber();

		void setNumber(RNumber *number);

		void output(std::string & buf);

		//int hashCode();
		//bool equals(Object obj);
	protected:
		void accept0(SQLASTVisitor *visitor);

};
typedef boost::shared_ptr<SQLNumberExpr> SQLNumberExpr_ptr;
#endif

