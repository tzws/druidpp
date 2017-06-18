#include "SchemaStatVisitor.h"

std::string  SchemaStatVisitor::ATTR_TABLE     = "_table_";
std::string  SchemaStatVisitor::ATTR_COLUMN    = "_column_";

SchemaStatVisitor::SchemaStatVisitor(){
	this(new ArrayList<Object>());
}

SchemaStatVisitor::SchemaStatVisitor(List<Object> parameters){
	this->parameters = parameters;
}

SchemaStatVisitor::List<Object> getParameters() {
	return parameters;
}

void SchemaStatVisitor::setParameters(List<Object> parameters) {
	this->parameters = parameters;
}

TableStat SchemaStatVisitor::getTableStat(std::string ident) {
	return getTableStat(ident, null);
}

Column SchemaStatVisitor::addColumn(std::string tableName, std::string columnName) {
	tableName = handleName(tableName);
	columnName = handleName(columnName);

	Column column = this->getColumn(tableName, columnName);
	if (column == null) {
		column = new Column(tableName, columnName);
		columns.add(column);
	}
	return column;
}

TableStat SchemaStatVisitor::getTableStat(std::string tableName, std::string alias) {
	if (variants.containsKey(tableName)) {
		return null;
	}

	tableName = handleName(tableName);
	TableStat stat = tableStats.get(tableName);
	if (stat == null) {
		stat = new TableStat();
		tableStats.put(new TableStat.Name(tableName), stat);
		if (alias != null) {
			aliasMap.put(alias, tableName);
		}
	}
	return stat;
}

std::string SchemaStatVisitor::handleName(std::string ident) {
	int len = ident.length();
	if (ident.charAt(0) == '[' && ident.charAt(len - 1) == ']') {
		ident = ident.substring(1, len - 1);
	} else {
		bool  flag0 = false;
		bool  flag1 = false;
		bool  flag2 = false;
		bool  flag3 = false;
		for (int i = 0; i < len; ++i) {
			final char ch = ident.charAt(i);
			if (ch == '\"') {
				flag0 = true;
			} else if (ch == '`') {
				flag1 = true;
			} else if (ch == ' ') {
				flag2 = true;
			} else if (ch == '\'') {
				flag3 = true;
			}
		}
		if (flag0) {
			ident = ident.replaceAll("\"", "");
		}

		if (flag1) {
			ident = ident.replaceAll("`", "");
		}

		if (flag2) {
			ident = ident.replaceAll(" ", "");
		}

		if (flag3) {
			ident = ident.replaceAll("'", "");
		}
	}
	ident = aliasWrap(ident);

	return ident;
}

Map<std::string, SQLObject> SchemaStatVisitor::getVariants() {
	return variants;
}

void SchemaStatVisitor::setAliasMap() {
	this->setAliasMap(new HashMap<std::string, std::string>());
}

void SchemaStatVisitor::clearAliasMap() {
	this->aliasMap = null;
}

void SchemaStatVisitor::setAliasMap(Map<std::string, std::string> aliasMap) {
	this->aliasMap = aliasMap;
}

Map<std::string, std::string> SchemaStatVisitor::getAliasMap() {
	return aliasMap;
}

void SchemaStatVisitor::setCurrentTable(std::string table) {
	this->currentTable = table;
}

void SchemaStatVisitor::setCurrentTable(SQLObject x) {
	x.putAttribute("_old_local_", this->currentTable);
}

void SchemaStatVisitor::restoreCurrentTable(SQLObject x) {
	std::string table = (std::string) x.getAttribute("_old_local_");
	this->currentTable = table;
}

void SchemaStatVisitor::setCurrentTable(SQLObject x, std::string table) {
	x.putAttribute("_old_local_", this->currentTable);
	this->currentTable = table;
}

std::string SchemaStatVisitor::getCurrentTable() {
	return currentTable;
}

Mode SchemaStatVisitor::getMode() {
	return mode;
}

