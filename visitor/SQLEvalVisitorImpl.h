#ifndef SQLEvalVisitorImpl_HEADER_H 
#define SQLEvalVisitorImpl_HEADER_H

//import java.util.ArrayList;
//import java.util.HashMap;
//import java.util.std::list;
//import java.util.std::unordered_map;

//import com.alibaba.druid.sql.ast.expr.SQLBinaryOpExpr;
//import com.alibaba.druid.sql.ast.expr.SQLCaseExpr;
//import com.alibaba.druid.sql.ast.expr.SQLCharExpr;
//import com.alibaba.druid.sql.ast.expr.SQLHexExpr;
//import com.alibaba.druid.sql.ast.expr.SQLIdentifierExpr;
//import com.alibaba.druid.sql.ast.expr.SQLInListExpr;
//import com.alibaba.druid.sql.ast.expr.SQLIntegerExpr;
//import com.alibaba.druid.sql.ast.expr.SQLMethodInvokeExpr;
//import com.alibaba.druid.sql.ast.expr.SQLNullExpr;
//import com.alibaba.druid.sql.ast.expr.SQLNumberExpr;
//import com.alibaba.druid.sql.ast.expr.SQLQueryExpr;
//import com.alibaba.druid.sql.ast.expr.SQLVariantRefExpr;
//import com.alibaba.druid.sql.visitor.functions.Function;

class SQLEvalVisitorImpl : virtual public SQLASTVisitorAdapter,virtual public SQLEvalVisitor {

	private:
		std::list<Object *>        parameters;

		std::unordered_map<std::string, Function> functions;

		int                 variantIndex;

		bool             markVariantIndex;

	public:
		SQLEvalVisitorImpl();
		virtual ~SQLEvalVisitorImpl();

		SQLEvalVisitorImpl(std::list<Object *> parameters);

		std::list<Object *> getParameters();

		void setParameters(std::list<Object *> parameters);

		bool visit(SQLCharExpr *x);

		int incrementAndGetVariantIndex();

		int getVariantIndex();

		bool visit(SQLVariantRefExpr *x);

		bool visit(SQLBinaryOpExpr *x);

		bool visit(SQLIntegerExpr *x);

		bool visit(SQLNumberExpr *x);

		bool visit(SQLHexExpr *x);

		bool visit(SQLCaseExpr *x);

		bool visit(SQLInListExpr *x);

		bool visit(SQLNullExpr *x);

		bool visit(SQLMethodInvokeExpr *x);

		bool visit(SQLQueryExpr *x);

		bool isMarkVariantIndex();

		void setMarkVariantIndex(bool markVariantIndex);

		Function getFunction(std::string funcName);

		void registerFunction(std::string funcName, Function function);

		bool visit(SQLIdentifierExpr *x);

		void unregisterFunction(std::string funcName);
};
#endif

