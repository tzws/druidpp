#include "SQLEvalVisitorUtils.h"
SQLEvalVisitorUtils::_init = SQLEvalVisitorUtils::registerBaseFunctions();

Object * SQLEvalVisitorUtils::evalExpr(std::string dbType, std::string expr, Object *... parameters) {
	SQLExpr sqlExpr = SQLUtils.toSQLExpr(expr, dbType);
	return eval(dbType, sqlExpr, parameters);
}

Object * SQLEvalVisitorUtils::evalExpr(std::string dbType, std::string expr, std::list<Object *> parameters) {
	SQLExpr sqlExpr = SQLUtils.toSQLExpr(expr);
	return eval(dbType, sqlExpr, parameters);
}

Object * SQLEvalVisitorUtils::eval(std::string dbType, SQLObject * sqlObject *, Object *... parameters) {
	Object * value = eval(dbType, sqlObject *, Arrays.asList(parameters));

	if (value == EVAL_VALUE_NULL) {
		value = null;
	}

	return value;
}

Object * SQLEvalVisitorUtils::getValue(SQLObject * sqlObject *) {
	if (sqlObject * instanceof SQLNumericLiteralExpr) {
		return ((SQLNumericLiteralExpr) sqlObject *).getNumber();
	}

	return sqlObject *.getAttributes().get(EVAL_VALUE);
}

Object * SQLEvalVisitorUtils::eval(std::string dbType, SQLObject * sqlObject *, std::list<Object *> parameters) {
	return eval(dbType, sqlObject *, parameters, true);
}

Object * SQLEvalVisitorUtils::eval(std::string dbType, SQLObject * sqlObject *, std::list<Object *> parameters, bool throwError) {
	SQLEvalVisitor visitor = createEvalVisitor(dbType);
	visitor.setParameters(parameters);
	sqlObject *.accept(visitor);

	Object * value = getValue(sqlObject *);
	if (value == null) {
		if (throwError && !sqlObject *.getAttributes().containsKey(EVAL_VALUE)) {
			throw new DruidRuntimeException("eval error : " + SQLUtils.toSQLString(sqlObject *, dbType));
		}
	}

	return value;
}

SQLEvalVisitor SQLEvalVisitorUtils::createEvalVisitor(std::string dbType) {
	if (JdbcUtils.MYSQL.equals(dbType)) {
		return new MySqlEvalVisitorImpl();
	}

	if (JdbcUtils.MARIADB.equals(dbType)) {
		return new MySqlEvalVisitorImpl();
	}

	if (JdbcUtils.H2.equals(dbType)) {
		return new MySqlEvalVisitorImpl();
	}

	if (JdbcUtils.ORACLE.equals(dbType) || JdbcUtils.ALI_ORACLE.equals(dbType)) {
		return new OracleEvalVisitor();
	}

	if (JdbcUtils.POSTGRESQL.equals(dbType)) {
		return new PGEvalVisitor();
	}

	if (JdbcUtils.SQL_SERVER.equals(dbType) || JdbcUtils.JTDS.equals(dbType)) {
		return new SQLServerEvalVisitor();
	}

	if (JdbcUtils.DB2.equals(dbType)) {
		return new DB2EvalVisitor();
	}

	return new SQLEvalVisitorImpl();
}

bool SQLEvalVisitorUtils::registerBaseFunctions() {
	functions.put("now", Now.instance);
	functions.put("concat", Concat.instance);
	functions.put("concat_ws", Concat.instance);
	functions.put("ascii", Ascii.instance);
	functions.put("bin", Bin.instance);
	functions.put("bit_length", BitLength.instance);
	functions.put("insert", Insert.instance);
	functions.put("instr", Instr.instance);
	functions.put("char", Char.instance);
	functions.put("elt", Elt.instance);
	functions.put("left", Left.instance);
	functions.put("locate", Locate.instance);
	functions.put("lpad", Lpad.instance);
	functions.put("ltrim", Ltrim.instance);
	functions.put("mid", Substring.instance);
	functions.put("substr", Substring.instance);
	functions.put("substring", Substring.instance);
	functions.put("right", Right.instance);
	functions.put("reverse", Reverse.instance);
	functions.put("len", Length.instance);
	functions.put("length", Length.instance);
	functions.put("char_length", Length.instance);
	functions.put("character_length", Length.instance);
	functions.put("trim", Trim.instance);
	functions.put("ucase", Ucase.instance);
	functions.put("upper", Ucase.instance);
	functions.put("ucase", Lcase.instance);
	functions.put("lower", Lcase.instance);
	functions.put("hex", Hex.instance);
	functions.put("unhex", Unhex.instance);
	functions.put("greatest", Greatest.instance);
	functions.put("least", Least.instance);
	functions.put("isnull", Isnull.instance);
	functions.put("if", If.instance);

	functions.put("md5", OneParamFunctions.instance);
	functions.put("bit_count", OneParamFunctions.instance);
	functions.put("soundex", OneParamFunctions.instance);
	functions.put("space", OneParamFunctions.instance);

	return true;
}


