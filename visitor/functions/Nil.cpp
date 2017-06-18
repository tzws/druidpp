#include "Nil.h"
Nil::~Nil()
{

}

Nil * Nil::instance()
{
	static Nil x;
	return &x;
}

Object *Nil::eval(SQLEvalVisitor *visitor, SQLMethodInvokeExpr *x) {
	return NULL;
}

