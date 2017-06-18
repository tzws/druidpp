#ifndef SQLASTOutputVisitor_HEADER_H 
#define SQLASTOutputVisitor_HEADER_H

//import java.io.IOException;
//import java.io.InputStream;
//import java.io.Reader;
//import java.sql.Blob;
//import java.sql.Clob;
//import java.sql.NClob;
//import java.text.SimpleDateFormat;
//import java.util.ArrayList;
//import java.util.Date;
//import java.util.List;

#include "../ast/SQLCommentHint.h"
#include "../ast/SQLDataType.h"
#include "../ast/SQLExpr.h"
#include "../ast/SQLObject.h"
#include "../ast/SQLOrderBy.h"
#include "../ast/SQLOver.h"
#include "../ast/SQLSetQuantifier.h"
#include "../ast/SQLStatement.h"
#include "../ast/expr/SQLAggregateExpr.h"
#include "../ast/expr/SQLAllColumnExpr.h"
#include "../ast/expr/SQLAllExpr.h"
#include "../ast/expr/SQLAnyExpr.h"
#include "../ast/expr/SQLBetweenExpr.h"
#include "../ast/expr/SQLBinaryOpExpr.h"
#include "../ast/expr/SQLBinaryOperator.h"
#include "../ast/expr/SQLCaseExpr.h"
#include "../ast/expr/SQLCastExpr.h"
#include "../ast/expr/SQLCharExpr.h"
#include "../ast/expr/SQLCurrentOfCursorExpr.h"
#include "../ast/expr/SQLDefaultExpr.h"
#include "../ast/expr/SQLExistsExpr.h"
#include "../ast/expr/SQLHexExpr.h"
#include "../ast/expr/SQLIdentifierExpr.h"
#include "../ast/expr/SQLInListExpr.h"
#include "../ast/expr/SQLInSubQueryExpr.h"
#include "../ast/expr/SQLIntegerExpr.h"
#include "../ast/expr/SQLListExpr.h"
#include "../ast/expr/SQLMethodInvokeExpr.h"
#include "../ast/expr/SQLNCharExpr.h"
#include "../ast/expr/SQLNotExpr.h"
#include "../ast/expr/SQLNullExpr.h"
#include "../ast/expr/SQLNumberExpr.h"
#include "../ast/expr/SQLPropertyExpr.h"
#include "../ast/expr/SQLQueryExpr.h"
#include "../ast/expr/SQLSomeExpr.h"
#include "../ast/expr/SQLUnaryExpr.h"
#include "../ast/expr/SQLVariantRefExpr.h"
#include "../ast/statement/NotNullConstraint.h"
#include "../ast/statement/SQLAlterTableAddColumn.h"
#include "../ast/statement/SQLAlterTableAddConstraint.h"
#include "../ast/statement/SQLAlterTableAddIndex.h"
#include "../ast/statement/SQLAlterTableAlterColumn.h"
#include "../ast/statement/SQLAlterTableDisableConstraint.h"
#include "../ast/statement/SQLAlterTableDisableKeys.h"
#include "../ast/statement/SQLAlterTableDropColumnItem.h"
#include "../ast/statement/SQLAlterTableDropConstraint.h"
#include "../ast/statement/SQLAlterTableDropForeinKey.h"
#include "../ast/statement/SQLAlterTableDropIndex.h"
#include "../ast/statement/SQLAlterTableDropPrimaryKey.h"
#include "../ast/statement/SQLAlterTableEnableConstraint.h"
#include "../ast/statement/SQLAlterTableEnableKeys.h"
#include "../ast/statement/SQLAlterTableItem.h"
#include "../ast/statement/SQLAlterTableRenameColumn.h"
#include "../ast/statement/SQLAlterTableStatement.h"
#include "../ast/statement/SQLAssignItem.h"
#include "../ast/statement/SQLCallStatement.h"
#include "../ast/statement/SQLCharactorDataType.h"
#include "../ast/statement/SQLCheck.h"
#include "../ast/statement/SQLColumnCheck.h"
#include "../ast/statement/SQLColumnConstraint.h"
#include "../ast/statement/SQLColumnDefinition.h"
#include "../ast/statement/SQLColumnPrimaryKey.h"
#include "../ast/statement/SQLColumnReference.h"
#include "../ast/statement/SQLColumnUniqueKey.h"
#include "../ast/statement/SQLCommentStatement.h"
#include "../ast/statement/SQLCreateDatabaseStatement.h"
#include "../ast/statement/SQLCreateIndexStatement.h"
#include "../ast/statement/SQLCreateTableStatement.h"
#include "../ast/statement/SQLCreateTriggerStatement.h"
//#include "../ast/statement/SQLCreateTriggerstatement/TriggerEvent.h"
//#include "../ast/statement/SQLCreateTriggerstatement/TriggerType.h"
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
#include "../ast/statement/SQLExprHint.h"
#include "../ast/statement/SQLExprTableSource.h"
#include "../ast/statement/SQLForeignKeyConstraint.h"
#include "../ast/statement/SQLForeignKeyImpl.h"
#include "../ast/statement/SQLGrantStatement.h"
#include "../ast/statement/SQLInsertStatement.h"
//#include "../ast/statement/SQLInsertstatement/ValuesClause.h"
#include "../ast/statement/SQLValuesClause.h"
#include "../ast/statement/SQLJoinTableSource.h"
//#include "../ast/statement/SQLJoinTableSource.JoinType.h"
#include "../ast/statement/SQLPrimaryKey.h"
#include "../ast/statement/SQLPrimaryKeyImpl.h"
#include "../ast/statement/SQLReleaseSavePointStatement.h"
#include "../ast/statement/SQLRollbackStatement.h"
#include "../ast/statement/SQLSavePointStatement.h"
#include "../ast/statement/SQLSelect.h"
#include "../ast/statement/SQLSelectGroupByClause.h"
#include "../ast/statement/SQLSelectItem.h"
#include "../ast/statement/SQLSelectOrderByItem.h"
#include "../ast/statement/SQLSelectQueryBlock.h"
#include "../ast/statement/SQLSelectStatement.h"
#include "../ast/statement/SQLSetStatement.h"
#include "../ast/statement/SQLSubqueryTableSource.h"
#include "../ast/statement/SQLTableElement.h"
#include "../ast/statement/SQLTruncateStatement.h"
#include "../ast/statement/SQLUnionQuery.h"
#include "../ast/statement/SQLUnique.h"
#include "../ast/statement/SQLUniqueConstraint.h"
#include "../ast/statement/SQLUpdateSetItem.h"
#include "../ast/statement/SQLUpdateStatement.h"
#include "../ast/statement/SQLUseStatement.h"
#include "../ast/statement/SQLWithSubqueryClause.h"

