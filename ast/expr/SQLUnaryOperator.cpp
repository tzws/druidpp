#include "SQLUnaryOperator.h"

SQLUnaryOperator SQLUnaryOperator::Plus(std::string("+"));
SQLUnaryOperator SQLUnaryOperator::Negative(std::string("-"));
SQLUnaryOperator SQLUnaryOperator::Not(std::string("!"));
SQLUnaryOperator SQLUnaryOperator::Compl(std::string("~"));
SQLUnaryOperator SQLUnaryOperator::Prior(std::string("PRIOR"));
SQLUnaryOperator SQLUnaryOperator::ConnectByRoot(std::string("CONNECT BY"));
SQLUnaryOperator SQLUnaryOperator::BINARY(std::string("BINARY"));
SQLUnaryOperator SQLUnaryOperator::RAW(std::string("RAW"));
SQLUnaryOperator SQLUnaryOperator::NOT(std::string("NOT"));

SQLUnaryOperator::SQLUnaryOperator(std::string theName){
	name = theName;
}


