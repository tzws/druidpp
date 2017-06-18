
#include "SQLASTVisitorAdapter.h"
SQLASTVisitorAdapter::~SQLASTVisitorAdapter () {
	
}

void SQLASTVisitorAdapter::endVisit(SQLAllColumnExpr *x) {
}

void SQLASTVisitorAdapter::endVisit(SQLBetweenExpr *x) {
}

void SQLASTVisitorAdapter::endVisit(SQLBinaryOpExpr *x) {
}

void SQLASTVisitorAdapter::endVisit(SQLCaseExpr *x) {
}

void SQLASTVisitorAdapter::endVisit(SQLCaseExpr_Item *x) {
}

void SQLASTVisitorAdapter::endVisit(SQLCharExpr *x) {
}

void SQLASTVisitorAdapter::endVisit(SQLIdentifierExpr *x) {
}

void SQLASTVisitorAdapter::endVisit(SQLInListExpr *x) {
}

void SQLASTVisitorAdapter::endVisit(SQLIntegerExpr *x) {
}

void SQLASTVisitorAdapter::endVisit(SQLExistsExpr *x) {
}

void SQLASTVisitorAdapter::endVisit(SQLNCharExpr *x) {
}

void SQLASTVisitorAdapter::endVisit(SQLNotExpr *x) {
}

void SQLASTVisitorAdapter::endVisit(SQLNullExpr *x) {
}

void SQLASTVisitorAdapter::endVisit(SQLNumberExpr *x) {
}

void SQLASTVisitorAdapter::endVisit(SQLPropertyExpr *x) {
}

void SQLASTVisitorAdapter::endVisit(SQLSelectGroupByClause *x) {
}

void SQLASTVisitorAdapter::endVisit(SQLSelectItem *x) {
}

void SQLASTVisitorAdapter::endVisit(SQLSelectStatement *selectStatement) {
}

void SQLASTVisitorAdapter::postVisit(SQLObject *astNode) {
}

void SQLASTVisitorAdapter::preVisit(SQLObject *astNode) {
}

bool SQLASTVisitorAdapter::visit(SQLAllColumnExpr *x) {
	return true;
}

bool SQLASTVisitorAdapter::visit(SQLBetweenExpr *x) {
	return true;
}

bool SQLASTVisitorAdapter::visit(SQLBinaryOpExpr *x) {
	return true;
}

bool SQLASTVisitorAdapter::visit(SQLCaseExpr *x) {
	return true;
}

bool SQLASTVisitorAdapter::visit(SQLCaseExpr_Item *x) {
	return true;
}

bool SQLASTVisitorAdapter::visit(SQLCastExpr *x) {
	return true;
}

bool SQLASTVisitorAdapter::visit(SQLCharExpr *x) {
	return true;
}

bool SQLASTVisitorAdapter::visit(SQLExistsExpr *x) {
	return true;
}

bool SQLASTVisitorAdapter::visit(SQLIdentifierExpr *x) {
	return true;
}

bool SQLASTVisitorAdapter::visit(SQLInListExpr *x) {
	return true;
}

bool SQLASTVisitorAdapter::visit(SQLIntegerExpr *x) {
	return true;
}

bool SQLASTVisitorAdapter::visit(SQLNCharExpr *x) {
	return true;
}

bool SQLASTVisitorAdapter::visit(SQLNotExpr *x) {
	return true;
}

bool SQLASTVisitorAdapter::visit(SQLNullExpr *x) {
	return true;
}

bool SQLASTVisitorAdapter::visit(SQLNumberExpr *x) {
	return true;
}

bool SQLASTVisitorAdapter::visit(SQLPropertyExpr *x) {
	return true;
}

bool SQLASTVisitorAdapter::visit(SQLSelectGroupByClause *x) {
	return true;
}

bool SQLASTVisitorAdapter::visit(SQLSelectItem *x) {
	return true;
}

void SQLASTVisitorAdapter::endVisit(SQLCastExpr *x) {
}

bool SQLASTVisitorAdapter::visit(SQLSelectStatement *astNode) {
	return true;
}

void SQLASTVisitorAdapter::endVisit(SQLAggregateExpr *x) {
}

bool SQLASTVisitorAdapter::visit(SQLAggregateExpr *x) {
	return true;
}

