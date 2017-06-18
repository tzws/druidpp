#ifndef SQLListExpr_HEADER_H 
#define SQLListExpr_HEADER_H
#include <boost/smart_ptr.hpp>
#include "../SQLExpr.h"
#include "../SQLExprImpl.h"
#include "../../visitor/SQLASTVisitor.h"



class SQLListExpr : virtual public SQLExprImpl {

	private:
		std::list<SQLExpr *> items;

	public:
		SQLListExpr();
		virtual ~SQLListExpr();
		std::list<SQLExpr *> & getItems();

		//int hashCode();
		//bool equals(Object obj);
	protected:
		void accept0(SQLASTVisitor *visitor);


};
typedef boost::shared_ptr<SQLListExpr> SQLListExpr_ptr;

#endif