void SchemaStatVisitor::setModeOrigin(SQLObject x) {
	Mode originalMode = (Mode) x.getAttribute("_original_use_mode");
	mode = originalMode;
}

Mode SchemaStatVisitor::setMode(SQLObject x, Mode mode) {
	Mode oldMode = this->mode;
	x.putAttribute("_original_use_mode", oldMode);
	this->mode = mode;
	return oldMode;
}



SchemaStatVisitor::OrderByStatVisitor::OrderByStatVisitor(SQLOrderBy orderBy){
	this->orderBy = orderBy;
	for (SQLSelectOrderByItem item : orderBy.getItems()) {
		item.getExpr().setParent(item);
	}
}

SQLOrderBy SchemaStatVisitor::OrderByStatVisitor::getOrderBy() {
	return orderBy;
}

bool  SchemaStatVisitor::OrderByStatVisitor::visit(SQLIdentifierExpr x) {
	if (subQueryMap.containsKey(currentTable)) {
		return false;
	}

	if (currentTable != null) {
		addOrderByColumn(currentTable, x.getName(), x);
	} else {
		addOrderByColumn("UNKOWN", x.getName(), x);
	}
	return false;
}

bool  SchemaStatVisitor::OrderByStatVisitor::visit(SQLPropertyExpr x) {
	if (x.getOwner() instanceof SQLIdentifierExpr) {
		std::string owner = ((SQLIdentifierExpr) x.getOwner()).getName();

		if (subQueryMap.containsKey(owner)) {
			return false;
		}

		owner = aliasWrap(owner);

		if (owner != null) {
			addOrderByColumn(owner, x.getName(), x);
		}
	}

	return false;
}

void SchemaStatVisitor::OrderByStatVisitor::addOrderByColumn(std::string table, std::string columnName, SQLObject expr) {
	Column column = new Column(table, columnName);

		SQLObject parent = expr.getParent();
		if (parent instanceof SQLSelectOrderByItem) {
			SQLOrderingSpecification type = ((SQLSelectOrderByItem) parent).getType();
			column.getAttributes().put("orderBy.type", type);
		}

		orderByColumns.add(column);
	}

bool  SchemaStatVisitor::visit(SQLOrderBy x) {
	OrderByStatVisitor orderByVisitor = new OrderByStatVisitor(x);
	SQLSelectQueryBlock query = null;
	if (x.getParent() instanceof SQLSelectQueryBlock) {
		query = (SQLSelectQueryBlock) x.getParent();
	}
	if (query != null) {
		for (SQLSelectOrderByItem item : x.getItems()) {
			SQLExpr expr = item.getExpr();
			if (expr instanceof SQLIntegerExpr) {
				int intValue = ((SQLIntegerExpr) expr).getNumber().intValue() - 1;
				if (intValue < query.getSelectList().size()) {
					SQLSelectItem selectItem = query.getSelectList().get(intValue);
					selectItem.getExpr().accept(orderByVisitor);
				}
			}
		}
	}
	x.accept(orderByVisitor);
	return true;
}

Set<Relationship> SchemaStatVisitor::getRelationships() {
	return relationships;
}

List<Column> SchemaStatVisitor::getOrderByColumns() {
	return orderByColumns;
}

Set<Column> SchemaStatVisitor::getGroupByColumns() {
	return groupByColumns;
}

List<Condition> SchemaStatVisitor::getConditions() {
	return conditions;
}

bool  SchemaStatVisitor::visit(SQLBinaryOpExpr x) {
	x.getLeft().setParent(x);
	x.getRight().setParent(x);

	switch (x.getOperator()) {
		case Equality:
		case NotEqual:
		case GreaterThan:
		case GreaterThanOrEqual:
		case LessThan:
		case LessThanOrEqual:
		case LessThanOrEqualOrGreaterThan:
		case Like:
		case NotLike:
		case Is:
		case IsNot:
			handleCondition(x.getLeft(), x.getOperator().name, x.getRight());
			handleCondition(x.getRight(), x.getOperator().name, x.getLeft());

			handleRelationship(x.getLeft(), x.getOperator().name, x.getRight());
			break;
		default:
			break;
	}
	return true;
}

