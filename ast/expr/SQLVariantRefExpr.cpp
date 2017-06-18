#include "SQLVariantRefExpr.h"
SQLVariantRefExpr::SQLVariantRefExpr(std::string & theName) : name(theName), global (false), index(-1){
	//this.name = name;
}
SQLVariantRefExpr::SQLVariantRefExpr(const char * theName) : name(theName), global (false), index(-1){
	//this.name = name;
}

SQLVariantRefExpr::SQLVariantRefExpr(std::string &theName, bool theGlobal): name(theName), global (theGlobal), index(-1){
	//this.name = name;
	//this.global = global;
}
SQLVariantRefExpr::~SQLVariantRefExpr() {

}

SQLVariantRefExpr::SQLVariantRefExpr(){

}

int SQLVariantRefExpr::getIndex() {
	return index;
}

void SQLVariantRefExpr::setIndex(int theIndex) {
	index = theIndex;
}

std::string &SQLVariantRefExpr::getName() {
	return name;
}

void SQLVariantRefExpr::setName(std::string &theName) {
	name = theName;
}

void SQLVariantRefExpr::output(std::string & buf) {
	buf += name;
	//buf.append(name);
}

void SQLVariantRefExpr::accept0(SQLASTVisitor *visitor) {
	visitor->visit(this);

	visitor->endVisit(this);
}

//int SQLVariantRefExpr::hashCode() {
	//final int prime = 31;
	//int result = 1;
	//result = prime * result + ((name == null) ? 0 : name.hashCode());
	//return result;
//}

//bool SQLVariantRefExpr::equals(Object obj) {
	//if (this == obj) {
		//return true;
	//}
	//if (obj == null) {
		//return false;
	//}
	//if (!(obj instanceof SQLVariantRefExpr)) {
		//return false;
	//}
	//SQLVariantRefExpr other = (SQLVariantRefExpr) obj;
	//if (name == null) {
		//if (other.name != null) {
			//return false;
		//}
	//} else if (!name.equals(other.name)) {
		//return false;
	//}
	//return true;
//}

bool SQLVariantRefExpr::isGlobal() {
	return global;
}

void SQLVariantRefExpr::setGlobal(bool theGlobal) {
	global = theGlobal;
}


