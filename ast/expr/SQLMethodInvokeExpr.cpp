#include "SQLMethodInvokeExpr.h"
SQLMethodInvokeExpr::SQLMethodInvokeExpr(): owner(NULL){

}

SQLMethodInvokeExpr::~SQLMethodInvokeExpr(){

	//std::cout << "\t\t" <<  __FILE__ << ": " << __LINE__ << ", SQLMethodInvokeExpr::~SQLMethodInvokeExpr, methodName is: " << methodName << std::endl;
	for(std::list<SQLExpr *>::iterator it = parameters.begin(); it != parameters.end(); ++it) 
	{
		delete *it; 
	}
	parameters.clear();

	if (owner != NULL)
	{
		
		delete owner;
		owner = NULL;
	}


}
SQLMethodInvokeExpr::SQLMethodInvokeExpr(std::string &theMethodName) : owner(NULL), methodName (theMethodName){
	//methodName = theMethodName;
}

SQLMethodInvokeExpr::SQLMethodInvokeExpr(std::string &theMethodName, SQLExpr *theOwner) : methodName (theMethodName), owner (theOwner){

	//this.methodName = methodName;
	//setOwner(owner);
}

std::string &SQLMethodInvokeExpr::getMethodName() {
	return methodName;
}

void SQLMethodInvokeExpr::setMethodName(std::string &theMethodName) {
	methodName = theMethodName;
}

SQLExpr *SQLMethodInvokeExpr::getOwner() {
	return owner;
}

void SQLMethodInvokeExpr::setOwner(SQLExpr *theOwner) {

	//std::cout << "\t\t" <<  __FILE__ << ": " << __LINE__ << ", SQLMethodInvokeExpr::setOwner" << std::endl;
	if (theOwner != NULL) {
		theOwner->setParent(this);
	}
	owner = theOwner;
}

std::list<SQLExpr *> & SQLMethodInvokeExpr::getParameters() {
	return parameters;
}

void SQLMethodInvokeExpr::addParameter(SQLExpr *theParam) {
	if (theParam != NULL) {
		theParam->setParent(this);
	}
	parameters.push_back(theParam);
}

void SQLMethodInvokeExpr::output(std::string & buf) {
	if (owner != NULL) {
		owner->output(buf);
		buf += ".";
	}

	buf += methodName;
	buf += "(";


	//for (int i = 0, size = parameters.size(); i < size; ++i) {
		//if (i != 0) {
			//buf.append(", ");
		//}

		//this.parameters.get(i).output(buf);
	//}

	for(std::list<SQLExpr *>::iterator it = parameters.begin(); it != parameters.end(); ++it)
	{

		buf += ", ";
		(*it)->output(buf);
	}

	buf += ")";
}

void SQLMethodInvokeExpr::accept0(SQLASTVisitor *visitor) {
	if (visitor->visit(this)) {
		acceptChild(visitor, owner);
		acceptChild(visitor, parameters);
	}

	visitor->endVisit(this);
}

//void SQLMethodInvokeExpr::accept0(OracleASTVisitor *visitor) {
	//if (visitor->visit(this)) {
		//acceptChild(visitor, owner);
		//acceptChild(visitor, parameters);
	//}

	//visitor->endVisit(this);
//}

//int SQLMethodInvokeExpr::hashCode() {
	//final int prime = 31;
	//int result = 1;
	//result = prime * result + ((methodName == NULL) ? 0 : methodName.hashCode());
	//result = prime * result + ((owner == NULL) ? 0 : owner.hashCode());
	//result = prime * result + ((parameters == NULL) ? 0 : parameters.hashCode());
	//return result;
//}

//bool SQLMethodInvokeExpr::equals(Object obj) {
	//if (this == obj) {
		//return true;
	//}
	//if (obj == NULL) {
		//return false;
	//}
	//if (getClass() != obj.getClass()) {
		//return false;
	//}
	//SQLMethodInvokeExpr other = (SQLMethodInvokeExpr) obj;
	//if (methodName == NULL) {
		//if (other.methodName != NULL) {
			//return false;
		//}
	//} else if (!methodName.equals(other.methodName)) {
		//return false;
	//}
	//if (owner == NULL) {
		//if (other.owner != NULL) {
			//return false;
		//}
	//} else if (!owner.equals(other.owner)) {
		//return false;
	//}
	//if (parameters == NULL) {
		//if (other.parameters != NULL) {
			//return false;
		//}
	//} else if (!parameters.equals(other.parameters)) {
		//return false;
	//}
	//return true;
//}

