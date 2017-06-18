
#ifndef SQLDataTypeImpl_HEADER_H
#define SQLDataTypeImpl_HEADER_H
//import com.alibaba.druid.sql.visitor.SQLASTVisitor;
#include <boost/smart_ptr.hpp>
#include <string>
#include <list>
#include "Object.h"
#include "SQLObjectImpl.h"
#include "SQLDataType.h"
#include "SQLExpr.h"
#include "../visitor/SQLASTVisitor.h"

class SQLDataTypeImpl : virtual public SQLObjectImpl, virtual public SQLDataType {

	protected:
		std::string              name;
		std::list<SQLExpr *> arguments;

		void accept0(SQLASTVisitor *visitor);
		int listHashcode();
		int stringHashcode(std::string & x);

	public: 
		SQLDataTypeImpl();
		virtual ~SQLDataTypeImpl();
		SQLDataTypeImpl(std::string &name);
		std::string &getName();

		void setName(std::string &name);

		std::list<SQLExpr *>& getArguments();

		int hashCode();

		bool equals(Object *obj);


		virtual std::string & getClass()
		{
			static std::string className = "SQLDataTypeImpl";
			return className;
		} 


};
typedef boost::shared_ptr<SQLDataTypeImpl> SQLDataTypeImpl_ptr;
#endif

