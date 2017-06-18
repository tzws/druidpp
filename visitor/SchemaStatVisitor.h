#ifndef SchemaStatVisitor_HEADER_H 
#define SchemaStatVisitor_HEADER_H

//import java.util.ArrayList;
//import java.util.std::unordered_map;
//import java.util.LinkedHashMap;
//import java.util.LinkedHashSet;
//import java.util.std::list;
//import java.util.std::unordered_map;
//import java.util.Set;

//import com.alibaba.druid.sql.ast.SQLExpr;
//import com.alibaba.druid.sql.ast.SQLName;
//import com.alibaba.druid.sql.ast.SQLObject;
//import com.alibaba.druid.sql.ast.SQLOrderBy;
//import com.alibaba.druid.sql.ast.SQLOrderingSpecification;
//import com.alibaba.druid.sql.ast.expr.SQLAggregateExpr;
//import com.alibaba.druid.sql.ast.expr.SQLAllColumnExpr;
//import com.alibaba.druid.sql.ast.expr.SQLBinaryOpExpr;
//import com.alibaba.druid.sql.ast.expr.SQLCurrentOfCursorExpr;
//import com.alibaba.druid.sql.ast.expr.SQLIdentifierExpr;
//import com.alibaba.druid.sql.ast.expr.SQLInListExpr;
//import com.alibaba.druid.sql.ast.expr.SQLInSubQueryExpr;
//import com.alibaba.druid.sql.ast.expr.SQLIntegerExpr;
//import com.alibaba.druid.sql.ast.expr.SQLMethodInvokeExpr;
//import com.alibaba.druid.sql.ast.expr.SQLPropertyExpr;
//import com.alibaba.druid.sql.ast.statement.SQLAlterTableAddColumn;
//import com.alibaba.druid.sql.ast.statement.SQLAlterTableAddIndex;
//import com.alibaba.druid.sql.ast.statement.SQLAlterTableDisableConstraint;
//import com.alibaba.druid.sql.ast.statement.SQLAlterTableDropConstraint;
//import com.alibaba.druid.sql.ast.statement.SQLAlterTableDropForeinKey;
//import com.alibaba.druid.sql.ast.statement.SQLAlterTableEnableConstraint;
//import com.alibaba.druid.sql.ast.statement.SQLAlterTableItem;
//import com.alibaba.druid.sql.ast.statement.SQLAlterTableStatement;
//import com.alibaba.druid.sql.ast.statement.SQLCallStatement;
//import com.alibaba.druid.sql.ast.statement.SQLCheck;
//import com.alibaba.druid.sql.ast.statement.SQLColumnDefinition;
//import com.alibaba.druid.sql.ast.statement.SQLCommentStatement;
//import com.alibaba.druid.sql.ast.statement.SQLCreateIndexStatement;
//import com.alibaba.druid.sql.ast.statement.SQLCreateTableStatement;
//import com.alibaba.druid.sql.ast.statement.SQLCreateTriggerStatement;
//import com.alibaba.druid.sql.ast.statement.SQLCreateViewStatement;
//import com.alibaba.druid.sql.ast.statement.SQLDeleteStatement;
//import com.alibaba.druid.sql.ast.statement.SQLDropDatabaseStatement;
//import com.alibaba.druid.sql.ast.statement.SQLDropFunctionStatement;
//import com.alibaba.druid.sql.ast.statement.SQLDropIndexStatement;
//import com.alibaba.druid.sql.ast.statement.SQLDropProcedureStatement;
//import com.alibaba.druid.sql.ast.statement.SQLDropSequenceStatement;
//import com.alibaba.druid.sql.ast.statement.SQLDropTableSpaceStatement;
//import com.alibaba.druid.sql.ast.statement.SQLDropTableStatement;
//import com.alibaba.druid.sql.ast.statement.SQLDropTriggerStatement;
//import com.alibaba.druid.sql.ast.statement.SQLDropUserStatement;
//import com.alibaba.druid.sql.ast.statement.SQLDropViewStatement;
//import com.alibaba.druid.sql.ast.statement.SQLExprTableSource;
//import com.alibaba.druid.sql.ast.statement.SQLForeignKeyImpl;
//import com.alibaba.druid.sql.ast.statement.SQLGrantStatement;
//import com.alibaba.druid.sql.ast.statement.SQLInsertStatement;
//import com.alibaba.druid.sql.ast.statement.SQLJoinTableSource;
//import com.alibaba.druid.sql.ast.statement.SQLRollbackStatement;
//import com.alibaba.druid.sql.ast.statement.SQLSelect;
//import com.alibaba.druid.sql.ast.statement.SQLSelectGroupByClause;
//import com.alibaba.druid.sql.ast.statement.SQLSelectItem;
//import com.alibaba.druid.sql.ast.statement.SQLSelectOrderByItem;
//import com.alibaba.druid.sql.ast.statement.SQLSelectQuery;
//import com.alibaba.druid.sql.ast.statement.SQLSelectQueryBlock;
//import com.alibaba.druid.sql.ast.statement.SQLSelectStatement;
//import com.alibaba.druid.sql.ast.statement.SQLSubqueryTableSource;
//import com.alibaba.druid.sql.ast.statement.SQLTableElement;
//import com.alibaba.druid.sql.ast.statement.SQLTruncateStatement;
//import com.alibaba.druid.sql.ast.statement.SQLUpdateStatement;
//import com.alibaba.druid.sql.ast.statement.SQLUseStatement;
//import com.alibaba.druid.stat.TableStat;
//import com.alibaba.druid.stat.TableStat.Column;
//import com.alibaba.druid.stat.TableStat.Condition;
//import com.alibaba.druid.stat.TableStat.Mode;
//import com.alibaba.druid.stat.TableStat.Relationship;
//import com.alibaba.druid.util.StringUtils;

