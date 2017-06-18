#ifndef SQLCaseExpr_HEADER_H
#define SQLCaseExpr_HEADER_H

#include <boost/smart_ptr.hpp>
#include <list>
#include "../SQLExpr.h"
#include "../SQLExprImpl.h"
#include "../../visitor/SQLASTVisitor.h"
#include "../SQLObjectImpl.h"

#include "SQLCaseExpr_Item.h"

class SQLCaseExpr : virtual public SQLExprImpl {


	private:
		//static long serialVersionUID = 1L;
		std::list<SQLCaseExpr_Item *>  items;
		SQLExpr           *valueExpr;
		SQLExpr           *elseExpr;

	public:
		SQLCaseExpr();
		virtual ~SQLCaseExpr();

		SQLExpr *getValueExpr();

		void setValueExpr(SQLExpr *valueExpr);

		SQLExpr *getElseExpr();

		void setElseExpr(SQLExpr *elseExpr);

		std::list<SQLCaseExpr_Item *> & getItems();

		void addItem(SQLCaseExpr_Item *item);

	protected:
		void accept0(SQLASTVisitor *visitor);
		void acceptChild(SQLASTVisitor *visitor, std::list<SQLCaseExpr_Item *> &children);
		void acceptChild(SQLASTVisitor *visitor, SQLExpr * children);
	public:
		//int hashCode();
		//bool equals(Object obj);

};
typedef boost::shared_ptr<SQLCaseExpr> SQLCaseExpr_ptr;
typedef boost::shared_ptr<SQLCaseExpr_Item> SQLCaseExpr_Item_ptr;
#endif

