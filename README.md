# druidpp
A C++ hand writing SQL parser inspired by [Ali Druid](https://github.com/alibaba/druid) which is written in Java

# Introduction

Most of the RDBMS vendor and SQL related tools parse SQL use [Yacc](https://en.wikipedia.org/wiki/Yacc) or [GNU Bison](https://www.gnu.org/software/bison/) or [LEMON](http://www.hwaci.com/sw/lemon/)

However, the author of [Sqlite](https://sqlite.org/arch.html) just have written SQL tokenizer by hand

> When a string containing SQL statements is to be evaluated it is first sent to the tokenizer. The tokenizer breaks the SQL text into tokens and hands those tokens one by one to the parser. The tokenizer is hand-coded in the file tokenize.c.
> 
> Note that in this design, the tokenizer calls the parser. People who are familiar with YACC and BISON may be accustomed to doing things the other way around — having the parser call the tokenizer. Having the tokenizer call the parser is better, though, because it can be made threadsafe and it runs faster.

And except that, I searched the whole internet, only found the project [druid](https://github.com/alibaba/druid) included a SQL parser, which is hand-coded.

**And, it's JAVA**

And it says:

The hand-coded SQL Parser is **10 times faster** than antlr、javacc, etc.

And it supports SQL-92、SQL-99 standards, and mysql/oracle/pg/sqlserver/odps dialects.

That's exactly what I want. 

# translate java to C++

## Java is OOP, C++ is OOP

So, is it possible translate the SQL parser from [druid](https://github.com/alibaba/druid) from Java to C++?

I don't know. That's why here's this project.

## Progress

The document of [Druid Sql Parser](https://github.com/alibaba/druid/wiki/SQL-Parser) said there're 3 modules:

>* Parser
>* AST
>* Visitor

I started this project in 2014, and finished the Parser translation.

The project should compile in *nix, Mac, cygwin, and Windows.


## screenshot

![](https://github.com/tzws/druidpp/blob/master/screenshot/druidpp-2014-1.jpg)
![](https://github.com/tzws/druidpp/blob/master/screenshot/druidpp-2014-2.jpg)
![](https://github.com/tzws/druidpp/blob/master/screenshot/druidpp-2014-3.jpg)

## Some example

```sh
cd build
./bench
parsing SQL: SELECT ID, NAME, AGE FROM USER WHERE ID = ? 
qps: 164647, time: 6.074 s
qps: 142260, time: 7.029 s
qps: 129776, time: 7.706 s
qps: 122824, time: 8.142 s
qps: 117446, time: 8.515 s
parsing SQL: select id, name, age from user where id = ? 
qps: 112727, time: 8.871 s
qps: 109403, time: 9.140 s
qps: 104890, time: 9.534 s
qps: 103107, time: 9.699 s
qps: 103855, time: 9.629 s
parsing SQL: SELECT e.last_name    AS name, e.commission_pct comm, e.salary * 12    Annual FROM  scott.employees AS e WHERE  e.salary > 1000 ORDER  BY e.first_name, e.last_name;
```

```sh
./test_CharTypes 
 in CharTypes's constructor 
in CharTypes isDigit
1
1
1
0
1
1
0
 in CharTypes's destructor 
```

```sh
./test_Keywords 
 enum SELECT = SELECT
 getKeywods 41
 getKeywods 235
key:GRANTvalue:137
key:WITHvalue:120
key:COMMENTvalue:115
key:REPLACEvalue:91
key:TOvalue:58
key:XORvalue:61
key:WHENvalue:63
key:USERvalue:25
key:TRIGGERvalue:24
key:VIEWvalue:22
key:UPDATEvalue:4
key:UNIQUEvalue:35
key:UNIONvalue:42
key:TABLEvalue:20
key:OVERvalue:116
key:RIGHTvalue:48
key:REFERENCESvalue:37
key:PRIMARYvalue:30
key:ORDERvalue:8
key:ORvalue:60
key:NOTvalue:18
key:LIKEvalue:73
key:SCHEMAvalue:53
key:TRUNCATEvalue:81
key:KEYvalue:31
key:SEQUENCEvalue:23
key:JOINvalue:51
key:INTOvalue:11
key:INTERVALvalue:77
key:INSERTvalue:3
key:INNERvalue:46
key:THENvalue:64
key:INDEXvalue:26
key:INvalue:68
key:HAVINGvalue:6
key:GROUPvalue:10
key:ONvalue:52
key:FORvalue:39
key:ESCAPEvalue:74
key:SETvalue:16
key:EXCEPTvalue:43
key:ELSEvalue:65
key:DROPvalue:15
key:EXISTSvalue:67
key:SOMEvalue:79
key:DESCvalue:71
key:VALUESvalue:76
key:PROCEDUREvalue:28
key:DISTINCTvalue:19
key:COLUMNvalue:55
key:NO_EXISTING_TOKENvalue:235
key:CONSTRAINTvalue:33
key:FROMvalue:5
key:EXPLAINvalue:38
key:DEFAULTvalue:32
key:USEvalue:56
key:FOREIGNvalue:36
key:CHECKvalue:34
key:CREATEvalue:13
key:CASTvalue:54
key:SELECTvalue:1
key:WHEREvalue:7
key:MINUSvalue:45
key:ISvalue:72
key:ASCvalue:70
key:CASEvalue:62
key:NULLvalue:17
key:FULLvalue:49
key:ENDvalue:66
key:ENABLEvalue:147
key:LOCKvalue:78
key:FUNCTIONvalue:29
key:BETWEENvalue:75
key:ASvalue:12
key:DATABASEvalue:57
key:LEFTvalue:47
key:TABLESPACEvalue:21
key:DISABLEvalue:148
key:INTERSECTvalue:44
key:ANYvalue:80
key:COMPUTEvalue:172
key:DELETEvalue:2
key:ALTERvalue:14
key:OUTERvalue:50
key:BYvalue:9
key:ANDvalue:59
key:ALLvalue:41
 ./test_Lexer 
3		../parser/Lexer_test.cpp: 59: Token is: SELECT		, stringVal is: SELECT<---- done
1		../parser/Lexer_test.cpp: 51: Token is: IDENTIFIER		, stringVal is: ID<---- done
1		../parser/Lexer_test.cpp: 51: Token is: IDENTIFIER		, stringVal is: NAME<---- done
1		../parser/Lexer_test.cpp: 51: Token is: IDENTIFIER		, stringVal is: AGE<---- done
3		../parser/Lexer_test.cpp: 59: Token is: FROM		, stringVal is: FROM<---- done
3		../parser/Lexer_test.cpp: 59: Token is: USER		, stringVal is: USER<---- done
3		../parser/Lexer_test.cpp: 59: Token is: WHERE		, stringVal is: WHERE<---- done
		../parser/Lexer_test.cpp: 65: Token is: WHERE		, stringVal is: WHERE<---- done
1		../parser/Lexer_test.cpp: 51: Token is: IDENTIFIER		, stringVal is: ID<---- done
3		../parser/Lexer_test.cpp: 59: Token is: =		, stringVal is: ID<---- done
3		../parser/Lexer_test.cpp: 59: Token is: ?		, stringVal is: ID<---- done
3		../parser/Lexer_test.cpp: 59: Token is: ENDOFFILE		, stringVal is: ID<---- done
./test_Token 
 enum SELECT = SELECT
./test_SQLExprParser 
>
AGE
516
```