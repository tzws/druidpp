
#include "SQLHint.h"
#include "SQLCommentHint.h"
SQLCommentHint::SQLCommentHint(){

}

SQLCommentHint::~SQLCommentHint(){

}
SQLCommentHint::SQLCommentHint(std::string &theText){

	text = theText;
}

std::string &SQLCommentHint::getText() {
	return text;
}

void SQLCommentHint::setText(std::string &theText) {
	text = theText;
}

void SQLCommentHint::accept0(SQLASTVisitor *visitor) {

	visitor->visit(this);
	visitor->endVisit(this);

}