void SchemaStatVisitor::handleRelationship(SQLExpr left, std::string operator, SQLExpr right) {
	Column leftColumn = getColumn(left);
	if (leftColumn == null) {
		return;
	}

	Column rightColumn = getColumn(right);
	if (rightColumn == null) {
		return;
	}

	Relationship relationship = new Relationship();
	relationship.setLeft(leftColumn);
	relationship.setRight(rightColumn);
	relationship.setOperator(operator);

	this->relationships.add(relationship);
}

void SchemaStatVisitor::handleCondition(SQLExpr expr, std::string operator, List<SQLExpr> values) {
	handleCondition(expr, operator, values.toArray(new SQLExpr[values.size()]));
}

void SchemaStatVisitor::handleCondition(SQLExpr expr, std::string operator, SQLExpr... valueExprs) {
	Column column = getColumn(expr);
	if (column == null) {
		return;
	}

	Condition condition = null;
	for (Condition item : this->getConditions()) {
		if (item.getColumn().equals(column) && item.getOperator().equals(operator)) {
			condition = item;
			break;
		}
	}

	if (condition == null) {
		condition = new Condition();
		condition.setColumn(column);
		condition.setOperator(operator);
		this->conditions.add(condition);
	}

	for (SQLExpr item : valueExprs) {
		Object value = SQLEvalVisitorUtils.eval(getDbType(), item, parameters, false);
		condition.getValues().add(value);
	}
}

std::string SchemaStatVisitor::getDbType() {
	return null;
}

Column SchemaStatVisitor::getColumn(SQLExpr expr) {
	Map<std::string, std::string> aliasMap = getAliasMap();
	if (aliasMap == null) {
		return null;
	}

	if (expr instanceof SQLPropertyExpr) {
		SQLExpr owner = ((SQLPropertyExpr) expr).getOwner();
		std::string column = ((SQLPropertyExpr) expr).getName();

		if (owner instanceof SQLIdentifierExpr) {
			std::string tableName = ((SQLIdentifierExpr) owner).getName();
			std::string table = tableName;
			if (aliasMap.containsKey(table)) {
				table = aliasMap.get(table);
			}

			if (variants.containsKey(table)) {
				return null;
			}

			if (table != null) {
				return new Column(table, column);
			}

			return handleSubQueryColumn(tableName, column);
		}

		return null;
	}

	if (expr instanceof SQLIdentifierExpr) {
		Column attrColumn = (Column) expr.getAttribute(ATTR_COLUMN);
		if (attrColumn != null) {
			return attrColumn;
		}

		std::string column = ((SQLIdentifierExpr) expr).getName();
		std::string table = getCurrentTable();
		if (table != null && aliasMap.containsKey(table)) {
			table = aliasMap.get(table);
			if (table == null) {
				return null;
			}
		}

		if (table != null) {
			return new Column(table, column);
		}

		if (variants.containsKey(column)) {
			return null;
		}

		return new Column("UNKNOWN", column);
	}

	return null;
}

@Override
bool  SchemaStatVisitor::visit(SQLTruncateStatement x) {
	setMode(x, Mode.Delete);

	setAliasMap();

	std::string originalTable = getCurrentTable();

	for (SQLExprTableSource tableSource : x.getTableSources()) {
		SQLName name = (SQLName) tableSource.getExpr();

		std::string ident = name.toString();
		setCurrentTable(ident);
		x.putAttribute("_old_local_", originalTable);

		TableStat stat = getTableStat(ident);
		stat.incrementDeleteCount();

		Map<std::string, std::string> aliasMap = getAliasMap();
		if (aliasMap != null) {
			aliasMap.put(ident, ident);
		}
	}

	return false;
}

@Override
bool  SchemaStatVisitor::visit(SQLDropViewStatement x) {
	setMode(x, Mode.Drop);
	return true;
}

