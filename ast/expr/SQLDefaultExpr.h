#ifndef SQLDefaultExpr_HEADER_H
#define SQLDefaultExpr_HEADER_H

#include <boost/smart_ptr.hpp>
#include <string>

#include "../SQLExprImpl.h"
#include "../../visitor/SQLASTVisitor.h"

#include "SQLLiteralExpr.h"

class SQLDefaultExpr : virtual public SQLExprImpl, virtual public SQLLiteralExpr {

	public:
		SQLDefaultExpr();
		virtual ~SQLDefaultExpr();
		//bool equals(Object o);
		//int hashCode();

		//std::string &toString();
	protected:
		void accept0(SQLASTVisitor *visitor);

};
typedef boost::shared_ptr<SQLDefaultExpr> SQLDefaultExpr_ptr;

#endif
