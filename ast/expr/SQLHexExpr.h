#ifndef SQLHexExpr_HEADER_H
#define SQLHexExpr_HEADER_H

#include <boost/smart_ptr.hpp>
#include <string>

#include "../Object.h"
#include "../SQLExprImpl.h"
#include "../statement/SQLSelect.h"
//#include "../HexBin.h"
#include "SQLLiteralExpr.h"

//import com.alibaba.druid.util.HexBin;

class SQLHexExpr : virtual public SQLExprImpl, virtual public SQLLiteralExpr {

	private:
		std::string hex;

	public:
		SQLHexExpr(std::string &hex);
		virtual ~SQLHexExpr();

		std::string &getHex();

		void output(std::string & buf);

		//int hashCode();
		//bool equals(Object obj);
		//char[] toBytes();
	protected:
		void accept0(SQLASTVisitor *visitor);

};
typedef boost::shared_ptr<SQLHexExpr> SQLHexExpr_ptr;
#endif

