
#ifndef SQLStatementParser_HEADER_H
#define SQLStatementParser_HEADER_H

#include <boost/smart_ptr.hpp>
#include "../ast/SQLExpr.h"
#include "../ast/SQLName.h"
#include "../ast/SQLObject.h"
#include "../ast/SQLStatement.h"
#include "../ast/expr/SQLIdentifierExpr.h"
#include "../ast/expr/SQLListExpr.h"
#include "../ast/expr/SQLQueryExpr.h"
#include "../ast/expr/SQLVariantRefExpr.h"
#include "../ast/statement/SQLAlterTableAddColumn.h"
#include "../ast/statement/SQLAlterTableAddConstraint.h"
#include "../ast/statement/SQLAlterTableAddIndex.h"
#include "../ast/statement/SQLAlterTableAlterColumn.h"
#include "../ast/statement/SQLAlterTableDisableConstraint.h"
#include "../ast/statement/SQLAlterTableDisableKeys.h"
#include "../ast/statement/SQLAlterTableDropColumnItem.h"
#include "../ast/statement/SQLAlterTableDropConstraint.h"
#include "../ast/statement/SQLAlterTableEnableConstraint.h"
#include "../ast/statement/SQLAlterTableEnableKeys.h"
#include "../ast/statement/SQLAlterTableStatement.h"
#include "../ast/statement/SQLAssignItem.h"
#include "../ast/statement/SQLCallStatement.h"
#include "../ast/statement/SQLColumnDefinition.h"
#include "../ast/statement/SQLCommentStatement.h"
#include "../ast/statement/SQLConstaint.h"
#include "../ast/statement/SQLCreateDatabaseStatement.h"
#include "../ast/statement/SQLCreateIndexStatement.h"
#include "../ast/statement/SQLCreateTableStatement.h"
#include "../ast/statement/SQLCreateTriggerStatement.h"
//#include "../ast/statement/SQLCreateTriggerstatement/TriggerEvent.h"
//#include "../ast/statement/SQLCreateTriggerstatement/TriggerType.h"
#include "../ast/statement/SQLCreateViewStatement.h"
#include "../ast/statement/SQLDeleteStatement.h"
#include "../ast/statement/SQLDropDatabaseStatement.h"
#include "../ast/statement/SQLDropFunctionStatement.h"
#include "../ast/statement/SQLDropIndexStatement.h"
#include "../ast/statement/SQLDropProcedureStatement.h"
#include "../ast/statement/SQLDropSequenceStatement.h"
#include "../ast/statement/SQLDropTableSpaceStatement.h"
#include "../ast/statement/SQLDropTableStatement.h"
#include "../ast/statement/SQLDropTriggerStatement.h"
#include "../ast/statement/SQLDropUserStatement.h"
#include "../ast/statement/SQLDropViewStatement.h"
#include "../ast/statement/SQLExplainStatement.h"
#include "../ast/statement/SQLExprTableSource.h"
#include "../ast/statement/SQLGrantStatement.h"
//#include "../ast/statement/SQLGrantstatement/ObjectType.h"
#include "../ast/statement/SQLInsertInto.h"
#include "../ast/statement/SQLValuesClause.h"
#include "../ast/statement/SQLInsertStatement.h"
#include "../ast/statement/SQLPrimaryKey.h"
#include "../ast/statement/SQLReleaseSavePointStatement.h"
#include "../ast/statement/SQLRollbackStatement.h"
#include "../ast/statement/SQLSavePointStatement.h"
#include "../ast/statement/SQLSelect.h"
#include "../ast/statement/SQLSelectOrderByItem.h"
#include "../ast/statement/SQLSelectStatement.h"
#include "../ast/statement/SQLSetStatement.h"
#include "../ast/statement/SQLTableSource.h"
#include "../ast/statement/SQLTruncateStatement.h"
#include "../ast/statement/SQLUpdateSetItem.h"
#include "../ast/statement/SQLUpdateStatement.h"
#include "../ast/statement/SQLUseStatement.h"




