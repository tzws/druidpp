#ifndef SQLExprParser_HEADER_H
#define SQLExprParser_HEADER_H

#include <boost/smart_ptr.hpp>
#include <string>
#include <vector>

#include "../ast/SQLCommentHint.h"
#include "../ast/SQLDataType.h"
#include "../ast/SQLDataTypeImpl.h"
#include "../ast/SQLExpr.h"
#include "../ast/SQLName.h"
#include "../ast/SQLObject.h"
#include "../ast/SQLOrderBy.h"
#include "../ast/SQLOrderingSpecification.h"
#include "../ast/SQLOver.h"
#include "../ast/expr/SQLAggregateExpr.h"
#include "../ast/expr/SQLAllColumnExpr.h"
#include "../ast/expr/SQLAllExpr.h"
#include "../ast/expr/SQLAnyExpr.h"
#include "../ast/expr/SQLBetweenExpr.h"
#include "../ast/expr/SQLBinaryOpExpr.h"
#include "../ast/expr/SQLBinaryOperator.h"
#include "../ast/expr/SQLCaseExpr.h"
#include "../ast/expr/SQLCaseExpr_Item.h"
#include "../ast/expr/SQLCastExpr.h"
#include "../ast/expr/SQLCharExpr.h"
#include "../ast/expr/SQLCurrentOfCursorExpr.h"
#include "../ast/expr/SQLDefaultExpr.h"
#include "../ast/expr/SQLExistsExpr.h"
#include "../ast/expr/SQLHexExpr.h"
#include "../ast/expr/SQLIdentifierExpr.h"
#include "../ast/expr/SQLInListExpr.h"
#include "../ast/expr/SQLInSubQueryExpr.h"
#include "../ast/expr/SQLIntegerExpr.h"
#include "../ast/expr/SQLListExpr.h"
#include "../ast/expr/SQLMethodInvokeExpr.h"
#include "../ast/expr/SQLNCharExpr.h"
#include "../ast/expr/SQLNotExpr.h"
#include "../ast/expr/SQLNullExpr.h"
#include "../ast/expr/SQLNumberExpr.h"
#include "../ast/expr/SQLPropertyExpr.h"
#include "../ast/expr/SQLQueryExpr.h"
#include "../ast/expr/SQLSomeExpr.h"
#include "../ast/expr/SQLUnaryExpr.h"
#include "../ast/expr/SQLUnaryOperator.h"
#include "../ast/expr/SQLVariantRefExpr.h"
#include "../ast/statement/NotNullConstraint.h"
#include "../ast/statement/SQLAssignItem.h"
#include "../ast/statement/SQLCharactorDataType.h"
#include "../ast/statement/SQLCheck.h"
#include "../ast/statement/SQLColumnCheck.h"
#include "../ast/statement/SQLColumnDefinition.h"
#include "../ast/statement/SQLColumnPrimaryKey.h"
#include "../ast/statement/SQLColumnReference.h"
#include "../ast/statement/SQLColumnUniqueKey.h"
#include "../ast/statement/SQLConstaint.h"
#include "../ast/statement/SQLForeignKeyConstraint.h"
#include "../ast/statement/SQLForeignKeyImpl.h"
#include "../ast/statement/SQLPrimaryKey.h"
#include "../ast/statement/SQLPrimaryKeyImpl.h"
#include "../ast/statement/SQLSelect.h"
#include "../ast/statement/SQLSelectOrderByItem.h"
#include "../ast/statement/SQLUnique.h"

#include "SQLParser.h"


class SQLSelectParser;
class SQLExprParser : public SQLParser {

	private:

		std::list<SQLHint *> myHints;
	public:
		typedef SQLParser super;
		//static std::string[] AGGREGATE_FUNCTIONS;
		static const std::vector<std::string> AGGREGATE_FUNCTIONS;
		SQLExprParser(std::string &sql);
		SQLExprParser(Lexer *lexer);
		~SQLExprParser();

		SQLExpr *getExpr();
		SQLExpr *exprRest(SQLExpr *expr);
		SQLExpr *bitXor();
		SQLExpr *bitXorRest(SQLExpr *expr);
		SQLExpr *multiplicative();
		SQLExpr *multiplicativeRest(SQLExpr *expr);
		SQLExpr *primary();
		SQLSelectParser *createSelectParser();
		SQLExpr *primaryRest(SQLExpr *expr);
		SQLExpr *groupComparisionRest(SQLExpr *expr);

		void getNames(std::list<SQLName *> & exprCol);
		void getNames(std::list<SQLName *> &exprCol, SQLObject *parent);
		void exprList(std::list<SQLExpr *> & exprCol);
		void exprList(std::list<SQLExpr *> & exprCol, SQLObject *parent);
		SQLName *getName();
		SQLName *nameRest(SQLName *name);
		bool isAggreateFunction(std::string &word);
		SQLOrderBy *parseOrderBy();
		SQLSelectOrderByItem *parseSelectOrderByItem();
		SQLExpr *bitAnd();
		SQLExpr *bitAndRest(SQLExpr *expr);
		SQLExpr *bitOr();
		SQLExpr *bitOrRest(SQLExpr *expr);
		SQLExpr *equality();
		SQLExpr *equalityRest(SQLExpr *expr);
		SQLExpr *inRest(SQLExpr *expr);
		SQLExpr *additive();
		SQLExpr *additiveRest(SQLExpr *expr);
		SQLExpr *shift();
		SQLExpr *shiftRest(SQLExpr *expr);
		SQLExpr *getAnd();
		SQLExpr *andRest(SQLExpr *expr);
		SQLExpr *getOr();
		SQLExpr *orRest(SQLExpr *expr);
		SQLExpr *relational();
		SQLExpr *relationalRest(SQLExpr *expr);
		SQLExpr *notRationalRest(SQLExpr *expr);
		SQLDataType *parseDataType();
		void accept(Token token);
		SQLColumnDefinition *parseColumn();
		SQLColumnDefinition *parseColumnRest(SQLColumnDefinition *column);
		SQLPrimaryKey *parsePrimaryKey();
		SQLUnique *parseUnique();
		SQLAssignItem *parseAssignItem();
		std::list<SQLHint *> & parseHints();
		void parseHints(std::list<SQLHint *> & hints);
		SQLConstaint *parseConstaint();
		SQLCheck *parseCheck();
		SQLForeignKeyConstraint *parseForeignKey();

	protected:
		//std::string[]           aggregateFunctions;
		std::vector<std::string> aggregateFunctions;

		SQLExpr *parseInterval();

		SQLExpr *methodRest(SQLExpr *expr, bool acceptLPAREN);

		SQLExpr *dotRest(SQLExpr *expr);

		SQLAggregateExpr *parseAggregateExpr(std::string &methodName);

		SQLAggregateExpr *parseAggregateExprRest(SQLAggregateExpr *aggregateExpr);

		SQLDataType *parseDataTypeRest(SQLDataType *dataType);

		bool isCharType(std::string &dataTypeName);

		SQLDataType *parseCharTypeRest(SQLCharactorDataType *charType);

		SQLColumnDefinition *createColumnDefinition();


		SQLColumnCheck *parseColumnCheck();

		SQLCheck *createCheck();

		SQLForeignKeyConstraint *createForeignKey();
};
typedef boost::shared_ptr<SQLExprParser> SQLExprParser_ptr;

#endif

