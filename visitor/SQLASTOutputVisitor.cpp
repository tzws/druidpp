#include "SQLASTOutputVisitor.h"

SQLASTOutputVisitor::SQLASTOutputVisitor(std::string & theAppender) 
	: 
		appender( theAppender), 
		indent("\t"), 
		indentCount(0), 
		prettyFormat(true), 
		selectListNumberOfLine(5)
{
	//this->appender = appender;
}

SQLASTOutputVisitor::~SQLASTOutputVisitor() 
{

	//if (appender != NULL)
	//{
		//delete appender;
	//}

}

int SQLASTOutputVisitor::getParametersSize() {

	//if (parameters == NULL) {
		//return 0;
	//}

	return this->parameters.size();
}

std::list<Object *> &SQLASTOutputVisitor::getParameters() {

	//if (parameters == NULL) {
		//parameters = new ArrayList<Object *>();
	//}

	return parameters;
}

void SQLASTOutputVisitor::setParameters(std::list<Object *> &parameters) {
	this->parameters = parameters;
}

int SQLASTOutputVisitor::getIndentCount() {
	return indentCount;
}

std::string & SQLASTOutputVisitor::getAppender() {
	return appender;
}

bool  SQLASTOutputVisitor::isPrettyFormat() {
	return prettyFormat;
}

void SQLASTOutputVisitor::setPrettyFormat(bool  prettyFormat) {
	this->prettyFormat = prettyFormat;
}

void SQLASTOutputVisitor::decrementIndent() {
	this->indentCount -= 1;
}

void SQLASTOutputVisitor::incrementIndent() {
	this->indentCount += 1;
}

void SQLASTOutputVisitor::print(char value) {
	try {
		this->appender.append(value);
	} catch (IOException e) {
		throw new RuntimeException("println error", e);
	}
}

void SQLASTOutputVisitor::print(int value) {
	print(Integer.toString(value));
}

void SQLASTOutputVisitor::print(Date date) {
	SimpleDateFormat dateFormat;
	if (date instanceof java.sql.Timestamp) {
		dateFormat = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss.SSS");
	} else {
		dateFormat = new SimpleDateFormat("yyyy-MM-dd");
	}
	print("'" + dateFormat.format(date) + "'");
}

void SQLASTOutputVisitor::print(long value) {
	print(Long.toString(value));
}

void SQLASTOutputVisitor::print(std::string &text) {
	try {
		this->appender.append(text);
	} catch (IOException e) {
		throw new RuntimeException("println error", e);
	}
}

void SQLASTOutputVisitor::printAlias(std::string &alias) {
	if ((alias != NULL) && (alias.length() > 0)) {
		print(" ");
		print(alias);
	}
}

void SQLASTOutputVisitor::printAndAccept(std::list<SQLObject *> &nodes, std::string &seperator) {
	for (int i = 0, size = nodes.size(); i < size; ++i) {
		if (i != 0) {
			print(seperator);
		}
		nodes.get(i).accept(this);
	}
}

void SQLASTOutputVisitor::printSelectList(std::list<SQLSelectItem *> & selectList) {
	incrementIndent();
	for (int i = 0, size = selectList.size(); i < size; ++i) {
		if (i != 0) {
			if (i % selectListNumberOfLine == 0) {
				println();
			}

			print(", ");
		}

		selectList.get(i).accept(this);
	}
	decrementIndent();
}

void SQLASTOutputVisitor::printlnAndAccept(std::list<SQLObject *> & nodes, std::string &seperator) {
	for (int i = 0, size = nodes.size(); i < size; ++i) {
		if (i != 0) {
			println(seperator);
		}

		((SQLObject) nodes.get(i)).accept(this);
	}
}

void SQLASTOutputVisitor::printIndent() {
	for (int i = 0; i < this->indentCount; ++i) {
		print(this->indent);
	}
}

void SQLASTOutputVisitor::println() {
	if (!isPrettyFormat()) {
		print(' ');
		return;
	}

	print("\n");
	printIndent();
}

void SQLASTOutputVisitor::println(std::string &text) {
	print(text);
	println();
}

// ////////////////////

bool  SQLASTOutputVisitor::visit(SQLBetweenExpr *x) {
	x->getTestExpr().accept(this);

	if (x->isNot()) {
		print(" NOT BETWEEN ");
	} else {
		print(" BETWEEN ");
	}

	x->getBeginExpr().accept(this);
	print(" AND ");
	x->getEndExpr().accept(this);

	return false;
}

bool  SQLASTOutputVisitor::visit(SQLBinaryOpExpr *x) {
	SQLObject parent = x->getParent();
	bool  isRoot = parent instanceof SQLSelectQueryBlock;
	bool  relational = x->getOperator() == SQLBinaryOperator.BooleanAnd
		|| x->getOperator() == SQLBinaryOperator.BooleanOr;

	if (isRoot && relational) {
		incrementIndent();
	}

	std::list<SQLExpr> groupList = new ArrayList<SQLExpr>();
	SQLExpr left = x->getLeft();
	for (;;) {
		if (left instanceof SQLBinaryOpExpr && ((SQLBinaryOpExpr) left).getOperator() == x->getOperator()) {
			SQLBinaryOpExpr binaryLeft = (SQLBinaryOpExpr) left;
			groupList.add(binaryLeft.getRight());
			left = binaryLeft.getLeft();
		} else {
			groupList.add(left);
			break;
		}
	}

	for (int i = groupList.size() - 1; i >= 0; --i) {
		SQLExpr item = groupList.get(i);
		visitBinaryLeft(item, x->getOperator());

		if (relational) {
			println();
		} else {
			print(" ");
		}
		print(x->getOperator().name);
		print(" ");
	}

	visitorBinaryRight(x);

	if (isRoot && relational) {
		decrementIndent();
	}

	return false;
}

