#include "SQLObjectImpl.h"

//std::string SQLObjectImpl::buf ("xxx:");
SQLObjectImpl::SQLObjectImpl() : buf(" in SQLObjectImpl class, "){
//SQLObjectImpl::SQLObjectImpl() {
//SQLObjectImpl::SQLObjectImpl() {
}



SQLObjectImpl::~SQLObjectImpl() {

	//for(std::map<std::string, Object*>::iterator it = attributes.begin(); it != attributes.end(); ++it) 
	//{
		//delete it->second;
	//}


}
void SQLObjectImpl::accept(SQLASTVisitor *visitor) {

	if (visitor == NULL) {
		//throw new IllegalArgumentException();
	}

	visitor->preVisit(this);

	accept0(visitor);

	visitor->postVisit(this);

}


void SQLObjectImpl::acceptChild(SQLASTVisitor *visitor, std::list<SQLObject *> &children) {
	if (children.empty()) {
		return;
	}

	std::list<SQLObject *>::iterator iStart = children.begin() ;
	std::list<SQLObject *>::iterator iEnd = children.end() ;
	std::list<SQLObject *>::iterator  it;
	for (it=iStart ;it!=iEnd;++it)
	{
		acceptChild(visitor, *it);
	}

}

void SQLObjectImpl::acceptChild(SQLASTVisitor *visitor, std::list<SQLExpr *> &children) {
	if (children.empty()) {
		return;
	}

	std::list<SQLExpr *>::iterator iStart = children.begin() ;
	std::list<SQLExpr *>::iterator iEnd = children.end() ;
	std::list<SQLExpr *>::iterator  it;
	for (it=iStart ;it!=iEnd;++it)
	{
		acceptChild(visitor, *it);
	}
}


void SQLObjectImpl::acceptChild(SQLASTVisitor *visitor, SQLObject *child) {
	if (child == NULL) {
		return;
	}

	child->accept(visitor);
}

void SQLObjectImpl::output(std::string &theBuf) {
	//buf.append(super::toString());
	//buf.push_back(super::toString());
	//std::cout << super::toString() << std::endl;
	theBuf += "";
}

std::string &SQLObjectImpl::toString() {
	//std::cout << buf << std::endl;
	//exit(1);
	buf = "";
	output(buf);
	return buf;

	//std::string *x = new std::string();
	//output(*x);
	//return *x;
}

SQLObject *SQLObjectImpl::getParent() {
	return parent;
}

void SQLObjectImpl::setParent(SQLObject *theParent) {
	parent = theParent;
}

std::map<std::string, Object*>& SQLObjectImpl::getAttributes() {
	//if (attributes.empty()) {
		//attributes = new Hashstd::map<std::string, Object>(1);
	//}

	return attributes;
}

Object *SQLObjectImpl::getAttribute(std::string &name) {
	//if (attributes == NULL) {
		//return NULL;
	//}

	//test is empty is unneccessary??
	//map<std::string &,Object &>::const_iterator it = attributes.find(name);
	//if (it != attributes.end())
	//{
		//return attributes.find(name)->second;
	//}

	return attributes.find(name)->second;
}

void SQLObjectImpl::putAttribute(std::string name, Object *value) {
	//if (attributes == NULL) {
		//attributes = new Hashstd::map<std::string, Object>(1);
	//}

	attributes[name] = value;
	//attributes.put(name, value);
}

std::map<std::string, Object*>& SQLObjectImpl::getAttributesDirect() {
	return attributes;
}


//std::string &SQLObjectImpl::toString()
//{
	//static std::string x = "in SQLObjectImpl class";
	//return x;
//}


