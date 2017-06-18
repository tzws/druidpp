// g++ x.cpp -std=c++11
// clearing vectors
#include <iostream>
#include <vector>
#include <typeinfo>
/* isalpha example */
#include <stdio.h>
#include <ctype.h>
#include <assert.h> 

#include "Object.h"
#include "SQLObject.h"
#include "SQLObjectImpl.h"
#include "SQLExpr.h"
#include "SQLExprImpl.h"
#include "SQLName.h"
#include "SQLHint.h"
#include "SQLCommentHint.h"
#include "SQLDataType.h"
#include "SQLDataTypeImpl.h"
#include "SQLExprImpl.h"
#include "SQLOrderBy.h"
#include "SQLPartitioningClause.h"
#include "SQLSetQuantifier.h"
#include "SQLStatement.h"
#include "SQLStatementImpl.h"



#include "statement/SQLDDLStatement.h"
#include "statement/SQLTableSource.h"
#include "statement/SQLTableSourceImpl.h"
#include "statement/SQLExprTableSource.h"
#include "statement/SQLDropTableStatement.h"
#include "statement/SQLDropSequenceStatement.h"
#include "statement/SQLDropTriggerStatement.h"
#include "statement/SQLDropViewStatement.h"
#include "statement/SQLDropDatabaseStatement.h"
#include "statement/SQLDropFunctionStatement.h"
#include "statement/SQLDropTableSpaceStatement.h"
#include "statement/SQLDropProcedureStatement.h"

#include "statement/SQLValuesClause.h"
#include "expr/SQLIdentifierExpr.h"
#include "statement/SQLSelectQuery.h"
#include "statement/SQLSelect.h"
#include "statement/SQLWithSubqueryClause.h"

#include "statement/SQLInsertInto.h"
#include "statement/SQLInsertStatement.h"


#include "expr/SQLListExpr.h"
#include "expr/SQLQueryExpr.h"


#include "statement/SQLColumnConstraint.h"
#include "statement/SQLColumnDefinition.h"
#include "statement/SQLAlterTableAddColumn.h"
#include "statement/SQLAlterTableAddConstraint.h"
#include "statement/SQLAlterTableAddIndex.h"
#include "statement/SQLAlterTableAlterColumn.h"
#include "statement/SQLAlterTableDisableConstraint.h"
#include "statement/SQLAlterTableDisableKeys.h"
#include "statement/SQLAlterTableDropColumnItem.h"
#include "statement/SQLAlterTableDropConstraint.h"
#include "statement/SQLAlterTableEnableConstraint.h"
#include "statement/SQLAlterTableEnableKeys.h"
#include "statement/SQLAlterTableStatement.h"
#include "statement/SQLAssignItem.h"
#include "statement/SQLCallStatement.h"
#include "statement/SQLCommentStatement.h"
#include "statement/SQLConstaint.h"
#include "statement/SQLCreateDatabaseStatement.h"
#include "statement/SQLCreateIndexStatement.h"
#include "statement/SQLCreateTableStatement.h"
#include "statement/SQLCreateTriggerStatement.h"
#include "statement/SQLCreateViewStatement.h"
#include "statement/SQLDeleteStatement.h"
#include "statement/SQLDropIndexStatement.h"
#include "statement/SQLDropUserStatement.h"
#include "statement/SQLExplainStatement.h"
#include "statement/SQLGrantStatement.h"
#include "statement/SQLUniqueConstraint.h"
#include "statement/SQLPrimaryKey.h"
#include "statement/SQLConstaintImpl.h"
#include "statement/SQLUnique.h"
#include "statement/SQLPrimaryKeyImpl.h"
#include "statement/SQLReleaseSavePointStatement.h"
#include "statement/SQLRollbackStatement.h"
#include "statement/SQLSavePointStatement.h"
#include "statement/SQLSelectStatement.h"
#include "statement/SQLSetStatement.h"
#include "statement/SQLTruncateStatement.h"
#include "statement/SQLUpdateSetItem.h"
#include "statement/SQLUpdateStatement.h"
#include "statement/SQLUseStatement.h"
#include "statement/SQLSelectItem.h"
#include "statement/SQLJoinTableSource.h"
#include "statement/SQLSelectGroupByClause.h"
#include "statement/SQLSelectQueryBlock.h"
#include "statement/SQLSubqueryTableSource.h"
#include "statement/SQLUnionOperator.h"
#include "statement/SQLUnionQuery.h"
#include "expr/SQLAggregateExpr.h"
#include "expr/SQLAllColumnExpr.h"
#include "expr/SQLAllExpr.h"
#include "expr/SQLAnyExpr.h"
#include "expr/SQLBetweenExpr.h"
#include "expr/SQLBinaryOperator.h"
#include "expr/SQLBinaryOpExpr.h"
#include "expr/SQLCaseExpr.h"
#include "expr/SQLCastExpr.h"
#include "expr/SQLLiteralExpr.h"
#include "expr/SQLTextLiteralExpr.h"
#include "expr/SQLCharExpr.h"
#include "expr/SQLCurrentOfCursorExpr.h"
#include "expr/SQLDefaultExpr.h"
#include "expr/SQLExistsExpr.h"
#include "expr/SQLHexExpr.h"
#include "expr/SQLInListExpr.h"
#include "expr/SQLInSubQueryExpr.h"
#include "expr/SQLNumericLiteralExpr.h"
#include "expr/SQLIntegerExpr.h"
#include "expr/SQLMethodInvokeExpr.h"
#include "expr/SQLNCharExpr.h"
#include "expr/SQLNotExpr.h"
#include "expr/SQLNullExpr.h"
#include "expr/SQLNumberExpr.h"
#include "expr/SQLPropertyExpr.h"
#include "expr/SQLSomeExpr.h"
#include "expr/SQLUnaryOperator.h"
#include "expr/SQLUnaryExpr.h"
#include "expr/SQLVariantRefExpr.h"
#include "statement/NotNullConstraint.h"
#include "statement/SQLCharactorDataType.h"
#include "statement/SQLCheck.h"
#include "statement/SQLColumnCheck.h"
#include "statement/SQLColumnPrimaryKey.h"
#include "statement/SQLColumnReference.h"
#include "statement/SQLColumnUniqueKey.h"
#include "statement/SQLForeignKeyConstraint.h"
#include "statement/SQLForeignKeyImpl.h"
class A{
	public:
		int id;
		A(){};
		void setId(int x) { id = x;}

};

