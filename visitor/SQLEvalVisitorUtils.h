#ifndef ParameterizedVisitor_HEADER_H
#define ParameterizedVisitor_HEADER_H

//import static com.alibaba.druid.sql.visitor.SQLEvalVisitor.EVAL_ERROR;
//import static com.alibaba.druid.sql.visitor.SQLEvalVisitor.EVAL_EXPR;
//import static com.alibaba.druid.sql.visitor.SQLEvalVisitor.EVAL_VALUE;
//import static com.alibaba.druid.sql.visitor.SQLEvalVisitor.EVAL_VALUE_NULL;

//import java.math.BigDecimal;
//import java.math.BigInteger;
//import java.text.ParseException;
//import java.text.SimpleDateFormat;
//import java.util.ArrayList;
//import java.util.Arrays;
//import java.util.Date;
//import java.util.HashMap;
//import java.util.List;
//import java.util.std::unordered_map;
//import java.util.regex.Pattern;

//import com.alibaba.druid.DruidRuntimeException;
//import com.alibaba.druid.sql.SQLUtils;
//import com.alibaba.druid.sql.ast.SQLExpr;
//import com.alibaba.druid.sql.ast.SQLObject;
//import com.alibaba.druid.sql.ast.expr.SQLBetweenExpr;
//import com.alibaba.druid.sql.ast.expr.SQLBinaryOpExpr;
//import com.alibaba.druid.sql.ast.expr.SQLBinaryOperator;
//import com.alibaba.druid.sql.ast.expr.SQLCaseExpr;
//import com.alibaba.druid.sql.ast.expr.SQLCharExpr;
//import com.alibaba.druid.sql.ast.expr.SQLHexExpr;
//import com.alibaba.druid.sql.ast.expr.SQLIdentifierExpr;
//import com.alibaba.druid.sql.ast.expr.SQLInListExpr;
//import com.alibaba.druid.sql.ast.expr.SQLMethodInvokeExpr;
//import com.alibaba.druid.sql.ast.expr.SQLNullExpr;
//import com.alibaba.druid.sql.ast.expr.SQLNumericLiteralExpr;
//import com.alibaba.druid.sql.ast.expr.SQLQueryExpr;
//import com.alibaba.druid.sql.ast.expr.SQLUnaryExpr;
//import com.alibaba.druid.sql.ast.expr.SQLUnaryOperator;
//import com.alibaba.druid.sql.ast.expr.SQLVariantRefExpr;
//import com.alibaba.druid.sql.ast.statement.SQLExprTableSource;
//import com.alibaba.druid.sql.ast.statement.SQLSelect;
//import com.alibaba.druid.sql.ast.statement.SQLSelectItem;
//import com.alibaba.druid.sql.ast.statement.SQLSelectQueryBlock;
//import com.alibaba.druid.sql.dialect.db2.visitor.DB2EvalVisitor;
//import com.alibaba.druid.sql.dialect.mysql.ast.expr.MySqlBinaryExpr;
//import com.alibaba.druid.sql.dialect.mysql.visitor.MySqlEvalVisitorImpl;
//import com.alibaba.druid.sql.dialect.oracle.visitor.OracleEvalVisitor;
//import com.alibaba.druid.sql.dialect.postgresql.visitor.PGEvalVisitor;
//import com.alibaba.druid.sql.dialect.sqlserver.visitor.SQLServerEvalVisitor;
//import com.alibaba.druid.sql.visitor.functions.Ascii;
//import com.alibaba.druid.sql.visitor.functions.Bin;
//import com.alibaba.druid.sql.visitor.functions.BitLength;
//import com.alibaba.druid.sql.visitor.functions.Char;
//import com.alibaba.druid.sql.visitor.functions.Concat;
//import com.alibaba.druid.sql.visitor.functions.Elt;
//import com.alibaba.druid.sql.visitor.functions.Function;
//import com.alibaba.druid.sql.visitor.functions.Greatest;
//import com.alibaba.druid.sql.visitor.functions.Hex;
//import com.alibaba.druid.sql.visitor.functions.If;
//import com.alibaba.druid.sql.visitor.functions.Insert;
//import com.alibaba.druid.sql.visitor.functions.Instr;
//import com.alibaba.druid.sql.visitor.functions.Isnull;
//import com.alibaba.druid.sql.visitor.functions.Lcase;
//import com.alibaba.druid.sql.visitor.functions.Least;
//import com.alibaba.druid.sql.visitor.functions.Left;
//import com.alibaba.druid.sql.visitor.functions.Length;
//import com.alibaba.druid.sql.visitor.functions.Locate;
//import com.alibaba.druid.sql.visitor.functions.Lpad;
//import com.alibaba.druid.sql.visitor.functions.Ltrim;
//import com.alibaba.druid.sql.visitor.functions.Now;
//import com.alibaba.druid.sql.visitor.functions.OneParamFunctions;
//import com.alibaba.druid.sql.visitor.functions.Reverse;
//import com.alibaba.druid.sql.visitor.functions.Right;
//import com.alibaba.druid.sql.visitor.functions.Substring;
//import com.alibaba.druid.sql.visitor.functions.Trim;
//import com.alibaba.druid.sql.visitor.functions.Ucase;
//import com.alibaba.druid.sql.visitor.functions.Unhex;
//import com.alibaba.druid.util.HexBin;
//import com.alibaba.druid.util.JdbcUtils;
//import com.alibaba.druid.util.Utils;
//import com.alibaba.druid.wall.spi.WallVisitorUtils;
//import com.alibaba.druid.wall.spi.WallVisitorUtils.WallConditionContext;

