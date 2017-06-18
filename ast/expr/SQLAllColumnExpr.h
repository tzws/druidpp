#ifndef SQLAllColumnExpr_HEADER_H
#define SQLAllColumnExpr_HEADER_H

#include <boost/smart_ptr.hpp>
#include <string>
#include "../SQLExprImpl.h"
#include "../../visitor/SQLASTVisitor.h"



class SQLAllColumnExpr : virtual public SQLExprImpl {

	public:
		SQLAllColumnExpr();
		virtual ~SQLAllColumnExpr();

		void output(std::string & buf);

		//int hashCode();
		//bool equals(Object o);
	protected:
		void accept0(SQLASTVisitor *visitor);

};
typedef boost::shared_ptr<SQLAllColumnExpr> SQLAllColumnExpr_ptr;


#endif

