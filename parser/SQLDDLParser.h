#ifndef SQLDDLParser_HEADER_H
#define SQLDDLParser_HEADER_H

#include <boost/smart_ptr.hpp>
#include <string>
#include "../ast/statement/SQLTableConstaint.h"

#include "SQLParser.h"
#include "SQLExprParser.h"
#include "SQLStatementParser.h"

class SQLDDLParser : public SQLStatementParser {

	public:
		SQLDDLParser(std::string &sql);
		~SQLDDLParser();

		SQLDDLParser(SQLExprParser *exprParser);

	protected:
		SQLTableConstaint *parseConstraint();
};
typedef boost::shared_ptr<SQLDDLParser> SQLDDLParser_ptr;

#endif

