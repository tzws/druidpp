

SQLStatementParser SQLParserUtils::createSQLStatementParser(std::string sql, std::string dbType) {
	if (JdbcUtils.ORACLE.equals(dbType) || JdbcUtils.ALI_ORACLE.equals(dbType)) {
		return new OracleStatementParser(sql);
	}

	if (JdbcUtils.MYSQL.equals(dbType)) {
		return new MySqlStatementParser(sql);
	}

	if (JdbcUtils.MARIADB.equals(dbType)) {
		return new MySqlStatementParser(sql);
	}

	if (JdbcUtils.POSTGRESQL.equals(dbType)) {
		return new PGSQLStatementParser(sql);
	}

	if (JdbcUtils.SQL_SERVER.equals(dbType) || JdbcUtils.JTDS.equals(dbType)) {
		return new SQLServerStatementParser(sql);
	}

	if (JdbcUtils.H2.equals(dbType)) {
		return new MySqlStatementParser(sql);
	}

	if (JdbcUtils.DB2.equals(dbType)) {
		return new DB2StatementParser(sql);
	}

	return new SQLStatementParser(sql);
}

SQLExprParser SQLParserUtils::createExprParser(std::string sql, std::string dbType) {
	if (JdbcUtils.ORACLE.equals(dbType) || JdbcUtils.ALI_ORACLE.equals(dbType)) {
		return new OracleExprParser(sql);
	}

	if (JdbcUtils.MYSQL.equals(dbType) || //
			JdbcUtils.MARIADB.equals(dbType) || //
			JdbcUtils.H2.equals(dbType)) {
		return new MySqlExprParser(sql);
	}

	if (JdbcUtils.POSTGRESQL.equals(dbType)) {
		return new PGExprParser(sql);
	}

	if (JdbcUtils.SQL_SERVER.equals(dbType) || JdbcUtils.JTDS.equals(dbType)) {
		return new SQLServerExprParser(sql);
	}

	if (JdbcUtils.DB2.equals(dbType)) {
		return new DB2ExprParser(sql);
	}

	if (JdbcUtils.ODPS.equals(dbType)) {
		return new OdpsExprParser(sql);
	}

	return new SQLExprParser(sql);
}

