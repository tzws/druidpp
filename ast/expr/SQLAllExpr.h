#ifndef SQLAllExpr_HEADER_H
#define SQLAllExpr_HEADER_H

#include <boost/smart_ptr.hpp>
#include <string>

#include "../SQLExprImpl.h"
#include "../../visitor/SQLASTVisitor.h"
#include "../statement/SQLSelect.h"

class SQLAllExpr : virtual public SQLExprImpl {

	public:
		SQLSelect *subQuery;

	public:
		SQLAllExpr();
		virtual ~SQLAllExpr();

		SQLAllExpr(SQLSelect *select);

		SQLSelect *getSubQuery();

		void setSubQuery(SQLSelect *subQuery);

		void output(std::string & buf);

		//int hashCode();
		//bool equals(Object obj);
	protected:
		void accept0(SQLASTVisitor *visitor);


};
typedef boost::shared_ptr<SQLAllExpr> SQLAllExpr_ptr;

#endif

