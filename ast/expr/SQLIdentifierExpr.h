#ifndef SQLIdentifierExpr_HEADER_H 
#define SQLIdentifierExpr_HEADER_H
#include <boost/smart_ptr.hpp>
#include "../SQLExprImpl.h"
#include "../../visitor/SQLASTVisitor.h"
#include "../SQLName.h"

class SQLIdentifierExpr : virtual public SQLExprImpl, virtual public SQLName {

	private:
		std::string           name;

		std::string lowerName;

	public:
		SQLIdentifierExpr();
		virtual ~SQLIdentifierExpr();

		SQLIdentifierExpr(std::string &name);

		std::string &getSimleName();

		std::string &getName();

		void setName(std::string &name);

		std::string &getLowerName();

		void setLowerName(std::string &lowerName);

		void output(std::string &buf);
		//int hashCode();
		//bool equals(Object obj);

	protected:
		void accept0(SQLASTVisitor *visitor);


};
typedef boost::shared_ptr<SQLIdentifierExpr> SQLIdentifierExpr_ptr;


#endif