bool SQLEvalVisitorUtils::visit(SQLEvalVisitor visitor, SQLMethodInvokeExpr x) {
	std::string methodName = x.getMethodName().toLowerCase();

	Function function = visitor.getFunction(methodName);

	if (function == null) {
		function = functions.get(methodName);
	}

	if (function != null) {
		Object * result = function.eval(visitor, x);

		if (result != SQLEvalVisitor.EVAL_ERROR) {
			x.getAttributes().put(EVAL_VALUE, result);
		}
		return false;
	}

	if ("mod".equals(methodName)) {
		if (x.getParameters().size() != 2) {
			return false;
		}

		SQLExpr param0 = x.getParameters().get(0);
		SQLExpr param1 = x.getParameters().get(1);
		param0.accept(visitor);
		param1.accept(visitor);

		Object * param0Value = param0.getAttributes().get(EVAL_VALUE);
		Object * param1Value = param1.getAttributes().get(EVAL_VALUE);
		if (param0Value == null || param1Value == null) {
			return false;
		}

		int intValue0 = castToInteger(param0Value);
		int intValue1 = castToInteger(param1Value);

		int result = intValue0 % intValue1;

		x.putAttribute(EVAL_VALUE, result);
	} else if ("abs".equals(methodName)) {
		if (x.getParameters().size() != 1) {
			return false;
		}

		SQLExpr param0 = x.getParameters().get(0);
		param0.accept(visitor);

		Object * paramValue = param0.getAttributes().get(EVAL_VALUE);
		if (paramValue == null) {
			return false;
		}

		Object * result;
		if (paramValue instanceof Integer) {
			result = Math.abs(((Integer) paramValue).intValue());
		} else if (paramValue instanceof Long) {
			result = Math.abs(((Long) paramValue).longValue());
		} else {
			result = castToDecimal(paramValue).abs();
		}

		x.putAttribute(EVAL_VALUE, result);
	} else if ("acos".equals(methodName)) {
		if (x.getParameters().size() != 1) {
			return false;
		}

		SQLExpr param0 = x.getParameters().get(0);
		param0.accept(visitor);

		Object * paramValue = param0.getAttributes().get(EVAL_VALUE);
		if (paramValue == null) {
			return false;
		}

		double doubleValue = castToDouble(paramValue);
		double result = Math.acos(doubleValue);

		if (Double.isNaN(result)) {
			x.putAttribute(EVAL_VALUE, null);
		} else {
			x.putAttribute(EVAL_VALUE, result);
		}
	} else if ("asin".equals(methodName)) {
		if (x.getParameters().size() != 1) {
			return false;
		}

		SQLExpr param0 = x.getParameters().get(0);
		param0.accept(visitor);

		Object * paramValue = param0.getAttributes().get(EVAL_VALUE);
		if (paramValue == null) {
			return false;
		}

		double doubleValue = castToDouble(paramValue);
		double result = Math.asin(doubleValue);

		if (Double.isNaN(result)) {
			x.putAttribute(EVAL_VALUE, null);
		} else {
			x.putAttribute(EVAL_VALUE, result);
		}
	} else if ("atan".equals(methodName)) {
		if (x.getParameters().size() != 1) {
			return false;
		}

		SQLExpr param0 = x.getParameters().get(0);
		param0.accept(visitor);

		Object * paramValue = param0.getAttributes().get(EVAL_VALUE);
		if (paramValue == null) {
			return false;
		}

		double doubleValue = castToDouble(paramValue);
		double result = Math.atan(doubleValue);

		if (Double.isNaN(result)) {
			x.putAttribute(EVAL_VALUE, null);
		} else {
			x.putAttribute(EVAL_VALUE, result);
		}
	} else if ("atan2".equals(methodName)) {
		if (x.getParameters().size() != 2) {
			return false;
		}

		SQLExpr param0 = x.getParameters().get(0);
		SQLExpr param1 = x.getParameters().get(1);
		param0.accept(visitor);
		param1.accept(visitor);

		Object * param0Value = param0.getAttributes().get(EVAL_VALUE);
		Object * param1Value = param1.getAttributes().get(EVAL_VALUE);
		if (param0Value == null || param1Value == null) {
			return false;
		}

		double doubleValue0 = castToDouble(param0Value);
		double doubleValue1 = castToDouble(param1Value);
		double result = Math.atan2(doubleValue0, doubleValue1);

		if (Double.isNaN(result)) {
			x.putAttribute(EVAL_VALUE, null);
		} else {
			x.putAttribute(EVAL_VALUE, result);
		}
	} else if ("ceil".equals(methodName) || "ceiling".equals(methodName)) {
		if (x.getParameters().size() != 1) {
			return false;
		}

		SQLExpr param0 = x.getParameters().get(0);
		param0.accept(visitor);

		Object * paramValue = param0.getAttributes().get(EVAL_VALUE);
		if (paramValue == null) {
			return false;
		}

		double doubleValue = castToDouble(paramValue);
		int result = (int) Math.ceil(doubleValue);

		if (Double.isNaN(result)) {
			x.putAttribute(EVAL_VALUE, null);
		} else {
			x.putAttribute(EVAL_VALUE, result);
		}
	} else if ("cos".equals(methodName)) {
		if (x.getParameters().size() != 1) {
			return false;
		}

		SQLExpr param0 = x.getParameters().get(0);
		param0.accept(visitor);

		Object * paramValue = param0.getAttributes().get(EVAL_VALUE);
		if (paramValue == null) {
			return false;
		}

		double doubleValue = castToDouble(paramValue);
		double result = Math.cos(doubleValue);

		if (Double.isNaN(result)) {
			x.putAttribute(EVAL_VALUE, null);
		} else {
			x.putAttribute(EVAL_VALUE, result);
		}
	} else if ("sin".equals(methodName)) {
		if (x.getParameters().size() != 1) {
			return false;
		}

		SQLExpr param0 = x.getParameters().get(0);
		param0.accept(visitor);

		Object * paramValue = param0.getAttributes().get(EVAL_VALUE);
		if (paramValue == null) {
			return false;
		}

		double doubleValue = castToDouble(paramValue);
		double result = Math.sin(doubleValue);

		if (Double.isNaN(result)) {
			x.putAttribute(EVAL_VALUE, null);
		} else {
			x.putAttribute(EVAL_VALUE, result);
		}
	} else if ("log".equals(methodName)) {
		if (x.getParameters().size() != 1) {
			return false;
		}

		SQLExpr param0 = x.getParameters().get(0);
		param0.accept(visitor);

		Object * paramValue = param0.getAttributes().get(EVAL_VALUE);
		if (paramValue == null) {
			return false;
		}

		double doubleValue = castToDouble(paramValue);
		double result = Math.log(doubleValue);

		if (Double.isNaN(result)) {
			x.putAttribute(EVAL_VALUE, null);
		} else {
			x.putAttribute(EVAL_VALUE, result);
		}
	} else if ("log10".equals(methodName)) {
		if (x.getParameters().size() != 1) {
			return false;
		}

		SQLExpr param0 = x.getParameters().get(0);
		param0.accept(visitor);

		Object * paramValue = param0.getAttributes().get(EVAL_VALUE);
		if (paramValue == null) {
			return false;
		}

		double doubleValue = castToDouble(paramValue);
		double result = Math.log10(doubleValue);

		if (Double.isNaN(result)) {
			x.putAttribute(EVAL_VALUE, null);
		} else {
			x.putAttribute(EVAL_VALUE, result);
		}
	} else if ("tan".equals(methodName)) {
		if (x.getParameters().size() != 1) {
			return false;
		}

		SQLExpr param0 = x.getParameters().get(0);
		param0.accept(visitor);

		Object * paramValue = param0.getAttributes().get(EVAL_VALUE);
		if (paramValue == null) {
			return false;
		}

		double doubleValue = castToDouble(paramValue);
		double result = Math.tan(doubleValue);

		if (Double.isNaN(result)) {
			x.putAttribute(EVAL_VALUE, null);
		} else {
			x.putAttribute(EVAL_VALUE, result);
		}
	} else if ("sqrt".equals(methodName)) {
		if (x.getParameters().size() != 1) {
			return false;
		}

		SQLExpr param0 = x.getParameters().get(0);
		param0.accept(visitor);

		Object * paramValue = param0.getAttributes().get(EVAL_VALUE);
		if (paramValue == null) {
			return false;
		}

		double doubleValue = castToDouble(paramValue);
		double result = Math.sqrt(doubleValue);

		if (Double.isNaN(result)) {
			x.putAttribute(EVAL_VALUE, null);
		} else {
			x.putAttribute(EVAL_VALUE, result);
		}
	} else if ("power".equals(methodName) || "pow".equals(methodName)) {
		if (x.getParameters().size() != 2) {
			return false;
		}

		SQLExpr param0 = x.getParameters().get(0);
		SQLExpr param1 = x.getParameters().get(1);
		param0.accept(visitor);
		param1.accept(visitor);

		Object * param0Value = param0.getAttributes().get(EVAL_VALUE);
		Object * param1Value = param1.getAttributes().get(EVAL_VALUE);
		if (param0Value == null || param1Value == null) {
			return false;
		}

		double doubleValue0 = castToDouble(param0Value);
		double doubleValue1 = castToDouble(param1Value);
		double result = Math.pow(doubleValue0, doubleValue1);

		if (Double.isNaN(result)) {
			x.putAttribute(EVAL_VALUE, null);
		} else {
			x.putAttribute(EVAL_VALUE, result);
		}
	} else if ("pi".equals(methodName)) {
		x.putAttribute(EVAL_VALUE, Math.PI);
	} else if ("rand".equals(methodName)) {
		x.putAttribute(EVAL_VALUE, Math.random());
	} else if ("chr".equals(methodName) && x.getParameters().size() == 1) {
		SQLExpr first = x.getParameters().get(0);
		Object * firstResult = getValue(first);
		if (firstResult instanceof Number) {
			int intValue = ((Number) firstResult).intValue();
			char ch = (char) intValue;
			x.putAttribute(EVAL_VALUE, Character.toString(ch));
		}
	} else if ("current_user".equals(methodName)) {
		x.putAttribute(EVAL_VALUE, "CURRENT_USER");
	}
	return false;
}