int main ()
{
	//assert(false);
	A xxx;
	SQLCommentHint hint;
	SQLCommentHint hint1;
	std::string strHint1 = "hint 1";
	hint.setText(strHint1);


	std::cout << "typeif of A is: " << typeid(xxx).name() << std::endl;
	std::cout << "toString() is: " << hint.toString() << std::endl;
	std::cout << "getClass() is: " << hint.getClass() << std::endl;
	std::cout << "equals is: " << (hint1.getClass() == hint.getClass() ) << std::endl;
	std::cout << "equals is: " << (hint1.getClass() != hint.getClass() ) << std::endl;

	std::string txtImp1 = "imp 1";
	std::string txtImp2 = "imp 2";

	SQLDataTypeImpl dataTypeImpl1(txtImp1);
	SQLDataTypeImpl dataTypeImpl2(txtImp2);
	SQLDataTypeImpl dataTypeImpl3(txtImp1);

	std::cout << "equals is: " << (dataTypeImpl1.equals(&dataTypeImpl2) ) << std::endl;
	std::cout << "equals is: " << (dataTypeImpl1.equals(&dataTypeImpl1) ) << std::endl;

	//SQLObjectImpl imp;
	//SQLObjectImpl imp1;
	//imp1.setParent(&imp);
	//std::cout << "toString() is: " << imp.toString() << std::endl;

	SQLOrderBy ob;


	//SQLSetQuantifier alll;
	//alll = SQLSetQuantifier::ALL;

	std::map<char,A> mymap;
	std::map<char,A>::iterator it;

	A a;
	a.setId(1);

	A b;
	b.setId(50);

	A c;
	c.setId(100);


	A d;
	d.setId(200);

	mymap['a']=a;
	mymap['b']=b;
	mymap['c']=c;
	mymap['d']=d;

	it=mymap.find('b');
	mymap.erase (it);
	mymap.erase (mymap.find('d'));

	// print content:
	std::cout << "elements in mymap:" << '\n';
	it = mymap.find('a');
	std::cout << "a => " << mymap.find('a')->second.id << '\n';
	std::cout << "c => " << mymap.find('c')->second.id << '\n';
	std::cout << "f => " << mymap.find('f')->second.id << '\n';

	return 0;

	std::string x = "";

	if (x.empty())
	{

		std::cout << "x is NULL " << std::endl;
	} else {

		std::cout << "x is not NULL " << std::endl;
	}


	int i=0;
	char str[]="C51";
	while (str[i])
	{
		if (isalpha(str[i])) printf ("character %c is alphabetic\n",str[i]);
		else printf ("character %c is not alphabetic\n",str[i]);
		i++;
	}
	return 0;
}