bool SQLASTVisitorAdapter::visit(SQLVariantRefExpr *x) {
	return true;
}

void SQLASTVisitorAdapter::endVisit(SQLVariantRefExpr *x) {
}

bool SQLASTVisitorAdapter::visit(SQLQueryExpr *x) {
	return true;
}

void SQLASTVisitorAdapter::endVisit(SQLQueryExpr *x) {
}

bool SQLASTVisitorAdapter::visit(SQLSelect *x) {
	return true;
}

void SQLASTVisitorAdapter::endVisit(SQLSelect *select) {
}

bool SQLASTVisitorAdapter::visit(SQLSelectQueryBlock *x) {
	return true;
}

void SQLASTVisitorAdapter::endVisit(SQLSelectQueryBlock *x) {
}

bool SQLASTVisitorAdapter::visit(SQLExprTableSource *x) {
	return true;
}

void SQLASTVisitorAdapter::endVisit(SQLExprTableSource *x) {
}

bool SQLASTVisitorAdapter::visit(SQLOrderBy *x) {
	return true;
}

void SQLASTVisitorAdapter::endVisit(SQLOrderBy *x) {
}

bool SQLASTVisitorAdapter::visit(SQLSelectOrderByItem *x) {
	return true;
}

void SQLASTVisitorAdapter::endVisit(SQLSelectOrderByItem *x) {
}

bool SQLASTVisitorAdapter::visit(SQLDropTableStatement *x) {
	return true;
}

void SQLASTVisitorAdapter::endVisit(SQLDropTableStatement *x) {
}

bool SQLASTVisitorAdapter::visit(SQLCreateTableStatement *x) {
	return true;
}

void SQLASTVisitorAdapter::endVisit(SQLCreateTableStatement *x) {
}

bool SQLASTVisitorAdapter::visit(SQLColumnDefinition *x) {
	return true;
}

void SQLASTVisitorAdapter::endVisit(SQLColumnDefinition *x) {
}

bool SQLASTVisitorAdapter::visit(SQLDataType *x) {
	return true;
}

void SQLASTVisitorAdapter::endVisit(SQLDataType *x) {
}

bool SQLASTVisitorAdapter::visit(SQLDeleteStatement *x) {
	return true;
}

void SQLASTVisitorAdapter::endVisit(SQLDeleteStatement *x) {
}

bool SQLASTVisitorAdapter::visit(SQLCurrentOfCursorExpr *x) {
	return true;
}

void SQLASTVisitorAdapter::endVisit(SQLCurrentOfCursorExpr *x) {
}

bool SQLASTVisitorAdapter::visit(SQLInsertStatement *x) {
	return true;
}

void SQLASTVisitorAdapter::endVisit(SQLInsertStatement *x) {
}

bool SQLASTVisitorAdapter::visit(SQLUpdateSetItem *x) {
	return true;
}

void SQLASTVisitorAdapter::endVisit(SQLUpdateSetItem *x) {
}

bool SQLASTVisitorAdapter::visit(SQLUpdateStatement *x) {
	return true;
}

void SQLASTVisitorAdapter::endVisit(SQLUpdateStatement *x) {
}

bool SQLASTVisitorAdapter::visit(SQLCreateViewStatement *x) {
	return true;
}

void SQLASTVisitorAdapter::endVisit(SQLCreateViewStatement *x) {
}

bool SQLASTVisitorAdapter::visit(NotNullConstraint *x) {
	return true;
}

void SQLASTVisitorAdapter::endVisit(NotNullConstraint *x) {
}

void SQLASTVisitorAdapter::endVisit(SQLMethodInvokeExpr *x) {

}

bool SQLASTVisitorAdapter::visit(SQLMethodInvokeExpr *x) {
	return true;
}

void SQLASTVisitorAdapter::endVisit(SQLUnionQuery *x) {

}

bool SQLASTVisitorAdapter::visit(SQLUnionQuery *x) {
	return true;
}

bool SQLASTVisitorAdapter::visit(SQLUnaryExpr *x) {
	return true;
}

void SQLASTVisitorAdapter::endVisit(SQLUnaryExpr *x) {

}

bool SQLASTVisitorAdapter::visit(SQLHexExpr *x) {
	return false;
}

