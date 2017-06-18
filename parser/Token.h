//http://codereview.stackexchange.com/questions/14309/conversion-between-enum-and-string-in-c-class-header
//http://stackoverflow.com/questions/207976/how-to-easily-map-c-enums-to-strings
#ifndef TOKEN_HEADER_H
#define TOKEN_HEADER_H

#include <boost/assign/list_of.hpp>
#include <boost/unordered_map.hpp>
#include <iostream>

#include <boost/algorithm/string.hpp>
#include <boost/smart_ptr.hpp>

using boost::assign::map_list_of;

enum Token {
	TOKEN_SELECT = 1, //("SELECT"), 
    TOKEN_DELETE, //("DELETE"), 
    TOKEN_INSERT, //("INSERT"), 
    UPDATE, //("UPDATE"), 
    
    FROM, //("FROM"), 
    HAVING, //("HAVING"), 
    WHERE, //("WHERE"), 
    ORDER, //("ORDER"), 
    BY, //("BY"),
    GROUP, //("GROUP"), 
    INTO, //("INTO"), 
    AS, //("AS"), 
    
    CREATE, //("CREATE"),
    ALTER, //("ALTER"), 
    DROP, //("DROP"), 
    SET, //("SET"), 
   
    XNULL, //("NULL"), 
    NOT, //("NOT"), 
    DISTINCT, //("DISTINCT"),

    TABLE, //("TABLE"), 
    TABLESPACE, //("TABLESPACE"), 
    VIEW, //("VIEW"), 
    SEQUENCE, //("SEQUENCE"), 
    TRIGGER, //("TRIGGER"), 
    USER, //("USER"), 
    INDEX, //("INDEX"), 
    SESSION, //("SESSION"),
    PROCEDURE, //("PROCEDURE"),
    FUNCTION, //("FUNCTION"),
    
    PRIMARY, //("PRIMARY"), 
    KEY, //("KEY"), 
    DEFAULT, //("DEFAULT"), 
    CONSTRAINT, //("CONSTRAINT"), 
    CHECK, //("CHECK"), 
    UNIQUE, //("UNIQUE"), 
    FOREIGN, //("FOREIGN"), 
    REFERENCES, //("REFERENCES"), 
    
    EXPLAIN, //("EXPLAIN"), 
    FOR, //("FOR"), 
    IF, //("IF"), 
   
   
   
    ALL, //("ALL"), 
    UNION, //("UNION"), 
    EXCEPT, //("EXCEPT"), 
    INTERSECT, //("INTERSECT"), 
    MINUS, //("MINUS"),
    INNER, //("INNER"), 
    LEFT, //("LEFT"), 
    RIGHT, //("RIGHT"), 
    FULL, //("FULL"), 
    OUTER, //("OUTER"), 
    JOIN, //("JOIN"), 
    ON, //("ON"), 
    SCHEMA, //("SCHEMA"), 
    CAST, //("CAST"),
    COLUMN, //("COLUMN"),
    USE, //("USE"),
    DATABASE, //("DATABASE"),
    TO, //("TO"),

    AND, //("AND"), 
    OR, //("OR"), 
    XOR, //("XOR"), 
    CASE, //("CASE"), 
    WHEN, //("WHEN"), 
    THEN, //("THEN"), 
    ELSE, //("ELSE"), 
    END, //("END"), 
    EXISTS, //("EXISTS"), 
    TOKEN_IN, //("IN"),

    NEW, //("NEW"), 
    ASC, //("ASC"), 
    DESC, //("DESC"), 
    IS, //("IS"), 
    LIKE, //("LIKE"), 
    ESCAPE, //("ESCAPE"), 
    BETWEEN, //("BETWEEN"), 
    VALUES, //("VALUES"), 
    INTERVAL, //("INTERVAL"),

    LOCK, //("LOCK"), 
    SOME, //("SOME"), 
    ANY, //("ANY"),
    TRUNCATE, //("TRUNCATE"),

