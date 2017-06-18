
#ifndef SQLSelectParser_HEADER_H
#define SQLSelectParser_HEADER_H

#include <boost/smart_ptr.hpp>

#include "../ast/SQLExpr.h"
#include "../ast/SQLOrderBy.h"
#include "../ast/SQLSetQuantifier.h"
#include "../ast/expr/SQLIdentifierExpr.h"
#include "../ast/statement/SQLExprTableSource.h"
#include "../ast/statement/SQLJoinTableSource.h"

#include "../ast/statement/SQLSelect.h"
#include "../ast/statement/SQLSelectGroupByClause.h"
#include "../ast/statement/SQLSelectItem.h"
#include "../ast/statement/SQLSelectQuery.h"
#include "../ast/statement/SQLSelectQueryBlock.h"
#include "../ast/statement/SQLSubqueryTableSource.h"
#include "../ast/statement/SQLTableSource.h"
#include "../ast/statement/SQLUnionOperator.h"
#include "../ast/statement/SQLUnionQuery.h"
#include "../ast/statement/SQLWithSubqueryClause.h"
#include "../ast/statement/SQLWithSubqueryClause_Entry.h"


#include "SQLParser.h"

class SQLExprParser;
typedef boost::shared_ptr<SQLExprParser> SQLExprParser_ptr;
class SQLSelectParser : public SQLParser {

	typedef SQLParser super;

	private:
	//std::list<SQLSelectItem *> selectList;
	protected:
		SQLExprParser *exprParser;

		SQLUnionQuery *createSQLUnionQuery();
		void withSubquery(SQLSelect *select);
		void parseWhere(SQLSelectQueryBlock *queryBlock);
		void parseGroupBy(SQLSelectQueryBlock *queryBlock);
		void parseSelectList(SQLSelectQueryBlock *queryBlock);
		SQLSelectItem *parseSelectItem();
		SQLTableSource *parseTableSourceRest(SQLTableSource *tableSource);

	public:
		SQLSelectParser(std::string &sql);
		~SQLSelectParser();

		SQLSelectParser(Lexer *lexer);

		SQLSelectParser(SQLExprParser *exprParser);

		SQLSelect *select();
		SQLUnionQuery *unionRest(SQLUnionQuery *xunion);
		SQLSelectQuery *queryRest(SQLSelectQuery *selectQuery);
		SQLSelectQuery *query();
		void parseFrom(SQLSelectQueryBlock *queryBlock);
		SQLTableSource *parseTableSource();
		SQLExpr *expr();
		SQLOrderBy *parseOrderBy();
		void acceptKeyword(std::string &ident);

	private:
		void parseTableSourceQueryTableExpr(SQLExprTableSource *tableReference);

};
typedef boost::shared_ptr<SQLSelectParser> SQLSelectParser_ptr;


#endif

