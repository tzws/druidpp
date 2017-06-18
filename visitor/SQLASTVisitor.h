#ifndef SQLASTVisitor_HEADER_H 
#define SQLASTVisitor_HEADER_H

class SQLCommentHint;
class SQLDataType;
class SQLObject;
class SQLOrderBy;
class SQLOver;
class SQLAggregateExpr;
class SQLAllColumnExpr;
class SQLAllExpr;
class SQLAnyExpr;
class SQLBetweenExpr;
class SQLBinaryOpExpr;
class SQLCaseExpr;
class SQLCaseExpr_Item;
class SQLCastExpr;
class SQLCharExpr;
class SQLCurrentOfCursorExpr;
class SQLDefaultExpr;
class SQLExistsExpr;
class SQLHexExpr;
class SQLIdentifierExpr;
class SQLInListExpr;
class SQLInSubQueryExpr;
class SQLIntegerExpr;
class SQLListExpr;
class SQLMethodInvokeExpr;
class SQLNCharExpr;
class SQLNotExpr;
class SQLNullExpr;
class SQLNumberExpr;
class SQLPropertyExpr;
class SQLQueryExpr;
class SQLSomeExpr;
class SQLUnaryExpr;
class SQLVariantRefExpr;
class NotNullConstraint;
class SQLAlterTableAddColumn;
class SQLAlterTableAddConstraint;
class SQLAlterTableAddIndex;
class SQLAlterTableAlterColumn;
class SQLAlterTableDisableConstraint;
class SQLAlterTableDisableKeys;
class SQLAlterTableDropColumnItem;
class SQLAlterTableDropConstraint;
class SQLAlterTableDropForeinKey;
class SQLAlterTableDropIndex;
class SQLAlterTableDropPrimaryKey;
class SQLAlterTableEnableConstraint;
class SQLAlterTableEnableKeys;
class SQLAlterTableRenameColumn;
class SQLAlterTableStatement;
class SQLAssignItem;
class SQLCallStatement;
class SQLCharactorDataType;
class SQLCheck;
class SQLColumnCheck;
class SQLColumnDefinition;
class SQLColumnPrimaryKey;
class SQLColumnReference;
class SQLColumnUniqueKey;
class SQLCommentStatement;
class SQLCreateDatabaseStatement;
class SQLCreateIndexStatement;
class SQLCreateTableStatement;
class SQLCreateTriggerStatement;
class SQLCreateViewStatement;
class SQLDeleteStatement;
class SQLDropDatabaseStatement;
class SQLDropFunctionStatement;
class SQLDropIndexStatement;
class SQLDropProcedureStatement;
class SQLDropSequenceStatement;
class SQLDropTableSpaceStatement;
class SQLDropTableStatement;
class SQLDropTriggerStatement;
class SQLDropUserStatement;
class SQLDropViewStatement;
class SQLExplainStatement;
class SQLExprHint;
class SQLExprTableSource;
class SQLForeignKeyImpl;
class SQLGrantStatement;
class SQLInsertStatement;
class SQLJoinTableSource;
class SQLPrimaryKeyImpl;
class SQLReleaseSavePointStatement;
class SQLRollbackStatement;
class SQLSavePointStatement;
class SQLSelect;
class SQLSelectGroupByClause;
class SQLSelectItem;
class SQLSelectOrderByItem;
class SQLSelectQueryBlock;
class SQLSelectStatement;
class SQLSetStatement;
class SQLSubqueryTableSource;
class SQLTruncateStatement;
class SQLUnionQuery;
class SQLUnique;
class SQLUpdateSetItem;
class SQLUpdateStatement;
class SQLUseStatement;
class SQLWithSubqueryClause;
class SQLWithSubqueryClause_Entry;
class ValuesClause;

class SQLASTVisitor {

	public:
		virtual ~SQLASTVisitor() {

		}

		virtual void endVisit(SQLAllColumnExpr *x) = 0;

		virtual void endVisit(SQLBetweenExpr *x) = 0;

		virtual void endVisit(SQLBinaryOpExpr *x) = 0;

		virtual void endVisit(SQLCaseExpr *x) = 0;

		virtual void endVisit(SQLCaseExpr_Item *x) = 0;

		virtual void endVisit(SQLCharExpr *x) = 0;

		virtual void endVisit(SQLIdentifierExpr *x) = 0;

		virtual void endVisit(SQLInListExpr *x) = 0;

		virtual void endVisit(SQLIntegerExpr *x) = 0;

		virtual void endVisit(SQLExistsExpr *x) = 0;

		virtual void endVisit(SQLNCharExpr *x) = 0;

