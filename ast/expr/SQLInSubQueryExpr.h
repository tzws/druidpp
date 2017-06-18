#ifndef SQLInSubQueryExpr_HEADER_H
#define SQLInSubQueryExpr_HEADER_H

#include <boost/smart_ptr.hpp>
#include <string>

#include "../SQLExpr.h"
#include "../SQLExprImpl.h"
#include "../statement/SQLSelect.h"
#include "../../visitor/SQLASTVisitor.h"



class SQLInSubQueryExpr : virtual public SQLExprImpl {

	private:
		//static long serialVersionUID = 1L;
		bool           xnot;
		SQLExpr           *expr;

	public:
		SQLSelect          *subQuery;

		SQLInSubQueryExpr();
		virtual ~SQLInSubQueryExpr();

		bool isNot();

		void setNot(bool xnot);

		SQLExpr *getExpr();

		void setExpr(SQLExpr *expr);

		SQLInSubQueryExpr(SQLSelect *select);

		SQLSelect *getSubQuery();

		void setSubQuery(SQLSelect *subQuery);

		void output(std::string & buf);

		//int hashCode();
		//bool equals(Object obj);
	protected:
		void accept0(SQLASTVisitor *visitor);


};
typedef boost::shared_ptr<SQLInSubQueryExpr> SQLInSubQueryExpr_ptr;
#endif