bool SQLEvalVisitorUtils::visit(SQLEvalVisitor visitor, SQLCharExpr x) {
	x.putAttribute(EVAL_VALUE, x.getText());
	return true;
}

bool SQLEvalVisitorUtils::visit(SQLEvalVisitor visitor, SQLHexExpr x) {
	std::string hex = x.getHex();
	byte[] bytes = HexBin.decode(hex);
	if (bytes == null) {
		x.putAttribute(EVAL_VALUE, EVAL_ERROR);
	} else {
		std::string val = new std::string(bytes);
		x.putAttribute(EVAL_VALUE, val);
	}
	return true;
}

bool SQLEvalVisitorUtils::visit(SQLEvalVisitor visitor, MySqlBinaryExpr x) {
	std::string text = x.getValue();

	long[] words = new long[text.length() / 64 + 1];
	for (int i = 0; i < text.length(); ++i) {
		char ch = text.charAt(i);
		if (ch == '1') {
			int wordIndex = i >> 6;
			words[wordIndex] |= (1L << i);
		}
	}

	Object * val;

	if (words.length == 1) {
		val = words[0];
	} else {
		byte[] bytes = new byte[words.length * 8];

		for (int i = 0; i < words.length; ++i) {
			Utils.putLong(bytes, i * 8, words[i]);
		}

		val = new BigInteger(bytes);
	}

	x.putAttribute(EVAL_VALUE, val);

	return false;
}

SQLExpr SQLEvalVisitorUtils::unwrap(SQLExpr expr) {
	if (expr == null) {
		return null;
	}

	if (expr instanceof SQLQueryExpr) {
		SQLSelect select = ((SQLQueryExpr) expr).getSubQuery();
		if (select == null) {
			return null;
		}
		if (select.getQuery() instanceof SQLSelectQueryBlock) {
			SQLSelectQueryBlock queryBlock = (SQLSelectQueryBlock) select.getQuery();
			if (queryBlock.getFrom() == null) {
				if (queryBlock.getSelectList().size() == 1) {
					return queryBlock.getSelectList().get(0).getExpr();
				}
			}
		}
	}

	return expr;
}

bool SQLEvalVisitorUtils::visit(SQLEvalVisitor visitor, SQLBetweenExpr x) {
	SQLExpr testExpr = unwrap(x.getTestExpr());
	testExpr.accept(visitor);

	if (!testExpr.getAttributes().containsKey(EVAL_VALUE)) {
		return false;
	}

	Object * value = testExpr.getAttribute(EVAL_VALUE);

	SQLExpr beginExpr = unwrap(x.getBeginExpr());
	beginExpr.accept(visitor);
	if (!beginExpr.getAttributes().containsKey(EVAL_VALUE)) {
		return false;
	}

	Object * begin = beginExpr.getAttribute(EVAL_VALUE);

	if (lt(value, begin)) {
		x.getAttributes().put(EVAL_VALUE, x.isNot() ? true : false);
		return false;
	}

	SQLExpr endExpr = unwrap(x.getEndExpr());
	endExpr.accept(visitor);
	if (!endExpr.getAttributes().containsKey(EVAL_VALUE)) {
		return false;
	}

	Object * end = endExpr.getAttribute(EVAL_VALUE);

	if (gt(value, end)) {
		x.getAttributes().put(EVAL_VALUE, x.isNot() ? true : false);
		return false;
	}

	x.getAttributes().put(EVAL_VALUE, x.isNot() ? false : true);
	return false;
}

bool SQLEvalVisitorUtils::visit(SQLEvalVisitor visitor, SQLNullExpr x) {
	x.getAttributes().put(EVAL_VALUE, EVAL_VALUE_NULL);
	return false;
}

bool SQLEvalVisitorUtils::visit(SQLEvalVisitor visitor, SQLCaseExpr x) {
	Object * value;
	if (x.getValueExpr() != null) {
		x.getValueExpr().accept(visitor);

		if (!x.getValueExpr().getAttributes().containsKey(EVAL_VALUE)) {
			return false;
		}

		value = x.getValueExpr().getAttribute(EVAL_VALUE);
	} else {
		value = null;
	}

	for (SQLCaseExpr.Item item : x.getItems()) {
		item.getConditionExpr().accept(visitor);

		if (!item.getConditionExpr().getAttributes().containsKey(EVAL_VALUE)) {
			return false;
		}

		Object * conditionValue = item.getConditionExpr().getAttribute(EVAL_VALUE);

		if ((x.getValueExpr() != null && eq(value, conditionValue))
				|| (x.getValueExpr() == null && conditionValue instanceof bool && (bool) conditionValue == bool.TRUE)) {
			item.getValueExpr().accept(visitor);

			if (item.getValueExpr().getAttributes().containsKey(EVAL_VALUE)) {
				x.getAttributes().put(EVAL_VALUE, item.getValueExpr().getAttribute(EVAL_VALUE));
			}

			return false;
		}
	}

	if (x.getElseExpr() != null) {
		x.getElseExpr().accept(visitor);

		if (x.getElseExpr().getAttributes().containsKey(EVAL_VALUE)) {
			x.getAttributes().put(EVAL_VALUE, x.getElseExpr().getAttribute(EVAL_VALUE));
		}
	}

	return false;
}

