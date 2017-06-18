#ifndef SQLMethodInvokeExpr_HEADER_H
#define SQLMethodInvokeExpr_HEADER_H

#include <boost/smart_ptr.hpp>
#include <string>
#include "../SQLExpr.h"
#include "../SQLExprImpl.h"
#include "../../visitor/SQLASTVisitor.h"


class SQLMethodInvokeExpr : virtual public SQLExprImpl {

	private:
		//static long   serialVersionUID = 1L;
		std::string         methodName;
		SQLExpr             *owner;
		std::list<SQLExpr *> parameters;

	public:
		SQLMethodInvokeExpr();
		virtual ~SQLMethodInvokeExpr();

		SQLMethodInvokeExpr(std::string &methodName);

		SQLMethodInvokeExpr(std::string &methodName, SQLExpr *owner);

		std::string &getMethodName();

		void setMethodName(std::string &methodName);

		SQLExpr *getOwner();

		void setOwner(SQLExpr *owner);

		std::list<SQLExpr *> & getParameters();

		void addParameter(SQLExpr *param);

		void output(std::string & buf);

		//int hashCode();
		//bool equals(Object obj);
	protected:
		void accept0(SQLASTVisitor *visitor);

		//void accept0(OracleASTVisitor *visitor);

};
typedef boost::shared_ptr<SQLMethodInvokeExpr> SQLMethodInvokeExpr_ptr;
#endif

