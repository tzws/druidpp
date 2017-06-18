#ifndef SQLASTOutputVisitorUtils_HEADER_H 
#define SQLASTOutputVisitorUtils_HEADER_H

//import com.alibaba.druid.sql.ast.expr.SQLCharExpr;
//import com.alibaba.druid.sql.ast.expr.SQLIntegerExpr;
//import com.alibaba.druid.sql.ast.expr.SQLNumberExpr;

class SQLASTOutputVisitorUtils {

	public:
		static bool  visit(PrintableVisitor visitor, SQLIntegerExpr x);

		static bool  visit(PrintableVisitor visitor, SQLNumberExpr x);

		static bool  visit(PrintableVisitor visitor, SQLCharExpr x);
};

#endif

