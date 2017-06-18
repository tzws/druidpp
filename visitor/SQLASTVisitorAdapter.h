#ifndef SQLASTVisitorAdapter_HEADER_H 
#define SQLASTVisitorAdapter_HEADER_H

#include "../ast/SQLCommentHint.h"
#include "../ast/SQLDataType.h"
#include "../ast/SQLExpr.h"
#include "../ast/SQLObject.h"
#include "../ast/SQLOrderBy.h"
#include "../ast/SQLOver.h"
#include "../ast/expr/SQLAggregateExpr.h"
#include "../ast/expr/SQLAllColumnExpr.h"
#include "../ast/expr/SQLAllExpr.h"
#include "../ast/expr/SQLAnyExpr.h"
#include "../ast/expr/SQLBetweenExpr.h"
#include "../ast/expr/SQLBinaryOpExpr.h"
#include "../ast/expr/SQLCaseExpr.h"
#include "../ast/expr/SQLCaseExpr_Item.h"
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
#include "../ast/statement/SQLAlterTableRenameColumn.h"
#include "../ast/statement/SQLAlterTableStatement.h"
#include "../ast/statement/SQLAssignItem.h"
#include "../ast/statement/SQLCallStatement.h"
#include "../ast/statement/SQLCharactorDataType.h"
#include "../ast/statement/SQLCheck.h"
#include "../ast/statement/SQLColumnCheck.h"
#include "../ast/statement/SQLColumnDefinition.h"
#include "../ast/statement/SQLColumnPrimaryKey.h"
#include "../ast/statement/SQLColumnReference.h"
#include "../ast/statement/SQLColumnUniqueKey.h"
#include "../ast/statement/SQLCommentStatement.h"
#include "../ast/statement/SQLCreateDatabaseStatement.h"
#include "../ast/statement/SQLCreateIndexStatement.h"
#include "../ast/statement/SQLCreateTableStatement.h"
#include "../ast/statement/SQLCreateTriggerStatement.h"
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
#include "../ast/statement/SQLExprHint.h"
#include "../ast/statement/SQLExprTableSource.h"
#include "../ast/statement/SQLForeignKeyImpl.h"
#include "../ast/statement/SQLGrantStatement.h"
#include "../ast/statement/SQLInsertStatement.h"
#include "../ast/statement/SQLValuesClause.h"
#include "../ast/statement/SQLJoinTableSource.h"
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
#include "../ast/statement/SQLTruncateStatement.h"
#include "../ast/statement/SQLUnionQuery.h"
#include "../ast/statement/SQLUnique.h"
#include "../ast/statement/SQLUpdateSetItem.h"
#include "../ast/statement/SQLUpdateStatement.h"
#include "../ast/statement/SQLUseStatement.h"
#include "../ast/statement/SQLWithSubqueryClause.h"
#include "../ast/statement/SQLWithSubqueryClause_Entry.h"

class SQLASTVisitorAdapter : virtual public SQLASTVisitor {

	public:

		virtual ~SQLASTVisitorAdapter();
		void endVisit(SQLAllColumnExpr *x);

		void endVisit(SQLBetweenExpr *x);

		void endVisit(SQLBinaryOpExpr *x);

		void endVisit(SQLCaseExpr *x);

		void endVisit(SQLCaseExpr_Item *x);

		void endVisit(SQLCharExpr *x);

		void endVisit(SQLIdentifierExpr *x);

		void endVisit(SQLInListExpr *x);

		void endVisit(SQLIntegerExpr *x);

		void endVisit(SQLExistsExpr *x);

		void endVisit(SQLNCharExpr *x);

		void endVisit(SQLNotExpr *x);

		void endVisit(SQLNullExpr *x);

		void endVisit(SQLNumberExpr *x);

		void endVisit(SQLPropertyExpr *x);

		void endVisit(SQLSelectGroupByClause *x);

		void endVisit(SQLSelectItem *x);

		void endVisit(SQLSelectStatement *selectStatement);

		void postVisit(SQLObject *astNode);

		void preVisit(SQLObject *astNode);

		bool visit(SQLAllColumnExpr *x);

		bool visit(SQLBetweenExpr *x);

		bool visit(SQLBinaryOpExpr *x);

		bool visit(SQLCaseExpr *x);

		bool visit(SQLCaseExpr_Item *x);

		bool visit(SQLCastExpr *x);

		bool visit(SQLCharExpr *x);

		bool visit(SQLExistsExpr *x);

		bool visit(SQLIdentifierExpr *x);

		bool visit(SQLInListExpr *x);

		bool visit(SQLIntegerExpr *x);

		bool visit(SQLNCharExpr *x);

		bool visit(SQLNotExpr *x);

