
#ifndef SQLObjectImpl_HEADER_H
#define SQLObjectImpl_HEADER_H
//import com.alibaba.druid.sql.visitor.SQLASTVisitor;
#include <boost/smart_ptr.hpp>
#include "Object.h"
#include "SQLObject.h"
#include "SQLExpr.h"
#include "../visitor/SQLASTVisitor.h"
//#include "../visitor/SQLASTVisitor.h"

#include <map>
#include <list>



//http://stackoverflow.com/questions/11919014/inaccessible-base-class

class SQLObjectImpl : virtual public  SQLObject {

	private:
		SQLObject           *parent;

		//http://stackoverflow.com/questions/1155142/why-do-i-get-an-error-in-forming-reference-to-reference-type-map
		//The map needs a copy of the string to store:
		std::map<std::string, Object*> attributes;

		typedef SQLObject super;
		std::string buf;

	public:

		SQLObjectImpl();
		virtual ~SQLObjectImpl();
		virtual void accept(SQLASTVisitor *visitor);
		virtual void output(std::string &buf);
		virtual std::string &toString();
		SQLObject *getParent();
		void setParent(SQLObject* parent);
		virtual std::map<std::string, Object*> &getAttributes();
		Object *getAttribute(std::string &name);
		virtual void putAttribute(std::string name, Object *value);
		virtual std::map<std::string, Object*> &getAttributesDirect();

		//virtual std::string & getClass()
		//{
			//static std::string className = "SQLObjectImpl";
			//return className;
		//} 


	protected:

		virtual void accept0(SQLASTVisitor *visitor) = 0;
		void acceptChild(SQLASTVisitor *visitor, std::list<SQLObject *> &children);
		void acceptChild(SQLASTVisitor *visitor, std::list<SQLExpr *> &children);
		void acceptChild(SQLASTVisitor *visitor, SQLObject *child);
};
typedef boost::shared_ptr<SQLObjectImpl> SQLObjectImpl_ptr;

#endif

