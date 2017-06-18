
#ifndef ParameterizedOutputVisitor_HEADER_H 
#define ParameterizedOutputVisitor_HEADER_H

#include <list>

//import com.alibaba.druid.sql.ast.expr.SQLBinaryOpExpr;
//import com.alibaba.druid.sql.ast.expr.SQLCharExpr;
//import com.alibaba.druid.sql.ast.expr.SQLInListExpr;
//import com.alibaba.druid.sql.ast.expr.SQLIntegerExpr;
//import com.alibaba.druid.sql.ast.expr.SQLNCharExpr;
//import com.alibaba.druid.sql.ast.expr.SQLNullExpr;
//import com.alibaba.druid.sql.ast.expr.SQLNumberExpr;

class ParameterizedOutputVisitor : virtual public SQLASTOutputVisitor, virtual public ParameterizedVisitor {

	private:
		int replaceCount;

	public:
		ParameterizedOutputVisitor();
		virtual ~ParameterizedOutputVisitor();

		//ParameterizedOutputVisitor(Appendable *appender);

		int getReplaceCount();

		void incrementReplaceCunt();

		bool visit(SQLInListExpr *x);

		bool visit(SQLBinaryOpExpr *x);

		bool  visit(SQLIntegerExpr *x);

		bool  visit(SQLNumberExpr *x);

		bool  visit(SQLCharExpr *x);

		bool  visit(SQLNCharExpr *x);

		bool  visit(SQLNullExpr *x);

};
#endif