#include "PrintableVisitor.h"
#include "SQLASTVisitorAdapter.h"

class SQLASTOutputVisitor : virtual public  SQLASTVisitorAdapter, virtual public PrintableVisitor {

	protected:
		//Appendable appender;
		std::string appender;
		int              selectListNumberOfLine;
	private:
		std::string             indent;
		int                indentCount;
		bool             prettyFormat;

		std::list<Object *>       parameters;

	public:
		SQLASTOutputVisitor(std::string & appender);
		virtual ~SQLASTOutputVisitor();

		int getParametersSize();

		std::list<Object *> &getParameters();

		void setParameters(std::list<Object *> &parameters);

		int getIndentCount();

		std::string & getAppender();

		bool  isPrettyFormat();

		void setPrettyFormat(bool  prettyFormat);

		void decrementIndent();

		void incrementIndent();

		void print(char value);

		void print(int value);

		void print(Date date);

		void print(long value);

		void print(std::string &text);

	protected:
		void printAlias(std::string &alias);

		void printAndAccept(std::list<SQLObject *> &nodes, std::string &seperator);

		void printSelectList(std::list<SQLSelectItem> &selectList);

		void printlnAndAccept(std::list<SQLObject *> &nodes, std::string &seperator);

	public:
		void printIndent();

		void println();

		void println(std::string &text);

		// ////////////////////

		bool  visit(SQLBetweenExpr *x);

		bool  visit(SQLBinaryOpExpr *x);

	private:
		void visitorBinaryRight(SQLBinaryOpExpr *x);

		void visitBinaryLeft(SQLExpr *left, SQLBinaryOperator *op);

	public:
		bool  visit(SQLCaseExpr *x);

		bool  visit(SQLCaseExpr_Item *x);

		bool  visit(SQLCastExpr *x);

		bool  visit(SQLCharExpr *x);

		bool  visit(SQLDataType *x);

		bool  visit(SQLCharactorDataType *x);

		bool  visit(SQLExistsExpr *x);

		bool  visit(SQLIdentifierExpr *x);

		bool  visit(SQLInListExpr *x);

		bool  visit(SQLIntegerExpr *x);

		bool  visit(SQLMethodInvokeExpr *x);

		bool  visit(SQLAggregateExpr *x);

	protected:
		void visitAggreateRest(SQLAggregateExpr *aggregateExpr);

	public:
		bool  visit(SQLAllColumnExpr *x);

		bool  visit(SQLNCharExpr *x);

		bool  visit(SQLNotExpr *x);

		bool  visit(SQLNullExpr *x);

		bool  visit(SQLNumberExpr *x);

		bool  visit(SQLPropertyExpr *x);

		bool  visit(SQLQueryExpr *x);

		bool  visit(SQLSelectGroupByClause *x);

		bool  visit(SQLSelect *x);

		bool  visit(SQLSelectQueryBlock *x);

