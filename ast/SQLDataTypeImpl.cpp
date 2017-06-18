#include <boost/functional/hash.hpp>
#include <sstream>
#include "SQLDataTypeImpl.h"

SQLDataTypeImpl::SQLDataTypeImpl(){

}
SQLDataTypeImpl::~SQLDataTypeImpl(){

	for(std::list<SQLExpr *>::iterator it = arguments.begin(); it != arguments.end(); ++it) 
	{
		delete *it; 
	}
	arguments.clear();


}

SQLDataTypeImpl::SQLDataTypeImpl(std::string &theName){
	name = theName;
}

void SQLDataTypeImpl::accept0(SQLASTVisitor *visitor) {

	if (visitor->visit(this)) {
		acceptChild(visitor, arguments);
	}

	visitor->endVisit(this);

}

std::string& SQLDataTypeImpl::getName() {
	return name;
}

void SQLDataTypeImpl::setName(std::string &theName) {
	name = theName;
}

std::list<SQLExpr *> &SQLDataTypeImpl::getArguments() {
	return arguments;
}

int SQLDataTypeImpl::hashCode() {
	int prime = 31;
	int result = 1;
	result = prime * result + ((arguments.empty()) ? 0 : listHashcode());
	result = prime * result + ((name == "") ? 0 : stringHashcode(name));
	return result;
}

int SQLDataTypeImpl::listHashcode()
{
	int c = 0;
	std::stringstream ss;
	ss << "x ";

      for (std::list<SQLExpr *>::const_iterator ci = arguments.begin(); ci != arguments.end(); ++ci)
	  {
		  ss << "SQLExpr " << c++;
	  }
	  std::string x = ss.str();
	  return stringHashcode(x);
}
int SQLDataTypeImpl::stringHashcode(std::string & x)
{
    boost::hash<std::string> string_hash;

    return string_hash(x);	
}

bool SQLDataTypeImpl::equals(Object *obj) {

	//http://stackoverflow.com/questions/4364536/c-null-reference
	/*  A reference shall be initialized to refer to a valid object or function. [Note: in particular, a null reference cannot exist in a well-defined program, because the only way to create such a reference would be to bind it to the “object” obtained by dereferencing a null pointer, which causes undefined behavior. As described in 9.6, a reference cannot be bound directly to a bit-field. ]  */

	//if (this == obj) return true;
	SQLDataTypeImpl *x = dynamic_cast<SQLDataTypeImpl*>(obj);
	if (this == x) return true;
	if (x == NULL) return false;

	if (getClass() != x->getClass()) return false;
	//SQLDataTypeImpl other = (SQLDataTypeImpl) obj;
	if (arguments.empty()) {
		if (!(x->getArguments()).empty() ) return false;

	} 
	//else if (!arguments.equals(other.arguments)) return false;
	if (name == "") {
		if (x->getName() != "") return false;
	} else if (name != x->getName()) return false;


	return true;
}

