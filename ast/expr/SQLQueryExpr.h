#ifndef SQLQueryExpr_HEADER_H 
#define SQLQueryExpr_HEADER_H
#include <boost/smart_ptr.hpp>
#include <string>
#include "../SQLExprImpl.h"
#include "../statement/SQLSelect.h"
#include "../../visitor/SQLASTVisitor.h"


class SQLQueryExpr : virtual public SQLExprImpl {

	private:
		//static final long serialVersionUID = 1L;
	public:
		SQLSelect          *subQuery;

		SQLQueryExpr();
		virtual ~SQLQueryExpr();

		SQLQueryExpr(SQLSelect *select);

		SQLSelect *getSubQuery();

		void setSubQuery(SQLSelect *subQuery);

		void output(std::string &buf);

		//int hashCode();
		//bool equals(Object obj);
	protected:
		void accept0(SQLASTVisitor *visitor);

};
typedef boost::shared_ptr<SQLQueryExpr> SQLQueryExpr_ptr;

#endif

