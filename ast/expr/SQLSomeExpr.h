#ifndef SQLSomeExpr_HEADER_H
#define SQLSomeExpr_HEADER_H


#include <boost/smart_ptr.hpp>
#include <string>
#include "../SQLExprImpl.h"
#include "../statement/SQLSelect.h"
#include "../../visitor/SQLASTVisitor.h"


#include "../statement/SQLSelect.h"

class SQLSomeExpr : virtual public SQLExprImpl {

	public:
		SQLSelect *subQuery;

		SQLSomeExpr();
		virtual ~SQLSomeExpr();

		SQLSomeExpr(SQLSelect *select);

		SQLSelect *getSubQuery();

		void setSubQuery(SQLSelect *subQuery);

		void output(std::string & buf);

		//int hashCode();
		//bool equals(Object obj);
	protected:
		void accept0(SQLASTVisitor *visitor);

};
typedef boost::shared_ptr<SQLSomeExpr> SQLSomeExpr_ptr;
#endif

