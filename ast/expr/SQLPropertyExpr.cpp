#include "SQLPropertyExpr.h"
SQLPropertyExpr::SQLPropertyExpr(SQLExpr * theOwner, std::string & theName) : owner(theOwner){
	//setOwner(theOwner);
	name = theName;
}

SQLPropertyExpr::~SQLPropertyExpr(){
	if (owner != NULL)
	{
		delete owner;
		owner = NULL;
	}

}
SQLPropertyExpr::SQLPropertyExpr(){

}

std::string &SQLPropertyExpr::getSimleName() {
	return name;
}

SQLExpr *SQLPropertyExpr::getOwner() {
	return owner;
}

void SQLPropertyExpr::setOwner(SQLExpr *theOwner) {
	if (theOwner != NULL) {
		theOwner->setParent(this);
	}
	//owner = owner;
}

std::string &SQLPropertyExpr::getName() {
	return name;
}

void SQLPropertyExpr::setName(std::string &theName) {
	name = theName;
}

void SQLPropertyExpr::output(std::string & buf) {
	owner->output(buf);
	buf += ".";
	buf += name;
}

void SQLPropertyExpr::accept0(SQLASTVisitor *visitor) {
	if (visitor->visit(this)) {
		acceptChild(visitor, owner);
	}

	visitor->endVisit(this);
}

//int SQLPropertyExpr::hashCode() {
	//final int prime = 31;
	//int result = 1;
	//result = prime * result + ((name == NULL) ? 0 : name.hashCode());
	//result = prime * result + ((owner == NULL) ? 0 : owner.hashCode());
	//return result;
//}

//bool SQLPropertyExpr::equals(Object obj) {
	//if (this == obj) {
		//return true;
	//}
	//if (obj == NULL) {
		//return false;
	//}
	//if (!(obj instanceof SQLPropertyExpr)) {
		//return false;
	//}
	//SQLPropertyExpr other = (SQLPropertyExpr) obj;
	//if (name == NULL) {
		//if (other.name != NULL) {
			//return false;
		//}
	//} else if (!name.equals(other.name)) {
		//return false;
	//}
	//if (owner == NULL) {
		//if (other.owner != NULL) {
			//return false;
		//}
	//} else if (!owner.equals(other.owner)) {
		//return false;
	//}
	//return true;
//}