void SQLASTOutputVisitor::visitorBinaryRight(SQLBinaryOpExpr *x) {
	if (x->getRight() instanceof SQLBinaryOpExpr) {
		SQLBinaryOpExpr right = (SQLBinaryOpExpr) x->getRight();
		bool  rightRational = right.getOperator() == SQLBinaryOperator.BooleanAnd
			|| right.getOperator() == SQLBinaryOperator.BooleanOr;

		if (right.getOperator().priority >= x->getOperator().priority) {
			if (rightRational) {
				incrementIndent();
			}

			print('(');
			right.accept(this);
			print(')');

			if (rightRational) {
				decrementIndent();
			}
		} else {
			right.accept(this);
		}
	} else {
		x->getRight().accept(this);
	}
}

void SQLASTOutputVisitor::visitBinaryLeft(SQLExpr *left, SQLBinaryOperator *op) {
	if (left instanceof SQLBinaryOpExpr) {
		SQLBinaryOpExpr binaryLeft = (SQLBinaryOpExpr) left;
		bool  leftRational = binaryLeft.getOperator() == SQLBinaryOperator.BooleanAnd
			|| binaryLeft.getOperator() == SQLBinaryOperator.BooleanOr;

		if (binaryLeft.getOperator().priority > op.priority) {
			if (leftRational) {
				incrementIndent();
			}
			print('(');
			left.accept(this);
			print(')');

			if (leftRational) {
				decrementIndent();
			}
		} else {
			left.accept(this);
		}
	} else {
		left.accept(this);
	}
}

bool  SQLASTOutputVisitor::visit(SQLCaseExpr *x) {
	print("CASE ");
	if (x->getValueExpr() != NULL) {
		x->getValueExpr().accept(this);
		print(" ");
	}

	printAndAccept(x->getItems(), " ");

	if (x->getElseExpr() != NULL) {
		print(" ELSE ");
		x->getElseExpr().accept(this);
	}

	print(" END");
	return false;
}

bool  SQLASTOutputVisitor::visit(SQLCaseExpr_Item *x) {
	print("WHEN ");
	x->getConditionExpr().accept(this);
	print(" THEN ");
	x->getValueExpr().accept(this);
	return false;
}

bool  SQLASTOutputVisitor::visit(SQLCastExpr *x) {
	print("CAST(");
	x->getExpr().accept(this);
	print(" AS ");
	x->getDataType().accept(this);
	print(")");

	return false;
}

bool  SQLASTOutputVisitor::visit(SQLCharExpr *x) {
	if ((x->getText() == NULL) || (x->getText().length() == 0)) {
		print("NULL");
	} else {
		print("'");
		print(x->getText().replaceAll("'", "''"));
		print("'");
	}

	return false;
}

bool  SQLASTOutputVisitor::visit(SQLDataType *x) {
	print(x->getName());
	if (x->getArguments().size() > 0) {
		print("(");
		printAndAccept(x->getArguments(), ", ");
		print(")");
	}

	return false;
}

bool  SQLASTOutputVisitor::visit(SQLCharactorDataType *x) {
	visit((SQLDataType) x);
	return false;
}

bool  SQLASTOutputVisitor::visit(SQLExistsExpr *x) {
	if (x->isNot()) {
		print("NOT EXISTS (");
	} else {
		print("EXISTS (");
	}
	incrementIndent();
	x->getSubQuery().accept(this);
	decrementIndent();
	print(")");
	return false;
}

bool  SQLASTOutputVisitor::visit(SQLIdentifierExpr *x) {
	print(x->getName());
	return false;
}

bool  SQLASTOutputVisitor::visit(SQLInListExpr *x) {
	x->getExpr().accept(this);

	if (x->isNot()) {
		print(" NOT IN (");
	} else {
		print(" IN (");
	}

	printAndAccept(x->getTargetList(), ", ");
	print(')');
	return false;
}

bool  SQLASTOutputVisitor::visit(SQLIntegerExpr *x) {
	return SQLASTOutputVisitorUtils.visit(this, x);
}

bool  SQLASTOutputVisitor::visit(SQLMethodInvokeExpr *x) {
	if (x->getOwner() != NULL) {
		x->getOwner().accept(this);
		print(".");
	}
	print(x->getMethodName());
	print("(");
	printAndAccept(x->getParameters(), ", ");
	print(")");
	return false;
}

bool  SQLASTOutputVisitor::visit(SQLAggregateExpr *x) {
	print(x->getMethodName());
	print("(");

	if (x->getOption() != NULL) {
		print(x->getOption().toString());
		print(' ');
	}

	printAndAccept(x->getArguments(), ", ");

	visitAggreateRest(x);

	print(")");

	if (x->getOver() != NULL) {
		print(" ");
		x->getOver().accept(this);
	}
	return false;
}

