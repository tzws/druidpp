#ifndef SQLIntegerExpr_HEADER_H
#define SQLIntegerExpr_HEADER_H

#include <boost/smart_ptr.hpp>

#include <string>

#include "../../visitor/SQLASTVisitor.h"
#include "SQLNumericLiteralExpr.h"


class SQLIntegerExpr : virtual public SQLNumericLiteralExpr {

	private:
		RNumber *number;

	public:
		SQLIntegerExpr(RNumber *number);

		SQLIntegerExpr();
		virtual ~SQLIntegerExpr();

		RNumber *getNumber();
		int intValue();

		void setNumber(RNumber *number);

		void output(std::string & buf);

		//int hashCode();
		//bool equals(Object obj);
	protected:
		void accept0(SQLASTVisitor *visitor);

};
typedef boost::shared_ptr<SQLIntegerExpr> SQLIntegerExpr_ptr;
#endif