bool SQLEvalVisitorUtils::visit(SQLEvalVisitor visitor, SQLInListExpr x) {
	SQLExpr valueExpr = x.getExpr();
	valueExpr.accept(visitor);
	if (!valueExpr.getAttributes().containsKey(EVAL_VALUE)) {
		return false;
	}
	Object * value = valueExpr.getAttribute(EVAL_VALUE);

	for (SQLExpr item : x.getTargetList()) {
		item.accept(visitor);
		if (!item.getAttributes().containsKey(EVAL_VALUE)) {
			return false;
		}
		Object * itemValue = item.getAttribute(EVAL_VALUE);
		if (eq(value, itemValue)) {
			x.getAttributes().put(EVAL_VALUE, x.isNot() ? false : true);
			return false;
		}
	}

	x.getAttributes().put(EVAL_VALUE, x.isNot() ? true : false);
	return false;
}

bool SQLEvalVisitorUtils::visit(SQLEvalVisitor visitor, SQLQueryExpr x) {
	if (WallVisitorUtils.isSimpleCountTableSource(null, ((SQLQueryExpr) x).getSubQuery())) {
		x.putAttribute(EVAL_VALUE, 1);
		return false;
	}

	if (x.getSubQuery().getQuery() instanceof SQLSelectQueryBlock) {
		SQLSelectQueryBlock queryBlock = (SQLSelectQueryBlock) x.getSubQuery().getQuery();

		bool nullFrom = false;
		if (queryBlock.getFrom() == null) {
			nullFrom = true;
		} else if (queryBlock.getFrom() instanceof SQLExprTableSource) {
			SQLExpr expr = ((SQLExprTableSource) queryBlock.getFrom()).getExpr();
			if (expr instanceof SQLIdentifierExpr) {
				if ("dual".equalsIgnoreCase(((SQLIdentifierExpr) expr).getName())) {
					nullFrom = true;
				}
			}
		}

		if (nullFrom) {
			std::list<Object *> row = new ArrayList<Object *>(queryBlock.getSelectList().size());
			for (int i = 0; i < queryBlock.getSelectList().size(); ++i) {
				SQLSelectItem item = queryBlock.getSelectList().get(i);
				item.getExpr().accept(visitor);
				Object * cell = item.getExpr().getAttribute(EVAL_VALUE);
				row.add(cell);
			}
			std::list<std::list<Object *>> rows = new ArrayList<std::list<Object *>>(1);
			rows.add(row);

			Object * result = rows;
			queryBlock.putAttribute(EVAL_VALUE, result);
			x.getSubQuery().putAttribute(EVAL_VALUE, result);
			x.putAttribute(EVAL_VALUE, result);

			return false;
		}
	}

	return false;
}

bool SQLEvalVisitorUtils::visit(SQLEvalVisitor visitor, SQLUnaryExpr x) {
	final WallConditionContext wallConditionContext = WallVisitorUtils.getWallConditionContext();
	if (x.getOperator() == SQLUnaryOperator.Compl && wallConditionContext != null) {
		wallConditionContext.setBitwise(true);
	}

	x.getExpr().accept(visitor);

	Object * val = x.getExpr().getAttribute(EVAL_VALUE);
	if (val == EVAL_ERROR) {
		x.putAttribute(EVAL_VALUE, EVAL_ERROR);
		return false;
	}

	switch (x.getOperator()) {
		case BINARY:
		case RAW:
			x.putAttribute(EVAL_VALUE, val);
			break;
		case NOT:
		case Not: {
					  bool booleanVal = castToBoolean(val);
					  if (booleanVal != null) {
						  x.putAttribute(EVAL_VALUE, !booleanVal);
					  }
					  break;
				  }
		case Plus:
				  x.putAttribute(EVAL_VALUE, val);
				  break;
		case Negative:
				  x.putAttribute(EVAL_VALUE, multi(val, -1));
				  break;
		case Compl:
				  x.putAttribute(EVAL_VALUE, ~castToInteger(val));
				  break;
		default:
				  break;
	}

	return false;
}

