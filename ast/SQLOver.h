#ifndef SQLOver_HEADER_H
#define SQLOver_HEADER_H

#include <boost/smart_ptr.hpp>
#include "Object.h"
#include "SQLObject.h"
#include "SQLObjectImpl.h"
#include "SQLExpr.h"
#include "SQLOrderBy.h"
#include "../visitor/SQLASTVisitor.h"



class SQLOver : virtual public SQLObjectImpl {

	protected:
		std::list<SQLExpr *> partitionBy;
		SQLOrderBy          *orderBy;
		void accept0(SQLASTVisitor *visitor);

	public:
		SQLOver();
		virtual ~SQLOver();

		SQLOver(SQLOrderBy *orderBy);
		SQLOrderBy *getOrderBy();

		void setOrderBy(SQLOrderBy *orderBy);
		std::list<SQLExpr *> &getPartitionBy();
		//void acceptChild(SQLASTVisitor *visitor, std::list<SQLSelectOrderByItem*> &children);

		//int hashCode();

		//bool equals(Object obj);
};
typedef boost::shared_ptr<SQLOver> SQLOver_ptr;
#endif

