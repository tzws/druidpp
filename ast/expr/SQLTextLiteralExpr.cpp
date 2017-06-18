#include "SQLTextLiteralExpr.h"
SQLTextLiteralExpr::SQLTextLiteralExpr(){

}
SQLTextLiteralExpr::~SQLTextLiteralExpr(){

}


SQLTextLiteralExpr::SQLTextLiteralExpr(std::string &theText){

	text = theText;
}

std::string &SQLTextLiteralExpr::getText() {
	return text;
}

void SQLTextLiteralExpr::setText(std::string &theText) {
	text = theText;
}

//int SQLTextLiteralExpr::hashCode() {
	//final int prime = 31;
	//int result = 1;
	//result = prime * result + ((text == null) ? 0 : text.hashCode());
	//return result;
//}

//bool SQLTextLiteralExpr::equals(Object obj) {
	//if (this == obj) {
		//return true;
	//}
	//if (obj == null) {
		//return false;
	//}
	//if (getClass() != obj.getClass()) {
		//return false;
	//}
	//SQLTextLiteralExpr other = (SQLTextLiteralExpr) obj;
	//if (text == null) {
		//if (other.text != null) {
			//return false;
		//}
	//} else if (!text.equals(other.text)) {
		//return false;
	//}
	//return true;
//}

