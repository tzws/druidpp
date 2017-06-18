#include "ParameterizedOutputVisitorUtils.h"

std::string ParameterizedOutputVisitorUtils::ATTR_PARAMS_SKIP = "druid.parameterized.skip";

std::string parameterize(std::string sql, std::string dbType) {
	SQLStatementParser parser = SQLParserUtils.createSQLStatementParser(sql, dbType);
	std::list<SQLStatement> statementList = parser.parseStatementList();
	if (statementList.size() == 0) {
		return sql;
	}

	SQLStatement stmt = statementList.get(0);

	StringBuilder out = new StringBuilder();
	ParameterizedVisitor visitor = createParameterizedOutputVisitor(out, dbType);
	stmt.accept(visitor);

	if (visitor.getReplaceCount() == 0) {
		return sql;
	}

	return out.toString();
}

ParameterizedVisitor createParameterizedOutputVisitor(Appendable out, std::string dbType) {
	if (JdbcUtils.ORACLE.equals(dbType) || JdbcUtils.ALI_ORACLE.equals(dbType)) {
		return new OracleParameterizedOutputVisitor(out);
	}

	if (JdbcUtils.MYSQL.equals(dbType)) {
		return new MySqlParameterizedOutputVisitor(out);
	}

	if (JdbcUtils.MARIADB.equals(dbType)) {
		return new MySqlParameterizedOutputVisitor(out);
	}

	if (JdbcUtils.H2.equals(dbType)) {
		return new MySqlParameterizedOutputVisitor(out);
	}

	if (JdbcUtils.POSTGRESQL.equals(dbType)) {
		return new PGParameterizedOutputVisitor(out);
	}

	if (JdbcUtils.SQL_SERVER.equals(dbType) || JdbcUtils.JTDS.equals(dbType)) {
		return new SQLServerParameterizedOutputVisitor(out);
	}

	if (JdbcUtils.DB2.equals(dbType)) {
		return new DB2ParameterizedOutputVisitor(out);
	}

	return new ParameterizedOutputVisitor(out);
}

boolean visit(ParameterizedVisitor v, SQLInListExpr x) {
	std::list<SQLExpr> targetList = x.getTargetList();

	boolean changed = true;
	if (targetList.size() == 1 && targetList.get(0) instanceof SQLVariantRefExpr) {
		changed = false;
	}

	x.getExpr().accept(v);

	if (x.isNot()) {
		v.print(" NOT IN (?)");
	} else {
		v.print(" IN (?)");
	}

	if (changed) {
		v.incrementReplaceCunt();
	}

	return false;
}

boolean visit(ParameterizedVisitor v, SQLIntegerExpr x) {
	if (!checkParameterize(x)) {
		return SQLASTOutputVisitorUtils.visit(v, x);
	}

	v.print('?');
	v.incrementReplaceCunt();
	return false;
}

boolean visit(ParameterizedVisitor v, SQLNumberExpr x) {
	if (!checkParameterize(x)) {
		return SQLASTOutputVisitorUtils.visit(v, x);
	}

	v.print('?');
	v.incrementReplaceCunt();
	return false;
}

boolean visit(ParameterizedVisitor v, SQLCharExpr x) {
	v.print('?');
	v.incrementReplaceCunt();
	return false;
}

boolean checkParameterize(SQLObject x) {
	if (Boolean.TRUE.equals(x.getAttribute(ParameterizedOutputVisitorUtils.ATTR_PARAMS_SKIP))) {
		return false;
	}

	SQLObject parent = x.getParent();

	if (parent instanceof SQLDataType //
			|| parent instanceof SQLColumnDefinition //
			|| parent instanceof SQLServerTop //
			|| parent instanceof SQLAssignItem //
			|| parent instanceof SQLSelectOrderByItem //
	   ) {
		return false;
	}

	return true;
}

boolean visit(ParameterizedVisitor v, SQLNCharExpr x) {
	v.print('?');
	v.incrementReplaceCunt();
	return false;
}

boolean visit(ParameterizedVisitor v, SQLNullExpr x) {
	SQLObject parent = x.getParent();
	if (parent instanceof SQLBinaryOpExpr) {
		SQLBinaryOpExpr binaryOpExpr = (SQLBinaryOpExpr) parent;
		if (binaryOpExpr.getOperator() == SQLBinaryOperator.IsNot
				|| binaryOpExpr.getOperator() == SQLBinaryOperator.Is) {
			v.print("NULL");
			return false;
		}
	}

	v.print('?');
	v.incrementReplaceCunt();
	return false;
}

