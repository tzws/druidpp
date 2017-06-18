#include "SQLEvalVisitor.h"
std::string SQLEvalVisitor::EVAL_VALUE       = "eval.value";
std::string SQLEvalVisitor::EVAL_EXPR        = "eval.expr";
Object * SQLEvalVisitor::EVAL_ERROR       = new Object();
Object * SQLEvalVisitor::EVAL_VALUE_COUNT = new Object();
Object * SQLEvalVisitor::EVAL_VALUE_NULL  = new Object();

SQLEvalVisitor::~SQLEvalVisitor() {

}

