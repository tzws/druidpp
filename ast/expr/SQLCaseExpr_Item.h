#ifndef SQLCaseExpr_Item_HEADER_H
#define SQLCaseExpr_Item_HEADER_H

#include <boost/smart_ptr.hpp>
#include <list>
#include "../SQLExpr.h"
#include "../SQLExprImpl.h"
#include "../../visitor/SQLASTVisitor.h"
#include "../SQLObjectImpl.h"

class SQLCaseExpr_Item : virtual public SQLObjectImpl {

	private:
		//static long serialVersionUID = 1L;
		SQLExpr           *conditionExpr;
		SQLExpr           *valueExpr;

	public:
		SQLCaseExpr_Item();
		virtual ~SQLCaseExpr_Item();

		SQLCaseExpr_Item(SQLExpr *conditionExpr, SQLExpr *valueExpr);

		SQLExpr *getConditionExpr();

		void setConditionExpr(SQLExpr *conditionExpr);

		SQLExpr *getValueExpr();

		void setValueExpr(SQLExpr *valueExpr);

	protected:
		void accept0(SQLASTVisitor *visitor);

	public:
		//int hashCode();
		//bool equals(Object obj);

};

typedef boost::shared_ptr<SQLCaseExpr_Item> SQLCaseExpr_Item_ptr;
#endif