		virtual void endVisit(SQLNotExpr *x) = 0;

		virtual void endVisit(SQLNullExpr *x) = 0;

		virtual void endVisit(SQLNumberExpr *x) = 0;

		virtual void endVisit(SQLPropertyExpr *x) = 0;

		virtual void endVisit(SQLSelectGroupByClause *x) = 0;

		virtual void endVisit(SQLSelectItem *x) = 0;

		virtual void endVisit(SQLSelectStatement *selectStatement) = 0;

		virtual void postVisit(SQLObject *astNode) = 0;

		virtual void preVisit(SQLObject *astNode) = 0;

		virtual bool visit(SQLAllColumnExpr *x) = 0;

		virtual bool visit(SQLBetweenExpr *x) = 0;

		virtual bool visit(SQLBinaryOpExpr *x) = 0;

		virtual bool visit(SQLCaseExpr *x) = 0;

		virtual bool visit(SQLCaseExpr_Item *x) = 0;

		virtual bool visit(SQLCastExpr *x) = 0;

		virtual bool visit(SQLCharExpr *x) = 0;

		virtual bool visit(SQLExistsExpr *x) = 0;

		virtual bool visit(SQLIdentifierExpr *x) = 0;

		virtual bool visit(SQLInListExpr *x) = 0;

		virtual bool visit(SQLIntegerExpr *x) = 0;

		virtual bool visit(SQLNCharExpr *x) = 0;

		virtual bool visit(SQLNotExpr *x) = 0;

		virtual bool visit(SQLNullExpr *x) = 0;

		virtual bool visit(SQLNumberExpr *x) = 0;

		virtual bool visit(SQLPropertyExpr *x) = 0;

		virtual bool visit(SQLSelectGroupByClause *x) = 0;

		virtual bool visit(SQLSelectItem *x) = 0;

		virtual void endVisit(SQLCastExpr *x) = 0;

		virtual bool visit(SQLSelectStatement *astNode) = 0;

		virtual void endVisit(SQLAggregateExpr *astNode) = 0;

		virtual bool visit(SQLAggregateExpr *astNode) = 0;

		virtual bool visit(SQLVariantRefExpr *x) = 0;

		virtual void endVisit(SQLVariantRefExpr *x) = 0;

		virtual bool visit(SQLQueryExpr *x) = 0;

		virtual void endVisit(SQLQueryExpr *x) = 0;

		virtual bool visit(SQLUnaryExpr *x) = 0;

		virtual void endVisit(SQLUnaryExpr *x) = 0;

		virtual bool visit(SQLHexExpr *x) = 0;

		virtual void endVisit(SQLHexExpr *x) = 0;

		virtual bool visit(SQLSelect *x) = 0;

		virtual void endVisit(SQLSelect *select) = 0;

		virtual bool visit(SQLSelectQueryBlock *x) = 0;

		virtual void endVisit(SQLSelectQueryBlock *x) = 0;

		virtual bool visit(SQLExprTableSource *x) = 0;

		virtual void endVisit(SQLExprTableSource *x) = 0;

		virtual bool visit(SQLOrderBy *x) = 0;

		virtual void endVisit(SQLOrderBy *x) = 0;

		virtual bool visit(SQLSelectOrderByItem *x) = 0;

		virtual void endVisit(SQLSelectOrderByItem *x) = 0;

		virtual bool visit(SQLDropTableStatement *x) = 0;

		virtual void endVisit(SQLDropTableStatement *x) = 0;

		virtual bool visit(SQLCreateTableStatement *x) = 0;

		virtual void endVisit(SQLCreateTableStatement *x) = 0;

		virtual bool visit(SQLColumnDefinition *x) = 0;

		virtual void endVisit(SQLColumnDefinition *x) = 0;

		virtual bool visit(SQLDataType *x) = 0;

		virtual void endVisit(SQLDataType *x) = 0;

		virtual bool visit(SQLCharactorDataType *x) = 0;

		virtual void endVisit(SQLCharactorDataType *x) = 0;

		virtual bool visit(SQLDeleteStatement *x) = 0;

		virtual void endVisit(SQLDeleteStatement *x) = 0;

		virtual bool visit(SQLCurrentOfCursorExpr *x) = 0;

		virtual void endVisit(SQLCurrentOfCursorExpr *x) = 0;

		virtual bool visit(SQLInsertStatement *x) = 0;

		virtual void endVisit(SQLInsertStatement *x) = 0;

		virtual bool visit(ValuesClause *x) = 0;

		virtual void endVisit(ValuesClause *x) = 0;

		virtual bool visit(SQLUpdateSetItem *x) = 0;

		virtual void endVisit(SQLUpdateSetItem *x) = 0;

