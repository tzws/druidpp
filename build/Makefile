INCLUDE = -I../ast -I../ast/statement -I../ast/expr  -I../parser -I../deps/xxhash -I../deps/smhasher -I../visitor
VPATH = ../ast:../ast/statement:../ast/expr:../parser:../visitor

THELIB = parser.a
CXXFLAGS?= -Wall -O2 -W -DDEBUG -ggdb
#CXXFLAGS?= -Wall -O2 -W 

all: $(THELIB) test_CharTypes test_Keywords test_Lexer test_Token test_SQLParser test_SQLExprParser bench

xxhash.o: ../deps/xxhash/xxhash.c
	g++ $(CXXFLAGS) $(INCLUDE) -c $^ -o $@

MurmurHash3.o: ../deps/smhasher/MurmurHash3.cpp
	g++ $(CXXFLAGS) $(INCLUDE) -c $^ -o $@

OBJECTS = Lexer.o \
	CharTypes.o \
	xxhash.o \
	MurmurHash3.o \
	Keywords.o \
	IllegalStateException.o \
	NotAllowCommentException.o \
	ParserException.o  \
	LayoutCharacters.o \
	NotAllowCommentException.o \
	IllegalArgumentException.o \
	EOFParserException.o \
	NumberFormatException.o \
	UnsupportedOperationException.o \
	SQLExprParser.o \
	SQLParser.o \
	SQLSelectParser.o \
	SQLStatementParser.o \
	SQLDDLParser.o \
	OdpsSelectParser.o \
	OdpsUDTFSQLSelectItem.o \
	SQLCreateTableParser.o \
	SQLSetQuantifier.o \
	SQLObjectImpl.o \
	SQLCommentHint.o \
	SQLDataTypeImpl.o \
	SQLSelectOrderByItem.o \
	SQLOrderBy.o \
	SQLOver.o \
	SQLTableSourceImpl.o \
	SQLExprTableSource.o \
	SQLDropTableStatement.o \
	SQLDropSequenceStatement.o \
	SQLDropTriggerStatement.o \
	SQLDropViewStatement.o \
	SQLDropDatabaseStatement.o \
	SQLDropFunctionStatement.o \
	SQLDropTableSpaceStatement.o \
	SQLDropProcedureStatement.o \
	SQLIdentifierExpr.o \
	SQLSelect.o \
	SQLWithSubqueryClause.o \
	SQLWithSubqueryClause_Entry.o \
	SQLInsertInto.o \
	SQLInsertStatement.o \
	SQLListExpr.o \
	SQLQueryExpr.o \
	SQLVariantRefExpr.o \
	SQLColumnDefinition.o \
	SQLAlterTableAddColumn.o \
	SQLAlterTableAddConstraint.o \
	SQLAlterTableAddIndex.o \
	SQLAlterTableAlterColumn.o \
	SQLAlterTableDisableConstraint.o \
	SQLAlterTableDisableKeys.o \
	SQLAlterTableDropColumnItem.o \
	SQLAlterTableDropConstraint.o \
	SQLAlterTableEnableConstraint.o \
	SQLAlterTableEnableKeys.o \
	SQLAlterTableStatement.o \
	SQLAssignItem.o \
	SQLCallStatement.o \
	SQLCommentStatement.o \
	SQLCreateDatabaseStatement.o \
	SQLCreateIndexStatement.o \
	SQLCreateTableStatement.o \
	SQLValuesClause.o \
	SQLCreateTriggerStatement.o \
	SQLCreateViewStatement.o \
	SQLDeleteStatement.o \
	SQLDropIndexStatement.o \
	SQLDropUserStatement.o \
	SQLExplainStatement.o \
	SQLGrantStatement.o \
	SQLConstaintImpl.o \
	SQLUnique.o \
	SQLPrimaryKeyImpl.o \
	SQLReleaseSavePointStatement.o \
	SQLRollbackStatement.o \
	SQLSavePointStatement.o \
	SQLSelectStatement.o \
	SQLSetStatement.o \
	SQLTruncateStatement.o \
	SQLUpdateSetItem.o \
	SQLUpdateStatement.o \
	SQLUseStatement.o \
	SQLSelectItem.o \
	SQLJoinTableSource.o \
	SQLSelectGroupByClause.o \
	SQLSelectQueryBlock.o \
	SQLSubqueryTableSource.o \
	SQLUnionOperator.o \
	SQLUnionQuery.o \
	SQLAggregateExpr.o \
	SQLAllColumnExpr.o \
	SQLAllExpr.o \
	SQLAnyExpr.o \
	SQLBetweenExpr.o \
	SQLBinaryOperator.o \
	SQLBinaryOpExpr.o \
	SQLCaseExpr.o \
	SQLCaseExpr_Item.o \
	SQLCastExpr.o \
	SQLTextLiteralExpr.o \
	SQLCharExpr.o \
	SQLCurrentOfCursorExpr.o \
	SQLDefaultExpr.o \
	SQLExistsExpr.o \
	SQLHexExpr.o \
	SQLInListExpr.o \
	SQLInSubQueryExpr.o \
	SQLIntegerExpr.o \
	SQLMethodInvokeExpr.o \
	SQLNCharExpr.o \
	SQLNotExpr.o \
	SQLNullExpr.o \
	SQLNumberExpr.o \
	SQLPropertyExpr.o \
	SQLSomeExpr.o \
	SQLUnaryOperator.o \
	SQLUnaryExpr.o \
	NotNullConstraint.o \
	SQLCharactorDataType.o \
	SQLCheck.o \
	SQLColumnCheck.o \
	SQLColumnPrimaryKey.o \
	SQLColumnReference.o \
	SQLColumnUniqueKey.o \
	SQLForeignKeyImpl.o \
	SQLOrderingSpecification.o \
	SQLStatementImpl.o


#.cpp.o:
	#g++ -c $(CXXFLAGS) $<

#%.o: %.cpp
	#g++ $(CXXFLAGS) $< -o $@

.cpp.o:
	g++ $(CXXFLAGS) -c -o $@ $<

$(THELIB): $(OBJECTS)
	ar rcs $@ $^

CharTypes_test.o: CharTypes_test.cpp
	g++ $(CXXFLAGS) -c $^ -o $@

Keywords_test.o: Keywords_test.cpp
	g++ $(CXXFLAGS) -c $^ -o $@

Lexer_test.o: Lexer_test.cpp
	g++ $(CXXFLAGS) $(INCLUDE) -c $^ -o $@

Token_test.o: Token_test.cpp
	g++ $(CXXFLAGS) $(INCLUDE) -c $^ -o $@

SQLParser.o: SQLParser.cpp
	g++ $(CXXFLAGS) $(INCLUDE) -c $^ -o $@

test_CharTypes: CharTypes_test.o $(THELIB)
	g++ $^ -o $@

test_Keywords: Keywords_test.o $(THELIB)
	g++ $^ -o $@

test_Token: Token_test.o
	g++ $^ -o $@

test_Lexer: Lexer_test.o $(THELIB)
	g++ $^ -o $@


test_SQLParser: SQLParser_test.o $(THELIB)
	g++ $^ -o $@


test_SQLExprParser: SQLExprParser_test.o $(THELIB) 
	g++ $^ -o $@


bench: bench.o $(THELIB) 
	g++ $^ -o $@

clean:
	rm -rf *.o 

cleanObj:
	rm -rf *.o 



############### from parser directory ################################


