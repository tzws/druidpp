#ifndef SQLBinaryOpExpr_HEADER_H
#define SQLBinaryOpExpr_HEADER_H

#include <boost/smart_ptr.hpp>
#include "../SQLExpr.h"
#include "../SQLExprImpl.h"
#include "../../visitor/SQLASTVisitor.h"

#include "SQLBinaryOperator.h"

class SQLBinaryOpExpr : virtual public SQLExprImpl {

	private:
		//static long serialVersionUID = 1L;
		SQLExpr           *left;
		SQLExpr           *right;
		SQLBinaryOperator *xoperator;

	public:
		SQLBinaryOpExpr();
		virtual ~SQLBinaryOpExpr();

		SQLBinaryOpExpr(SQLExpr *left, SQLBinaryOperator *xoperator, SQLExpr *right);

		SQLBinaryOpExpr(SQLExpr *left, SQLExpr *right, SQLBinaryOperator *xoperator);

		SQLExpr *getLeft();

		void setLeft(SQLExpr *left);

		SQLExpr *getRight();

		void setRight(SQLExpr *right);

		SQLBinaryOperator *getOperator();

		void setOperator(SQLBinaryOperator *xoperator);

		//int hashCode();
		//bool equals(Object obj);

	protected:
		void accept0(SQLASTVisitor *visitor);


};
typedef boost::shared_ptr<SQLBinaryOpExpr> SQLBinaryOpExpr_ptr;
#endif

