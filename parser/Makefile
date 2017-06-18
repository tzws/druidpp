

#CFLAGS?= -pedantic -O2 -Wall -DNEBUG -W
CFLAGS?= -pedantic -O0 -W -DDEBUG -g
CC = g++

#INCLUDE = -I/home/aa/ssdb/api/cpp

all: test_CharTypes test_Keywords test_Lexer test_Token test_SQLParser

IllegalStateException.o: IllegalStateException.cpp
	g++ $(CXXFLAGS) $(INCLUDE) -DTEST_JSON -c $^ -o $@

NotAllowCommentException.o: NotAllowCommentException.cpp
	g++ $(CXXFLAGS) $(INCLUDE) -DTEST_JSON -c $^ -o $@

ParserException.o: ParserException.cpp
	g++ $(CXXFLAGS) $(INCLUDE) -DTEST_JSON -c $^ -o $@

LayoutCharacters.o: LayoutCharacters.cpp
	g++ $(CXXFLAGS) $(INCLUDE) -DTEST_JSON -c $^ -o $@

CharTypes.o: CharTypes.cpp
	g++ $(CXXFLAGS) -c $^ -o $@

CharTypes_test.o: CharTypes_test.cpp
	g++ $(CXXFLAGS) -c $^ -o $@

Keywords.o: Keywords.cpp
	g++ $(CXXFLAGS) -c $^ -o $@

Keywords_test.o: Keywords_test.cpp
	g++ $(CXXFLAGS) -c $^ -o $@

Lexer.o: Lexer.cpp
	g++ $(CXXFLAGS) $(INCLUDE) -c $^ -o $@

Lexer_test.o: Lexer_test.cpp
	g++ $(CXXFLAGS) $(INCLUDE) -c $^ -o $@

Token_test.o: Token_test.cpp
	g++ $(CXXFLAGS) $(INCLUDE) -c $^ -o $@

SQLParser.o: SQLParser.cpp
	g++ $(CXXFLAGS) $(INCLUDE) -c $^ -o $@

SQLSelectParser.o: SQLSelectParser.cpp
	g++ $(CXXFLAGS) $(INCLUDE) -c $^ -o $@

SQLExprParser.o: SQLExprParser.cpp
	g++ $(CXXFLAGS) $(INCLUDE) -c $^ -o $@


OdpsSelectParser.o: OdpsSelectParser.cpp
	g++ $(CXXFLAGS) $(INCLUDE) -c $^ -o $@

SQLStatementParser.o: SQLStatementParser.cpp
	g++ $(CXXFLAGS) $(INCLUDE) -c $^ -o $@


SQLCreateTableParser.o: SQLCreateTableParser.cpp
	g++ $(CXXFLAGS) $(INCLUDE) -c $^ -o $@

SQLDDLParser.o: SQLDDLParser.cpp
	g++ $(CXXFLAGS) $(INCLUDE) -c $^ -o $@


NumberFormatException.o: NumberFormatException.cpp
	g++ $(CXXFLAGS) $(INCLUDE) -c $^ -o $@

test_CharTypes: CharTypes_test.o CharTypes.o LayoutCharacters.o
	g++ $^ -o $@

test_Keywords: Keywords_test.o Keywords.o LayoutCharacters.o
	g++ $^ -o $@

test_Token: Token_test.o
	g++ $^ -o $@


test_CharTypes: CharTypes_test.o CharTypes.o LayoutCharacters.o
	g++ $^ -o $@

test_Keywords: Keywords_test.o Keywords.o LayoutCharacters.o
	g++ $^ -o $@

test_Token: Token_test.o
	g++ $^ -o $@

test_Lexer: Lexer_test.o \
	Lexer.o \
	CharTypes.o \
	Keywords.o \
	IllegalStateException.o \
	NotAllowCommentException.o \
	ParserException.o  \
	NumberFormatException.o \
	LayoutCharacters.o
	g++ $^ -o $@


test_SQLParser: Lexer.o \
	CharTypes.o \
	Keywords.o \
	IllegalStateException.o \
	NotAllowCommentException.o \
	ParserException.o  \
	LayoutCharacters.o \
	SQLParser.o \
	SQLExprParser.o \
	SQLSelectParser.o \
	SQLStatementParser.o \
	SQLDDLParser.o \
	OdpsSelectParser.o \
	SQLCreateTableParser.o \
	NumberFormatException.o \
	SQLParser_test.o
	g++ $^ -o $@


clean:
	rm -rf *.o 

cleanObj:
	rm -rf *.o 