void SQLASTVisitorAdapter::endVisit(SQLHexExpr *x) {

}

void SQLASTVisitorAdapter::endVisit(SQLSetStatement *x) {

}

bool SQLASTVisitorAdapter::visit(SQLSetStatement *x) {
	return true;
}

void SQLASTVisitorAdapter::endVisit(SQLAssignItem *x) {

}

bool SQLASTVisitorAdapter::visit(SQLAssignItem *x) {
	return true;
}

void SQLASTVisitorAdapter::endVisit(SQLCallStatement *x) {

}

bool SQLASTVisitorAdapter::visit(SQLCallStatement *x) {
	return true;
}

void SQLASTVisitorAdapter::endVisit(SQLJoinTableSource *x) {

}

bool SQLASTVisitorAdapter::visit(SQLJoinTableSource *x) {
	return true;
}

bool SQLASTVisitorAdapter::visit(ValuesClause *x) {
	return true;
}

void SQLASTVisitorAdapter::endVisit(ValuesClause *x) {

}

void SQLASTVisitorAdapter::endVisit(SQLSomeExpr *x) {

}

bool SQLASTVisitorAdapter::visit(SQLSomeExpr *x) {
	return true;
}

void SQLASTVisitorAdapter::endVisit(SQLAnyExpr *x) {

}

bool SQLASTVisitorAdapter::visit(SQLAnyExpr *x) {
	return true;
}

void SQLASTVisitorAdapter::endVisit(SQLAllExpr *x) {

}

bool SQLASTVisitorAdapter::visit(SQLAllExpr *x) {
	return true;
}

void SQLASTVisitorAdapter::endVisit(SQLInSubQueryExpr *x) {

}

bool SQLASTVisitorAdapter::visit(SQLInSubQueryExpr *x) {
	return true;
}

void SQLASTVisitorAdapter::endVisit(SQLListExpr *x) {

}

bool SQLASTVisitorAdapter::visit(SQLListExpr *x) {
	return true;
}

void SQLASTVisitorAdapter::endVisit(SQLSubqueryTableSource *x) {

}

bool SQLASTVisitorAdapter::visit(SQLSubqueryTableSource *x) {
	return true;
}

void SQLASTVisitorAdapter::endVisit(SQLTruncateStatement *x) {

}

bool SQLASTVisitorAdapter::visit(SQLTruncateStatement *x) {
	return true;
}

void SQLASTVisitorAdapter::endVisit(SQLDefaultExpr *x) {

}

bool SQLASTVisitorAdapter::visit(SQLDefaultExpr *x) {
	return true;
}

void SQLASTVisitorAdapter::endVisit(SQLCommentStatement *x) {

}

bool SQLASTVisitorAdapter::visit(SQLCommentStatement *x) {
	return true;
}

void SQLASTVisitorAdapter::endVisit(SQLUseStatement *x) {

}

bool SQLASTVisitorAdapter::visit(SQLUseStatement *x) {
	return true;
}

bool SQLASTVisitorAdapter::visit(SQLAlterTableAddColumn *x) {
	return true;
}

void SQLASTVisitorAdapter::endVisit(SQLAlterTableAddColumn *x) {

}

bool SQLASTVisitorAdapter::visit(SQLAlterTableDropColumnItem *x) {
	return true;
}

void SQLASTVisitorAdapter::endVisit(SQLAlterTableDropColumnItem *x) {

}

bool SQLASTVisitorAdapter::visit(SQLDropIndexStatement *x) {
	return true;
}

void SQLASTVisitorAdapter::endVisit(SQLDropIndexStatement *x) {

}

bool SQLASTVisitorAdapter::visit(SQLDropViewStatement *x) {
	return true;
}

void SQLASTVisitorAdapter::endVisit(SQLDropViewStatement *x) {

}

bool SQLASTVisitorAdapter::visit(SQLSavePointStatement *x) {
	return true;
}

void SQLASTVisitorAdapter::endVisit(SQLSavePointStatement *x) {

}

bool SQLASTVisitorAdapter::visit(SQLRollbackStatement *x) {
	return true;
}

void SQLASTVisitorAdapter::endVisit(SQLRollbackStatement *x) {

}

bool SQLASTVisitorAdapter::visit(SQLReleaseSavePointStatement *x) {
	return true;
}