class SchemaStatVisitor : virtual public SQLASTVisitorAdapter {

	protected:
		std::unordered_map<TableStat.Name, TableStat> tableStats     = new LinkedHashMap<TableStat.Name, TableStat>();
		Set<Column>                        columns        = new LinkedHashSet<Column>();
		std::list<Condition>                    conditions     = new ArrayList<Condition>();
		Set<Relationship>                  relationships  = new LinkedHashSet<Relationship>();
		std::list<Column>                       orderByColumns = new ArrayList<Column>();
		Set<Column>                        groupByColumns = new LinkedHashSet<Column>();

		std::unordered_map<std::string, SQLObject>             subQueryMap    = new LinkedHashMap<std::string, SQLObject>();

		std::unordered_map<std::string, SQLObject>             variants       = new LinkedHashMap<std::string, SQLObject>();

		std::unordered_map<std::string, std::string>                      aliasMap       = new std::unordered_map<std::string, std::string>();

		std::string                                   currentTable;

	public:
		static std::string                         ATTR_TABLE     = "_table_";
		static std::string                         ATTR_COLUMN    = "_column_";

	private:
		std::list<Object>                               parameters;
		Mode                                       mode;

	public:
		SchemaStatVisitor();

		SchemaStatVisitor(std::list<Object> parameters);

		std::list<Object> getParameters();

		void setParameters(std::list<Object> parameters);

		TableStat getTableStat(std::string ident);

		Column addColumn(std::string tableName, std::string columnName);

		TableStat getTableStat(std::string tableName, std::string alias);

	private:
		std::string handleName(std::string ident);

	public:
		std::unordered_map<std::string, SQLObject> getVariants();

		void setAliasMap();

		void clearAliasMap();

		void setAliasMap(std::unordered_map<std::string, std::string> aliasMap);

		std::unordered_map<std::string, std::string> getAliasMap();

		void setCurrentTable(std::string table);

		void setCurrentTable(SQLObject x);

		void restoreCurrentTable(SQLObject x);

		void setCurrentTable(SQLObject x, std::string table);

		std::string getCurrentTable();

	protected:
		Mode getMode();

		void setModeOrigin(SQLObject x);

		Mode setMode(SQLObject x, Mode mode);

	public:
		class OrderByStatVisitor : virtual public SQLASTVisitorAdapter {

			private:
				SQLOrderBy orderBy;

			public:
				OrderByStatVisitor(SQLOrderBy orderBy);

				SQLOrderBy getOrderBy();

				boolean visit(SQLIdentifierExpr x);

				boolean visit(SQLPropertyExpr x);

				void addOrderByColumn(std::string table, std::string columnName, SQLObject expr);
		};

	public:
		boolean visit(SQLOrderBy x);

