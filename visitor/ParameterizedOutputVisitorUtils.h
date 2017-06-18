
#ifndef ParameterizedOutputVisitor_HEADER_H 
#define ParameterizedOutputVisitor_HEADER_H

#include <list>


//import com.alibaba.druid.sql.ast.SQLDataType;
//import com.alibaba.druid.sql.ast.SQLExpr;
//import com.alibaba.druid.sql.ast.SQLObject;
//import com.alibaba.druid.sql.ast.SQLStatement;
//import com.alibaba.druid.sql.ast.expr.SQLBinaryOpExpr;
//import com.alibaba.druid.sql.ast.expr.SQLBinaryOperator;
//import com.alibaba.druid.sql.ast.expr.SQLCharExpr;
//import com.alibaba.druid.sql.ast.expr.SQLInListExpr;
//import com.alibaba.druid.sql.ast.expr.SQLIntegerExpr;
//import com.alibaba.druid.sql.ast.expr.SQLLiteralExpr;
//import com.alibaba.druid.sql.ast.expr.SQLNCharExpr;
//import com.alibaba.druid.sql.ast.expr.SQLNullExpr;
//import com.alibaba.druid.sql.ast.expr.SQLNumberExpr;
//import com.alibaba.druid.sql.ast.expr.SQLVariantRefExpr;
//import com.alibaba.druid.sql.ast.statement.SQLAssignItem;
//import com.alibaba.druid.sql.ast.statement.SQLColumnDefinition;
//import com.alibaba.druid.sql.ast.statement.SQLSelectOrderByItem;
//import com.alibaba.druid.sql.dialect.db2.visitor.DB2ParameterizedOutputVisitor;
//import com.alibaba.druid.sql.dialect.mysql.visitor.MySqlParameterizedOutputVisitor;
//import com.alibaba.druid.sql.dialect.oracle.visitor.OracleParameterizedOutputVisitor;
//import com.alibaba.druid.sql.dialect.postgresql.visitor.PGParameterizedOutputVisitor;
//import com.alibaba.druid.sql.dialect.sqlserver.ast.SQLServerTop;
//import com.alibaba.druid.sql.dialect.sqlserver.visitor.SQLServerParameterizedOutputVisitor;
//import com.alibaba.druid.sql.parser.SQLParserUtils;
//import com.alibaba.druid.sql.parser.SQLStatementParser;
//import com.alibaba.druid.util.JdbcUtils;

class ParameterizedOutputVisitorUtils {

	public:
		static std::string ATTR_PARAMS_SKIP;

	public:
		static std::string parameterize(std::string sql, std::string dbType);

		static ParameterizedVisitor createParameterizedOutputVisitor(Appendable out, std::string dbType);

		static bool  visit(ParameterizedVisitor v, SQLInListExpr x);

		static bool  visit(ParameterizedVisitor v, SQLIntegerExpr x);

		static bool  visit(ParameterizedVisitor v, SQLNumberExpr x);

		static bool  visit(ParameterizedVisitor v, SQLCharExpr x);

		static bool  checkParameterize(SQLObject x);

		static bool  visit(ParameterizedVisitor v, SQLNCharExpr x);

		static bool  visit(ParameterizedVisitor v, SQLNullExpr x);

		static SQLBinaryOpExpr merge(ParameterizedVisitor v, SQLBinaryOpExpr x);

	private:
		static bool  mergeEqual(SQLExpr a, SQLExpr b);

		static bool  isLiteralExpr(SQLExpr expr);
};

#endif