		bool visit(SQLNullExpr *x);

		bool visit(SQLNumberExpr *x);

		bool visit(SQLPropertyExpr *x);

		bool visit(SQLSelectGroupByClause *x);

		bool visit(SQLSelectItem *x);

		void endVisit(SQLCastExpr *x);

		bool visit(SQLSelectStatement *astNode);

		void endVisit(SQLAggregateExpr *x);

		bool visit(SQLAggregateExpr *x);

		bool visit(SQLVariantRefExpr *x);

		void endVisit(SQLVariantRefExpr *x);

		bool visit(SQLQueryExpr *x);

		void endVisit(SQLQueryExpr *x);

		bool visit(SQLSelect *x);

		void endVisit(SQLSelect *select);

		bool visit(SQLSelectQueryBlock *x);

		void endVisit(SQLSelectQueryBlock *x);

		bool visit(SQLExprTableSource *x);

		void endVisit(SQLExprTableSource *x);

		bool visit(SQLOrderBy *x);

		void endVisit(SQLOrderBy *x);

		bool visit(SQLSelectOrderByItem *x);

		void endVisit(SQLSelectOrderByItem *x);

		bool visit(SQLDropTableStatement *x);

		void endVisit(SQLDropTableStatement *x);

		bool visit(SQLCreateTableStatement *x);

		void endVisit(SQLCreateTableStatement *x);

		bool visit(SQLColumnDefinition *x);

		void endVisit(SQLColumnDefinition *x);

		bool visit(SQLDataType *x);

		void endVisit(SQLDataType *x);

		bool visit(SQLDeleteStatement *x);

		void endVisit(SQLDeleteStatement *x);

		bool visit(SQLCurrentOfCursorExpr *x);

		void endVisit(SQLCurrentOfCursorExpr *x);

		bool visit(SQLInsertStatement *x);

		void endVisit(SQLInsertStatement *x);

		bool visit(SQLUpdateSetItem *x);

		void endVisit(SQLUpdateSetItem *x);

		bool visit(SQLUpdateStatement *x);

		void endVisit(SQLUpdateStatement *x);

		bool visit(SQLCreateViewStatement *x);

		void endVisit(SQLCreateViewStatement *x);

		bool visit(NotNullConstraint *x);

		void endVisit(NotNullConstraint *x);

		void endVisit(SQLMethodInvokeExpr *x);

		bool visit(SQLMethodInvokeExpr *x);

		void endVisit(SQLUnionQuery *x);

		bool visit(SQLUnionQuery *x);

		bool visit(SQLUnaryExpr *x);

		void endVisit(SQLUnaryExpr *x);

		bool visit(SQLHexExpr *x);

		void endVisit(SQLHexExpr *x);

		void endVisit(SQLSetStatement *x);

		bool visit(SQLSetStatement *x);

		void endVisit(SQLAssignItem *x);

		bool visit(SQLAssignItem *x);

		void endVisit(SQLCallStatement *x);

		bool visit(SQLCallStatement *x);

		void endVisit(SQLJoinTableSource *x);

		bool visit(SQLJoinTableSource *x);

		bool visit(ValuesClause *x);

		void endVisit(ValuesClause *x);

		void endVisit(SQLSomeExpr *x);

		bool visit(SQLSomeExpr *x);

		void endVisit(SQLAnyExpr *x);

		bool visit(SQLAnyExpr *x);

		void endVisit(SQLAllExpr *x);

		bool visit(SQLAllExpr *x);

		void endVisit(SQLInSubQueryExpr *x);

		bool visit(SQLInSubQueryExpr *x);

		void endVisit(SQLListExpr *x);

		bool visit(SQLListExpr *x);

		void endVisit(SQLSubqueryTableSource *x);

		bool visit(SQLSubqueryTableSource *x);

		void endVisit(SQLTruncateStatement *x);

		bool visit(SQLTruncateStatement *x);

		void endVisit(SQLDefaultExpr *x);

		bool visit(SQLDefaultExpr *x);

		void endVisit(SQLCommentStatement *x);

		bool visit(SQLCommentStatement *x);

		void endVisit(SQLUseStatement *x);

		bool visit(SQLUseStatement *x);

		bool visit(SQLAlterTableAddColumn *x);

		void endVisit(SQLAlterTableAddColumn *x);

		bool visit(SQLAlterTableDropColumnItem *x);

		void endVisit(SQLAlterTableDropColumnItem *x);

		bool visit(SQLDropIndexStatement *x);

		void endVisit(SQLDropIndexStatement *x);

		bool visit(SQLDropViewStatement *x);

		void endVisit(SQLDropViewStatement *x);

		bool visit(SQLSavePointStatement *x);