		Set<Relationship> getRelationships() {
			return relationships;
		}

		std::list<Column> getOrderByColumns() {
			return orderByColumns;
		}

		Set<Column> getGroupByColumns() {
			return groupByColumns;
		}

		std::list<Condition> getConditions() {
			return conditions;
		}

		boolean visit(SQLBinaryOpExpr x);

	protected:
		void handleRelationship(SQLExpr left, std::string operator, SQLExpr right);

		void handleCondition(SQLExpr expr, std::string operator, std::list<SQLExpr> values);

		void handleCondition(SQLExpr expr, std::string operator, SQLExpr... valueExprs);

	public:
		std::string getDbType();

	protected:
		Column getColumn(SQLExpr expr) 

	public:
			boolean visit(SQLTruncateStatement x);

			boolean visit(SQLDropViewStatement x);

			boolean visit(SQLDropTableStatement x);

			boolean visit(SQLInsertStatement x);

	protected:
			void accept(SQLObject x);

			void accept(std::list<? extends SQLObject> nodes);

	public:
			boolean visit(SQLSelectQueryBlock x);

			void endVisit(SQLSelectQueryBlock x);

			boolean visit(SQLJoinTableSource x);

			boolean visit(SQLPropertyExpr x);

	protected:
			std::string aliasWrap(std::string name);

			Column handleSubQueryColumn(std::string owner, std::string alias);

	public:
			boolean visit(SQLIdentifierExpr x);

	private:
			void setColumn(SQLExpr x, Column column);

	protected:
			Column handleUnkownColumn(std::string columnName);

	public:
			boolean visit(SQLAllColumnExpr x);

	public:
			std::unordered_map<TableStat.Name, TableStat> getTables();

			boolean containsTable(std::string tableName);

			Set<Column> getColumns();

			Column getColumn(std::string tableName, std::string columnName);

			boolean visit(SQLSelectStatement x);

			void endVisit(SQLSelectStatement x);

			boolean visit(SQLSubqueryTableSource x);

	protected:
			boolean isSimpleExprTableSource(SQLExprTableSource x);

	public:
			boolean visit(SQLExprTableSource x);

			boolean visit(SQLSelectItem x);

			void endVisit(SQLSelect x);

			boolean visit(SQLSelect x);

			boolean visit(SQLAggregateExpr x);

			boolean visit(SQLMethodInvokeExpr x);

			boolean visit(SQLUpdateStatement x);

			boolean visit(SQLDeleteStatement x);

			boolean visit(SQLInListExpr x);

			boolean visit(SQLInSubQueryExpr x);

			void endVisit(SQLDeleteStatement x);

			void endVisit(SQLUpdateStatement x);

			boolean visit(SQLCreateTableStatement x);

			boolean visit(SQLColumnDefinition x);

			boolean visit(SQLCallStatement x);

			void endVisit(SQLCommentStatement x);

			boolean visit(SQLCommentStatement x);

			boolean visit(SQLCurrentOfCursorExpr x);

			boolean visit(SQLAlterTableAddColumn x);

			void endVisit(SQLAlterTableAddColumn x);

			boolean visit(SQLRollbackStatement x);

			boolean visit(SQLCreateViewStatement x);

			boolean visit(SQLAlterTableDropForeinKey x);

			boolean visit(SQLUseStatement x);

			boolean visit(SQLAlterTableDisableConstraint x);

			boolean visit(SQLAlterTableEnableConstraint x);

			boolean visit(SQLAlterTableStatement x);

			boolean visit(SQLAlterTableDropConstraint x);

			boolean visit(SQLDropIndexStatement x);

			boolean visit(SQLCreateIndexStatement x);

			boolean visit(SQLForeignKeyImpl x);

			boolean visit(SQLDropSequenceStatement x);

			boolean visit(SQLDropTriggerStatement x);

			boolean visit(SQLDropUserStatement x);

			boolean visit(SQLGrantStatement x);

			boolean visit(SQLDropDatabaseStatement x);

			boolean visit(SQLAlterTableAddIndex x);

			boolean visit(SQLCheck x);

			boolean visit(SQLCreateTriggerStatement x);

			boolean visit(SQLDropFunctionStatement x);

			boolean visit(SQLDropTableSpaceStatement x);

			boolean visit(SQLDropProcedureStatement x);
};
#endif

