#include "SQLCurrentOfCursorExpr.h"
SQLCurrentOfCursorExpr::SQLCurrentOfCursorExpr(){

}

SQLCurrentOfCursorExpr::~SQLCurrentOfCursorExpr(){
	if (cursorName != NULL)
	{
		delete cursorName;
		cursorName = NULL;
		
	}
}
SQLCurrentOfCursorExpr::SQLCurrentOfCursorExpr(SQLName * theCursorName){
	cursorName = theCursorName;
}

SQLName *SQLCurrentOfCursorExpr::getCursorName() {
	return cursorName;
}

void SQLCurrentOfCursorExpr::setCursorName(SQLName *theCursorName) {
	cursorName = theCursorName;
}

void SQLCurrentOfCursorExpr::output(std::string & buf) {
	//buf.append("CURRENT OF ");
	buf += "CURRENT OF ";
	cursorName->output(buf);
}

void SQLCurrentOfCursorExpr::accept0(SQLASTVisitor *visitor) {
	if (visitor->visit(this)) {
		acceptChild(visitor, cursorName);
	}
	visitor->endVisit(this);
}

//int SQLCurrentOfCursorExpr::hashCode() {
	//final int prime = 31;
	//int result = 1;
	//result = prime * result + ((cursorName == NULL) ? 0 : cursorName.hashCode());
	//return result;
//}

//bool SQLCurrentOfCursorExpr::equals(Object obj) {
	//if (this == obj) {
		//return true;
	//}
	//if (obj == NULL) {
		//return false;
	//}
	//if (getClass() != obj.getClass()) {
		//return false;
	//}
	//SQLCurrentOfCursorExpr other = (SQLCurrentOfCursorExpr) obj;
	//if (cursorName == NULL) {
		//if (other.cursorName != NULL) {
			//return false;
		//}
	//} else if (!cursorName.equals(other.cursorName)) {
		//return false;
	//}
	//return true;
//}

