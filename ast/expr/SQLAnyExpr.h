#ifndef SQLAnyExpr_HEADER_H
#define SQLAnyExpr_HEADER_H

#include <boost/smart_ptr.hpp>
#include <string>
#include "../SQLExprImpl.h"
#include "../../visitor/SQLASTVisitor.h"
#include "../statement/SQLSelect.h"


class SQLAnyExpr : virtual public SQLExprImpl {

	public:
		SQLSelect *subQuery;

		SQLAnyExpr();
		virtual ~SQLAnyExpr();

		SQLAnyExpr(SQLSelect *select);

		SQLSelect *getSubQuery();

		void setSubQuery(SQLSelect *subQuery);

		void output(std::string & buf);
		//int hashCode();
		//bool equals(Object obj);

	protected:
		void accept0(SQLASTVisitor *visitor);

};
typedef boost::shared_ptr<SQLAnyExpr> SQLAnyExpr_ptr;
#endif

