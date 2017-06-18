#include <boost/lexical_cast.hpp>
#include "SQLNumberExpr.h"
SQLNumberExpr::SQLNumberExpr(){

}
SQLNumberExpr::~SQLNumberExpr(){
	if (number != NULL)
	{
		delete number;
		number = NULL;
	}
}
SQLNumberExpr::SQLNumberExpr(RNumber * theNumber){

	number = theNumber;
}

RNumber *SQLNumberExpr::getNumber() {
	return number;
}

void SQLNumberExpr::setNumber(RNumber * theNumber) {
	number = theNumber;
}

void SQLNumberExpr::output(std::string & buf) {

	double a = boost::rational_cast<double>(*number);
	std::string s = boost::lexical_cast<std::string>(a);
	buf += s;

	//buf.append(this.number.toString());
}

void SQLNumberExpr::accept0(SQLASTVisitor *visitor) {
	visitor->visit(this);
	visitor->endVisit(this);
}

//int SQLNumberExpr::hashCode() {
	//final int prime = 31;
	//int result = 1;
	//result = prime * result + ((number == null) ? 0 : number.hashCode());
	//return result;
//}

//bool SQLNumberExpr::equals(Object obj) {
	//if (this == obj) {
		//return true;
	//}
	//if (obj == null) {
		//return false;
	//}
	//if (getClass() != obj.getClass()) {
		//return false;
	//}
	//SQLNumberExpr other = (SQLNumberExpr) obj;
	//if (number == null) {
		//if (other.number != null) {
			//return false;
		//}
	//} else if (!number.equals(other.number)) {
		//return false;
	//}
	//return true;
//}

