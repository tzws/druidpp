#include <boost/algorithm/string/replace.hpp>
#include "SQLNCharExpr.h"
SQLNCharExpr::SQLNCharExpr(){

}

SQLNCharExpr::~SQLNCharExpr(){

}
SQLNCharExpr::SQLNCharExpr(std::string &theText) : super(theText){
	//super(theText);
}

void SQLNCharExpr::output(std::string & buf) {
	if ((text == "") || (text.length() == 0)) {
		buf += "NULL";
		return;
	}

	buf += "N'";
	//buf.append(this.text.replaceAll("'", "''"));
	boost::replace_all(text,"'", "''");
	buf += text;
	buf += "'";

	//buf.append("'");

}

void SQLNCharExpr::accept0(SQLASTVisitor * visitor) {
	visitor->visit(this);
	visitor->endVisit(this);
}