void SQLASTOutputVisitor::visitAggreateRest(SQLAggregateExpr *aggregateExpr) {

}

bool  SQLASTOutputVisitor::visit(SQLAllColumnExpr *x) {
	print("*");
	return true;
}

bool  SQLASTOutputVisitor::visit(SQLNCharExpr *x) {
	if ((x->getText() == NULL) || (x->getText().length() == 0)) {
		print("NULL");
	} else {
		print("N'");
		print(x->getText().replace("'", "''"));
		print("'");
	}
	return false;
}

bool  SQLASTOutputVisitor::visit(SQLNotExpr *x) {
	print("NOT ");
	x->getExpr().accept(this);
	return false;
}

bool  SQLASTOutputVisitor::visit(SQLNullExpr *x) {
	print("NULL");
	return false;
}

bool  SQLASTOutputVisitor::visit(SQLNumberExpr *x) {
	return SQLASTOutputVisitorUtils.visit(this, x);
}

bool  SQLASTOutputVisitor::visit(SQLPropertyExpr *x) {
	x->getOwner().accept(this);
	print(".");
	print(x->getName());
	return false;
}

bool  SQLASTOutputVisitor::visit(SQLQueryExpr *x) {
	SQLObject parent = x->getParent();
	if (parent instanceof SQLSelect) {
		parent = parent.getParent();
	}

	if (parent instanceof SQLStatement) {
		incrementIndent();

		println();
		x->getSubQuery().accept(this);

		decrementIndent();
	} else if (parent instanceof ValuesClause) {
		println();
		x->getSubQuery().accept(this);
		println();
	} else {
		print("(");
		incrementIndent();
		println();
		x->getSubQuery().accept(this);
		println();
		decrementIndent();
		print(")");
	}
	return false;
}

bool  SQLASTOutputVisitor::visit(SQLSelectGroupByClause *x) {
	if (x->getItems().size() > 0) {
		print("GROUP BY ");
		printAndAccept(x->getItems(), ", ");
	}

	if (x->getHaving() != NULL) {
		println();
		print("HAVING ");
		x->getHaving().accept(this);
	}
	return false;
}

bool  SQLASTOutputVisitor::visit(SQLSelect *x) {
	x->getQuery().setParent(x);

	if (x->getWithSubQuery() != NULL) {
		x->getWithSubQuery().accept(this);
		println();
	}

	x->getQuery().accept(this);

	if (x->getOrderBy() != NULL) {
		println();
		x->getOrderBy().accept(this);
	}

	if (x->getHintsSize() > 0) {
		printAndAccept(x->getHints(), "");
	}

	return false;
}

bool  SQLASTOutputVisitor::visit(SQLSelectQueryBlock *x) {
	print("SELECT ");

	if (SQLSetQuantifier.ALL == x->getDistionOption()) {
		print("ALL ");
	} else if (SQLSetQuantifier.DISTINCT == x->getDistionOption()) {
		print("DISTINCT ");
	} else if (SQLSetQuantifier.UNIQUE == x->getDistionOption()) {
		print("UNIQUE ");
	}

	printSelectList(x->getSelectList());

	if (x->getFrom() != NULL) {
		println();
		print("FROM ");
		x->getFrom().accept(this);
	}

	if (x->getWhere() != NULL) {
		println();
		print("WHERE ");
		x->getWhere().setParent(x);
		x->getWhere().accept(this);
	}

	if (x->getGroupBy() != NULL) {
		println();
		x->getGroupBy().accept(this);
	}

	return false;
}

bool  SQLASTOutputVisitor::visit(SQLSelectItem *x) {
	x->getExpr().accept(this);

	if ((x->getAlias() != NULL) && (x->getAlias().length() > 0)) {
		print(" AS ");
		print(x->getAlias());
	}
	return false;
}

bool  SQLASTOutputVisitor::visit(SQLOrderBy *x) {
	if (x->getItems().size() > 0) {
		print("ORDER BY ");

		printAndAccept(x->getItems(), ", ");
	}
	return false;
}

bool  SQLASTOutputVisitor::visit(SQLSelectOrderByItem *x) {
	x->getExpr().accept(this);
	if (x->getType() != NULL) {
		print(" ");
		print(x->getType().name().toUpperCase());
	}

	if (x->getCollate() != NULL) {
		print(" COLLATE ");
		print(x->getCollate());
	}

	return false;
}

bool  SQLASTOutputVisitor::visit(SQLExprTableSource *x) {
	x->getExpr().accept(this);

	if (x->getAlias() != NULL) {
		print(' ');
		print(x->getAlias());
	}

	return false;
}

bool  SQLASTOutputVisitor::visit(SQLSelectStatement *stmt) {
	SQLSelect select = stmt.getSelect();

	select.accept(this);

	return false;
}

bool  SQLASTOutputVisitor::visit(SQLVariantRefExpr *x) {
	int index = x->getIndex();

	if (parameters == NULL || index >= parameters.size()) {
		print(x->getName());
		return false;
	}

	Object * param = parameters.get(index);
	printParameter(param);
	return false;
}

