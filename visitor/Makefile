

#CFLAGS?= -pedantic -O2 -Wall -DNEBUG -W
CFLAGS?= -pedantic -O0 -W -DDEBUG -g
CC = g++

#INCLUDE = -I/home/aa/ssdb/api/cpp

all: test 

IllegalStateException.o: IllegalStateException.cpp
	g++ $(CXXFLAGS) $(INCLUDE) -DTEST_JSON -c $^ -o $@

NotAllowCommentException.o: NotAllowCommentException.cpp
	g++ $(CXXFLAGS) $(INCLUDE) -DTEST_JSON -c $^ -o $@

ExportParameterVisitorUtils.o: ExportParameterVisitorUtils.cpp
	g++ $(CXXFLAGS) $(INCLUDE) -c $^ -o $@


NumberFormatException.o: NumberFormatException.cpp
	g++ $(CXXFLAGS) $(INCLUDE) -c $^ -o $@


x.o: x.cpp
	g++ $(CXXFLAGS) $(INCLUDE) -c $^ -o $@

test: x.o ExportParameterVisitorUtils.o
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
