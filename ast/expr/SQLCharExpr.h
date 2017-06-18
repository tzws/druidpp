#ifndef SQLCharExpr_HEADER_H
#define SQLCharExpr_HEADER_H

#include <boost/smart_ptr.hpp>
#include <string>
#include "../../visitor/SQLASTVisitor.h"
#include "SQLLiteralExpr.h"
#include "SQLTextLiteralExpr.h"

class SQLCharExpr : virtual public SQLTextLiteralExpr {
	typedef SQLTextLiteralExpr super;
	public:
		SQLCharExpr();
		virtual ~SQLCharExpr();

		SQLCharExpr(std::string &text);

		void output(std::string &buf);

	protected:
		void accept0(SQLASTVisitor *visitor);
};
typedef boost::shared_ptr<SQLCharExpr> SQLCharExpr_ptr;
#endif