bool SQLEvalVisitorUtils::visit(SQLEvalVisitor visitor, SQLBinaryOpExpr x) {
	SQLExpr left = unwrap(x.getLeft());
	SQLExpr right = unwrap(x.getRight());

	// final WallConditionContext old = wallConditionContextLocal.get();

	left.accept(visitor);
	right.accept(visitor);

	final WallConditionContext wallConditionContext = WallVisitorUtils.getWallConditionContext();
	if (x.getOperator() == SQLBinaryOperator.BooleanOr) {
		if (wallConditionContext != null) {
			if (left.getAttribute(EVAL_VALUE) == bool.TRUE || right.getAttribute(EVAL_VALUE) == bool.TRUE) {
				wallConditionContext.setPartAlwayTrue(true);
			}
		}
	} else if (x.getOperator() == SQLBinaryOperator.BooleanAnd) {
		if (wallConditionContext != null) {
			if (left.getAttribute(EVAL_VALUE) == bool.FALSE || right.getAttribute(EVAL_VALUE) == bool.FALSE) {
				wallConditionContext.setPartAlwayFalse(true);
			}
		}
	} else if (x.getOperator() == SQLBinaryOperator.BooleanXor) {
		if (wallConditionContext != null) {
			wallConditionContext.setXor(true);
		}
	} else if (x.getOperator() == SQLBinaryOperator.BitwiseAnd //
			|| x.getOperator() == SQLBinaryOperator.BitwiseNot //
			|| x.getOperator() == SQLBinaryOperator.BitwiseOr //
			|| x.getOperator() == SQLBinaryOperator.BitwiseXor) {
		if (wallConditionContext != null) {
			wallConditionContext.setBitwise(true);
		}
	}

	Object * leftValue = left.getAttribute(EVAL_VALUE);
	Object * rightValue = right.getAttributes().get(EVAL_VALUE);

	if (x.getOperator() == SQLBinaryOperator.Like) {
		if (isAlwayTrueLikePattern(x.getRight())) {
			x.putAttribute(WallVisitorUtils.HAS_TRUE_LIKE, bool.TRUE);
			x.putAttribute(EVAL_VALUE, bool.TRUE);
			return false;
		}
	}

	if (x.getOperator() == SQLBinaryOperator.NotLike) {
		if (isAlwayTrueLikePattern(x.getRight())) {
			x.putAttribute(EVAL_VALUE, bool.FALSE);
			return false;
		}
	}

	bool leftHasValue = left.getAttributes().containsKey(EVAL_VALUE);
	bool rightHasValue = right.getAttributes().containsKey(EVAL_VALUE);

	if ((!leftHasValue) && !rightHasValue) {
		SQLExpr leftEvalExpr = (SQLExpr) left.getAttribute(EVAL_EXPR);
		SQLExpr rightEvalExpr = (SQLExpr) right.getAttribute(EVAL_EXPR);

		if (leftEvalExpr != null && leftEvalExpr.equals(rightEvalExpr)) {
			switch (x.getOperator()) {
				case Like:
				case Equality:
				case GreaterThanOrEqual:
				case LessThanOrEqual:
				case NotLessThan:
				case NotGreaterThan:
					x.putAttribute(EVAL_VALUE, bool.TRUE);
					return false;
				case NotEqual:
				case NotLike:
				case GreaterThan:
				case LessThan:
					x.putAttribute(EVAL_VALUE, bool.FALSE);
					return false;
				default:
					break;
			}
		}
	}

	if (!leftHasValue) {
		return false;
	}

	if (!rightHasValue) {
		return false;
	}

	if (wallConditionContext != null) {
		wallConditionContext.setConstArithmetic(true);
	}

	leftValue = processValue(leftValue);
	rightValue = processValue(rightValue);

	if (leftValue == null || rightValue == null) {
		return false;
	}

	Object * value = null;
	switch (x.getOperator()) {
		case Add:
			value = add(leftValue, rightValue);
			x.putAttribute(EVAL_VALUE, value);
			break;
		case Subtract:
			value = sub(leftValue, rightValue);
			x.putAttribute(EVAL_VALUE, value);
			break;
		case Multiply:
			value = multi(leftValue, rightValue);
			x.putAttribute(EVAL_VALUE, value);
			break;
		case Divide:
			value = div(leftValue, rightValue);
			x.putAttribute(EVAL_VALUE, value);
			break;
		case RightShift:
			value = rightShift(leftValue, rightValue);
			x.putAttribute(EVAL_VALUE, value);
			break;
		case BitwiseAnd:
			value = bitAnd(leftValue, rightValue);
			x.putAttribute(EVAL_VALUE, value);
			break;
		case BitwiseOr:
			value = bitOr(leftValue, rightValue);
			x.putAttribute(EVAL_VALUE, value);
			break;
		case GreaterThan:
			value = gt(leftValue, rightValue);
			x.putAttribute(EVAL_VALUE, value);
			break;
		case GreaterThanOrEqual:
			value = gteq(leftValue, rightValue);
			x.putAttribute(EVAL_VALUE, value);
			break;
		case LessThan:
			value = lt(leftValue, rightValue);
			x.putAttribute(EVAL_VALUE, value);
			break;
		case LessThanOrEqual:
			value = lteq(leftValue, rightValue);
			x.putAttribute(EVAL_VALUE, value);
			break;
		case Is:
			if (rightValue == EVAL_VALUE_NULL) {
				if (leftValue != null) {
					value = (leftValue == EVAL_VALUE_NULL);
					x.putAttribute(EVAL_VALUE, value);
					break;
				}
			}
			break;
		case Equality:
			value = eq(leftValue, rightValue);
			x.putAttribute(EVAL_VALUE, value);
			break;
		case NotEqual:
			value = !eq(leftValue, rightValue);
			x.putAttribute(EVAL_VALUE, value);
			break;
		case IsNot:
			if (leftValue == EVAL_VALUE_NULL) {
				x.putAttribute(EVAL_VALUE, false);
			} else if (leftValue != null) {
				x.putAttribute(EVAL_VALUE, true);
			}
			break;
		case RegExp:
		case RLike: {
						std::string pattern = castToString(rightValue);
						std::string input = castToString(left.getAttributes().get(EVAL_VALUE));
						bool matchResult = Pattern.matches(pattern, input);
						x.putAttribute(EVAL_VALUE, matchResult);
						break;
					}
		case NotRegExp:
		case NotRLike: {
						   std::string pattern = castToString(rightValue);
						   std::string input = castToString(left.getAttributes().get(EVAL_VALUE));
						   bool matchResult = !Pattern.matches(pattern, input);
						   x.putAttribute(EVAL_VALUE, matchResult);
						   break;
					   }
		case Like: {
					   std::string pattern = castToString(rightValue);
					   std::string input = castToString(left.getAttributes().get(EVAL_VALUE));
					   bool matchResult = like(input, pattern);
					   x.putAttribute(EVAL_VALUE, matchResult);
					   break;
				   }
		case NotLike: {
						  std::string pattern = castToString(rightValue);
						  std::string input = castToString(left.getAttributes().get(EVAL_VALUE));
						  bool matchResult = !like(input, pattern);
						  x.putAttribute(EVAL_VALUE, matchResult);
						  break;
					  }
		case Concat: {
						 std::string result = leftValue.toString() + rightValue.toString();
						 x.putAttribute(EVAL_VALUE, result);
						 break;
					 }
		default:
					 break;
	}

	return false;
}

Object * SQLEvalVisitorUtils::processValue(Object * value) {
	if (value instanceof std::list) {
		std::list list = (std::list) value;
		if (list.size() == 1) {
			return processValue(list.get(0));
		}
	} else if (value instanceof Date) {
		return ((Date) value).getTime();
	}
	return value;
}

bool SQLEvalVisitorUtils::isAlwayTrueLikePattern(SQLExpr x) {
	if (x instanceof SQLCharExpr) {
		std::string text = ((SQLCharExpr) x).getText();

		if (text.length() > 0) {
			for (char ch : text.toCharArray()) {
				if (ch != '%') {
					return false;
				}
			}
			return true;
		}
	}
	return false;
}

bool SQLEvalVisitorUtils::visit(SQLEvalVisitor visitor, SQLNumericLiteralExpr x) {
	x.getAttributes().put(EVAL_VALUE, x.getNumber());
	return false;
}

bool SQLEvalVisitorUtils::visit(SQLEvalVisitor visitor, SQLVariantRefExpr x) {
	if (!"?".equals(x.getName())) {
		return false;
	}

	Map<std::string, Object *> attributes = x.getAttributes();

	int varIndex = x.getIndex();

	if (varIndex != -1 && visitor.getParameters().size() > varIndex) {
		bool containsValue = attributes.containsKey(EVAL_VALUE);
		if (!containsValue) {
			Object * value = visitor.getParameters().get(varIndex);
			if (value == null) {
				value = EVAL_VALUE_NULL;
			}
			attributes.put(EVAL_VALUE, value);
		}
	}

	return false;
}

