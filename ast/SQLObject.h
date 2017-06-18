
//import com.alibaba.druid.sql.visitor.SQLASTVisitor;

#ifndef SQLObject_HEADER_H
#define SQLObject_HEADER_H

#include <boost/smart_ptr.hpp>
#include <map>
#include <vector>

#include "Object.h"


#include "../visitor/SQLASTVisitor.h"
//class SQLASTVisitor;
class SQLObject : public Object {

	//http://stackoverflow.com/questions/11945993/equivalent-of-java-interfaces-in-c

	typedef Object inherited;
	private:
	//static std::string x;
	//static std::string className;
	//static std::string x = "in SQLObject class";
	//static std::string className = "SQLObject";
	public:
	virtual void accept(SQLASTVisitor *visitor) = 0;

	virtual SQLObject * getParent() = 0;

	virtual void setParent(SQLObject *parent) = 0;

	virtual std::map<std::string, Object*>& getAttributes() = 0;

	virtual Object *getAttribute(std::string& name) = 0;

	virtual void putAttribute(std::string name, Object* value) = 0;

	virtual std::map<std::string, Object*> &getAttributesDirect() = 0;

	virtual void output(std::string &buf) = 0;

	virtual void accept0(SQLASTVisitor *visitor) = 0;
	virtual ~SQLObject() {

	}

	virtual std::string & getClass()
	{

		static std::string className = "SQLObject";
		return className;
	} 

	virtual std::string &toString()
	{

#if WIN32
		std::string x = "";
		return x;
#else

#endif		

	}

};

//std::string SQLObject::x = "in SQLObject class";
//std::string SQLObject::className = "SQLObject";

//std::string & SQLObject::getClass() { 
//return className;
//}

//std::string &SQLObject::toString()
//{
//return x;
//}


typedef boost::shared_ptr<SQLObject> SQLObject_ptr;
#endif

