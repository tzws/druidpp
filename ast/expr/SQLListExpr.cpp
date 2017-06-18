#include "SQLListExpr.h"
SQLListExpr::SQLListExpr() {
}

SQLListExpr::~SQLListExpr() {

	for(std::list<SQLExpr *>::iterator it = items.begin(); it != items.end(); ++it) 
	{
		delete *it; 
	}
	items.clear();


}
std::list<SQLExpr *> & SQLListExpr::getItems() {
	return items;
}

void SQLListExpr::accept0(SQLASTVisitor *visitor) {
	if (visitor->visit(this)) {
		acceptChild(visitor, items);
	}
	visitor->endVisit(this);
}

//int SQLListExpr::hashCode() {
//final int prime = 31;
//int result = 1;
//result = prime * result + ((items == NULL) ? 0 : items.hashCode());
//return result;
//}

//bool SQLListExpr::equals(Object obj) {
//if (this == obj) {
//return true;
//}
//if (obj == NULL) {
//return false;
//}
//if (getClass() != obj.getClass()) {
//return false;
//}
//SQLListExpr other = (SQLListExpr) obj;
//if (items == NULL) {
//if (other.items != NULL) {
//return false;
//}
//} else if (!items.equals(other.items)) {
//return false;
//}
//return true;
//}

