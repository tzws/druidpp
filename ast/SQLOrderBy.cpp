#include "SQLOrderBy.h"


SQLOrderBy::SQLOrderBy() : buf(" "), parent(NULL) {

}
SQLOrderBy::~SQLOrderBy() {

	//std::cout <<  "++++\t" << __FILE__ << ": " << __LINE__ << ", in SQLOrderBy::~SQLOrderBy, step 1 " << std::endl;
	for(std::list<SQLSelectOrderByItem *>::iterator it = items.begin(); it != items.end(); ++it) 
	{
		//std::cout <<  "++++\t" << __FILE__ << ": " << __LINE__ << ", in SQLOrderBy::~SQLOrderBy, step 1.1 " << std::endl;
		delete *it; 
	}
	items.clear();

	for(std::map<std::string, Object*>::iterator it = attributes.begin(); it != attributes.end(); ++it) 
	{
		//std::cout <<  "++++\t" << __FILE__ << ": " << __LINE__ << ", in SQLOrderBy::~SQLOrderBy, step 1.2 " << std::endl;
		delete it->second;
	}

	if (parent != NULL)
	{
		delete parent;
		parent = NULL;
		
	}

}
SQLOrderBy::SQLOrderBy(SQLExpr *theExpr) : buf(" "), parent(NULL)  {
	SQLSelectOrderByItem *item = new SQLSelectOrderByItem(theExpr);
	item->setParent(this);
	items.push_back(item);
}

void SQLOrderBy::addItem(SQLSelectOrderByItem *item) {
	if (item != NULL) {
		item->setParent(this);
	}
	items.push_back(item);
}

std::list<SQLSelectOrderByItem *> &SQLOrderBy::getItems() {
	return items;
}

void SQLOrderBy::accept0(SQLASTVisitor *visitor) {
	if (visitor->visit(this)) {
		acceptChild(visitor, items);
	}

	visitor->endVisit(this);
}

void SQLOrderBy::acceptChild(SQLASTVisitor *visitor, std::list<SQLObject *> &children) {
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
void SQLOrderBy::acceptChild(SQLASTVisitor *visitor, std::list<SQLSelectOrderByItem *> &children) {
	if (children.empty()) {
		return;
	}

	std::list<SQLSelectOrderByItem *>::iterator iStart = children.begin() ;
	std::list<SQLSelectOrderByItem *>::iterator iEnd = children.end() ;
	std::list<SQLSelectOrderByItem *>::iterator  it;
	for (it=iStart ;it!=iEnd;++it)
	{
		acceptChild(visitor, *it);
	}
}



void SQLOrderBy::acceptChild(SQLASTVisitor *visitor, SQLObject *child) {
	if (child == NULL) {
		return;
	}

	child->accept(visitor);
}


//int SQLOrderBy::hashCode() {
	//int prime = 31;
	//int result = 1;
	//result = prime * result + ((items == NULL) ? 0 : items.hashCode());
	//return result;
//}

//bool SQLOrderBy::equals(Object obj) {
	//if (this == obj) return true;
	//if (obj == NULL) return false;
	//if (getClass() != obj.getClass()) return false;
	//SQLOrderBy other = (SQLOrderBy) obj;
	//if (items == NULL) {
		//if (other.items != NULL) return false;
	//} else if (!items.equals(other.items)) return false;
	//return true;
//}


void SQLOrderBy::accept(SQLASTVisitor *visitor) {

	if (visitor == NULL) {
		//throw new IllegalArgumentException();
	}

	visitor->preVisit(this);

	accept0(visitor);

	visitor->postVisit(this);

}

SQLObject *SQLOrderBy::getParent() {
	return parent;
}


void SQLOrderBy::setParent(SQLObject *theParent) {
	parent = theParent;
}

std::map<std::string, Object*>& SQLOrderBy::getAttributes() {
	//if (attributes.empty()) {
		//attributes = new Hashstd::map<std::string, Object>(1);
	//}

	return attributes;
}


Object *SQLOrderBy::getAttribute(std::string &name) {
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

void SQLOrderBy::putAttribute(std::string name, Object *value) {
	//if (attributes == NULL) {
		//attributes = new Hashstd::map<std::string, Object>(1);
	//}

	attributes[name] = value;
	//attributes.put(name, value);
}

std::map<std::string, Object*>& SQLOrderBy::getAttributesDirect() {
	return attributes;
}

void SQLOrderBy::output(std::string &theBuf) {
	//buf.append(super::toString());
	//buf.push_back(super::toString());
	//std::cout << super::toString() << std::endl;
	theBuf += super::toString();
}

//std::string &SQLOrderBy::toString() {
	//output(buf);
	//return buf;
//}


