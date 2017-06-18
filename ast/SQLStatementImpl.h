#ifndef SQLStatementImpl_HEADER_H
#define SQLStatementImpl_HEADER_H

#include <boost/smart_ptr.hpp>
#include "Object.h"
#include "SQLObject.h"
#include "SQLObjectImpl.h"
#include "SQLExpr.h"
#include "SQLOrderBy.h"
#include "../visitor/SQLASTVisitor.h"
#include "SQLStatement.h"


//import com.alibaba.druid.sql.SQLUtils;
//import com.alibaba.druid.sql.visitor.SQLASTVisitor;

class SQLStatementImpl : virtual public SQLObjectImpl, virtual public SQLStatement {

	public:
		SQLStatementImpl();
		virtual ~SQLStatementImpl();

		std::string &toString();

	protected:
		void accept0(SQLASTVisitor *visitor);
};
typedef boost::shared_ptr<SQLStatementImpl> SQLStatementImpl_ptr;

#endif