@Override
bool  SchemaStatVisitor::visit(SQLDropTableStatement x) {
	setMode(x, Mode.Insert);

	setAliasMap();

	std::string originalTable = getCurrentTable();

	for (SQLExprTableSource tableSource : x.getTableSources()) {
		SQLName name = (SQLName) tableSource.getExpr();
		std::string ident = name.toString();
		setCurrentTable(ident);
		x.putAttribute("_old_local_", originalTable);

		TableStat stat = getTableStat(ident);
		stat.incrementDropCount();

		Map<std::string, std::string> aliasMap = getAliasMap();
		if (aliasMap != null) {
			aliasMap.put(ident, ident);
		}
	}

	return false;
}

@Override
bool  SchemaStatVisitor::visit(SQLInsertStatement x) {
	setMode(x, Mode.Insert);

	setAliasMap();

	std::string originalTable = getCurrentTable();

	if (x.getTableName() instanceof SQLName) {
		std::string ident = ((SQLName) x.getTableName()).toString();
		setCurrentTable(ident);
		x.putAttribute("_old_local_", originalTable);

		TableStat stat = getTableStat(ident);
		stat.incrementInsertCount();

		Map<std::string, std::string> aliasMap = getAliasMap();
		if (aliasMap != null) {
			if (x.getAlias() != null) {
				aliasMap.put(x.getAlias(), ident);
			}
			aliasMap.put(ident, ident);
		}
	}

	accept(x.getColumns());
	accept(x.getQuery());

	return false;
}

void SchemaStatVisitor::accept(SQLObject x) {
	if (x != null) {
		x.accept(this);
	}
}

void SchemaStatVisitor::accept(List<? extends SQLObject> nodes) {
	for (int i = 0, size = nodes.size(); i < size; ++i) {
		accept(nodes.get(i));
	}
}

bool  SchemaStatVisitor::visit(SQLSelectQueryBlock x) {
	if (x.getFrom() == null) {
		return false;
	}

	setMode(x, Mode.Select);

	if (x.getFrom() instanceof SQLSubqueryTableSource) {
		x.getFrom().accept(this);
		return false;
	}

	if (x.getInto() != null && x.getInto().getExpr() instanceof SQLName) {
		SQLName into = (SQLName) x.getInto().getExpr();
		std::string ident = into.toString();
		TableStat stat = getTableStat(ident);
		if (stat != null) {
			stat.incrementInsertCount();
		}
	}

	std::string originalTable = getCurrentTable();

	if (x.getFrom() instanceof SQLExprTableSource) {
		SQLExprTableSource tableSource = (SQLExprTableSource) x.getFrom();
		if (tableSource.getExpr() instanceof SQLName) {
			std::string ident = tableSource.getExpr().toString();

			setCurrentTable(x, ident);
			x.putAttribute(ATTR_TABLE, ident);
			if (x.getParent() instanceof SQLSelect) {
				x.getParent().putAttribute(ATTR_TABLE, ident);
			}
			x.putAttribute("_old_local_", originalTable);
		}
	}

	if (x.getFrom() != null) {
		x.getFrom().accept(this); // 提前执行，获得aliasMap
		std::string table = (std::string) x.getFrom().getAttribute(ATTR_TABLE);
		if (table != null) {
			x.putAttribute(ATTR_TABLE, table);
		}
	}

	// std::string ident = x.getTable().toString();
	//
	// TableStat stat = getTableStat(ident);
	// stat.incrementInsertCount();
	// return false;

	if (x.getWhere() != null) {
		x.getWhere().setParent(x);
	}

	return true;
}

void SchemaStatVisitor::endVisit(SQLSelectQueryBlock x) {
	std::string originalTable = (std::string) x.getAttribute("_old_local_");
	x.putAttribute("table", getCurrentTable());
	setCurrentTable(originalTable);

	setModeOrigin(x);
}

bool  SchemaStatVisitor::visit(SQLJoinTableSource x) {
	x.getLeft().accept(this);
	x.getRight().accept(this);
	if (x.getCondition() != null) {
		x.getCondition().accept(this);
	}
	return false;
}

