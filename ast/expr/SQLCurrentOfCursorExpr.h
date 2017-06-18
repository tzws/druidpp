#ifndef SQLCurrentOfCursorExpr_HEADER_H
#define SQLCurrentOfCursorExpr_HEADER_H

#include <boost/smart_ptr.hpp>
#include <string>
#include "../SQLName.h"
#include "../SQLExprImpl.h"
#include "../../visitor/SQLASTVisitor.h"



class SQLCurrentOfCursorExpr : virtual public SQLExprImpl {

	private:
		SQLName *cursorName;

	public:
		SQLCurrentOfCursorExpr();
		virtual ~SQLCurrentOfCursorExpr();

		SQLCurrentOfCursorExpr(SQLName *cursorName);

		SQLName *getCursorName();

		void setCursorName(SQLName *cursorName);

		void output(std::string & buf);

		//int hashCode();
		//bool equals(Object obj);
	protected:
		void accept0(SQLASTVisitor *visitor);


};
typedef boost::shared_ptr<SQLCurrentOfCursorExpr> SQLCurrentOfCursorExpr_ptr;
#endif