    // mysql
    TOKEN_TRUE, //("TRUE"), 
    TOKEN_FALSE, //("FALSE"),
    LIMIT, //("LIMIT"),
    KILL, //("KILL"),
    IDENTIFIED, //("IDENTIFIED"),
    PASSWORD, //("PASSWORD"),
    DUAL, //("DUAL"),
    BINARY, //("BINARY"),
    SHOW, //("SHOW"),
    REPLACE, //("REPLACE"),
    
    //postgresql
    WINDOW, //("WINDOW"),
    OFFSET, //("OFFSET"),
    ROW, //("ROW"),
    ROWS, //("ROWS"),
    ONLY, //("ONLY"),
    FIRST, //("FIRST"),
    NEXT, //("NEXT"),
    FETCH, //("FETCH"),
    OF, //("OF"),
    SHARE, //("SHARE"),
    NOWAIT, //("NOWAIT"),
    RECURSIVE, //("RECURSIVE"),
    TEMPORARY, //("TEMPORARY"),
    TEMP, //("TEMP"),
    UNLOGGED, //("UNLOGGED"),
    RESTART, //("RESTART"),
    IDENTITY, //("IDENTITY"),
    CONTINUE, //("CONTINUE"),
    CASCADE, //("CASCADE"),
    RESTRICT, //("RESTRICT"),
    USING, //("USING"),
    CURRENT, //("CURRENT"),
    RETURNING, //("RETURNING"),
    COMMENT, //("COMMENT"),
    OVER, //("OVER"),
    
    // oracle
    START, //("START"),
    PRIOR, //("PRIOR"),
    CONNECT, //("CONNECT"),
    WITH, //("WITH"),
    EXTRACT, //("EXTRACT"),
    CURSOR, //("CURSOR"),
    MODEL, //("MODEL"),
    MERGE, //("MERGE"),
    MATCHED, //("MATCHED"),
    ERRORS, //("ERRORS"),
    REJECT, //("REJECT"),
    UNLIMITED, //("UNLIMITED"),
    BEGIN, //("BEGIN"),
    EXCLUSIVE, //("EXCLUSIVE"),
    MODE, //("MODE"),
    WAIT, //("WAIT"),
    ADVISE, //("ADVISE"),
    SYSDATE, //("SYSDATE"),
    DECLARE, //("DECLARE"),
    EXCEPTION, //("EXCEPTION"),
    GRANT, //("GRANT"),
    LOOP, //("LOOP"),
    GOTO, //("GOTO"),
    COMMIT, //("COMMIT"),
    SAVEPOINT, //("SAVEPOINT"),
    CROSS, //("CROSS"),
    
    PCTFREE, //("PCTFREE"),
    INITRANS, //("INITRANS"),
    MAXTRANS, //("MAXTRANS"),
    INITIALLY, //("INITIALLY"),
    ENABLE, //("ENABLE"),
    DISABLE, //("DISABLE"),
    SEGMENT, //("SEGMENT"),
    CREATION, //("CREATION"),
    IMMEDIATE, //("IMMEDIATE"),
    DEFERRED, //("DEFERRED"),
    STORAGE, //("STORAGE"),
    MINEXTENTS, //("MINEXTENTS"),
    MAXEXTENTS, //("MAXEXTENTS"),
    MAXSIZE, //("MAXSIZE"),
    PCTINCREASE, //("PCTINCREASE"),
    FLASH_CACHE, //("FLASH_CACHE"),
    CELL_FLASH_CACHE, //("CELL_FLASH_CACHE"),
    KEEP, //("KEEP"),
    NONE, //("NONE"),
    LOB, //("LOB"),
    STORE, //("STORE"),
    CHUNK, //("CHUNK"),
    CACHE, //("CACHE"),
    NOCACHE, //("NOCACHE"),
    LOGGING, //("LOGGING"),
    NOCOMPRESS, //("NOCOMPRESS"),
    KEEP_DUPLICATES, //("KEEP_DUPLICATES"),
    EXCEPTIONS, //("EXCEPTIONS"),
    PURGE, //("PURGE"),
    
    COMPUTE, //("COMPUTE"),
    ANALYZE, //("ANALYZE"),
    OPTIMIZE, //("OPTIMIZE"),
    
    // transact-sql
    TOP, //("TOP"),
    
    // hive