bool  SchemaStatVisitor::visit(SQLPropertyExpr x) {
	if (x.getOwner() instanceof SQLIdentifierExpr) {
		std::string owner = ((SQLIdentifierExpr) x.getOwner()).getName();

		if (subQueryMap.containsKey(owner)) {
			return false;
		}

		owner = aliasWrap(owner);

		if (owner != null) {
			Column column = addColumn(owner, x.getName());
			x.putAttribute(ATTR_COLUMN, column);
			if (column != null) {
				if (column != null) {
					setColumn(x, column);
				}
			}
		}
	}
	return false;
}

std::string SchemaStatVisitor::aliasWrap(std::string name) {
	Map<std::string, std::string> aliasMap = getAliasMap();

	if (aliasMap != null) {
		for (Map.Entry<std::string, std::string> entry : aliasMap.entrySet()) {
			if (entry.getKey() == null) {
				continue;
			}
			if (entry.getKey().equalsIgnoreCase(name)) {
				return entry.getValue();
			}
		}
	}

	return name;
}

Column SchemaStatVisitor::handleSubQueryColumn(std::string owner, std::string alias) {
	SQLObject query = subQueryMap.get(owner);

	if (query == null) {
		return null;
	}

	List<SQLSelectItem> selectList = null;
	if (query instanceof SQLSelectQueryBlock) {
		selectList = ((SQLSelectQueryBlock) query).getSelectList();
	}

	if (selectList != null) {
		for (SQLSelectItem item : selectList) {
			std::string itemAlias = item.getAlias();
			SQLExpr itemExpr = item.getExpr();
			if (itemAlias == null) {
				if (itemExpr instanceof SQLIdentifierExpr) {
					itemAlias = itemExpr.toString();
				} else if (itemExpr instanceof SQLPropertyExpr) {
					itemAlias = ((SQLPropertyExpr) itemExpr).getName();
				}
			}

			if (alias.equalsIgnoreCase(itemAlias)) {
				Column column = (Column) itemExpr.getAttribute(ATTR_COLUMN);
				return column;
			}

		}
	}

	return null;
}

bool  SchemaStatVisitor::visit(SQLIdentifierExpr x) {
	std::string currentTable = getCurrentTable();

	if (subQueryMap.containsKey(currentTable)) {
		return false;
	}

	std::string ident = x.toString();

	if (variants.containsKey(ident)) {
		return false;
	}

	Column column;
	if (currentTable != null) {
		column = addColumn(currentTable, ident);
		x.putAttribute(ATTR_COLUMN, column);
	} else {
		column = handleUnkownColumn(ident);
		if (column != null) {
			x.putAttribute(ATTR_COLUMN, column);
		}
	}
	if (column != null) {
		setColumn(x, column);
	}
	return false;
}

void SchemaStatVisitor::setColumn(SQLExpr x, Column column) {
	SQLObject current = x;
	for (;;) {
		SQLObject parent = current.getParent();

		if (parent == null) {
			break;
		}

		if (parent instanceof SQLSelectQueryBlock) {
			SQLSelectQueryBlock query = (SQLSelectQueryBlock) parent;
			if (query.getWhere() == current) {
				column.setWhere(true);
			}
			break;
		}

		if (parent instanceof SQLSelectGroupByClause) {
			SQLSelectGroupByClause groupBy = (SQLSelectGroupByClause) parent;
			if (current == groupBy.getHaving()) {
				column.setHaving(true);
			} else if (groupBy.getItems().contains(current)) {
				column.setGroupBy(true);
			}
			break;
		}

		if (parent instanceof SQLSelectItem) {
			column.setSelec(true);
			break;
		}

		if (parent instanceof SQLJoinTableSource) {
			SQLJoinTableSource join = (SQLJoinTableSource) parent;
			if (join.getCondition() == current) {
				column.setJoin(true);
			}
			break;
		}

		current = parent;
	}
}

Column SchemaStatVisitor::handleUnkownColumn(std::string columnName) {
	return addColumn("UNKNOWN", columnName);
}