		void endVisit(SQLSavePointStatement *x);

		bool visit(SQLRollbackStatement *x);

		void endVisit(SQLRollbackStatement *x);

		bool visit(SQLReleaseSavePointStatement *x);

		void endVisit(SQLReleaseSavePointStatement *x);

		bool visit(SQLCommentHint *x);

		void endVisit(SQLCommentHint *x);

		void endVisit(SQLCreateDatabaseStatement *x);

		bool visit(SQLCreateDatabaseStatement *x);

		bool visit(SQLAlterTableDropIndex *x);

		void endVisit(SQLAlterTableDropIndex *x);

		void endVisit(SQLOver *x);

		bool visit(SQLOver *x);

		void endVisit(SQLColumnPrimaryKey *x);

		bool visit(SQLColumnPrimaryKey *x);

		void endVisit(SQLColumnUniqueKey *x);

		bool visit(SQLColumnUniqueKey *x);

		void endVisit(SQLWithSubqueryClause *x);

		bool visit(SQLWithSubqueryClause *x);

		void endVisit(SQLWithSubqueryClause_Entry *x);

		bool visit(SQLWithSubqueryClause_Entry *x);

		bool visit(SQLCharactorDataType *x);

		void endVisit(SQLCharactorDataType *x);

		void endVisit(SQLAlterTableAlterColumn *x);

		bool visit(SQLAlterTableAlterColumn *x);

		bool visit(SQLCheck *x);

		void endVisit(SQLCheck *x);

		bool visit(SQLAlterTableDropForeinKey *x);

		void endVisit(SQLAlterTableDropForeinKey *x);

		bool visit(SQLAlterTableDropPrimaryKey *x);

		void endVisit(SQLAlterTableDropPrimaryKey *x);

		bool visit(SQLAlterTableDisableKeys *x);

		void endVisit(SQLAlterTableDisableKeys *x);

		bool visit(SQLAlterTableEnableKeys *x);

		void endVisit(SQLAlterTableEnableKeys *x);

		bool visit(SQLAlterTableStatement *x);

		void endVisit(SQLAlterTableStatement *x);

		bool visit(SQLAlterTableDisableConstraint *x);

		void endVisit(SQLAlterTableDisableConstraint *x);

		bool visit(SQLAlterTableEnableConstraint *x);

		void endVisit(SQLAlterTableEnableConstraint *x);

		bool visit(SQLColumnCheck *x);

		void endVisit(SQLColumnCheck *x);

		bool visit(SQLExprHint *x);

		void endVisit(SQLExprHint *x);

		bool visit(SQLAlterTableDropConstraint *x);

		void endVisit(SQLAlterTableDropConstraint *x);

		bool visit(SQLUnique *x);

		void endVisit(SQLUnique *x);

		bool visit(SQLCreateIndexStatement *x);

		void endVisit(SQLCreateIndexStatement *x);

		bool visit(SQLPrimaryKeyImpl *x);

		void endVisit(SQLPrimaryKeyImpl *x);

		bool visit(SQLAlterTableRenameColumn *x);

		void endVisit(SQLAlterTableRenameColumn *x);

		bool visit(SQLColumnReference *x);

		void endVisit(SQLColumnReference *x);

		bool visit(SQLForeignKeyImpl *x);

		void endVisit(SQLForeignKeyImpl *x);

		bool visit(SQLDropSequenceStatement *x);

		void endVisit(SQLDropSequenceStatement *x);

		bool visit(SQLDropTriggerStatement *x);

		void endVisit(SQLDropTriggerStatement *x);

		void endVisit(SQLDropUserStatement *x);

		bool visit(SQLDropUserStatement *x);

		void endVisit(SQLExplainStatement *x);

		bool visit(SQLExplainStatement *x);

		void endVisit(SQLGrantStatement *x);

		bool visit(SQLGrantStatement *x);

		void endVisit(SQLDropDatabaseStatement *x);

		bool visit(SQLDropDatabaseStatement *x);

		void endVisit(SQLAlterTableAddIndex *x);

		bool visit(SQLAlterTableAddIndex *x);

		void endVisit(SQLAlterTableAddConstraint *x);

		bool visit(SQLAlterTableAddConstraint *x);

		void endVisit(SQLCreateTriggerStatement *x);

		bool visit(SQLCreateTriggerStatement *x);

		void endVisit(SQLDropFunctionStatement *x);

		bool visit(SQLDropFunctionStatement *x);

		void endVisit(SQLDropTableSpaceStatement *x);

		bool visit(SQLDropTableSpaceStatement *x);

		void endVisit(SQLDropProcedureStatement *x);

		bool visit(SQLDropProcedureStatement *x);
};
#endif

