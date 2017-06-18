#ifndef SQLUnaryOperator_HEADER_H
#define SQLUnaryOperator_HEADER_H
#include <boost/smart_ptr.hpp>
#include <string>
class SQLUnaryOperator {

	public:
		static SQLUnaryOperator Plus;
		static SQLUnaryOperator Negative;
		static SQLUnaryOperator Not;
		static SQLUnaryOperator Compl;
		static SQLUnaryOperator Prior;
		static SQLUnaryOperator ConnectByRoot;
		static SQLUnaryOperator BINARY;
		static SQLUnaryOperator RAW;
		static SQLUnaryOperator NOT;

		std::string name;

		SQLUnaryOperator(std::string theName);
};
typedef boost::shared_ptr<SQLUnaryOperator> SQLUnaryOperator_ptr;
#endif