		virtual bool visit(SQLUpdateStatement *x) = 0;

		virtual void endVisit(SQLUpdateStatement *x) = 0;

		virtual bool visit(SQLCreateViewStatement *x) = 0;

		virtual void endVisit(SQLCreateViewStatement *x) = 0;

		virtual bool visit(NotNullConstraint *x) = 0;

		virtual void endVisit(NotNullConstraint *x) = 0;

		virtual void endVisit(SQLMethodInvokeExpr *x) = 0;

		virtual bool visit(SQLMethodInvokeExpr *x) = 0;

		virtual void endVisit(SQLUnionQuery *x) = 0;

		virtual bool visit(SQLUnionQuery *x) = 0;

		virtual void endVisit(SQLSetStatement *x) = 0;

		virtual bool visit(SQLSetStatement *x) = 0;

		virtual void endVisit(SQLAssignItem *x) = 0;

		virtual bool visit(SQLAssignItem *x) = 0;

		virtual void endVisit(SQLCallStatement *x) = 0;

		virtual bool visit(SQLCallStatement *x) = 0;

		virtual void endVisit(SQLJoinTableSource *x) = 0;

		virtual bool visit(SQLJoinTableSource *x) = 0;

		virtual void endVisit(SQLSomeExpr *x) = 0;

		virtual bool visit(SQLSomeExpr *x) = 0;

		virtual void endVisit(SQLAnyExpr *x) = 0;

		virtual bool visit(SQLAnyExpr *x) = 0;

		virtual void endVisit(SQLAllExpr *x) = 0;

		virtual bool visit(SQLAllExpr *x) = 0;

		virtual void endVisit(SQLInSubQueryExpr *x) = 0;

		virtual bool visit(SQLInSubQueryExpr *x) = 0;

		virtual void endVisit(SQLListExpr *x) = 0;

		virtual bool visit(SQLListExpr *x) = 0;

		virtual void endVisit(SQLSubqueryTableSource *x) = 0;

		virtual bool visit(SQLSubqueryTableSource *x) = 0;

		virtual void endVisit(SQLTruncateStatement *x) = 0;

		virtual bool visit(SQLTruncateStatement *x) = 0;

		virtual void endVisit(SQLDefaultExpr *x) = 0;

		virtual bool visit(SQLDefaultExpr *x) = 0;

		virtual void endVisit(SQLCommentStatement *x) = 0;

		virtual bool visit(SQLCommentStatement *x) = 0;

		virtual void endVisit(SQLUseStatement *x) = 0;

		virtual bool visit(SQLUseStatement *x) = 0;

		virtual bool visit(SQLAlterTableAddColumn *x) = 0;

		virtual void endVisit(SQLAlterTableAddColumn *x) = 0;

		virtual bool visit(SQLAlterTableDropColumnItem *x) = 0;

		virtual void endVisit(SQLAlterTableDropColumnItem *x) = 0;

		virtual bool visit(SQLAlterTableDropIndex *x) = 0;

		virtual void endVisit(SQLAlterTableDropIndex *x) = 0;

		virtual bool visit(SQLDropIndexStatement *x) = 0;

		virtual void endVisit(SQLDropIndexStatement *x) = 0;

		virtual bool visit(SQLDropViewStatement *x) = 0;

		virtual void endVisit(SQLDropViewStatement *x) = 0;

		virtual bool visit(SQLSavePointStatement *x) = 0;

		virtual void endVisit(SQLSavePointStatement *x) = 0;

		virtual bool visit(SQLRollbackStatement *x) = 0;

		virtual void endVisit(SQLRollbackStatement *x) = 0;

		virtual bool visit(SQLReleaseSavePointStatement *x) = 0;

		virtual void endVisit(SQLReleaseSavePointStatement *x) = 0;

		virtual void endVisit(SQLCommentHint *x) = 0;

		virtual bool visit(SQLCommentHint *x) = 0;

		virtual void endVisit(SQLCreateDatabaseStatement *x) = 0;

		virtual bool visit(SQLCreateDatabaseStatement *x) = 0;

		virtual void endVisit(SQLOver *x) = 0;

		virtual bool visit(SQLOver *x) = 0;

		virtual void endVisit(SQLColumnPrimaryKey *x) = 0;

		virtual bool visit(SQLColumnPrimaryKey *x) = 0;

		virtual bool visit(SQLColumnUniqueKey *x) = 0;

		virtual void endVisit(SQLColumnUniqueKey *x) = 0;

		virtual void endVisit(SQLWithSubqueryClause *x) = 0;

		virtual bool visit(SQLWithSubqueryClause *x) = 0;

