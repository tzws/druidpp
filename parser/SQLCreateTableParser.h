#ifndef SQLCreateTableParser_HEADER_H
#define SQLCreateTableParser_HEADER_H

#include <boost/smart_ptr.hpp>
#include <string>

#include "SQLDDLParser.h"
#include "SQLParser.h"
#include "SQLExprParser.h"
#include "SQLStatementParser.h"
#include "../ast/statement/SQLCreateTableStatement.h"

class SQLCreateTableParser : public SQLDDLParser {

	public:
		SQLCreateTableParser(std::string &sql);
		SQLCreateTableParser(SQLExprParser *exprParser);
		~SQLCreateTableParser();

		SQLCreateTableStatement *parseCrateTable();

		SQLCreateTableStatement *parseCrateTable(bool acceptCreate);

	protected:
		SQLCreateTableStatement *newCreateStatement();
};
typedef boost::shared_ptr<SQLCreateTableParser> SQLCreateTableParser_ptr;

#endif
