#ifndef SQLOrderBy_HEADER_H
#define SQLOrderBy_HEADER_H


//import com.alibaba.druid.sql.ast.statement.SQLSelectOrderByItem;
//import com.alibaba.druid.sql.visitor.SQLASTVisitor;

#include <boost/smart_ptr.hpp>
#include "Object.h"
#include "SQLObject.h"
#include "SQLObjectImpl.h"
#include "SQLExpr.h"
#include "../visitor/SQLASTVisitor.h"
#include "statement/SQLSelectOrderByItem.h"

class SQLOrderBy : virtual public SQLObject{


	private:
		SQLObject           *parent;

		//http://stackoverflow.com/questions/1155142/why-do-i-get-an-error-in-forming-reference-to-reference-type-map
		//The map needs a copy of the string to store:
		std::map<std::string, Object*> attributes;

		typedef SQLObject super;
		std::string buf;


	protected:
		std::list<SQLSelectOrderByItem *> items;
		void accept0(SQLASTVisitor *visitor);

	public:
		SQLOrderBy();
		virtual ~SQLOrderBy();

		SQLOrderBy(SQLExpr *expr);

		void addItem(SQLSelectOrderByItem *item);

		std::list<SQLSelectOrderByItem *> &getItems();


		void acceptChild(SQLASTVisitor *visitor, SQLObject *child) ;
		void acceptChild(SQLASTVisitor *visitor, std::list<SQLObject *> &children);
		void acceptChild(SQLASTVisitor *visitor, std::list<SQLSelectOrderByItem*> &children);

		virtual void accept(SQLASTVisitor *visitor);
		virtual SQLObject * getParent();
		virtual void setParent(SQLObject *parent);
		virtual std::map<std::string, Object*>& getAttributes();

		virtual Object *getAttribute(std::string& name);

		virtual void putAttribute(std::string name, Object* value);

		virtual std::map<std::string, Object*> &getAttributesDirect();

		virtual void output(std::string &buf);



		//int hashCode();
		//bool equals(Object *obj);

};
typedef boost::shared_ptr<SQLOrderBy> SQLOrderBy_ptr;

#endif

