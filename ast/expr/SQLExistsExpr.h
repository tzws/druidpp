#ifndef SQLExistsExpr_HEADER_H
#define SQLExistsExpr_HEADER_H

#include <boost/smart_ptr.hpp>
#include "../SQLExprImpl.h"
#include "../statement/SQLSelect.h"
#include "../../visitor/SQLASTVisitor.h"
#include "../../visitor/SQLASTVisitor.h"



class SQLExistsExpr : virtual public SQLExprImpl {

	private:
		//static long serialVersionUID = 1L;
	public:
		bool            xnot;
		SQLSelect          *subQuery;

		SQLExistsExpr();
		virtual ~SQLExistsExpr();

		SQLExistsExpr(SQLSelect *subQuery);

		SQLExistsExpr(SQLSelect *subQuery, bool xnot);

		bool isNot();

		void setNot(bool xnot);

		SQLSelect *getSubQuery();

		void setSubQuery(SQLSelect *subQuery);

		//int hashCode();
		//bool equals(Object obj);
	protected:
		void accept0(SQLASTVisitor *visitor);

};
typedef boost::shared_ptr<SQLExistsExpr> SQLExistsExpr_ptr;
#endif

