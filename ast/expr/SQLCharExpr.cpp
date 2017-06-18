#include <boost/algorithm/string/replace.hpp>
#include "SQLCharExpr.h"
SQLCharExpr::SQLCharExpr(){

}

SQLCharExpr::~SQLCharExpr(){

}
SQLCharExpr::SQLCharExpr(std::string & thetext): super(thetext){
	//super(thetext);
}

void SQLCharExpr::output(std::string &buf) {
	if ((text == "") || (text.length() == 0)) {
		//buf.append("NULL");
		buf += "NULL";
	} else {
		//buf.append("'");
		//buf.append(this.text.replaceAll("'", "''"));
		//buf.append("'");


		buf += "'";
		boost::replace_all(text,"'", "''");
		buf += text;
		buf += "'";
	}
}

void SQLCharExpr::accept0(SQLASTVisitor *visitor) {
	visitor->visit(this);
	visitor->endVisit(this);
}