		bool  visit(SQLSelectItem *x);

		bool  visit(SQLOrderBy *x);

		bool  visit(SQLSelectOrderByItem *x);

		bool  visit(SQLExprTableSource *x);

		bool  visit(SQLSelectStatement stmt);

		bool  visit(SQLVariantRefExpr *x);

		void printParameter(Object * param);

		bool  visit(SQLDropTableStatement *x);

	protected:
		void printCascade();

	public:
		bool  visit(SQLDropViewStatement *x);

		bool  visit(SQLTableElement *x);

		bool  visit(SQLColumnDefinition *x);

	protected:
		void visitColumnDefault(SQLColumnDefinition *x);

	public:
		bool  visit(SQLDeleteStatement *x);

		bool  visit(SQLCurrentOfCursorExpr *x);

		bool  visit(SQLInsertStatement *x);

		bool  visit(SQLUpdateSetItem *x);

		bool  visit(SQLUpdateStatement *x);

		bool  visit(SQLCreateTableStatement *x);

		bool  visit(SQLUniqueConstraint *x);

		bool  visit(NotNullConstraint *x);

		bool  visit(SQLUnionQuery *x);

		bool  visit(SQLUnaryExpr *x);

		bool  visit(SQLHexExpr *x);

		bool  visit(SQLSetStatement *x);

		bool  visit(SQLAssignItem *x);

		bool  visit(SQLCallStatement *x);

		bool  visit(SQLJoinTableSource *x);

		bool  visit(ValuesClause *x);

		bool  visit(SQLSomeExpr *x);

		bool  visit(SQLAnyExpr *x);

		bool  visit(SQLAllExpr *x);

		bool  visit(SQLInSubQueryExpr *x);

		bool  visit(SQLListExpr *x);

		bool  visit(SQLSubqueryTableSource *x);

		bool  visit(SQLTruncateStatement *x);

		bool  visit(SQLDefaultExpr *x);

		void endVisit(SQLCommentStatement *x);

		bool  visit(SQLCommentStatement *x);

		bool  visit(SQLUseStatement *x);

		bool  visit(SQLAlterTableAddColumn *x);

		bool  visit(SQLAlterTableDropColumnItem *x);

		void endVisit(SQLAlterTableAddColumn *x);

		bool  visit(SQLDropIndexStatement *x);

		bool  visit(SQLSavePointStatement *x);

		bool  visit(SQLReleaseSavePointStatement *x);

		bool  visit(SQLRollbackStatement *x);

		bool  visit(SQLCommentHint *x);

		bool  visit(SQLCreateDatabaseStatement *x);

		bool  visit(SQLAlterTableDropIndex *x);

		bool  visit(SQLOver *x);

		bool  visit(SQLColumnPrimaryKey *x);

		bool  visit(SQLColumnUniqueKey *x);

		bool  visit(SQLColumnCheck *x);

		bool  visit(SQLWithSubqueryClause *x);

		bool  visit(SQLWithSubqueryClause_Entry *x);

		bool  visit(SQLAlterTableAlterColumn *x);

		bool  visit(SQLCheck *x);

		bool  visit(SQLAlterTableDropForeinKey *x);

		bool  visit(SQLAlterTableDropPrimaryKey *x);

		bool  visit(SQLAlterTableEnableKeys *x);

		bool  visit(SQLAlterTableDisableKeys *x);

		bool  visit(SQLAlterTableDisableConstraint *x);

		bool  visit(SQLAlterTableEnableConstraint *x);

		bool  visit(SQLAlterTableDropConstraint *x);

		bool  visit(SQLAlterTableStatement *x);

		bool  visit(SQLExprHint *x);

		bool  visit(SQLCreateIndexStatement *x);

		bool  visit(SQLUnique *x);

		bool  visit(SQLPrimaryKeyImpl *x);

		bool  visit(SQLAlterTableRenameColumn *x);

		bool  visit(SQLColumnReference *x);

		bool  visit(SQLForeignKeyImpl *x);

		bool  visit(SQLDropSequenceStatement *x);

		void endVisit(SQLDropSequenceStatement *x);

		bool  visit(SQLDropTriggerStatement *x);

		void endVisit(SQLDropUserStatement *x);

		bool  visit(SQLDropUserStatement *x);

		bool  visit(SQLExplainStatement *x);

		bool  visit(SQLGrantStatement *x);

		bool  visit(SQLDropDatabaseStatement *x);

		bool  visit(SQLDropFunctionStatement *x);

		bool  visit(SQLDropTableSpaceStatement *x);

		bool  visit(SQLDropProcedureStatement *x);

		bool  visit(SQLAlterTableAddIndex *x);

		bool  visit(SQLAlterTableAddConstraint *x);

		bool  visit(SQLCreateTriggerStatement *x);
};
#endif

