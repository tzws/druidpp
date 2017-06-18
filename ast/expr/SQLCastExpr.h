#ifndef SQLCastExpr_HEADER_H
#define SQLCastExpr_HEADER_H

#include <boost/smart_ptr.hpp>
#include "../SQLExpr.h"
#include "../SQLExprImpl.h"
#include "../../visitor/SQLASTVisitor.h"
#include "../SQLDataType.h"


class SQLCastExpr : virtual public SQLExprImpl {

	private:
		SQLExpr     *expr;
		SQLDataType *dataType;

	public:
		SQLCastExpr();
		virtual ~SQLCastExpr();

		SQLExpr *getExpr();

		void setExpr(SQLExpr *expr);

		SQLDataType *getDataType();

		void setDataType(SQLDataType *dataType);

	protected:
		void accept0(SQLASTVisitor *visitor);

	public:
		//int hashCode();
		//public bool equals(Object obj);

};
typedef boost::shared_ptr<SQLCastExpr> SQLCastExpr_ptr;
#endif