void SQLASTOutputVisitor::printParameter(Object * param) {
	if (param == NULL) {
		print("NULL");
		return;
	}

	if (param instanceof Number //
			|| param instanceof Boolean) {
		print(param.toString());
		return;
	}

	if (param instanceof std::string) {
		SQLCharExpr charExpr = new SQLCharExpr((std::string) param);
		visit(charExpr);
		return;
	}

	if (param instanceof Date) {
		print((Date) param);
		return;
	}

	if (param instanceof InputStream) {
		print("'<InputStream>");
		return;
	}

	if (param instanceof Reader) {
		print("'<Reader>");
		return;
	}

	if (param instanceof Blob) {
		print("'<Blob>");
		return;
	}

	if (param instanceof NClob) {
		print("'<NClob>");
		return;
	}

	if (param instanceof Clob) {
		print("'<Clob>");
		return;
	}

	print("'" + param.getClass().getName() + "'");
}

bool  SQLASTOutputVisitor::visit(SQLDropTableStatement *x) {
	if (x->isTemporary()) {
		print("DROP TEMPORARY TABLE ");
	} else {
		print("DROP TABLE ");
	}

	if (x->isIfExists()) {
		print("IF EXISTS ");
	}

	printAndAccept(x->getTableSources(), ", ");

	if (x->isCascade()) {
		printCascade();
	}

	if (x->isRestrict()) {
		print(" RESTRICT");
	}

	if (x->isPurge()) {
		print(" PURGE");
	}

	return false;
}

void SQLASTOutputVisitor::printCascade() {
	print(" CASCADE");
}

bool  SQLASTOutputVisitor::visit(SQLDropViewStatement *x) {
	print("DROP VIEW ");

	if (x->isIfExists()) {
		print("IF EXISTS ");
	}

	printAndAccept(x->getTableSources(), ", ");

	if (x->isCascade()) {
		printCascade();
	}
	return false;
}

bool  SQLASTOutputVisitor::visit(SQLTableElement *x) {
	if (x instanceof SQLColumnDefinition) {
		return visit((SQLColumnDefinition) x);
	}

	throw new RuntimeException("TODO");
}

bool  SQLASTOutputVisitor::visit(SQLColumnDefinition *x) {
	x->getName().accept(this);

	if (x->getDataType() != NULL) {
		print(' ');
		x->getDataType().accept(this);
	}

	if (x->getDefaultExpr() != NULL) {
		visitColumnDefault(x);
	}

	for (SQLColumnConstraint item : x->getConstaints()) {
		bool  newLine = item instanceof SQLForeignKeyConstraint //
			|| item instanceof SQLPrimaryKey //
			|| item instanceof SQLColumnCheck //
			|| item instanceof SQLColumnCheck //
			|| item.getName() != NULL;
		if (newLine) {
			incrementIndent();
			println();
		} else {
			print(' ');
		}

		item.accept(this);

		if (newLine) {
			decrementIndent();
		}
	}

	if (x->getEnable() != NULL) {
		if (x->getEnable().booleanValue()) {
			print(" ENABLE");
		}
	}

	if (x->getComment() != NULL) {
		print(" COMMENT ");
		x->getComment().accept(this);
	}

	return false;
}

void SQLASTOutputVisitor::visitColumnDefault(SQLColumnDefinition *x) {
	print(" DEFAULT ");
	x->getDefaultExpr().accept(this);
}

bool  SQLASTOutputVisitor::visit(SQLDeleteStatement *x) {
	print("DELETE FROM ");

	x->getTableName().accept(this);

	if (x->getWhere() != NULL) {
		print(" WHERE ");
		x->getWhere().setParent(x);
		x->getWhere().accept(this);
	}

	return false;
}

bool  SQLASTOutputVisitor::visit(SQLCurrentOfCursorExpr *x) {
	print("CURRENT OF ");
	x->getCursorName().accept(this);
	return false;
}

bool  SQLASTOutputVisitor::visit(SQLInsertStatement *x) {
	print("INSERT INTO ");

	x->getTableSource().accept(this);

	if (x->getColumns().size() > 0) {
		incrementIndent();
		println();
		print("(");
		for (int i = 0, size = x->getColumns().size(); i < size; ++i) {
			if (i != 0) {
				if (i % 5 == 0) {
					println();
				}
				print(", ");
			}
			x->getColumns().get(i).accept(this);
		}
		print(")");
		decrementIndent();
	}

	if (x->getValues() != NULL) {
		println();
		print("VALUES");
		println();
		x->getValues().accept(this);
	} else {
		if (x->getQuery() != NULL) {
			println();
			x->getQuery().setParent(x);
			x->getQuery().accept(this);
		}
	}

	return false;
}

bool  SQLASTOutputVisitor::visit(SQLUpdateSetItem *x) {
	x->getColumn().accept(this);
	print(" = ");
	x->getValue().accept(this);
	return false;
}

bool  SQLASTOutputVisitor::visit(SQLUpdateStatement *x) {
	print("UPDATE ");

	x->getTableSource().accept(this);

	println();
	print("SET ");
	for (int i = 0, size = x->getItems().size(); i < size; ++i) {
		if (i != 0) {
			print(", ");
		}
		x->getItems().get(i).accept(this);
	}

	if (x->getWhere() != NULL) {
		println();
		print("WHERE ");
		x->getWhere().setParent(x);
		x->getWhere().accept(this);
	}

	return false;
}

