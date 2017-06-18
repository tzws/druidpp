#ifndef SQLUnaryExpr_HEADER_H
#define SQLUnaryExpr_HEADER_H

#include <boost/smart_ptr.hpp>
#include "../SQLExpr.h"
#include "../SQLExprImpl.h"
#include "../../visitor/SQLASTVisitor.h"


#include "SQLUnaryOperator.h"


class SQLUnaryExpr : virtual public SQLExprImpl {

	private:
		//static long serialVersionUID = 1L;
		SQLExpr           *expr;
		SQLUnaryOperator  *xoperator;

	public:
		SQLUnaryExpr();
		virtual ~SQLUnaryExpr();

		SQLUnaryExpr(SQLUnaryOperator *xoperator, SQLExpr *expr);

		SQLUnaryOperator *getOperator();

		void setOperator(SQLUnaryOperator *xoperator);

		SQLExpr *getExpr();

		void setExpr(SQLExpr *expr);

		//int hashCode();
		//bool equals(Object obj);
	protected:
		void accept0(SQLASTVisitor *visitor);

};
typedef boost::shared_ptr<SQLUnaryExpr> SQLUnaryExpr_ptr;
#endif