    ENDOFFILE, 
    TOKEN_ERROR,
    IDENTIFIER,
    HINT,
    TOKEN_VARIANT,
    LITERAL_INT,
    LITERAL_FLOAT,
    LITERAL_HEX,
    LITERAL_CHARS,
    LITERAL_NCHARS,
    
    LITERAL_ALIAS,
    LINE_COMMENT,
    MULTI_LINE_COMMENT,
    
    // Oracle
    BINARY_FLOAT,
    BINARY_DOUBLE,
    
    // odps,hive
    PARTITION,
    PARTITIONED,
    OVERWRITE,

    LEFTPAREN, //("("), 
    RPAREN, //(")"), 
    LBRACE, //("{"), 
    RBRACE, //("}"), 
    LBRACKET, //("["), 
    RBRACKET, //("]"), 
    SEMI, //(";"), 
    COMMA, //(","), 
    DOT, //("."), 
    DOTDOT, //(".."), 
    DOTDOTDOT, //("..,"), 
    EQ, //("="), 
    GT, //(">"), 
    LT, //("<"), 
    BANG, //("!"),
    TILDE, //("~"), 
    QUES, //("?"), 
    COLON, //(":"), 
    COLONCOLON, //(":"), 
    COLONEQ, //(":="), 
    EQEQ, //("=="), 
    LTEQ, //("<="), 
    LTEQGT, //("<=>"), 
    LTGT, //("<>"), 
    GTEQ, //(">="), 
    BANGEQ, //("!="), 
    BANGGT, //("!>"), 
    BANGLT, //("!<"),
    AMPAMP, //("&&"), 
    BARBAR, //("||"), 
    PLUS, //("+"), 
    SUB, //("-"), 
    STAR, //("*"), 
    SLASH, //("/"), 
    AMP, //("&"), 
    BAR, //("|"), 
    CARET, //("^"), 
    PERCENT, //("%"), 
    LTLT, //("<<"), 
    GTGT, //(">>"),
    MONKEYS_AT,

	NO_EXISTING_TOKEN

};

const static boost::unordered_map<Token,const char*> tokenStringList = map_list_of
(    TOKEN_SELECT, "SELECT") 
(    TOKEN_DELETE, "DELETE") 
(    TOKEN_INSERT, "INSERT") 
(    UPDATE, "UPDATE") 
    
(    FROM, "FROM") 
(    HAVING, "HAVING") 
(    WHERE, "WHERE") 
(    ORDER, "ORDER") 
(    BY, "BY")
(    GROUP, "GROUP") 
(    INTO, "INTO") 
(    AS, "AS") 
    
(    CREATE, "CREATE")
(    ALTER, "ALTER") 
(    DROP, "DROP") 
(    SET, "SET") 
   
(    XNULL, "NULL") 
(    NOT, "NOT") 
(    DISTINCT, "DISTINCT")

(    TABLE, "TABLE") 
(    TABLESPACE, "TABLESPACE") 
(    VIEW, "VIEW") 
(    SEQUENCE, "SEQUENCE") 
(    TRIGGER, "TRIGGER") 
(    USER, "USER") 
(    INDEX, "INDEX") 
(    SESSION, "SESSION")
(    PROCEDURE, "PROCEDURE")
(    FUNCTION, "FUNCTION")
    
(    PRIMARY, "PRIMARY") 
(    KEY, "KEY") 
(    DEFAULT, "DEFAULT") 
(    CONSTRAINT, "CONSTRAINT") 
(    CHECK, "CHECK") 
(    UNIQUE, "UNIQUE") 
(    FOREIGN, "FOREIGN") 
(    REFERENCES, "REFERENCES") 
    
(    EXPLAIN, "EXPLAIN") 
(    FOR, "FOR") 
(    IF, "IF") 
   
   
   
(    ALL, "ALL") 
(    UNION, "UNION") 
(    EXCEPT, "EXCEPT") 
(    INTERSECT, "INTERSECT") 
(    MINUS, "MINUS")
(    INNER, "INNER") 
(    LEFT, "LEFT") 
(    RIGHT, "RIGHT") 
(    FULL, "FULL") 
(    OUTER, "OUTER") 
(    JOIN, "JOIN") 
(    ON, "ON") 
(    SCHEMA, "SCHEMA") 
(    CAST, "CAST")
(    COLUMN, "COLUMN")
(    USE, "USE")
(    DATABASE, "DATABASE")
(    TO, "TO")

