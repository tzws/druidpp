#ifndef SQLBetweenExpr_HEADER_H
#define SQLBetweenExpr_HEADER_H

#include <boost/smart_ptr.hpp>
#include "../SQLExpr.h"
#include "../SQLExprImpl.h"
#include "../../visitor/SQLASTVisitor.h"

class SQLBetweenExpr : virtual public SQLExprImpl {

	private:
		//static long serialVersionUID = 1L;
		bool           xnot;
	public:
		SQLExpr            *testExpr;
		SQLExpr            *beginExpr;
		SQLExpr            *endExpr;

		SQLBetweenExpr();
		virtual ~SQLBetweenExpr();

		SQLBetweenExpr(SQLExpr *testExpr, SQLExpr *beginExpr, SQLExpr *endExpr);

		SQLBetweenExpr(SQLExpr *testExpr, bool xnot, SQLExpr *beginExpr, SQLExpr *endExpr);


		SQLExpr *getTestExpr();

		void setTestExpr(SQLExpr *testExpr);

		bool isNot();

		void setNot(bool xnot);

		SQLExpr *getBeginExpr();

		void setBeginExpr(SQLExpr *beginExpr);

		SQLExpr *getEndExpr();

		void setEndExpr(SQLExpr *endExpr);

		//int hashCode();
		//bool equals(Object obj);
	protected:
		void accept0(SQLASTVisitor *visitor);
};
typedef boost::shared_ptr<SQLBetweenExpr> SQLBetweenExpr_ptr;
#endif