class SQLEvalVisitorUtils {

	private:
		bool _init;
		static std::unordered_map<std::string, Function> functions;

	public:
		static Object * evalExpr(std::string dbType, std::string expr, Object *... parameters);

		static Object * evalExpr(std::string dbType, std::string expr, List<Object *> parameters);

		static Object * eval(std::string dbType, SQLObject sqlObject, Object *... parameters);

		static Object * getValue(SQLObject sqlObject); 
		static Object * eval(std::string dbType, SQLObject sqlObject, List<Object *> parameters);

		static Object * eval(std::string dbType, SQLObject sqlObject, List<Object *> parameters, bool throwError);

		static SQLEvalVisitor createEvalVisitor(std::string dbType);

		static void registerBaseFunctions();

		static bool visit(SQLEvalVisitor visitor, SQLMethodInvokeExpr x);

		static bool visit(SQLEvalVisitor visitor, SQLCharExpr x);

		static bool visit(SQLEvalVisitor visitor, SQLHexExpr x);

		static bool visit(SQLEvalVisitor visitor, MySqlBinaryExpr x);

		static SQLExpr unwrap(SQLExpr expr);

		static bool visit(SQLEvalVisitor visitor, SQLBetweenExpr x);

		static bool visit(SQLEvalVisitor visitor, SQLNullExpr x);

		static bool visit(SQLEvalVisitor visitor, SQLCaseExpr x);

		static bool visit(SQLEvalVisitor visitor, SQLInListExpr x);

		static bool visit(SQLEvalVisitor visitor, SQLQueryExpr x);

		static bool visit(SQLEvalVisitor visitor, SQLUnaryExpr x);

		static bool visit(SQLEvalVisitor visitor, SQLBinaryOpExpr x);

	private:
		static Object * processValue(Object * value);

		static bool isAlwayTrueLikePattern(SQLExpr x);

	public:
		static bool visit(SQLEvalVisitor visitor, SQLNumericLiteralExpr x);

		static bool visit(SQLEvalVisitor visitor, SQLVariantRefExpr x);

		static bool castToBoolean(Object * val);

		static std::string castToString(Object * val);

		static Byte castToByte(Object * val);

		static Short castToShort(Object * val);

		static Integer castToInteger(Object * val);

		static Long castToLong(Object * val);

		static Float castToFloat(Object * val);

		static Double castToDouble(Object * val);

		static BigInteger castToBigInteger(Object * val);

		static Date castToDate(Object * val);

		static Date castToDate(std::string text);

		static BigDecimal castToDecimal(Object * val);

		static Object * rightShift(Object * a, Object * b);

		static Object * bitAnd(Object * a, Object * b);

		static Object * bitOr(Object * a, Object * b);

		static Object * div(Object * a, Object * b);

		static bool gt(Object * a, Object * b);

		static bool gteq(Object * a, Object * b);

		static bool lt(Object * a, Object * b);

		static bool lteq(Object * a, Object * b);

		static bool eq(Object * a, Object * b);

		static Object * add(Object * a, Object * b);

		static Object * sub(Object * a, Object * b);

		static Object * multi(Object * a, Object * b);

		static bool like(std::string input, std::string pattern);

		static bool visit(SQLEvalVisitor visitor, SQLIdentifierExpr x);
};
#endif