bool  SQLASTOutputVisitor::visit(SQLCreateTableStatement *x) {
	print("CREATE TABLE ");
	if (SQLCreateTableStatement.Type.GLOBAL_TEMPORARY.equals(x->getType())) {
		print("GLOBAL TEMPORARY ");
	} else if (SQLCreateTableStatement.Type.LOCAL_TEMPORARY.equals(x->getType())) {
		print("LOCAL TEMPORARY ");
	}

	x->getName().accept(this);

	int size = x->getTableElementList().size();

	if (size > 0) {
		print(" (");
		incrementIndent();
		println();
		for (int i = 0; i < size; ++i) {
			if (i != 0) {
				print(",");
				println();
			}
			x->getTableElementList().get(i).accept(this);
		}
		decrementIndent();
		println();
		print(")");
	}

	return false;
}

bool  SQLASTOutputVisitor::visit(SQLUniqueConstraint *x) {
	if (x->getName() != NULL) {
		print("CONSTRAINT ");
		x->getName().accept(this);
		print(' ');
	}

	print("UNIQUE (");
	for (int i = 0, size = x->getColumns().size(); i < size; ++i) {
		if (i != 0) {
			print(", ");
		}
		x->getColumns().get(i).accept(this);
	}
	print(")");
	return false;
}

bool  SQLASTOutputVisitor::visit(NotNullConstraint *x) {
	if (x->getName() != NULL) {
		print("CONSTRAINT ");
		x->getName().accept(this);
		print(' ');
	}
	print("NOT NULL");
	return false;
}

bool  SQLASTOutputVisitor::visit(SQLUnionQuery *x) {
	x->getLeft().accept(this);
	println();
	print(x->getOperator().name);
	println();

	bool  needParen = false;

	if (x->getOrderBy() != NULL) {
		needParen = true;
	}

	if (needParen) {
		print('(');
		x->getRight().accept(this);
		print(')');
	} else {
		x->getRight().accept(this);
	}

	if (x->getOrderBy() != NULL) {
		println();
		x->getOrderBy().accept(this);
	}

	return false;
}

bool  SQLASTOutputVisitor::visit(SQLUnaryExpr *x) {
	print(x->getOperator().name);

	SQLExpr expr = x->getExpr();

	switch (x->getOperator()) {
		case BINARY:
		case Prior:
		case ConnectByRoot:
			print(' ');
			expr.accept(this);
			return false;
		default:
			break;
	}

	if (expr instanceof SQLBinaryOpExpr) {
		print('(');
		expr.accept(this);
		print(')');
	} else if (expr instanceof SQLUnaryExpr) {
		print('(');
		expr.accept(this);
		print(')');
	} else {
		expr.accept(this);
	}
	return false;
}

bool  SQLASTOutputVisitor::visit(SQLHexExpr *x) {
	print("0x");
	print(x->getHex());

	std::string charset = (std::string) x->getAttribute("USING");
	if (charset != NULL) {
		print(" USING ");
		print(charset);
	}

	return false;
}

bool  SQLASTOutputVisitor::visit(SQLSetStatement *x) {
	print("SET ");
	printAndAccept(x->getItems(), ", ");
	return false;
}

bool  SQLASTOutputVisitor::visit(SQLAssignItem *x) {
	x->getTarget().accept(this);
	print(" = ");
	x->getValue().accept(this);
	return false;
}

bool  SQLASTOutputVisitor::visit(SQLCallStatement *x) {
	if (x->isBrace()) {
		print("{");
	}
	if (x->getOutParameter() != NULL) {
		x->getOutParameter().accept(this);
		print(" = ");
	}

	print("CALL ");
	x->getProcedureName().accept(this);
	print('(');

	printAndAccept(x->getParameters(), ", ");
	print(')');
	if (x->isBrace()) {
		print("}");
	}
	return false;
}

bool  SQLASTOutputVisitor::visit(SQLJoinTableSource *x) {
	x->getLeft().accept(this);
	incrementIndent();

	if (x->getJoinType() == JoinType.COMMA) {
		print(",");
	} else {
		println();
		print(JoinType.toString(x->getJoinType()));
	}
	print(" ");
	x->getRight().accept(this);

	if (x->getCondition() != NULL) {
		incrementIndent();
		print(" ON ");
		x->getCondition().accept(this);
		decrementIndent();
	}

	if (x->getUsing().size() > 0) {
		print(" USING (");
		printAndAccept(x->getUsing(), ", ");
		print(")");
	}

	if (x->getAlias() != NULL) {
		print(" AS ");
		print(x->getAlias());
	}

	decrementIndent();

	return false;
}

bool  SQLASTOutputVisitor::visit(ValuesClause *x) {
	print("(");
	incrementIndent();
	for (int i = 0, size = x->getValues().size(); i < size; ++i) {
		if (i != 0) {
			if (i % 5 == 0) {
				println();
			}
			print(", ");
		}

		SQLExpr expr = x->getValues().get(i);
		expr.setParent(x);
		expr.accept(this);
	}
	decrementIndent();
	print(")");
	return false;
}

bool  SQLASTOutputVisitor::visit(SQLSomeExpr *x) {
	print("SOME (");

	incrementIndent();
	x->getSubQuery().accept(this);
	decrementIndent();
	print(")");
	return false;
}

bool  SQLASTOutputVisitor::visit(SQLAnyExpr *x) {
	print("ANY (");

	incrementIndent();
	x->getSubQuery().accept(this);
	decrementIndent();
	print(")");
	return false;
}