#include "SQLParser.h"


class SQLExprParser;
class SQLCreateTableParser;
class SQLSelectParser;
class SQLStatementParser : public SQLParser {

	protected:
		std::list<SQLStatement *> statementList;
		std::list<SQLStatement *> yaList;
		SQLExprParser *exprParser;
		bool exprParserHere;
		SQLDropTableStatement *parseDropTable(bool acceptDrop);
		SQLDropSequenceStatement *parseDropSequece(bool acceptDrop);
		SQLDropTriggerStatement *parseDropTrigger(bool acceptDrop);
		SQLDropViewStatement *parseDropView(bool acceptDrop);
		SQLDropDatabaseStatement *parseDropDatabase(bool acceptDrop);
		SQLDropFunctionStatement *parseDropFunction(bool acceptDrop);
		SQLDropTableSpaceStatement *parseDropTablespace(bool acceptDrop);
		SQLDropProcedureStatement *parseDropProcedure(bool acceptDrop);
		void parseInsert0(SQLInsertInto *insertStatement);
		void parseInsert0_hinits(SQLInsertInto *insertStatement);
		void parseInsert0(SQLInsertInto *insertStatement, bool acceptSubQuery);
		void parseUpdateSet(SQLUpdateStatement *update);
		SQLUpdateStatement *createUpdateStatement();
		SQLAlterTableAddColumn *parseAlterTableAddColumn();
		SQLAlterTableAddIndex *parseAlterTableAddIndex();

	public:
		typedef SQLParser super;
		~SQLStatementParser();
		SQLStatementParser(std::string & sql);

		SQLStatementParser(SQLExprParser *exprParser);

		SQLExprParser *getExprParser();

		std::list<SQLStatement *>  & parseStatementList();

		void parseStatementList(std::list<SQLStatement *> & statementList);

		void parseStatementList(std::list<SQLStatement *> & statementList, int max);

		SQLRollbackStatement *parseRollback();

		SQLStatement *parseCommit();

		SQLStatement *parseShow();

		SQLUseStatement *parseUse();

		SQLGrantStatement *parseGrant();

		SQLStatement *parseSavePoint();

		SQLStatement *parseReleaseSavePoint();

		SQLStatement *parseAlter();

		void parseAlterDrop(SQLAlterTableStatement *stmt);

		SQLStatement *parseRename();

		SQLStatement *parseTruncate();

		SQLStatement *parseInsert();

		bool parseStatementListDialect(std::list<SQLStatement *> & statementList);

		SQLDropUserStatement *parseDropUser();

		SQLStatement *parseDropIndex();

		SQLCallStatement *parseCall();

		SQLStatement *parseSet();

		void parseAssignItems(std::list<SQLAssignItem *> & items, SQLObject *parent);

		SQLStatement *parseCreate();

		SQLStatement *parseCreateDbLink();

		SQLStatement *parseCreateTrigger();

		SQLStatement *parseBlock();

		SQLStatement *parseCreateDatabase();

		SQLStatement *parseCreateProcedure();

		SQLStatement *parseCreateSequence(bool acceptCreate);

		SQLStatement *parseCreateIndex(bool acceptCreate);

		SQLCreateTableParser *getSQLCreateTableParser();

		SQLSelectStatement *parseSelect();

		SQLSelectParser *createSQLSelectParser();

		SQLUpdateStatement *parseUpdateStatement();



		SQLDeleteStatement *parseDeleteStatement();

		SQLCreateTableStatement *parseCreateTable();

		SQLCreateViewStatement *parseCreateView(); 

		SQLCommentStatement *parseComment(); 


		SQLStatement *parseStatement();

		SQLExplainStatement *parseExplain();

};
typedef boost::shared_ptr<SQLStatementParser> SQLStatementParser_ptr;

#endif

