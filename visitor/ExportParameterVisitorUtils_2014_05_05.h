
#ifndef ExportParameterVisitorUtils_HEADER_H 
#define ExportParameterVisitorUtils_HEADER_H

#include <list>

#include "../ast/SQLExpr.h"
#include "../ast/expr/SQLBetweenExpr.h"
#include "../ast/expr/SQLBinaryOpExpr.h"
#include "../ast/expr/SQLCharExpr.h"
#include "../ast/expr/SQLLiteralExpr.h"
#include "../ast/expr/SQLNumericLiteralExpr.h"
#include "../ast/expr/SQLVariantRefExpr.h"

//#include "../dialect/mysql/ast/expr/MySqlBooleanExpr.h"



class ExportParameterVisitorUtils {

	private:
		//SQLVariantRefExpr *theRef;

	public:
		static bool exportParamterAndAccept(std::list<Object *> &parameters, std::list<SQLExpr *> &list);

		static SQLExpr *exportParameter(std::list<Object *> &parameters, SQLExpr *param);

		static void exportParameter(std::list<Object *> &parameters, SQLBinaryOpExpr *x);

		static void exportParameter(std::list<Object *> &parameters, SQLBetweenExpr *x);
};
#endif