(    AND, "AND") 
(    OR, "OR") 
(    XOR, "XOR") 
(    CASE, "CASE") 
(    WHEN, "WHEN") 
(    THEN, "THEN") 
(    ELSE, "ELSE") 
(    END, "END") 
(    EXISTS, "EXISTS") 
(    TOKEN_IN, "IN")

(    NEW, "NEW") 
(    ASC, "ASC") 
(    DESC, "DESC") 
(    IS, "IS") 
(    LIKE, "LIKE") 
(    ESCAPE, "ESCAPE") 
(    BETWEEN, "BETWEEN") 
(    VALUES, "VALUES") 
(    INTERVAL, "INTERVAL")

(    LOCK, "LOCK") 
(    SOME, "SOME") 
(    ANY, "ANY")
(    TRUNCATE, "TRUNCATE")

    // mysql
(    TOKEN_TRUE, "TRUE") 
(    TOKEN_FALSE, "FALSE")
(    LIMIT, "LIMIT")
(    KILL, "KILL")
(    IDENTIFIED, "IDENTIFIED")
(    PASSWORD, "PASSWORD")
(    DUAL, "DUAL")
(    BINARY, "BINARY")
(    SHOW, "SHOW")
(    REPLACE, "REPLACE")
    
    //postgresql
(    WINDOW, "WINDOW")
(    OFFSET, "OFFSET")
(    ROW, "ROW")
(    ROWS, "ROWS")
(    ONLY, "ONLY")
(    FIRST, "FIRST")
(    NEXT, "NEXT")
(    FETCH, "FETCH")
(    OF, "OF")
(    SHARE, "SHARE")
(    NOWAIT, "NOWAIT")
(    RECURSIVE, "RECURSIVE")
(    TEMPORARY, "TEMPORARY")
(    TEMP, "TEMP")
(    UNLOGGED, "UNLOGGED")
(    RESTART, "RESTART")
(    IDENTITY, "IDENTITY")
(    CONTINUE, "CONTINUE")
(    CASCADE, "CASCADE")
(    RESTRICT, "RESTRICT")
(    USING, "USING")
(    CURRENT, "CURRENT")
(    RETURNING, "RETURNING")
(    COMMENT, "COMMENT")
(    OVER, "OVER")
    
    // oracle
(    START, "START")
(    PRIOR, "PRIOR")
(    CONNECT, "CONNECT")
(    WITH, "WITH")
(    EXTRACT, "EXTRACT")
(    CURSOR, "CURSOR")
(    MODEL, "MODEL")
(    MERGE, "MERGE")
(    MATCHED, "MATCHED")
(    ERRORS, "ERRORS")
(    REJECT, "REJECT")
(    UNLIMITED, "UNLIMITED")
(    BEGIN, "BEGIN")
(    EXCLUSIVE, "EXCLUSIVE")
(    MODE, "MODE")
(    WAIT, "WAIT")
(    ADVISE, "ADVISE")
(    SYSDATE, "SYSDATE")
(    DECLARE, "DECLARE")
(    EXCEPTION, "EXCEPTION")
(    GRANT, "GRANT")
(    LOOP, "LOOP")
(    GOTO, "GOTO")
(    COMMIT, "COMMIT")
(    SAVEPOINT, "SAVEPOINT")
(    CROSS, "CROSS")
    