void SQLASTVisitorAdapter::endVisit(SQLReleaseSavePointStatement *x) {
}

bool SQLASTVisitorAdapter::visit(SQLCommentHint *x) {
	return true;
}

void SQLASTVisitorAdapter::endVisit(SQLCommentHint *x) {

}

void SQLASTVisitorAdapter::endVisit(SQLCreateDatabaseStatement *x) {

}

bool SQLASTVisitorAdapter::visit(SQLCreateDatabaseStatement *x) {
	return true;
}

bool SQLASTVisitorAdapter::visit(SQLAlterTableDropIndex *x) {
	return true;
}

void SQLASTVisitorAdapter::endVisit(SQLAlterTableDropIndex *x) {

}

void SQLASTVisitorAdapter::endVisit(SQLOver *x) {
}

bool SQLASTVisitorAdapter::visit(SQLOver *x) {
	return true;
}

void SQLASTVisitorAdapter::endVisit(SQLColumnPrimaryKey *x) {

}

bool SQLASTVisitorAdapter::visit(SQLColumnPrimaryKey *x) {
	return true;
}

void SQLASTVisitorAdapter::endVisit(SQLColumnUniqueKey *x) {

}

bool SQLASTVisitorAdapter::visit(SQLColumnUniqueKey *x) {
	return true;
}

void SQLASTVisitorAdapter::endVisit(SQLWithSubqueryClause *x) {
}

bool SQLASTVisitorAdapter::visit(SQLWithSubqueryClause *x) {
	return true;
}

void SQLASTVisitorAdapter::endVisit(SQLWithSubqueryClause_Entry *x) {
}

bool SQLASTVisitorAdapter::visit(SQLWithSubqueryClause_Entry *x) {
	return true;
}

bool SQLASTVisitorAdapter::visit(SQLCharactorDataType *x) {
	return true;
}

void SQLASTVisitorAdapter::endVisit(SQLCharactorDataType *x) {

}

void SQLASTVisitorAdapter::endVisit(SQLAlterTableAlterColumn *x) {

}

bool SQLASTVisitorAdapter::visit(SQLAlterTableAlterColumn *x) {
	return true;
}

bool SQLASTVisitorAdapter::visit(SQLCheck *x) {
	return true;
}

void SQLASTVisitorAdapter::endVisit(SQLCheck *x) {

}

bool SQLASTVisitorAdapter::visit(SQLAlterTableDropForeinKey *x) {
	return true;
}

void SQLASTVisitorAdapter::endVisit(SQLAlterTableDropForeinKey *x) {

}

bool SQLASTVisitorAdapter::visit(SQLAlterTableDropPrimaryKey *x) {
	return true;
}

void SQLASTVisitorAdapter::endVisit(SQLAlterTableDropPrimaryKey *x) {

}

bool SQLASTVisitorAdapter::visit(SQLAlterTableDisableKeys *x) {
	return true;
}

void SQLASTVisitorAdapter::endVisit(SQLAlterTableDisableKeys *x) {

}

bool SQLASTVisitorAdapter::visit(SQLAlterTableEnableKeys *x) {
	return true;
}

void SQLASTVisitorAdapter::endVisit(SQLAlterTableEnableKeys *x) {

}

bool SQLASTVisitorAdapter::visit(SQLAlterTableStatement *x) {
	return true;
}

void SQLASTVisitorAdapter::endVisit(SQLAlterTableStatement *x) {

}

bool SQLASTVisitorAdapter::visit(SQLAlterTableDisableConstraint *x) {
	return true;
}

void SQLASTVisitorAdapter::endVisit(SQLAlterTableDisableConstraint *x) {

}

bool SQLASTVisitorAdapter::visit(SQLAlterTableEnableConstraint *x) {
	return true;
}

void SQLASTVisitorAdapter::endVisit(SQLAlterTableEnableConstraint *x) {

}

bool SQLASTVisitorAdapter::visit(SQLColumnCheck *x) {
	return true;
}

void SQLASTVisitorAdapter::endVisit(SQLColumnCheck *x) {

}

bool SQLASTVisitorAdapter::visit(SQLExprHint *x) {
	return true;
}

void SQLASTVisitorAdapter::endVisit(SQLExprHint *x) {

}

