#include "ParameterizedOutputVisitor.h"

ParameterizedOutputVisitor::ParameterizedOutputVisitor(){
	this(new StringBuilder());
}
ParameterizedOutputVisitor::~ParameterizedOutputVisitor(){

}

ParameterizedOutputVisitor::ParameterizedOutputVisitor(Appendable appender){
	super(appender);
}

int ParameterizedOutputVisitor::getReplaceCount() {
	return this.replaceCount;
}

void ParameterizedOutputVisitor::incrementReplaceCunt() {
	replaceCount++;
}

bool  ParameterizedOutputVisitor::visit(SQLInListExpr *x) {
	return ParameterizedOutputVisitorUtils.visit(this, x);
}

bool  ParameterizedOutputVisitor::visit(SQLBinaryOpExpr *x) {
	x = ParameterizedOutputVisitorUtils.merge(this, x);

	return super.visit(x);
}

bool  ParameterizedOutputVisitor::visit(SQLIntegerExpr *x) {
	if (!ParameterizedOutputVisitorUtils.checkParameterize(x)) {
		return super.visit(x);
	}

	return ParameterizedOutputVisitorUtils.visit(this, x);
}

bool  ParameterizedOutputVisitor::visit(SQLNumberExpr *x) {
	if (!ParameterizedOutputVisitorUtils.checkParameterize(x)) {
		return super.visit(x);
	}

	return ParameterizedOutputVisitorUtils.visit(this, x);
}

bool  ParameterizedOutputVisitor::visit(SQLCharExpr *x) {
	if (!ParameterizedOutputVisitorUtils.checkParameterize(x)) {
		return super.visit(x);
	}

	return ParameterizedOutputVisitorUtils.visit(this, x);
}

bool  ParameterizedOutputVisitor::visit(SQLNCharExpr *x) {
	if (!ParameterizedOutputVisitorUtils.checkParameterize(x)) {
		return super.visit(x);
	}

	return ParameterizedOutputVisitorUtils.visit(this, x);
}

bool  ParameterizedOutputVisitor::visit(SQLNullExpr *x) {
	if (!ParameterizedOutputVisitorUtils.checkParameterize(x)) {
		return super.visit(x);
	}

	return ParameterizedOutputVisitorUtils.visit(this, x);
}