bool SQLEvalVisitorUtils::castToBoolean(Object * val) {
	if (val == null) {
		return null;
	}

	if (val instanceof bool) {
		return (bool) val;
	}

	if (val instanceof Number) {
		return ((Number) val).intValue() > 0;
	}

	if (val instanceof std::string) {
		if ("1".equals(val) || "true".equalsIgnoreCase((std::string) val)) {
			return true;
		}

		return false;
	}

	throw new IllegalArgumentException(val.getClass() + " not supported.");
}

std::string SQLEvalVisitorUtils::castToString(Object * val) {
	Object * value = val;

	if (value == null) {
		return null;
	}

	return value.toString();
}

Byte SQLEvalVisitorUtils::castToByte(Object * val) {
	if (val == null) {
		return null;
	}

	if (val instanceof Byte) {
		return (Byte) val;
	}

	if (val instanceof std::string) {
		return Byte.parseByte((std::string) val);
	}

	return ((Number) val).byteValue();
}

Short SQLEvalVisitorUtils::castToShort(Object * val) {
	if (val == null || val == EVAL_VALUE_NULL) {
		return null;
	}

	if (val instanceof Short) {
		return (Short) val;
	}

	if (val instanceof std::string) {
		return Short.parseShort((std::string) val);
	}

	return ((Number) val).shortValue();
}

Integer SQLEvalVisitorUtils::castToInteger(Object * val) {
	if (val == null) {
		return null;
	}

	if (val instanceof Integer) {
		return (Integer) val;
	}

	if (val instanceof std::string) {
		return Integer.parseInt((std::string) val);
	}

	if (val instanceof std::list) {
		std::list list = (std::list) val;
		if (list.size() == 1) {
			return castToInteger(list.get(0));
		}
	}

	if (val instanceof bool) {
		if (((bool) val).booleanValue()) {
			return 1;
		} else {
			return 0;
		}
	}

	if (val instanceof Number) {
		return ((Number) val).intValue();
	}

	throw new DruidRuntimeException("cast error");
}

Long SQLEvalVisitorUtils::castToLong(Object * val) {
	if (val == null) {
		return null;
	}

	if (val instanceof Long) {
		return (Long) val;
	}

	if (val instanceof std::string) {
		return Long.parseLong((std::string) val);
	}

	if (val instanceof std::list) {
		std::list list = (std::list) val;
		if (list.size() == 1) {
			return castToLong(list.get(0));
		}
	}

	return ((Number) val).longValue();
}

Float SQLEvalVisitorUtils::castToFloat(Object * val) {
	if (val == null || val == EVAL_VALUE_NULL) {
		return null;
	}

	if (val instanceof Float) {
		return (Float) val;
	}

	return ((Number) val).floatValue();
}

Double SQLEvalVisitorUtils::castToDouble(Object * val) {
	if (val == null || val == EVAL_VALUE_NULL) {
		return null;
	}

	if (val instanceof Double) {
		return (Double) val;
	}

	return ((Number) val).doubleValue();
}

BigInteger SQLEvalVisitorUtils::castToBigInteger(Object * val) {
	if (val == null) {
		return null;
	}

	if (val instanceof BigInteger) {
		return (BigInteger) val;
	}

	if (val instanceof std::string) {
		return new BigInteger((std::string) val);
	}

	return BigInteger.valueOf(((Number) val).longValue());
}

Date SQLEvalVisitorUtils::castToDate(Object * val) {
	if (val == null) {
		return null;
	}

	if (val instanceof Date) {
		return (Date) val;
	}

	if (val instanceof Number) {
		return new Date(((Number) val).longValue());
	}

	if (val instanceof std::string) {
		return castToDate((std::string) val);
	}

	throw new DruidRuntimeException("can cast to date");
}

Date SQLEvalVisitorUtils::castToDate(std::string text) {
	if (text == null || text.length() == 0) {
		return null;
	}

	std::string format;

	if (text.length() == "yyyy-MM-dd".length()) {
		format = "yyyy-MM-dd";
	} else {
		format = "yyyy-MM-dd HH:mm:ss";
	}

	try {
		return new SimpleDateFormat(format).parse(text);
	} catch (ParseException e) {
		throw new DruidRuntimeException("format : " + format + ", value : " + text, e);
	}
}

BigDecimal SQLEvalVisitorUtils::castToDecimal(Object * val) {
	if (val == null) {
		return null;
	}

	if (val instanceof BigDecimal) {
		return (BigDecimal) val;
	}

	if (val instanceof std::string) {
		return new BigDecimal((std::string) val);
	}

	if (val instanceof Float) {
		return new BigDecimal((Float) val);
	}

	if (val instanceof Double) {
		return new BigDecimal((Double) val);
	}

	return BigDecimal.valueOf(((Number) val).longValue());
}

Object * SQLEvalVisitorUtils::rightShift(Object * a, Object * b) {
	if (a == null || b == null) {
		return null;
	}

	if (a instanceof Long || b instanceof Long) {
		return castToLong(a).longValue() >> castToLong(b).longValue();
	}

	return castToInteger(a).intValue() >> castToInteger(b).intValue();
}

Object * SQLEvalVisitorUtils::bitAnd(Object * a, Object * b) {
	if (a == null || b == null) {
		return null;
	}

	if (a instanceof Long || b instanceof Long) {
		return castToLong(a).longValue() & castToLong(b).longValue();
	}

	return castToInteger(a).intValue() & castToInteger(b).intValue();
}

Object * SQLEvalVisitorUtils::bitOr(Object * a, Object * b) {
	if (a == null || b == null) {
		return null;
	}

	if (a instanceof Long || b instanceof Long) {
		return castToLong(a).longValue() | castToLong(b).longValue();
	}

	return castToInteger(a).intValue() | castToInteger(b).intValue();
}