bool  SQLASTOutputVisitor::visit(SQLAllExpr *x) {
	print("ALL (");

	incrementIndent();
	x->getSubQuery().accept(this);
	decrementIndent();
	print(")");
	return false;
}

bool  SQLASTOutputVisitor::visit(SQLInSubQueryExpr *x) {
	x->getExpr().accept(this);
	if (x->isNot()) {
		print(" NOT IN (");
	} else {
		print(" IN (");
	}

	incrementIndent();
	x->getSubQuery().accept(this);
	decrementIndent();
	print(")");

	return false;
}

bool  SQLASTOutputVisitor::visit(SQLListExpr *x) {
	print("(");
	printAndAccept(x->getItems(), ", ");
	print(")");

	return false;
}

bool  SQLASTOutputVisitor::visit(SQLSubqueryTableSource *x) {
	print("(");
	incrementIndent();
	x->getSelect().accept(this);
	println();
	decrementIndent();
	print(")");

	if (x->getAlias() != NULL) {
		print(' ');
		print(x->getAlias());
	}

	return false;
}

bool  SQLASTOutputVisitor::visit(SQLTruncateStatement *x) {
	print("TRUNCATE TABLE ");
	printAndAccept(x->getTableSources(), ", ");
	return false;
}

bool  SQLASTOutputVisitor::visit(SQLDefaultExpr *x) {
	print("DEFAULT");
	return false;
}

void SQLASTOutputVisitor::endVisit(SQLCommentStatement *x) {

}

bool  SQLASTOutputVisitor::visit(SQLCommentStatement *x) {
	print("COMMENT ON ");
	if (x->getType() != NULL) {
		print(x->getType().name());
		print(" ");
	}
	x->getOn().accept(this);

	print(" IS ");
	x->getComment().accept(this);

	return false;
}

bool  SQLASTOutputVisitor::visit(SQLUseStatement *x) {
	print("USE ");
	x->getDatabase().accept(this);
	return false;
}

bool  SQLASTOutputVisitor::visit(SQLAlterTableAddColumn *x) {
	print("ADD (");
	printAndAccept(x->getColumns(), ", ");
	print(")");
	return false;
}

bool  SQLASTOutputVisitor::visit(SQLAlterTableDropColumnItem *x) {
	print("DROP COLUMN ");
	this->printAndAccept(x->getColumns(), ", ");
	return false;
}

void SQLASTOutputVisitor::endVisit(SQLAlterTableAddColumn *x) {

}

bool  SQLASTOutputVisitor::visit(SQLDropIndexStatement *x) {
	print("DROP INDEX ");
	x->getIndexName().accept(this);

	SQLExprTableSource table = x->getTableName();
	if (table != NULL) {
		print(" ON ");
		table.accept(this);
	}
	return false;
}

bool  SQLASTOutputVisitor::visit(SQLSavePointStatement *x) {
	print("SAVEPOINT ");
	x->getName().accept(this);
	return false;
}

bool  SQLASTOutputVisitor::visit(SQLReleaseSavePointStatement *x) {
	print("RELEASE SAVEPOINT ");
	x->getName().accept(this);
	return false;
}

bool  SQLASTOutputVisitor::visit(SQLRollbackStatement *x) {
	print("ROLLBACK");
	if (x->getTo() != NULL) {
		print(" TO ");
		x->getTo().accept(this);
	}
	return false;
}

bool  SQLASTOutputVisitor::visit(SQLCommentHint *x) {
	print("/*");
	print(x->getText());
	print("*/");
	return false;
}

bool  SQLASTOutputVisitor::visit(SQLCreateDatabaseStatement *x) {
	print("CREATE DATABASE ");
	x->getName().accept(this);
	return false;
}

bool  SQLASTOutputVisitor::visit(SQLAlterTableDropIndex *x) {
	print("DROP INDEX ");
	x->getIndexName().accept(this);
	return false;
}

bool  SQLASTOutputVisitor::visit(SQLOver *x) {
	print("OVER (");
	if (x->getPartitionBy().size() > 0) {
		print("PARTITION BY ");
		printAndAccept(x->getPartitionBy(), ", ");
		print(' ');
	}
	if (x->getOrderBy() != NULL) {
		x->getOrderBy().accept(this);
	}
	print(")");
	return false;
}

bool  SQLASTOutputVisitor::visit(SQLColumnPrimaryKey *x) {
	if (x->getName() != NULL) {
		print("CONSTRAINT ");
		x->getName().accept(this);
		print(' ');
	}
	print("PRIMARY KEY");
	return false;
}

bool  SQLASTOutputVisitor::visit(SQLColumnUniqueKey *x) {
	if (x->getName() != NULL) {
		print("CONSTRAINT ");
		x->getName().accept(this);
		print(' ');
	}
	print("UNIQUE");
	return false;
}

bool  SQLASTOutputVisitor::visit(SQLColumnCheck *x) {
	if (x->getName() != NULL) {
		print("CONSTRAINT ");
		x->getName().accept(this);
		print(' ');
	}
	print("CHECK (");
	x->getExpr().accept(this);
	print(')');

	if (x->getEnable() != NULL) {
		if (x->getEnable().booleanValue()) {
			print(" ENABLE");
		} else {
			print(" DISABLE");
		}
	}
	return false;
}

