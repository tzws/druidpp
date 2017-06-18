#ifndef SQLPropertyExpr_HEADER_H
#define SQLPropertyExpr_HEADER_H

#include <boost/smart_ptr.hpp>
#include <string>

#include "../SQLExpr.h"
#include "../SQLExprImpl.h"
#include "../SQLName.h"
#include "../../visitor/SQLASTVisitor.h"


class SQLPropertyExpr : virtual public SQLExprImpl, virtual public SQLName {

	private:
		SQLExpr *owner;
		std::string  name;

	public:
		SQLPropertyExpr(SQLExpr *owner, std::string &name);

		SQLPropertyExpr();
		virtual ~SQLPropertyExpr();

		std::string &getSimleName();

		SQLExpr *getOwner();

		void setOwner(SQLExpr *owner);

		std::string &getName();

		void setName(std::string &name);

		void output(std::string & buf);
		//int hashCode();
		//bool equals(Object obj);

	protected:
		void accept0(SQLASTVisitor *visitor);


};
typedef boost::shared_ptr<SQLPropertyExpr> SQLPropertyExpr_ptr;
#endif