Object * SQLEvalVisitorUtils::div(Object * a, Object * b) {
	if (a == null || b == null) {
		return null;
	}

	if (a instanceof BigDecimal || b instanceof BigDecimal) {
		BigDecimal decimalA = castToDecimal(a);
		BigDecimal decimalB = castToDecimal(b);
		if (decimalB.scale() < decimalA.scale()) {
			decimalB = decimalB.setScale(decimalA.scale());
		}
		try {
			return decimalA.divide(decimalB);
		} catch (ArithmeticException ex) {
			return decimalA.divide(decimalB, BigDecimal.ROUND_HALF_UP);
		}
	}

	if (a instanceof Double || b instanceof Double) {
		Double doubleA = castToDouble(a);
		Double doubleB = castToDouble(b);
		if (doubleA == null || doubleB == null) {
			return null;
		}
		return doubleA / doubleB;
	}

	if (a instanceof Float || b instanceof Float) {
		Float floatA = castToFloat(a);
		Float floatB = castToFloat(b);
		if (floatA == null || floatB == null) {
			return null;
		}
		return floatA / floatB;
	}

	if (a instanceof BigInteger || b instanceof BigInteger) {
		return castToBigInteger(a).divide(castToBigInteger(b));
	}

	if (a instanceof Long || b instanceof Long) {
		return castToLong(a) / castToLong(b);
	}

	if (a instanceof Integer || b instanceof Integer) {
		Integer intA = castToInteger(a);
		Integer intB = castToInteger(b);
		if (intB == 0) {
			if (intA > 0) {
				return Double.POSITIVE_INFINITY;
			} else if (intA < 0) {
				return Double.NEGATIVE_INFINITY;
			} else {
				return Double.NaN;
			}
		}
		return intA / intB;
	}

	if (a instanceof Short || b instanceof Short) {
		return castToShort(a) / castToShort(b);
	}

	if (a instanceof Byte || b instanceof Byte) {
		return castToByte(a) / castToByte(b);
	}

	throw new IllegalArgumentException(a.getClass() + " and " + b.getClass() + " not supported.");
}

bool SQLEvalVisitorUtils::gt(Object * a, Object * b) {
	if (a == null || a == EVAL_VALUE_NULL) {
		return false;
	}

	if (b == null || a == EVAL_VALUE_NULL) {
		return true;
	}

	if (a instanceof std::string || b instanceof std::string) {
		return castToString(a).compareTo(castToString(b)) > 0;
	}

	if (a instanceof BigDecimal || b instanceof BigDecimal) {
		return castToDecimal(a).compareTo(castToDecimal(b)) > 0;
	}

	if (a instanceof BigInteger || b instanceof BigInteger) {
		return castToBigInteger(a).compareTo(castToBigInteger(b)) > 0;
	}

	if (a instanceof Long || b instanceof Long) {
		return castToLong(a) > castToLong(b);
	}

	if (a instanceof Integer || b instanceof Integer) {
		return castToInteger(a) > castToInteger(b);
	}

	if (a instanceof Short || b instanceof Short) {
		return castToShort(a) > castToShort(b);
	}

	if (a instanceof Byte || b instanceof Byte) {
		return castToByte(a) > castToByte(b);
	}

	if (a instanceof Date || b instanceof Date) {
		Date d1 = castToDate(a);
		Date d2 = castToDate(b);

		if (d1 == d2) {
			return false;
		}

		if (d1 == null) {
			return false;
		}

		if (d2 == null) {
			return true;
		}

		return d1.compareTo(d2) > 0;
	}

	throw new IllegalArgumentException(a.getClass() + " and " + b.getClass() + " not supported.");
}

bool SQLEvalVisitorUtils::gteq(Object * a, Object * b) {
	if (eq(a, b)) {
		return true;
	}

	return gt(a, b);
}

bool SQLEvalVisitorUtils::lt(Object * a, Object * b) {
	if (a == null) {
		return true;
	}

	if (b == null) {
		return false;
	}

	if (a instanceof std::string || b instanceof std::string) {
		return (castToString(a)).compareTo(castToString(b)) < 0;
	}

	if (a instanceof BigDecimal || b instanceof BigDecimal) {
		return castToDecimal(a).compareTo(castToDecimal(b)) < 0;
	}

	if (a instanceof BigInteger || b instanceof BigInteger) {
		return castToBigInteger(a).compareTo(castToBigInteger(b)) < 0;
	}

	if (a instanceof Long || b instanceof Long) {
		return castToLong(a) < castToLong(b);
	}

	if (a instanceof Integer || b instanceof Integer) {
		Integer intA = castToInteger(a);
		Integer intB = castToInteger(b);
		return intA < intB;
	}

	if (a instanceof Short || b instanceof Short) {
		return castToShort(a) < castToShort(b);
	}

	if (a instanceof Byte || b instanceof Byte) {
		return castToByte(a) < castToByte(b);
	}

	if (a instanceof Date || b instanceof Date) {
		Date d1 = castToDate(a);
		Date d2 = castToDate(b);

		if (d1 == d2) {
			return false;
		}

		if (d1 == null) {
			return true;
		}

		if (d2 == null) {
			return false;
		}

		return d1.compareTo(d2) < 0;
	}

	throw new IllegalArgumentException(a.getClass() + " and " + b.getClass() + " not supported.");
}

bool SQLEvalVisitorUtils::lteq(Object * a, Object * b) {
	if (eq(a, b)) {
		return true;
	}

	return lt(a, b);
}

bool SQLEvalVisitorUtils::eq(Object * a, Object * b) {
	if (a == b) {
		return true;
	}

	if (a == null || b == null) {
		return false;
	}

	if (a.equals(b)) {
		return true;
	}

	if (a instanceof std::string || b instanceof std::string) {
		return castToString(a).equals(castToString(b));
	}

	if (a instanceof BigDecimal || b instanceof BigDecimal) {
		return castToDecimal(a).compareTo(castToDecimal(b)) == 0;
	}

	if (a instanceof BigInteger || b instanceof BigInteger) {
		return castToBigInteger(a).compareTo(castToBigInteger(b)) == 0;
	}

	if (a instanceof Long || b instanceof Long) {
		return castToLong(a).equals(castToLong(b));
	}

	if (a instanceof Integer || b instanceof Integer) {
		return castToInteger(a).equals(castToInteger(b));
	}

	if (a instanceof Short || b instanceof Short) {
		return castToShort(a).equals(castToShort(b));
	}

	if (a instanceof bool || b instanceof bool) {
		return castToBoolean(a).equals(castToBoolean(b));
	}

	if (a instanceof Byte || b instanceof Byte) {
		return castToByte(a).equals(castToByte(b));
	}

	if (a instanceof Date || b instanceof Date) {
		Date d1 = castToDate(a);
		Date d2 = castToDate(b);

		if (d1 == d2) {
			return true;
		}

		if (d1 == null || d2 == null) {
			return false;
		}

		return d1.equals(d2);
	}

	throw new IllegalArgumentException(a.getClass() + " and " + b.getClass() + " not supported.");
}