bool  SQLASTOutputVisitor::visit(SQLWithSubqueryClause *x) {
	print("WITH");
	if (x->getRecursive() == Boolean.TRUE) {
		print(" RECURSIVE");
	}
	incrementIndent();
	println();
	printlnAndAccept(x->getEntries(), ", ");
	decrementIndent();
	return false;
}

bool  SQLASTOutputVisitor::visit(SQLWithSubqueryClause_Entry *x) {
	x->getName().accept(this);

	if (x->getColumns().size() > 0) {
		print(" (");
		printAndAccept(x->getColumns(), ", ");
		print(")");
	}
	println();
	print("AS");
	println();
	print("(");
	incrementIndent();
	println();
	x->getSubQuery().accept(this);
	decrementIndent();
	println();
	print(")");

	return false;
}

bool  SQLASTOutputVisitor::visit(SQLAlterTableAlterColumn *x) {
	print("ALTER COLUMN ");
	x->getColumn().accept(this);
	return false;
}

bool  SQLASTOutputVisitor::visit(SQLCheck *x) {
	if (x->getName() != NULL) {
		print("CONSTRAINT ");
		x->getName().accept(this);
		print(' ');
	}
	print("CHECK (");
	incrementIndent();
	x->getExpr().accept(this);
	decrementIndent();
	print(')');
	return false;
}

bool  SQLASTOutputVisitor::visit(SQLAlterTableDropForeinKey *x) {
	print("DROP FOREIGN KEY ");
	x->getIndexName().accept(this);
	return false;
}

bool  SQLASTOutputVisitor::visit(SQLAlterTableDropPrimaryKey *x) {
	print("DROP PRIMARY KEY");
	return false;
}

bool  SQLASTOutputVisitor::visit(SQLAlterTableEnableKeys *x) {
	print("ENABLE KEYS");
	return false;
}

bool  SQLASTOutputVisitor::visit(SQLAlterTableDisableKeys *x) {
	print("DISABLE KEYS");
	return false;
}

bool  SQLASTOutputVisitor::visit(SQLAlterTableDisableConstraint *x) {
	print("DISABLE CONSTRAINT ");
	x->getConstraintName().accept(this);
	return false;
}

bool  SQLASTOutputVisitor::visit(SQLAlterTableEnableConstraint *x) {
	print("ENABLE CONSTRAINT ");
	x->getConstraintName().accept(this);
	return false;
}

bool  SQLASTOutputVisitor::visit(SQLAlterTableDropConstraint *x) {
	print("DROP CONSTRAINT ");
	x->getConstraintName().accept(this);
	return false;
}

bool  SQLASTOutputVisitor::visit(SQLAlterTableStatement *x) {
	print("ALTER TABLE ");
	x->getName().accept(this);
	incrementIndent();
	for (int i = 0; i < x->getItems().size(); ++i) {
		SQLAlterTableItem item = x->getItems().get(i);
		if (i != 0) {
			print(',');
		}
		println();
		item.accept(this);
	}
	decrementIndent();
	return false;
}

bool  SQLASTOutputVisitor::visit(SQLExprHint *x) {
	x->getExpr().accept(this);
	return false;
}

bool  SQLASTOutputVisitor::visit(SQLCreateIndexStatement *x) {
	print("CREATE ");
	if (x->getType() != NULL) {
		print(x->getType());
		print(" ");
	}

	print("INDEX ");

	x->getName().accept(this);
	print(" ON ");
	x->getTable().accept(this);
	print(" (");
	printAndAccept(x->getItems(), ", ");
	print(")");

	return false;
}

bool  SQLASTOutputVisitor::visit(SQLUnique *x) {
	if (x->getName() != NULL) {
		print("CONSTRAINT ");
		x->getName().accept(this);
		print(" ");
	}
	print("UNIQUE (");
	printAndAccept(x->getColumns(), ", ");
	print(")");
	return false;
}

bool  SQLASTOutputVisitor::visit(SQLPrimaryKeyImpl *x) {
	if (x->getName() != NULL) {
		print("CONSTRAINT ");
		x->getName().accept(this);
		print(" ");
	}
	print("PRIMARY KEY (");
	printAndAccept(x->getColumns(), ", ");
	print(")");
	return false;
}

bool  SQLASTOutputVisitor::visit(SQLAlterTableRenameColumn *x) {
	print("RENAME COLUMN ");
	x->getColumn().accept(this);
	print(" TO ");
	x->getTo().accept(this);
	return false;
}

bool  SQLASTOutputVisitor::visit(SQLColumnReference *x) {
	if (x->getName() != NULL) {
		print("CONSTRAINT ");
		x->getName().accept(this);
		print(" ");
	}
	print("REFERENCES ");
	x->getTable().accept(this);
	print(" (");
	printAndAccept(x->getColumns(), ", ");
	print(")");
	return false;
}

bool  SQLASTOutputVisitor::visit(SQLForeignKeyImpl *x) {
	if (x->getName() != NULL) {
		print("CONSTRAINT ");
		x->getName().accept(this);
		print(' ');
	}

	print("FOREIGN KEY (");
	printAndAccept(x->getReferencedColumns(), ", ");
	print(")");

	print(" REFERENCES ");
	x->getReferencedTableName().accept(this);

	print(" (");
	printAndAccept(x->getReferencedColumns(), ", ");
	print(")");
	return false;
}

