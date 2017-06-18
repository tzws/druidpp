#ifndef SQLAggregateExpr_HEADER_H
#define SQLAggregateExpr_HEADER_H

#include <boost/smart_ptr.hpp>
#include <string>

#include "../SQLExpr.h"
#include "../SQLExprImpl.h"
#include "../SQLOver.h"
#include "../../visitor/SQLASTVisitor.h"

class SQLAggregateExpr : virtual public SQLExprImpl {

	public:

		enum Option {
			DISTINCT, ALL, UNIQUE
		};

	protected:
		std::string              methodName;
		Option              option;
		std::list<SQLExpr *> arguments;
		SQLOver             *over;
		void acceptChild(SQLASTVisitor *visitor, SQLOver * children);
		void acceptChild(SQLASTVisitor *visitor, std::list<SQLExpr *> &children);

	public:
		SQLAggregateExpr(std::string &methodName);
		virtual ~SQLAggregateExpr();

		SQLAggregateExpr(std::string &methodName, Option option);

		std::string &getMethodName();

		void setMethodName(std::string &methodName);

		Option getOption();

		void setOption(Option option);

		std::list<SQLExpr *> & getArguments();

		SQLOver *getOver();

		void setOver(SQLOver *over);

	protected:
		void accept0(SQLASTVisitor *visitor);

	public:
		//int hashCode();

		//bool equals(Object obj);
};
typedef boost::shared_ptr<SQLAggregateExpr> SQLAggregateExpr_ptr;

#endif

