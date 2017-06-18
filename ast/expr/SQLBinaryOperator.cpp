/**
 * 
 * 二元操作符
 * @author wenshao 2011-5-20 下午12:32:02
 * @formatter:off
 */
#include "SQLBinaryOperator.h"
#include <stdio.h>
#include <iostream>

SQLBinaryOperator    SQLBinaryOperator::Union = SQLBinaryOperator("UNION", 0);
SQLBinaryOperator    SQLBinaryOperator::COLLATE = SQLBinaryOperator("COLLATE", 20);
SQLBinaryOperator    SQLBinaryOperator::BitwiseXor = SQLBinaryOperator("^", 50);

SQLBinaryOperator    SQLBinaryOperator::Multiply = SQLBinaryOperator("*", 60);
SQLBinaryOperator    SQLBinaryOperator::Divide = SQLBinaryOperator("/", 60);
SQLBinaryOperator    SQLBinaryOperator::Modulus = SQLBinaryOperator("%", 60);

SQLBinaryOperator    SQLBinaryOperator::Add = SQLBinaryOperator("+", 70);
SQLBinaryOperator    SQLBinaryOperator::Subtract = SQLBinaryOperator("-", 70);

SQLBinaryOperator    SQLBinaryOperator::LeftShift = SQLBinaryOperator("<<", 80);
SQLBinaryOperator    SQLBinaryOperator::RightShift = SQLBinaryOperator(">>", 80);

SQLBinaryOperator    SQLBinaryOperator::BitwiseAnd = SQLBinaryOperator("&", 90);
SQLBinaryOperator    SQLBinaryOperator::BitwiseOr = SQLBinaryOperator("|", 100);

SQLBinaryOperator    SQLBinaryOperator::GreaterThan = SQLBinaryOperator(">", 110, true);
SQLBinaryOperator    SQLBinaryOperator::GreaterThanOrEqual = SQLBinaryOperator(">=", 110, true);
SQLBinaryOperator    SQLBinaryOperator::Is = SQLBinaryOperator("IS", 110);
SQLBinaryOperator    SQLBinaryOperator::LessThan = SQLBinaryOperator("<", 110, true);
SQLBinaryOperator    SQLBinaryOperator::LessThanOrEqual = SQLBinaryOperator("<=", 110, true);
SQLBinaryOperator    SQLBinaryOperator::LessThanOrEqualOrGreaterThan = SQLBinaryOperator("<=>",110);
SQLBinaryOperator    SQLBinaryOperator::LessThanOrGreater = SQLBinaryOperator("<>", 110, true);

SQLBinaryOperator    SQLBinaryOperator::Like = SQLBinaryOperator("LIKE", 110, true);
SQLBinaryOperator    SQLBinaryOperator::NotLike = SQLBinaryOperator("NOT LIKE", 110, true);

SQLBinaryOperator    SQLBinaryOperator::RLike = SQLBinaryOperator("RLIKE", 110, true);
SQLBinaryOperator    SQLBinaryOperator::NotRLike = SQLBinaryOperator("NOT RLIKE", 110, true);

SQLBinaryOperator    SQLBinaryOperator::NotEqual = SQLBinaryOperator("!=", 110, true);
SQLBinaryOperator    SQLBinaryOperator::NotLessThan = SQLBinaryOperator("!<", 110, true);
SQLBinaryOperator    SQLBinaryOperator::NotGreaterThan = SQLBinaryOperator("!>", 110, true);
SQLBinaryOperator    SQLBinaryOperator::IsNot = SQLBinaryOperator("IS NOT", 110);
SQLBinaryOperator    SQLBinaryOperator::Escape = SQLBinaryOperator("ESCAPE", 110);
SQLBinaryOperator    SQLBinaryOperator::RegExp = SQLBinaryOperator("REGEXP", 110, true);
SQLBinaryOperator    SQLBinaryOperator::NotRegExp = SQLBinaryOperator("NOT REGEXP", 110, true);
SQLBinaryOperator    SQLBinaryOperator::Equality = SQLBinaryOperator("=", 110, true);

SQLBinaryOperator    SQLBinaryOperator::BitwiseNot = SQLBinaryOperator("!", 130);
SQLBinaryOperator    SQLBinaryOperator::Concat = SQLBinaryOperator("||", 140);

SQLBinaryOperator    SQLBinaryOperator::BooleanAnd = SQLBinaryOperator("AND", 140);
SQLBinaryOperator    SQLBinaryOperator::BooleanXor = SQLBinaryOperator("XOR", 150);
SQLBinaryOperator    SQLBinaryOperator::BooleanOr = SQLBinaryOperator("OR", 160);
SQLBinaryOperator    SQLBinaryOperator::Assignment = SQLBinaryOperator(":=", 169);

SQLBinaryOperator    SQLBinaryOperator::PostgresStyleTypeCast = SQLBinaryOperator("::", 20);                                             


SQLBinaryOperator::SQLBinaryOperator(std::string &xname, int xpriority, bool xr){
	//std::cout << "name is: " << xname << std::endl;
	this->name = xname;
	this->priority = xpriority;
	this->isRel = xr;
}

SQLBinaryOperator::SQLBinaryOperator(const char * xname, int xpriority, bool xr){
	std::string x (xname);
	//std::cout << "name is: " << x << std::endl;
	this->name = x;
	this->priority = xpriority;
	this->isRel = xr;
}


int SQLBinaryOperator::getPriority(SQLBinaryOperator o) {
	return 0;
}


std::string &SQLBinaryOperator::getName() {
	return this->name;
}

int SQLBinaryOperator::getPriority() {
	return this->priority;
}

bool SQLBinaryOperator::isRelational() {
	return this->isRel;
}