bool  SQLASTOutputVisitor::visit(SQLDropSequenceStatement *x) {
	print("DROP SEQUENCE ");
	x->getName().accept(this);
	return false;
}

void SQLASTOutputVisitor::endVisit(SQLDropSequenceStatement *x) {

}

bool  SQLASTOutputVisitor::visit(SQLDropTriggerStatement *x) {
	print("DROP TRIGGER ");
	x->getName().accept(this);
	return false;
}

void SQLASTOutputVisitor::endVisit(SQLDropUserStatement *x) {

}

bool  SQLASTOutputVisitor::visit(SQLDropUserStatement *x) {
	print("DROP USER ");
	printAndAccept(x->getUsers(), ", ");
	return false;
}

bool  SQLASTOutputVisitor::visit(SQLExplainStatement *x) {
	print("EXPLAIN");
	println();
	x->getStatement().accept(this);
	return false;
}

bool  SQLASTOutputVisitor::visit(SQLGrantStatement *x) {
	print("GRANT ");
	printAndAccept(x->getPrivileges(), ", ");

	if (x->getOn() != NULL) {
		print(" ON ");

		if (x->getObjectType() != NULL) {
			print(x->getObjectType().name());
			print(' ');
		}

		x->getOn().accept(this);
	}

	if (x->getTo() != NULL) {
		print(" TO ");
		x->getTo().accept(this);
	}

	bool  with = false;
	if (x->getMaxQueriesPerHour() != NULL) {
		if (!with) {
			print(" WITH");
			with = true;
		}
		print(" MAX_QUERIES_PER_HOUR ");
		x->getMaxQueriesPerHour().accept(this);
	}

	if (x->getMaxUpdatesPerHour() != NULL) {
		if (!with) {
			print(" WITH");
			with = true;
		}
		print(" MAX_UPDATES_PER_HOUR ");
		x->getMaxUpdatesPerHour().accept(this);
	}

	if (x->getMaxConnectionsPerHour() != NULL) {
		if (!with) {
			print(" WITH");
			with = true;
		}
		print(" MAX_CONNECTIONS_PER_HOUR ");
		x->getMaxConnectionsPerHour().accept(this);
	}

	if (x->getMaxUserConnections() != NULL) {
		if (!with) {
			print(" WITH");
			with = true;
		}
		print(" MAX_USER_CONNECTIONS ");
		x->getMaxUserConnections().accept(this);
	}

	if (x->isAdminOption()) {
		if (!with) {
			print(" WITH");
			with = true;
		}
		print(" ADMIN OPTION");
	}

	if (x->getIdentifiedBy() != NULL) {
		print(" IDENTIFIED BY ");
		x->getIdentifiedBy().accept(this);
	}

	return false;
}

bool  SQLASTOutputVisitor::visit(SQLDropDatabaseStatement *x) {
	print("DROP DATABASE ");

	if (x->isIfExists()) {
		print("IF EXISTS ");
	}

	x->getDatabase().accept(this);

	return false;
}

bool  SQLASTOutputVisitor::visit(SQLDropFunctionStatement *x) {
	print("DROP FUNCTION ");

	if (x->isIfExists()) {
		print("IF EXISTS ");
	}

	x->getName().accept(this);

	return false;
}

bool  SQLASTOutputVisitor::visit(SQLDropTableSpaceStatement *x) {
	print("DROP TABLESPACE ");

	if (x->isIfExists()) {
		print("IF EXISTS ");
	}

	x->getName().accept(this);

	return false;
}

bool  SQLASTOutputVisitor::visit(SQLDropProcedureStatement *x) {
	print("DROP PROCEDURE ");

	if (x->isIfExists()) {
		print("IF EXISTS ");
	}

	x->getName().accept(this);

	return false;
}

bool  SQLASTOutputVisitor::visit(SQLAlterTableAddIndex *x) {
	print("ADD ");
	if (x->getType() != NULL) {
		print(x->getType());
		print(" ");
	}

	if (x->isUnique()) {
		print("UNIQUE ");
	}

	print("INDEX ");

	if (x->getName() != NULL) {
		x->getName().accept(this);
		print(' ');
	}
	print("(");
	printAndAccept(x->getItems(), ", ");
	print(")");

	if (x->getUsing() != NULL) {
		print(" USING ");
		print(x->getUsing());
	}
	return false;
}

bool  SQLASTOutputVisitor::visit(SQLAlterTableAddConstraint *x) {
	if (x->isWithNoCheck()) {
		print("WITH NOCHECK ");
	}

	print("ADD ");

	x->getConstraint().accept(this);
	return false;
}

bool  SQLASTOutputVisitor::visit(SQLCreateTriggerStatement *x) {
	print("CREATE ");

	if (x->isOrReplace()) {
		print("OR REPLEACE ");
	}

	print("TRIGGER ");

	x->getName().accept(this);

	incrementIndent();
	println();
	if (TriggerType.INSTEAD_OF.equals(x->getTriggerType())) {
		print("INSTEAD OF");
	} else {
		print(x->getTriggerType().name());
	}

	for (TriggerEvent event : x->getTriggerEvents()) {
		print(' ');
		print(event.name());
	}
	println();
	print("ON ");
	x->getOn().accept(this);

	if (x->isForEachRow()) {
		println();
		print("FOR EACH ROW");
	}
	decrementIndent();
	println();
	x->getBody().accept(this);
	return false;
}
