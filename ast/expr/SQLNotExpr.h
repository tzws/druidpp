#ifndef SQLNotExpr_HEADER_H
#define SQLNotExpr_HEADER_H

#include <boost/smart_ptr.hpp>
#include <string>
#include "../SQLExpr.h"
#include "../SQLExprImpl.h"
#include "../../visitor/SQLASTVisitor.h"


class SQLNotExpr : virtual public SQLExprImpl  {

	private:
		//static long serialVersionUID = 1L;
	public:
		SQLExpr            *expr;

		SQLNotExpr();
		virtual ~SQLNotExpr();

		SQLNotExpr(SQLExpr *expr);

		SQLExpr *getExpr();

		void setExpr(SQLExpr *expr);

		void output(std::string & buf);

		//int hashCode();
		//bool equals(Object obj);
	protected:
		void accept0(SQLASTVisitor *visitor);

};
typedef boost::shared_ptr<SQLNotExpr> SQLNotExpr_ptr;
#endif