		virtual void endVisit(SQLWithSubqueryClause_Entry *x) = 0;

		virtual bool visit(SQLWithSubqueryClause_Entry *x) = 0;

		virtual void endVisit(SQLAlterTableAlterColumn *x) = 0;

		virtual bool visit(SQLAlterTableAlterColumn *x) = 0;

		virtual bool visit(SQLCheck *x) = 0;

		virtual void endVisit(SQLCheck *x) = 0;

		virtual bool visit(SQLAlterTableDropForeinKey *x) = 0;

		virtual void endVisit(SQLAlterTableDropForeinKey *x) = 0;

		virtual bool visit(SQLAlterTableDropPrimaryKey *x) = 0;

		virtual void endVisit(SQLAlterTableDropPrimaryKey *x) = 0;

		virtual bool visit(SQLAlterTableDisableKeys *x) = 0;

		virtual void endVisit(SQLAlterTableDisableKeys *x) = 0;

		virtual bool visit(SQLAlterTableEnableKeys *x) = 0;

		virtual void endVisit(SQLAlterTableEnableKeys *x) = 0;

		virtual bool visit(SQLAlterTableStatement *x) = 0;

		virtual void endVisit(SQLAlterTableStatement *x) = 0;

		virtual bool visit(SQLAlterTableDisableConstraint *x) = 0;

		virtual void endVisit(SQLAlterTableDisableConstraint *x) = 0;

		virtual bool visit(SQLAlterTableEnableConstraint *x) = 0;

		virtual void endVisit(SQLAlterTableEnableConstraint *x) = 0;

		virtual bool visit(SQLColumnCheck *x) = 0;

		virtual void endVisit(SQLColumnCheck *x) = 0;

		virtual bool visit(SQLExprHint *x) = 0;

		virtual void endVisit(SQLExprHint *x) = 0;

		virtual bool visit(SQLAlterTableDropConstraint *x) = 0;

		virtual void endVisit(SQLAlterTableDropConstraint *x) = 0;

		virtual bool visit(SQLUnique *x) = 0;

		virtual void endVisit(SQLUnique *x) = 0;

		virtual bool visit(SQLPrimaryKeyImpl *x) = 0;

		virtual void endVisit(SQLPrimaryKeyImpl *x) = 0;

		virtual bool visit(SQLCreateIndexStatement *x) = 0;

		virtual void endVisit(SQLCreateIndexStatement *x) = 0;

		virtual bool visit(SQLAlterTableRenameColumn *x) = 0;

		virtual void endVisit(SQLAlterTableRenameColumn *x) = 0;

		virtual bool visit(SQLColumnReference *x) = 0;

		virtual void endVisit(SQLColumnReference *x) = 0;

		virtual bool visit(SQLForeignKeyImpl *x) = 0;

		virtual void endVisit(SQLForeignKeyImpl *x) = 0;

		virtual bool visit(SQLDropSequenceStatement *x) = 0;

		virtual void endVisit(SQLDropSequenceStatement *x) = 0;

		virtual bool visit(SQLDropTriggerStatement *x) = 0;

		virtual void endVisit(SQLDropTriggerStatement *x) = 0;

		virtual void endVisit(SQLDropUserStatement *x) = 0;

		virtual bool visit(SQLDropUserStatement *x) = 0;

		virtual void endVisit(SQLExplainStatement *x) = 0;

		virtual bool visit(SQLExplainStatement *x) = 0;

		virtual void endVisit(SQLGrantStatement *x) = 0;

		virtual bool visit(SQLGrantStatement *x) = 0;

		virtual void endVisit(SQLDropDatabaseStatement *x) = 0;

		virtual bool visit(SQLDropDatabaseStatement *x) = 0;

		virtual void endVisit(SQLAlterTableAddIndex *x) = 0;

		virtual bool visit(SQLAlterTableAddIndex *x) = 0;

		virtual void endVisit(SQLAlterTableAddConstraint *x) = 0;

		virtual bool visit(SQLAlterTableAddConstraint *x) = 0;

		virtual void endVisit(SQLCreateTriggerStatement *x) = 0;

		virtual bool visit(SQLCreateTriggerStatement *x) = 0;

		virtual void endVisit(SQLDropFunctionStatement *x) = 0;

		virtual bool visit(SQLDropFunctionStatement *x) = 0;

		virtual void endVisit(SQLDropTableSpaceStatement *x) = 0;

		virtual bool visit(SQLDropTableSpaceStatement *x) = 0;

		virtual void endVisit(SQLDropProcedureStatement *x) = 0;

		virtual bool visit(SQLDropProcedureStatement *x) = 0;
};

#endif

