#include <boost/algorithm/string.hpp>    
#include "SQLIdentifierExpr.h"
SQLIdentifierExpr::SQLIdentifierExpr(){

	//std::cout << "\t\t\t\t\t\t" <<  __FILE__ << ": " << __LINE__ << ", in SQLIdentifierExpr::SQLIdentifierExpr, constructor" << std::endl;
}

SQLIdentifierExpr::~SQLIdentifierExpr(){
	//std::cout << "\t\t\t\t\t\t" <<  __FILE__ << ": " << __LINE__ << ", in SQLIdentifierExpr::~SQLIdentifierExpr, destructor step 1" << std::endl;

}


SQLIdentifierExpr::SQLIdentifierExpr(std::string &theName){
	name = theName;
}

std::string &SQLIdentifierExpr::getSimleName() {
	return name;
}

std::string &SQLIdentifierExpr::getName() {
	return name;
}

void SQLIdentifierExpr::setName(std::string &theName) {
	name = name;
	lowerName = "";
}

std::string &SQLIdentifierExpr::getLowerName() {

	if (lowerName == "" && name != "") {
		boost::algorithm::to_lower(lowerName);
		//lowerName = name.toLowerCase();
	}

	return lowerName;
}

void SQLIdentifierExpr::setLowerName(std::string &theLowerName) {
	lowerName = theLowerName;
}

void SQLIdentifierExpr::output(std::string &buf) {
	buf += name;
	//buf.append(name);
}

void SQLIdentifierExpr::accept0(SQLASTVisitor *visitor) {
	visitor->visit(this);

	visitor->endVisit(this);
}

//int SQLIdentifierExpr::hashCode() {
	//final int prime = 31;
	//int result = 1;
	//result = prime * result + ((name == NULL) ? 0 : name.hashCode());
	//return result;
//}

//bool SQLIdentifierExpr::equals(Object obj) {
	//if (this == obj) {
		//return true;
	//}
	//if (obj == NULL) {
		//return false;
	//}
	//if (!(obj instanceof SQLIdentifierExpr)) {
		//return false;
	//}
	//SQLIdentifierExpr other = (SQLIdentifierExpr) obj;
	//if (name == NULL) {
		//if (other.name != NULL) {
			//return false;
		//}
	//} else if (!name.equals(other.name)) {
		//return false;
	//}
	//return true;
//}