bool  SchemaStatVisitor::visit(SQLAllColumnExpr x) {
	std::string currentTable = getCurrentTable();

	if (subQueryMap.containsKey(currentTable)) {
		return false;
	}

	if (currentTable != null) {
		addColumn(currentTable, "*");
	}
	return false;
}

Map<TableStat.Name, TableStat> SchemaStatVisitor::getTables() {
	return tableStats;
}

bool  SchemaStatVisitor::containsTable(std::string tableName) {
	return tableStats.containsKey(new TableStat.Name(tableName));
}

Set<Column> SchemaStatVisitor::getColumns() {
	return columns;
}

Column SchemaStatVisitor::getColumn(std::string tableName, std::string columnName) {
	for (Column column : this->columns) {
		if (StringUtils.equalsIgnoreCase(tableName, column.getTable())
				&& StringUtils.equalsIgnoreCase(columnName, column.getName())) {
			return column;
		}
	}
	return null;
}

bool  SchemaStatVisitor::visit(SQLSelectStatement x) {
	setAliasMap();
	return true;
}

void SchemaStatVisitor::endVisit(SQLSelectStatement x) {
}

bool  SchemaStatVisitor::visit(SQLSubqueryTableSource x) {
	x.getSelect().accept(this);

	SQLSelectQuery query = x.getSelect().getQuery();

	Map<std::string, std::string> aliasMap = getAliasMap();
	if (aliasMap != null && x.getAlias() != null) {
		aliasMap.put(x.getAlias(), null);
		subQueryMap.put(x.getAlias(), query);
	}
	return false;
}

bool  SchemaStatVisitor::isSimpleExprTableSource(SQLExprTableSource x) {
	return x.getExpr() instanceof SQLName;
}

bool  SchemaStatVisitor::visit(SQLExprTableSource x) {
	if (isSimpleExprTableSource(x)) {
		std::string ident = x.getExpr().toString();

		if (variants.containsKey(ident)) {
			return false;
		}

		if (subQueryMap.containsKey(ident)) {
			return false;
		}

		Map<std::string, std::string> aliasMap = getAliasMap();

		TableStat stat = getTableStat(ident);

		Mode mode = getMode();
		if (mode != null) {
			switch (mode) {
				case Delete:
					stat.incrementDeleteCount();
					break;
				case Insert:
					stat.incrementInsertCount();
					break;
				case Update:
					stat.incrementUpdateCount();
					break;
				case Select:
					stat.incrementSelectCount();
					break;
				case Merge:
					stat.incrementMergeCount();
					break;
				case Drop:
					stat.incrementDropCount();
					break;
				default:
					break;
			}
		}

		if (aliasMap != null) {
			std::string alias = x.getAlias();
			if (alias != null && !aliasMap.containsKey(alias)) {
				aliasMap.put(alias, ident);
			}
			if (!aliasMap.containsKey(ident)) {
				aliasMap.put(ident, ident);
			}
		}
	} else {
		accept(x.getExpr());
	}

	return false;
}

bool  SchemaStatVisitor::visit(SQLSelectItem x) {
	x.getExpr().setParent(x);
	return true;
}

void SchemaStatVisitor::endVisit(SQLSelect x) {
	restoreCurrentTable(x);
}

bool  SchemaStatVisitor::visit(SQLSelect x) {
	setCurrentTable(x);

	if (x.getOrderBy() != null) {
		x.getOrderBy().setParent(x);
	}

	accept(x.getQuery());

	std::string originalTable = getCurrentTable();

	setCurrentTable((std::string) x.getQuery().getAttribute("table"));
	x.putAttribute("_old_local_", originalTable);

	accept(x.getOrderBy());

	setCurrentTable(originalTable);

	return false;
}

bool  SchemaStatVisitor::visit(SQLAggregateExpr x) {
	accept(x.getArguments());
	return false;
}

bool  SchemaStatVisitor::visit(SQLMethodInvokeExpr x) {
	accept(x.getParameters());
	return false;
}

