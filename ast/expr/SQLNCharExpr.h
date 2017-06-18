#ifndef SQLNCharExpr_HEADER_H
#define SQLNCharExpr_HEADER_H

#include <boost/smart_ptr.hpp>
#include <string>


#include "../../visitor/SQLASTVisitor.h"
#include "SQLTextLiteralExpr.h"



class SQLNCharExpr : virtual public SQLTextLiteralExpr {

	typedef SQLTextLiteralExpr super;

	public:
		SQLNCharExpr();
		virtual ~SQLNCharExpr();

		SQLNCharExpr(std::string &text);

		void output(std::string & buf);

	protected:
		void accept0(SQLASTVisitor *visitor);
};
typedef boost::shared_ptr<SQLNCharExpr> SQLNCharExpr_ptr;
#endif