(    PCTFREE, "PCTFREE")
(    INITRANS, "INITRANS")
(    MAXTRANS, "MAXTRANS")
(    INITIALLY, "INITIALLY")
(    ENABLE, "ENABLE")
(    DISABLE, "DISABLE")
(    SEGMENT, "SEGMENT")
(    CREATION, "CREATION")
(    IMMEDIATE, "IMMEDIATE")
(    DEFERRED, "DEFERRED")
(    STORAGE, "STORAGE")
(    MINEXTENTS, "MINEXTENTS")
(    MAXEXTENTS, "MAXEXTENTS")
(    MAXSIZE, "MAXSIZE")
(    PCTINCREASE, "PCTINCREASE")
(    FLASH_CACHE, "FLASH_CACHE")
(    CELL_FLASH_CACHE, "CELL_FLASH_CACHE")
(    KEEP, "KEEP")
(    NONE, "NONE")
(    LOB, "LOB")
(    STORE, "STORE")
(    CHUNK, "CHUNK")
(    CACHE, "CACHE")
(    NOCACHE, "NOCACHE")
(    LOGGING, "LOGGING")
(    NOCOMPRESS, "NOCOMPRESS")
(    KEEP_DUPLICATES, "KEEP_DUPLICATES")
(    EXCEPTIONS, "EXCEPTIONS")
(    PURGE, "PURGE")
    
(    COMPUTE, "COMPUTE")
(    ANALYZE, "ANALYZE")
(    OPTIMIZE, "OPTIMIZE")
    
    // transact-sql
(    TOP, "TOP")
    
    // hive

    //EOF, 
    //ENDOFFILE, 
(    ENDOFFILE, "ENDOFFILE")
    //ERROR,
(    TOKEN_ERROR, "ERROR")
    //IDENTIFIER,
(    IDENTIFIER, "IDENTIFIER")
    //HINT,
(    HINT, "HINT")
    //VARIANT,
(    TOKEN_VARIANT, "VARIANT")
    //LITERAL_INT,
(    LITERAL_INT, "LITERAL_INT")
    //LITERAL_FLOAT,
(    LITERAL_FLOAT, "LITERAL_FLOAT")
    //LITERAL_HEX,
(    LITERAL_HEX, "LITERAL_HEX")
    //LITERAL_CHARS,
(    LITERAL_CHARS, "LITERAL_CHARS")
    //LITERAL_NCHARS,
(    LITERAL_NCHARS, "LITERAL_NCHARS")
    
    //LITERAL_ALIAS,
(    LITERAL_ALIAS, "LITERAL_ALIAS")
    //LINE_COMMENT,
(    LINE_COMMENT, "LINE_COMMENT")
    //MULTI_LINE_COMMENT,
(    MULTI_LINE_COMMENT, "MULTI_LINE_COMMENT")
    
    // Oracle
    //BINARY_FLOAT,
(    BINARY_FLOAT, "BINARY_FLOAT")
    //BINARY_DOUBLE,
(    BINARY_DOUBLE, "BINARY_DOUBLE")
    
    // odps,hive
    //PARTITION,
(    PARTITION, "PARTITION")
    //PARTITIONED,
(    PARTITIONED, "PARTITIONED")
    //OVERWRITE,
(    OVERWRITE, "OVERWRITE")

(    LEFTPAREN, ")") 
(    RPAREN, ")") 
(    LBRACE, "{") 
(    RBRACE, "}") 
(    LBRACKET, "[") 
(    RBRACKET, "]") 
(    SEMI, ";") 
(    COMMA, ",") 
(    DOT, ".") 
(    DOTDOT, "..") 
(    DOTDOTDOT, "..,") 
(    EQ, "=") 
(    GT, ">") 
(    LT, "<") 
(    BANG, "!")
(    TILDE, "~") 
(    QUES, "?") 
(    COLON, ":") 
(    COLONCOLON, ":") 
(    COLONEQ, ":=") 
(    EQEQ, "==") 
(    LTEQ, "<=") 
(    LTEQGT, "<=>") 
(    LTGT, "<>") 
(    GTEQ, ">=") 
(    BANGEQ, "!=") 
(    BANGGT, "!>") 
(    BANGLT, "!<")
(    AMPAMP, "&&") 
(    BARBAR, "||") 
(    PLUS, "+") 
(    SUB, "-") 
(    STAR, "*") 
(    SLASH, "/") 
(    AMP, "&") 
(    BAR, "|") 
(    CARET, "^") 
(    PERCENT, "%") 
(    LTLT, "<<") 
(    GTGT, ">>")
(MONKEYS_AT,"@")
(NO_EXISTING_TOKEN,"NO_EXISTING_TOKEN");

#endif