bool SQLASTVisitorAdapter::visit(SQLAlterTableDropConstraint *x) {
	return true;
}

void SQLASTVisitorAdapter::endVisit(SQLAlterTableDropConstraint *x) {

}

bool SQLASTVisitorAdapter::visit(SQLUnique *x) {

	//for (SQLExpr column : x.getColumns()) {
		//column.accept(this);
	//}

	std::list<SQLExpr *> columns =  x->getColumns();
	for(std::list<SQLExpr *>::iterator it = columns.begin(); it != columns.end(); ++it) 
	{
		(*it)->accept(this);
	}

	return false;
}

void SQLASTVisitorAdapter::endVisit(SQLUnique *x) {

}

bool SQLASTVisitorAdapter::visit(SQLCreateIndexStatement *x) {
	return true;
}

void SQLASTVisitorAdapter::endVisit(SQLCreateIndexStatement *x) {

}

bool SQLASTVisitorAdapter::visit(SQLPrimaryKeyImpl *x) {
	return true;
}

void SQLASTVisitorAdapter::endVisit(SQLPrimaryKeyImpl *x) {

}

bool SQLASTVisitorAdapter::visit(SQLAlterTableRenameColumn *x) {
	return true;
}

void SQLASTVisitorAdapter::endVisit(SQLAlterTableRenameColumn *x) {

}

bool SQLASTVisitorAdapter::visit(SQLColumnReference *x) {
	return true;
}

void SQLASTVisitorAdapter::endVisit(SQLColumnReference *x) {

}

bool SQLASTVisitorAdapter::visit(SQLForeignKeyImpl *x) {
	return true;
}

void SQLASTVisitorAdapter::endVisit(SQLForeignKeyImpl *x) {

}

bool SQLASTVisitorAdapter::visit(SQLDropSequenceStatement *x) {
	return true;
}

void SQLASTVisitorAdapter::endVisit(SQLDropSequenceStatement *x) {

}

bool SQLASTVisitorAdapter::visit(SQLDropTriggerStatement *x) {
	return true;
}

void SQLASTVisitorAdapter::endVisit(SQLDropTriggerStatement *x) {

}

void SQLASTVisitorAdapter::endVisit(SQLDropUserStatement *x) {

}

bool SQLASTVisitorAdapter::visit(SQLDropUserStatement *x) {
	return true;
}

void SQLASTVisitorAdapter::endVisit(SQLExplainStatement *x) {

}

bool SQLASTVisitorAdapter::visit(SQLExplainStatement *x) {
	return true;
}

void SQLASTVisitorAdapter::endVisit(SQLGrantStatement *x) {

}

bool SQLASTVisitorAdapter::visit(SQLGrantStatement *x) {
	return true;
}

void SQLASTVisitorAdapter::endVisit(SQLDropDatabaseStatement *x) {

}

bool SQLASTVisitorAdapter::visit(SQLDropDatabaseStatement *x) {
	return true;
}

void SQLASTVisitorAdapter::endVisit(SQLAlterTableAddIndex *x) {

}

bool SQLASTVisitorAdapter::visit(SQLAlterTableAddIndex *x) {
	return true;
}

void SQLASTVisitorAdapter::endVisit(SQLAlterTableAddConstraint *x) {

}

bool SQLASTVisitorAdapter::visit(SQLAlterTableAddConstraint *x) {
	return true;
}

void SQLASTVisitorAdapter::endVisit(SQLCreateTriggerStatement *x) {

}

bool SQLASTVisitorAdapter::visit(SQLCreateTriggerStatement *x) {
	return true;
}

void SQLASTVisitorAdapter::endVisit(SQLDropFunctionStatement *x) {

}

bool SQLASTVisitorAdapter::visit(SQLDropFunctionStatement *x) {
	return true;
}

void SQLASTVisitorAdapter::endVisit(SQLDropTableSpaceStatement *x) {

}

bool SQLASTVisitorAdapter::visit(SQLDropTableSpaceStatement *x) {
	return true;
}

void SQLASTVisitorAdapter::endVisit(SQLDropProcedureStatement *x) {

}

bool SQLASTVisitorAdapter::visit(SQLDropProcedureStatement *x) {
	return true;
}