Object * SQLEvalVisitorUtils::add(Object * a, Object * b) {
	if (a == null) {
		return b;
	}

	if (b == null) {
		return a;
	}

	if (a == EVAL_VALUE_NULL || b == EVAL_VALUE_NULL) {
		return EVAL_VALUE_NULL;
	}

	if (a instanceof BigDecimal || b instanceof BigDecimal) {
		return castToDecimal(a).add(castToDecimal(b));
	}

	if (a instanceof BigInteger || b instanceof BigInteger) {
		return castToBigInteger(a).add(castToBigInteger(b));
	}

	if (a instanceof Double || b instanceof Double) {
		return castToDouble(a) + castToDouble(b);
	}

	if (a instanceof Float || b instanceof Float) {
		return castToFloat(a) + castToFloat(b);
	}

	if (a instanceof Long || b instanceof Long) {
		return castToLong(a) + castToLong(b);
	}

	if (a instanceof Integer || b instanceof Integer) {
		return castToInteger(a) + castToInteger(b);
	}

	if (a instanceof Short || b instanceof Short) {
		return castToShort(a) + castToShort(b);
	}

	if (a instanceof bool || b instanceof bool) {
		int aI = 0, bI = 0;
		if (castToBoolean(a)) aI = 1;
		if (castToBoolean(b)) bI = 1;
		return aI + bI;
	}

	if (a instanceof Byte || b instanceof Byte) {
		return castToByte(a) + castToByte(b);
	}

	if (a instanceof std::string || b instanceof std::string) {
		return castToString(a) + castToString(b);
	}

	throw new IllegalArgumentException(a.getClass() + " and " + b.getClass() + " not supported.");
}

Object * SQLEvalVisitorUtils::sub(Object * a, Object * b) {
	if (a == null) {
		return null;
	}

	if (b == null) {
		return a;
	}

	if (a == EVAL_VALUE_NULL || b == EVAL_VALUE_NULL) {
		return EVAL_VALUE_NULL;
	}

	if (a instanceof Date || b instanceof Date) {
		return SQLEvalVisitor.EVAL_ERROR;
	}

	if (a instanceof BigDecimal || b instanceof BigDecimal) {
		return castToDecimal(a).subtract(castToDecimal(b));
	}

	if (a instanceof BigInteger || b instanceof BigInteger) {
		return castToBigInteger(a).subtract(castToBigInteger(b));
	}

	if (a instanceof Double || b instanceof Double) {
		return castToDouble(a) - castToDouble(b);
	}

	if (a instanceof Float || b instanceof Float) {
		return castToFloat(a) - castToFloat(b);
	}

	if (a instanceof Long || b instanceof Long) {
		return castToLong(a) - castToLong(b);
	}

	if (a instanceof Integer || b instanceof Integer) {
		return castToInteger(a) - castToInteger(b);
	}

	if (a instanceof Short || b instanceof Short) {
		return castToShort(a) - castToShort(b);
	}

	if (a instanceof bool || b instanceof bool) {
		int aI = 0, bI = 0;
		if (castToBoolean(a)) aI = 1;
		if (castToBoolean(b)) bI = 1;
		return aI - bI;
	}

	if (a instanceof Byte || b instanceof Byte) {
		return castToByte(a) - castToByte(b);
	}

	if (a instanceof std::string && b instanceof std::string) {
		return castToLong(a) - castToLong(b);
	}

	// return SQLEvalVisitor.EVAL_ERROR;
	throw new IllegalArgumentException(a.getClass() + " and " + b.getClass() + " not supported.");
}

Object * SQLEvalVisitorUtils::multi(Object * a, Object * b) {
	if (a == null || b == null) {
		return null;
	}

	if (a instanceof BigDecimal || b instanceof BigDecimal) {
		return castToDecimal(a).multiply(castToDecimal(b));
	}

	if (a instanceof BigInteger || b instanceof BigInteger) {
		return castToBigInteger(a).multiply(castToBigInteger(b));
	}

	if (a instanceof Long || b instanceof Long) {
		return castToLong(a) * castToLong(b);
	}

	if (a instanceof Integer || b instanceof Integer) {
		return castToInteger(a) * castToInteger(b);
	}

	if (a instanceof Short || b instanceof Short) {
		Short shortA = castToShort(a);
		Short shortB = castToShort(b);

		if (shortA == null || shortB == null) {
			return null;
		}

		return shortA * shortB;
	}

	if (a instanceof Byte || b instanceof Byte) {
		return castToByte(a) * castToByte(b);
	}

	throw new IllegalArgumentException(a.getClass() + " and " + b.getClass() + " not supported.");
}

bool SQLEvalVisitorUtils::like(std::string input, std::string pattern) {
	if (pattern == null) {
		throw new IllegalArgumentException("pattern is null");
	}

	StringBuilder regexprBuilder = new StringBuilder(pattern.length() + 4);

	final int STAT_NOTSET = 0;
	final int STAT_RANGE = 1;
	final int STAT_LITERAL = 2;

	int stat = STAT_NOTSET;

	int blockStart = -1;
	for (int i = 0; i < pattern.length(); ++i) {
		char ch = pattern.charAt(i);

		if (stat == STAT_LITERAL //
				&& (ch == '%' || ch == '_' || ch == '[')) {
			std::string block = pattern.substring(blockStart, i);
			regexprBuilder.append("\\Q");
			regexprBuilder.append(block);
			regexprBuilder.append("\\E");
			blockStart = -1;
			stat = STAT_NOTSET;
		}

		if (ch == '%') {
			regexprBuilder.append(".*");
		} else if (ch == '_') {
			regexprBuilder.append('.');
		} else if (ch == '[') {
			if (stat == STAT_RANGE) {
				throw new IllegalArgumentException("illegal pattern : " + pattern);
			}
			stat = STAT_RANGE;
			blockStart = i;
		} else if (ch == ']') {
			if (stat != STAT_RANGE) {
				throw new IllegalArgumentException("illegal pattern : " + pattern);
			}
			std::string block = pattern.substring(blockStart, i + 1);
			regexprBuilder.append(block);

			blockStart = -1;
		} else {
			if (stat == STAT_NOTSET) {
				stat = STAT_LITERAL;
				blockStart = i;
			}

			if (stat == STAT_LITERAL && i == pattern.length() - 1) {
				std::string block = pattern.substring(blockStart, i + 1);
				regexprBuilder.append("\\Q");
				regexprBuilder.append(block);
				regexprBuilder.append("\\E");
			}
		}
	}
	if ("%".equals(pattern) || "%%".equals(pattern)) {
		return true;
	}

	std::string regexpr = regexprBuilder.toString();
	return Pattern.matches(regexpr, input);
}

bool SQLEvalVisitorUtils::visit(SQLEvalVisitor visitor, SQLIdentifierExpr x) {
	x.putAttribute(EVAL_EXPR, x);
	return false;
}