bool  SchemaStatVisitor::visit(SQLUpdateStatement x) {
	setAliasMap();

	setMode(x, Mode.Update);

	SQLName identName = x.getTableName();
	if (identName != null) {
		std::string ident = identName.toString();
		setCurrentTable(ident);

		TableStat stat = getTableStat(ident);
		stat.incrementUpdateCount();

		Map<std::string, std::string> aliasMap = getAliasMap();
		aliasMap.put(ident, ident);
	} else {
		x.getTableSource().accept(this);
	}

	accept(x.getItems());
	accept(x.getWhere());

	return false;
}

bool  SchemaStatVisitor::visit(SQLDeleteStatement x) {
	setAliasMap();

	setMode(x, Mode.Delete);

	std::string tableName = x.getTableName().toString();
	setCurrentTable(tableName);

	if (x.getAlias() != null) {
		this->aliasMap.put(x.getAlias(), tableName);
	}

	TableStat stat = getTableStat(tableName);
	stat.incrementDeleteCount();

	accept(x.getWhere());

	return false;
}

bool  SchemaStatVisitor::visit(SQLInListExpr x) {
	if (x.isNot()) {
		handleCondition(x.getExpr(), "NOT IN", x.getTargetList());
	} else {
		handleCondition(x.getExpr(), "IN", x.getTargetList());
	}

	return true;
}

@Override
bool  SchemaStatVisitor::visit(SQLInSubQueryExpr x) {
	if (x.isNot()) {
		handleCondition(x.getExpr(), "NOT IN");
	} else {
		handleCondition(x.getExpr(), "IN");
	}
	return true;
}

void SchemaStatVisitor::endVisit(SQLDeleteStatement x) {

}

void SchemaStatVisitor::endVisit(SQLUpdateStatement x) {
}

bool  SchemaStatVisitor::visit(SQLCreateTableStatement x) {
	for (SQLTableElement e : x.getTableElementList()) {
		e.setParent(x);
	}

	std::string tableName = x.getName().toString();

	TableStat stat = getTableStat(tableName);
	stat.incrementCreateCount();
	setCurrentTable(x, tableName);

	accept(x.getTableElementList());

	restoreCurrentTable(x);

	return false;
}

bool  SchemaStatVisitor::visit(SQLColumnDefinition x) {
	std::string tableName = null;
	{
		SQLObject parent = x.getParent();
		if (parent instanceof SQLCreateTableStatement) {
			tableName = ((SQLCreateTableStatement) parent).getName().toString();
		}
	}

	if (tableName == null) {
		return true;
	}

	std::string columnName = x.getName().toString();
	addColumn(tableName, columnName);

	return false;
}

@Override
bool  SchemaStatVisitor::visit(SQLCallStatement x) {
	return false;
}

@Override
void SchemaStatVisitor::endVisit(SQLCommentStatement x) {

}

@Override
bool  SchemaStatVisitor::visit(SQLCommentStatement x) {
	return false;
}

bool  SchemaStatVisitor::visit(SQLCurrentOfCursorExpr x) {
	return false;
}

@Override
bool  SchemaStatVisitor::visit(SQLAlterTableAddColumn x) {
	SQLAlterTableStatement stmt = (SQLAlterTableStatement) x.getParent();
	std::string table = stmt.getName().toString();

	for (SQLColumnDefinition column : x.getColumns()) {
		std::string columnName = column.getName().toString();
		addColumn(table, columnName);
	}
	return false;
}

@Override
void SchemaStatVisitor::endVisit(SQLAlterTableAddColumn x) {

}

@Override
bool  SchemaStatVisitor::visit(SQLRollbackStatement x) {
	return false;
}

bool  SchemaStatVisitor::visit(SQLCreateViewStatement x) {
	x.getSubQuery().accept(this);
	return false;
}

@Override
bool  SchemaStatVisitor::visit(SQLAlterTableDropForeinKey x) {
	return false;
}

@Override
bool  SchemaStatVisitor::visit(SQLUseStatement x) {
	return false;
}