SQLBinaryOpExpr merge(ParameterizedVisitor v, SQLBinaryOpExpr x) {
	SQLExpr left = x.getLeft();
	SQLExpr right = x.getRight();
	SQLObject parent = x.getParent();

	if (left instanceof SQLLiteralExpr && right instanceof SQLLiteralExpr) {
		if (x.getOperator() == SQLBinaryOperator.Equality //
				|| x.getOperator() == SQLBinaryOperator.NotEqual) {
			left.putAttribute(ATTR_PARAMS_SKIP, true);
			right.putAttribute(ATTR_PARAMS_SKIP, true);
		}
		return x;
	}

	for (;;) {
		if (x.getRight() instanceof SQLBinaryOpExpr) {
			if (x.getLeft() instanceof SQLBinaryOpExpr) {
				SQLBinaryOpExpr leftBinaryExpr = (SQLBinaryOpExpr) x.getLeft();
				if (leftBinaryExpr.getRight().equals(x.getRight())) {
					x = leftBinaryExpr;
					v.incrementReplaceCunt();
					continue;
				}
			}
			SQLExpr mergedRight = merge(v, (SQLBinaryOpExpr) x.getRight());
			if (mergedRight != x.getRight()) {
				x = new SQLBinaryOpExpr(x.getLeft(), x.getOperator(), mergedRight);
				v.incrementReplaceCunt();
			}
			x.setParent(parent);
		}

		break;
	}

	if (x.getLeft() instanceof SQLBinaryOpExpr) {
		SQLExpr mergedLeft = merge(v, (SQLBinaryOpExpr) x.getLeft());
		if (mergedLeft != x.getLeft()) {
			x = new SQLBinaryOpExpr(mergedLeft, x.getOperator(), x.getRight());
			v.incrementReplaceCunt();
		}
		x.setParent(parent);
	}

	// ID = ? OR ID = ? => ID = ?
	if (x.getOperator() == SQLBinaryOperator.BooleanOr) {
		if ((left instanceof SQLBinaryOpExpr) && (right instanceof SQLBinaryOpExpr)) {
			SQLBinaryOpExpr leftBinary = (SQLBinaryOpExpr) x.getLeft();
			SQLBinaryOpExpr rightBinary = (SQLBinaryOpExpr) x.getRight();

			if (mergeEqual(leftBinary, rightBinary)) {
				v.incrementReplaceCunt();
				return leftBinary;
			}

			if (isLiteralExpr(leftBinary.getLeft()) //
					&& leftBinary.getOperator() == SQLBinaryOperator.BooleanOr) {
				if (mergeEqual(leftBinary.getRight(), right)) {
					v.incrementReplaceCunt();
					return leftBinary;
				}
			}
		}
	}

	return x;
}

private static boolean mergeEqual(SQLExpr a, SQLExpr b) {
	if (!(a instanceof SQLBinaryOpExpr)) {
		return false;
	}
	if (!(b instanceof SQLBinaryOpExpr)) {
		return false;
	}

	SQLBinaryOpExpr binaryA = (SQLBinaryOpExpr) a;
	SQLBinaryOpExpr binaryB = (SQLBinaryOpExpr) b;

	if (binaryA.getOperator() != SQLBinaryOperator.Equality) {
		return false;
	}

	if (binaryB.getOperator() != SQLBinaryOperator.Equality) {
		return false;
	}

	if (!(binaryA.getRight() instanceof SQLLiteralExpr || binaryA.getRight() instanceof SQLVariantRefExpr)) {
		return false;
	}

	if (!(binaryB.getRight() instanceof SQLLiteralExpr || binaryB.getRight() instanceof SQLVariantRefExpr)) {
		return false;
	}

	return binaryA.getLeft().toString().equals(binaryB.getLeft().toString());
}

private static boolean isLiteralExpr(SQLExpr expr) {
	if (expr instanceof SQLLiteralExpr) {
		return true;
	}

	if (expr instanceof SQLBinaryOpExpr) {
		SQLBinaryOpExpr binary = (SQLBinaryOpExpr) expr;
		return isLiteralExpr(binary.getLeft()) && isLiteralExpr(binary.getRight());
	}

	return false;
}
