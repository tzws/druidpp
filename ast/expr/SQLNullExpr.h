#ifndef SQLNullExpr_HEADER_H
#define SQLNullExpr_HEADER_H

#include <boost/smart_ptr.hpp>
#include <string>
#include "../SQLExpr.h"
#include "../SQLExprImpl.h"
#include "../../visitor/SQLASTVisitor.h"

#include "SQLLiteralExpr.h"

class SQLNullExpr : virtual public SQLExprImpl, virtual public SQLLiteralExpr {

	public:
		SQLNullExpr();
		virtual ~SQLNullExpr();

		void output(std::string & buf);

		//int hashCode();
		//bool equals(Object o);
	protected:
		void accept0(SQLASTVisitor *visitor);

};
typedef boost::shared_ptr<SQLNullExpr> SQLNullExpr_ptr;
#endif