@Override
bool  SchemaStatVisitor::visit(SQLAlterTableDisableConstraint x) {
	return false;
}

@Override
bool  SchemaStatVisitor::visit(SQLAlterTableEnableConstraint x) {
	return false;
}

@Override
bool  SchemaStatVisitor::visit(SQLAlterTableStatement x) {
	std::string tableName = x.getName().toString();
	TableStat stat = getTableStat(tableName);
	stat.incrementAlterCount();

	setCurrentTable(x, tableName);

	for (SQLAlterTableItem item : x.getItems()) {
		item.setParent(x);
		item.accept(this);
	}

	return false;
}

@Override
bool  SchemaStatVisitor::visit(SQLAlterTableDropConstraint x) {
	return false;
}

@Override
bool  SchemaStatVisitor::visit(SQLDropIndexStatement x) {
	setMode(x, Mode.DropIndex);
	SQLExprTableSource table = x.getTableName();
	if (table != null) {
		SQLName name = (SQLName) table.getExpr();

		std::string ident = name.toString();
		setCurrentTable(ident);

		TableStat stat = getTableStat(ident);
		stat.incrementDropIndexCount();

		Map<std::string, std::string> aliasMap = getAliasMap();
		if (aliasMap != null) {
			aliasMap.put(ident, ident);
		}
	}
	return false;
}

@Override
bool  SchemaStatVisitor::visit(SQLCreateIndexStatement x) {
	setMode(x, Mode.CreateIndex);

	SQLName name = (SQLName) ((SQLExprTableSource) x.getTable()).getExpr();

	std::string table = name.toString();
	setCurrentTable(table);

	TableStat stat = getTableStat(table);
	stat.incrementDropIndexCount();

	Map<std::string, std::string> aliasMap = getAliasMap();
	if (aliasMap != null) {
		aliasMap.put(table, table);
	}

	for (SQLSelectOrderByItem item : x.getItems()) {
		SQLExpr expr = item.getExpr();
		if (expr instanceof SQLIdentifierExpr) {
			SQLIdentifierExpr identExpr = (SQLIdentifierExpr) expr;
			std::string columnName = identExpr.getName();
			addColumn(table, columnName);
		}
	}

	return false;
}

@Override
bool  SchemaStatVisitor::visit(SQLForeignKeyImpl x) {

	for (SQLName column : x.getReferencedColumns()) {
		column.accept(this);
	}

	std::string table = x.getReferencedTableName().getSimleName();
	setCurrentTable(table);

	TableStat stat = getTableStat(table);
	stat.incrementReferencedCount();
	for (SQLName column : x.getReferencedColumns()) {
		std::string columnName = column.getSimleName();
		addColumn(table, columnName);
	}

	return false;
}

@Override
bool  SchemaStatVisitor::visit(SQLDropSequenceStatement x) {
	return false;
}

@Override
bool  SchemaStatVisitor::visit(SQLDropTriggerStatement x) {
	return false;
}

@Override
bool  SchemaStatVisitor::visit(SQLDropUserStatement x) {
	return false;
}

@Override
bool  SchemaStatVisitor::visit(SQLGrantStatement x) {
	return false;
}

@Override
bool  SchemaStatVisitor::visit(SQLDropDatabaseStatement x) {
	return false;
}

@Override
bool  SchemaStatVisitor::visit(SQLAlterTableAddIndex x) {
	for (SQLSelectOrderByItem item : x.getItems()) {
		item.accept(this);
	}
	return false;
}

bool  SchemaStatVisitor::visit(SQLCheck x) {
	x.getExpr().accept(this);
	return false;
}

bool  SchemaStatVisitor::visit(SQLCreateTriggerStatement x) {
	return false;
}

bool  SchemaStatVisitor::visit(SQLDropFunctionStatement x) {
	return false;
}

bool  SchemaStatVisitor::visit(SQLDropTableSpaceStatement x) {
	return false;
}

bool  SchemaStatVisitor::visit(SQLDropProcedureStatement x) {
	return false;
}


