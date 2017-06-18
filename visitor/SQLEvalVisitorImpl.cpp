#include "SQLEvalVisitorImpl.h"


SQLEvalVisitorImpl::SQLEvalVisitorImpl() : variantIndex(-1), markVariantIndex(true){
	this(new ArrayList<Object *>(1));
}

SQLEvalVisitorImpl::SQLEvalVisitorImpl(std::list<Object *> parameters) 
	: 
		variantIndex(-1), 
		markVariantIndex(true)
{
	this->parameters = parameters;
}

std::list<Object *> SQLEvalVisitorImpl::getParameters() {
	return parameters;
}

void SQLEvalVisitorImpl::setParameters(std::list<Object *> parameters) {
	this->parameters = parameters;
}

bool SQLEvalVisitorImpl::visit(SQLCharExpr *x) {
	return SQLEvalVisitorUtils.visit(this, x);
}

int SQLEvalVisitorImpl::incrementAndGetVariantIndex() {
	return ++variantIndex;
}

int SQLEvalVisitorImpl::getVariantIndex() {
	return variantIndex;
}

bool SQLEvalVisitorImpl::visit(SQLVariantRefExpr *x) {
	return SQLEvalVisitorUtils.visit(this, x);
}

bool SQLEvalVisitorImpl::visit(SQLBinaryOpExpr *x) {
	return SQLEvalVisitorUtils.visit(this, x);
}

bool SQLEvalVisitorImpl::visit(SQLIntegerExpr *x) {
	return SQLEvalVisitorUtils.visit(this, x);
}

bool SQLEvalVisitorImpl::visit(SQLNumberExpr *x) {
	return SQLEvalVisitorUtils.visit(this, x);
}

bool SQLEvalVisitorImpl::visit(SQLHexExpr *x) {
	return SQLEvalVisitorUtils.visit(this, x);
}

bool SQLEvalVisitorImpl::visit(SQLCaseExpr *x) {
	return SQLEvalVisitorUtils.visit(this, x);
}

bool SQLEvalVisitorImpl::visit(SQLInListExpr *x) {
	return SQLEvalVisitorUtils.visit(this, x);
}

bool SQLEvalVisitorImpl::visit(SQLNullExpr *x) {
	return SQLEvalVisitorUtils.visit(this, x);
}

bool SQLEvalVisitorImpl::visit(SQLMethodInvokeExpr *x) {
	return SQLEvalVisitorUtils.visit(this, x);
}

bool SQLEvalVisitorImpl::visit(SQLQueryExpr *x) {
	return SQLEvalVisitorUtils.visit(this, x);
}

bool SQLEvalVisitorImpl::isMarkVariantIndex() {
	return markVariantIndex;
}

void SQLEvalVisitorImpl::setMarkVariantIndex(bool markVariantIndex) {
	this->markVariantIndex = markVariantIndex;
}

Function SQLEvalVisitorImpl::getFunction(std::string funcName) {
	return functions.get(funcName);
}

void SQLEvalVisitorImpl::registerFunction(std::string funcName, Function function) {
	functions.put(funcName, function);
}

bool SQLEvalVisitorImpl::visit(SQLIdentifierExpr *x) {
	return SQLEvalVisitorUtils.visit(this, x);
}

void SQLEvalVisitorImpl::unregisterFunction(std::string funcName) {
	functions.remove(funcName);
}

