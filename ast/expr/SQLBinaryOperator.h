#ifndef SQLBinaryOperator_HEADER_H
#define SQLBinaryOperator_HEADER_H
#include <boost/smart_ptr.hpp>
/**
 * 
 * 二元操作符
 * @author wenshao 2011-5-20 下午12:32:02
 * @formatter:off
 */
#include <string>
class SQLBinaryOperator {
	public:
		static SQLBinaryOperator    Union;
		static SQLBinaryOperator    COLLATE;
		static SQLBinaryOperator    BitwiseXor;

		static SQLBinaryOperator    Multiply;
		static SQLBinaryOperator    Divide;
		static SQLBinaryOperator    Modulus;

		static SQLBinaryOperator    Add;
		static SQLBinaryOperator    Subtract;

		static SQLBinaryOperator    LeftShift;
		static SQLBinaryOperator    RightShift;

		static SQLBinaryOperator    BitwiseAnd;
		static SQLBinaryOperator    BitwiseOr;

		static SQLBinaryOperator    GreaterThan;
		static SQLBinaryOperator    GreaterThanOrEqual;
		static SQLBinaryOperator    Is;
		static SQLBinaryOperator    LessThan;
		static SQLBinaryOperator    LessThanOrEqual;
		static SQLBinaryOperator    LessThanOrEqualOrGreaterThan;
		static SQLBinaryOperator    LessThanOrGreater;

		static SQLBinaryOperator    Like;
		static SQLBinaryOperator    NotLike;

		static SQLBinaryOperator    RLike;
		static SQLBinaryOperator    NotRLike;

		static SQLBinaryOperator    NotEqual;
		static SQLBinaryOperator    NotLessThan;
		static SQLBinaryOperator    NotGreaterThan;
		static SQLBinaryOperator    IsNot;
		static SQLBinaryOperator    Escape;
		static SQLBinaryOperator    RegExp;
		static SQLBinaryOperator    NotRegExp;
		static SQLBinaryOperator    Equality;

		static SQLBinaryOperator    BitwiseNot;
		static SQLBinaryOperator    Concat;

		static SQLBinaryOperator    BooleanAnd;
		static SQLBinaryOperator    BooleanXor;
		static SQLBinaryOperator    BooleanOr;
		static SQLBinaryOperator    Assignment;

		static SQLBinaryOperator    PostgresStyleTypeCast;

	private:
		std::string name;
		int  priority;
		bool isRel;

		SQLBinaryOperator();
		SQLBinaryOperator(std::string &xname, int xpriority, bool xr = false);
		SQLBinaryOperator(const char *xname, int xpriority, bool xr = false);

	public:
		static int getPriority(SQLBinaryOperator o);
		std::string &getName();
		int getPriority();
		bool isRelational();
};
typedef boost::shared_ptr<SQLBinaryOperator> SQLBinaryOperator_ptr;
#endif

