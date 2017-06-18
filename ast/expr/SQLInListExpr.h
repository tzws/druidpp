#ifndef SQLInListExpr_HEADER_H
#define SQLInListExpr_HEADER_H

#include <boost/smart_ptr.hpp>
#include <list>
#include "../SQLExpr.h"
#include "../SQLExprImpl.h"
#include "../../visitor/SQLASTVisitor.h"


class SQLInListExpr : virtual public SQLExprImpl{

	private:
		//static long serialVersionUID = 1L;
		bool           xnot;
		SQLExpr           *expr;
		std::list<SQLExpr *>     targetList;

	public:
		SQLInListExpr();
		virtual ~SQLInListExpr();

		SQLInListExpr(SQLExpr *expr);

		SQLInListExpr(SQLExpr *expr, bool xnot);

		bool isNot();

		void setNot(bool xnot);

		SQLExpr *getExpr();

		void setExpr(SQLExpr *expr);

		std::list<SQLExpr *> & getTargetList();

		void setTargetList(std::list<SQLExpr *> & targetList);

		//int hashCode();
		//bool equals(Object obj);
	protected:
		void accept0(SQLASTVisitor *visitor);

};
typedef boost::shared_ptr<SQLInListExpr> SQLInListExpr_ptr;
#endif

