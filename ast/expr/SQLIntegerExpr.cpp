#include <boost/lexical_cast.hpp>
#include "SQLIntegerExpr.h"
SQLIntegerExpr::SQLIntegerExpr(RNumber * theNumber){

	number = theNumber;
}

SQLIntegerExpr::SQLIntegerExpr(){

}

SQLIntegerExpr::~SQLIntegerExpr(){
	if (number != NULL)
	{
		delete number;
		number = NULL;
	}

}
RNumber *SQLIntegerExpr::getNumber() {
	return number;
}

int SQLIntegerExpr::intValue() {
	int a = boost::rational_cast<int>(*number);
	return a;
}
void SQLIntegerExpr::setNumber(RNumber *theNumber) {
	number = theNumber;
}

void SQLIntegerExpr::output(std::string  & buf) {
	int a = boost::rational_cast<int>(*number);
	//std::string s = std::to_string(a);
	std::string s = boost::lexical_cast<std::string>(a);
	//buf.append(this.number);
	buf += s;
}

void SQLIntegerExpr::accept0(SQLASTVisitor *visitor) {
	visitor->visit(this);

	visitor->endVisit(this);
}

//int SQLIntegerExpr::hashCode() {
	//final int prime = 31;
	//int result = 1;
	//result = prime * result + ((number == NULL) ? 0 : number.hashCode());
	//return result;
//}

//bool SQLIntegerExpr::equals(Object obj) {
	//if (this == obj) {
		//return true;
	//}
	//if (obj == NULL) {
		//return false;
	//}
	//if (getClass() != obj.getClass()) {
		//return false;
	//}
	//SQLIntegerExpr other = (SQLIntegerExpr) obj;
	//if (number == NULL) {
		//if (other.number != NULL) {
			//return false;
		//}
	//} else if (!number.equals(other.number)) {
		//return false;
	//}
	//return true;
//}

