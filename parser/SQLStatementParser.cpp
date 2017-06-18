#include <memory>
#include "SQLStatementParser.h"
#include "OdpsSelectParser.h"
#include "SQLExprParser.h"
#include "SQLCreateTableParser.h"

SQLStatementParser::~SQLStatementParser(){


	//std::cout << __FILE__ << ": " << __LINE__ << ", in SQLStatementParser::~SQLStatementParser, destructor step 1" << std::endl;

	for(std::list<SQLStatement *>::iterator it = statementList.begin(); it != statementList.end(); ++it) 
	{
		//std::cout << __FILE__ << ": " << __LINE__ << ", in SQLStatementParser::~SQLStatementParser, destructor step 1.1" << std::endl;

		//SQLCreateTriggerStatement* x = dynamic_cast<SQLCreateTriggerStatement*>(*it);
		//if(x) 
		//{
			//delete x;
		//} else {
			//SQLCallStatement* x1 = dynamic_cast<SQLCallStatement*>(*it);
			//if(x1) 
			//{
				//delete x1;
			//} else {

				//SQLTruncateStatement* x2 = dynamic_cast<SQLTruncateStatement*>(*it);
				//if(x2) 
				//{
					//delete x2;
				//} else {

					//SQLDeleteStatement* x3 = dynamic_cast<SQLDeleteStatement*>(*it);
					//if(x3) 
					//{
						//delete x3;
					//} else {
						
						//SQLDropFunctionStatement* x4 = dynamic_cast<SQLDropFunctionStatement*>(*it);
						//if(x4) 
						//{
							//delete x4;
						//} else {
							
							//SQLDropSequenceStatement* x5 = dynamic_cast<SQLDropSequenceStatement*>(*it);
							//if(x5) 
							//{
								//delete x5;
							//} else {
								//SQLCreateDatabaseStatement* x6 = dynamic_cast<SQLCreateDatabaseStatement*>(*it);
								//if(x6) 
								//{
									//delete x6;
								//} else {

									//SQLDropTriggerStatement* x7 = dynamic_cast<SQLDropTriggerStatement*>(*it);
									//if(x7) 
									//{
										//delete x7;
									//} else {
										//SQLCreateTableStatement* x8 = dynamic_cast<SQLCreateTableStatement*>(*it);
										//if(x8) 
										//{
											//delete x8;
										//} else {
											
											//SQLDropTableStatement* x9 = dynamic_cast<SQLDropTableStatement*>(*it);
											//if(x9) 
											//{
												//delete x9;
											//} else {

												//SQLReleaseSavePointStatement* x10 = dynamic_cast<SQLReleaseSavePointStatement*>(*it);
												//if(x10) 
												//{
													//delete x10;
												//} else {

													//SQLDropIndexStatement* x11 = dynamic_cast<SQLDropIndexStatement*>(*it);
													//if(x11) 
													//{
														//delete x11;
													//} else {
														//SQLDropProcedureStatement* x12 = dynamic_cast<SQLDropProcedureStatement*>(*it);
														//if(x12) 
														//{
															//delete x12;
														//} else {
															//SQLSelectStatement* x111 = dynamic_cast<SQLSelectStatement*>(*it);
															//if(x111) 
															//{
																//delete x111;
															//}


														//}

													
													//}
												//}
											//}
										//}
									//}
								//}
							//}
						//}
					//}
				//}
			//}
		//}


		//SQLCreateTriggerStatement* x1 = dynamic_cast<SQLCreateTriggerStatement*>(*it);
		//SQLCallStatement* x2 = dynamic_cast<SQLCallStatement*>(*it);
		//SQLTruncateStatement* x3 = dynamic_cast<SQLTruncateStatement*>(*it);
		//SQLDeleteStatement* x4 = dynamic_cast<SQLDeleteStatement*>(*it);
		//SQLDropFunctionStatement* x5 = dynamic_cast<SQLDropFunctionStatement*>(*it);
		//SQLDropSequenceStatement* x6 = dynamic_cast<SQLDropSequenceStatement*>(*it);
		//SQLCreateDatabaseStatement* x7 = dynamic_cast<SQLCreateDatabaseStatement*>(*it);
		//SQLDropTriggerStatement* x9 = dynamic_cast<SQLDropTriggerStatement*>(*it);
		//SQLCreateTableStatement* x10 = dynamic_cast<SQLCreateTableStatement*>(*it);
		//SQLDropTableStatement* x11 = dynamic_cast<SQLDropTableStatement*>(*it);
		//SQLReleaseSavePointStatement* x12 = dynamic_cast<SQLReleaseSavePointStatement*>(*it);
		//SQLDropIndexStatement* x13 = dynamic_cast<SQLDropIndexStatement*>(*it);
		//SQLDropProcedureStatement* x14 = dynamic_cast<SQLDropProcedureStatement*>(*it);
		//SQLUseStatement* x15 = dynamic_cast<SQLUseStatement*>(*it);
		//SQLGrantStatement* x16 = dynamic_cast<SQLGrantStatement*>(*it);
		//SQLCreateViewStatement* x17 = dynamic_cast<SQLCreateViewStatement*>(*it);
		//SQLRollbackStatement* x18 = dynamic_cast<SQLRollbackStatement*>(*it);
		//SQLSetStatement* x19 = dynamic_cast<SQLSetStatement*>(*it);
		//SQLSavePointStatement* x20 = dynamic_cast<SQLSavePointStatement*>(*it);
		//SQLDropDatabaseStatement* x21 = dynamic_cast<SQLDropDatabaseStatement*>(*it);
		//SQLCreateIndexStatement* x22 = dynamic_cast<SQLCreateIndexStatement*>(*it);
		//SQLDropTableSpaceStatement* x23 = dynamic_cast<SQLDropTableSpaceStatement*>(*it);
		//SQLExplainStatement* x24 = dynamic_cast<SQLExplainStatement*>(*it);
		//SQLUpdateStatement* x25 = dynamic_cast<SQLUpdateStatement*>(*it);
		//SQLAlterTableStatement* x26 = dynamic_cast<SQLAlterTableStatement*>(*it);
		//SQLDropUserStatement* x27 = dynamic_cast<SQLDropUserStatement*>(*it);
		//SQLSelectStatement* x28 = dynamic_cast<SQLSelectStatement*>(*it);
		//SQLDropViewStatement* x29 = dynamic_cast<SQLDropViewStatement*>(*it);
		//if(x1) 
		//{
			//delete x1;
		//}

		//if(x2) 
		//{
			//delete x2;
		//}

		//if(x3) 
		//{
			//delete x3;
		//}

		//if(x4) 
		//{
			//delete x4;
		//}

		//if(x5) 
		//{
			//delete x5;
		//}

		//if(x6) 
		//{
			//delete x6;
		//}

		//if(x7) 
		//{
			//delete x7;
		//}

		//if(x9) 
		//{
			//delete x9;
		//}

		//if(x10) 
		//{
			//delete x10;
		//}

		//if(x11) 
		//{
			//delete x11;
		//}

		//if(x12) 
		//{
			//delete x12;
		//}

		//if(x13) 
		//{
			//delete x13;
		//}

		//if(x14) 
		//{
			//delete x14;
		//}

		//if(x15) 
		//{
			//delete x15;
		//}

		//if(x16) 
		//{
			//delete x16;
		//}

		//if(x17) 
		//{
			//delete x17;
		//}

		//if(x18) 
		//{
			//delete x18;
		//}

		//if(x19) 
		//{
			//delete x19;
		//}

		//if(x20) 
		//{
			//delete x20;
		//}

		//if(x21) 
		//{
			//delete x21;
		//}

		//if(x22) 
		//{
			//delete x22;
		//}

		//if(x23) 
		//{
			//delete x23;
		//}

		//if(x24) 
		//{
			//delete x24;
		//}

		//if(x25) 
		//{
			//delete x25;
		//}

		//if(x26) 
		//{
			//delete x26;
		//}

		//if(x27) 
		//{
			//delete x27;
		//}

		//if(x28) 
		//{
			//std::cout << "\t" <<  __FILE__ << ": " << __LINE__ << ", in SQLStatementParser::~SQLStatementParser, step x28" << std::endl;
			//delete x28;
		//}

		//if(x29) 
		//{
			//delete x29;
		//}

		delete *it; 
	}
	statementList.clear();

	for(std::list<SQLStatement *>::iterator it = yaList.begin(); it != yaList.end(); ++it) 
	{
		//std::cout << __FILE__ << ": " << __LINE__ << ", in SQLStatementParser::~SQLStatementParser, destructor step 1.2" << std::endl;
		delete *it; 
	}
	yaList.clear();


	if (exprParserHere && this->exprParser != NULL)
	{
		//std::cout << __FILE__ << ": " << __LINE__ << ", in SQLStatementParser::~SQLStatementParser, destructor step 2.1" << std::endl;
		delete exprParser;
	}
	//std::cout << __FILE__ << ": " << __LINE__ << ", in SQLStatementParser::~SQLStatementParser, destructor step 3" << std::endl;

}

//SQLStatementParser::SQLStatementParser(std::string &theSql) : exprParser(new SQLExprParser(theSql)), super(exprParser->getLexer()),  exprParserHere(true){
SQLStatementParser::SQLStatementParser(std::string &theSql) : super(theSql), exprParser(new SQLExprParser(getLexer())),  exprParserHere(true){
	//std::cout << __FILE__ << ": " << __LINE__ << ", in SQLStatementParser::SQLStatementParser, constructor 1 " << std::endl;
		//std::stringstream stream1;
		//stream1  <<  lexer->getToken() <<  " "  <<  lexer->getStringVal()  <<  ", pos "  <<  lexer->getPos();
		//std::cout << __FILE__ << ": " << __LINE__ << ", in SQLStatementParser::parseStatementList, " << stream1.str() << std::endl;
	//this(new SQLExprParser(theSql));
	//this->exprParser = new SQLExprParser(theSql);
	//super(this->exprParser->getLexer());
	//exprParserHere = true;
}

SQLStatementParser::SQLStatementParser(SQLExprParser *theExprParser) : super(theExprParser->getLexer()),exprParser(theExprParser), exprParserHere(false){
	//std::cout << __FILE__ << ": " << __LINE__ << ", in SQLStatementParser::SQLStatementParser, constructor 2 " << std::endl;
	//super(theExprParser->getLexer());
	//this->theExprParser = theExprParser;
}

SQLExprParser *SQLStatementParser::getExprParser() {
	return exprParser;
}

std::list<SQLStatement*> & SQLStatementParser::parseStatementList() {
	parseStatementList(statementList);
	return statementList;
}

void SQLStatementParser::parseStatementList(std::list<SQLStatement *> & theStatementList) {
	parseStatementList(theStatementList, -1);
}

void SQLStatementParser::parseStatementList(std::list<SQLStatement *> & theStatementList, int max) {
	for (;;) {
		if (max != -1) {
			if (theStatementList.size() >= max) {
				return;
			}
		}
		//std::stringstream stream1;
		//stream1 <<  lexer->getToken() <<  " " << tokenStringList.at(lexer->getToken() ) <<  ": "  <<  lexer->getStringVal()  <<  ", pos "  <<  lexer->getPos();
		//std::cout <<  "++++\t" << __FILE__ << ": " << __LINE__ << ", in SQLStatementParser::parseStatementList, " << stream1.str() << std::endl;
		if (lexer->getToken() == ENDOFFILE) {
			return;
		}

		if (lexer->getToken() == (SEMI)) {
			lexer->nextToken();
			continue;
		}

		if (lexer->getToken() == TOKEN_SELECT) {

			//std::cout << __FILE__ << ": " << __LINE__ << ", in SQLStatementParser::parseStatementList, token is: SELECT " << std::endl;
			theStatementList.push_back(parseSelect());

			continue;
		}

		if (lexer->getToken() == (UPDATE)) {
			theStatementList.push_back(parseUpdateStatement());
			continue;
		}

		if (lexer->getToken() == (CREATE)) {
			theStatementList.push_back(parseCreate());
			continue;
		}

		if (lexer->getToken() == (TOKEN_INSERT)) {
			SQLStatement *insertStatement = parseInsert();
			theStatementList.push_back(insertStatement);

			continue;
		}

		if (lexer->getToken() == (TOKEN_DELETE)) {
			theStatementList.push_back(parseDeleteStatement());
			continue;
		}

		if (lexer->getToken() == (EXPLAIN)) {
			theStatementList.push_back(parseExplain());
			continue;
		}

		if (lexer->getToken() == SET) {
			theStatementList.push_back(parseSet());
			continue;
		}

		if (lexer->getToken() == ALTER) {
			theStatementList.push_back(parseAlter());
			continue;
		}

		if (lexer->getToken() == DROP) {
			lexer->nextToken();

			if (lexer->getToken() == TABLE || identifierEquals("TEMPORARY")) {

				SQLDropTableStatement *stmt = parseDropTable(false);

				theStatementList.push_back(stmt);
				continue;
			} else if (lexer->getToken() == USER) {
				SQLStatement *stmt = parseDropUser();
				theStatementList.push_back(stmt);
				continue;
			} else if (lexer->getToken() == INDEX) {
				SQLStatement *stmt = parseDropIndex();
				theStatementList.push_back(stmt);
				continue;
			} else if (lexer->getToken() == VIEW) {
				SQLStatement *stmt = parseDropView(false);
				theStatementList.push_back(stmt);
				continue;
			} else if (lexer->getToken() == TRIGGER) {
				SQLStatement *stmt = parseDropTrigger(false);
				theStatementList.push_back(stmt);
				continue;
			} else if (lexer->getToken() == DATABASE) {
				SQLStatement *stmt = parseDropDatabase(false);
				theStatementList.push_back(stmt);
				continue;
			} else if (lexer->getToken() == FUNCTION) {
				SQLStatement *stmt = parseDropFunction(false);
				theStatementList.push_back(stmt);
				continue;
			} else if (lexer->getToken() == TABLESPACE) {
				SQLStatement *stmt = parseDropTablespace(false);
				theStatementList.push_back(stmt);
				continue;
			} else if (lexer->getToken() == PROCEDURE) {
				SQLStatement *stmt = parseDropProcedure(false);
				theStatementList.push_back(stmt);
				continue;
			} else {
				throw new ParserException("TODO " + lexer->getToken());
			}
		}

		if (lexer->getToken() == TRUNCATE) {
			SQLStatement *stmt = parseTruncate();
			theStatementList.push_back(stmt);
			continue;
		}

		if (lexer->getToken() == USE) {
			SQLStatement *stmt = parseUse();
			theStatementList.push_back(stmt);
			continue;
		}

		if (lexer->getToken() == GRANT) {
			SQLStatement *stmt = parseGrant();
			theStatementList.push_back(stmt);
			continue;
		}

		if (lexer->getToken() == LBRACE || identifierEquals("CALL")) {
			SQLCallStatement *stmt = parseCall();
			theStatementList.push_back(stmt);
			continue;
		}

		if (identifierEquals("RENAME")) {
			SQLStatement *stmt = parseRename();
			theStatementList.push_back(stmt);
			continue;
		}

		if (identifierEquals("RELEASE")) {
			SQLStatement *stmt = parseReleaseSavePoint();
			theStatementList.push_back(stmt);
			continue;
		}

		if (identifierEquals("SAVEPOINT")) {
			SQLStatement *stmt = parseSavePoint();
			theStatementList.push_back(stmt);
			continue;
		}

		if (identifierEquals("ROLLBACK")) {
			SQLRollbackStatement *stmt = parseRollback();

			theStatementList.push_back(stmt);
			continue;
		}

		if (identifierEquals("COMMIT")) {
			SQLStatement *stmt = parseCommit();

			theStatementList.push_back(stmt);
			continue;
		}

		if (lexer->getToken() == SHOW) {
			SQLStatement *stmt = parseShow();

			theStatementList.push_back(stmt);
			continue;
		}

		if (lexer->getToken() == LEFTPAREN) {
			char markChar = lexer->current();
			int markBp = lexer->bp();
			lexer->nextToken();
			if (lexer->getToken() == TOKEN_SELECT) {
				lexer->reset(markBp, markChar, LEFTPAREN);
				SQLStatement *stmt = parseSelect();
				theStatementList.push_back(stmt);
				continue;
			}
		}

		if (parseStatementListDialect(theStatementList)) {
			continue;
		}

		if (lexer->getToken() == COMMENT) {
			theStatementList.push_back(this->parseComment());
			continue;
		}

		std::stringstream stream;
		stream << "syntax error, "  <<  lexer->getToken() <<  " "  <<  lexer->getStringVal()  <<  ", pos "  <<  lexer->getPos();
		throw new ParserException(stream.str());
	}
}

SQLRollbackStatement *SQLStatementParser::parseRollback() {

	//std::cout << "\t" <<  __FILE__ << ": " << __LINE__ << ", in SQLStatementParser::parseRollback, step 1" << std::endl;
	lexer->nextToken();

	if (identifierEquals("WORK")) {
		lexer->nextToken();
	}

	SQLRollbackStatement *stmt = new SQLRollbackStatement();

	if (lexer->getToken() == TO) {
		lexer->nextToken();

		if (identifierEquals("SAVEPOINT")) {
			lexer->nextToken();
		}

		stmt->setTo(this->exprParser->getName());
	}
	return stmt;
}

SQLStatement *SQLStatementParser::parseCommit() {

	std::stringstream stream;
	stream << "TODO " <<  lexer->getToken() <<  " "  <<  lexer->getStringVal();
	throw new ParserException(stream.str());
}

SQLStatement *SQLStatementParser::parseShow() {
	std::stringstream stream;
	stream << "TODO " <<  lexer->getToken() <<  " "  <<  lexer->getStringVal();
	throw new ParserException(stream.str());
}

SQLUseStatement *SQLStatementParser::parseUse() {
	//std::cout << "\t" <<  __FILE__ << ": " << __LINE__ << ", in SQLStatementParser::parseUse, step 1" << std::endl;
	accept(USE);
	SQLUseStatement *stmt = new SQLUseStatement();
	//std::auto_ptr<SQLUseStatement> stmt (new SQLUseStatement);
	stmt->setDatabase(this->exprParser->getName());
	return stmt;
}

SQLGrantStatement *SQLStatementParser::parseGrant() {

	//std::cout << "\t" <<  __FILE__ << ": " << __LINE__ << ", in SQLStatementParser::parseGrant, step 1" << std::endl;
	accept(GRANT);
	SQLGrantStatement *stmt = new SQLGrantStatement();

	for (;;) {
		std::string privilege = "";
		if (lexer->getToken() == ALL) {
			lexer->nextToken();
			if (identifierEquals("PRIVILEGES")) {
				privilege = "ALL PRIVILEGES";
			} else {
				privilege = "ALL";
			}
		} else if (lexer->getToken() == TOKEN_SELECT) {
			privilege = "SELECT";
			lexer->nextToken();
		} else if (lexer->getToken() == UPDATE) {
			privilege = "UPDATE";
			lexer->nextToken();
		} else if (lexer->getToken() == TOKEN_DELETE) {
			privilege = "DELETE";
			lexer->nextToken();
		} else if (lexer->getToken() == TOKEN_INSERT) {
			privilege = "INSERT";
			lexer->nextToken();
		} else if (lexer->getToken() == INDEX) {
			lexer->nextToken();
			privilege = "INDEX";
		} else if (lexer->getToken() == TRIGGER) {
			lexer->nextToken();
			privilege = "TRIGGER";
		} else if (lexer->getToken() == REFERENCES) {
			privilege = "REFERENCES";
			lexer->nextToken();
		} else if (lexer->getToken() == CREATE) {
			lexer->nextToken();

			if (lexer->getToken() == TABLE) {
				privilege = "CREATE TABLE";
				lexer->nextToken();
			} else if (lexer->getToken() == SESSION) {
				privilege = "CREATE SESSION";
				lexer->nextToken();
			} else if (lexer->getToken() == TABLESPACE) {
				privilege = "CREATE TABLESPACE";
				lexer->nextToken();
			} else if (lexer->getToken() == USER) {
				privilege = "CREATE USER";
				lexer->nextToken();
			} else if (lexer->getToken() == VIEW) {
				privilege = "CREATE VIEW";
				lexer->nextToken();
			} else if (lexer->getToken() == ANY) {
				lexer->nextToken();

				if (lexer->getToken() == TABLE) {
					lexer->nextToken();
					privilege = "CREATE ANY TABLE";
				} else if (identifierEquals("MATERIALIZED")) {
					lexer->nextToken();
					accept(VIEW);
					privilege = "CREATE ANY MATERIALIZED VIEW";
				} else {

					std::stringstream stream;
					stream << "TODO " <<  lexer->getToken() <<  " "  <<  lexer->getStringVal();
					throw new ParserException(stream.str());
					//throw new ParserException("TODO : " + lexer->getToken() + " " + lexer->getStringVal());
				}
			} else if (identifierEquals("SYNONYM")) {
				privilege = "CREATE SYNONYM";
				lexer->nextToken();
			} else if (identifierEquals("ROUTINE")) {
				privilege = "CREATE ROUTINE";
				lexer->nextToken();
			} else if (identifierEquals("TEMPORARY")) {
				lexer->nextToken();
				accept(TABLE);
				privilege = "CREATE TEMPORARY TABLE";
			} else {

				std::stringstream stream;
				stream << "TODO " <<  lexer->getToken() <<  " "  <<  lexer->getStringVal();
				throw new ParserException(stream.str());
				//throw new ParserException("TODO : " + lexer->getToken() + " " + lexer->getStringVal());
			}
		} else if (lexer->getToken() == ALTER) {
			lexer->nextToken();
			if (lexer->getToken() == TABLE) {
				privilege = "ALTER TABLE";
				lexer->nextToken();
			} else if (lexer->getToken() == SESSION) {
				privilege = "ALTER SESSION";
				lexer->nextToken();
			} else if (lexer->getToken() == ANY) {
				lexer->nextToken();

				if (lexer->getToken() == TABLE) {
					lexer->nextToken();
					privilege = "ALTER ANY TABLE";
				} else if (identifierEquals("MATERIALIZED")) {
					lexer->nextToken();
					accept(VIEW);
					privilege = "ALTER ANY MATERIALIZED VIEW";
				} else {
					std::stringstream stream;
					stream << "TODO " <<  lexer->getToken() <<  " "  <<  lexer->getStringVal();
					throw new ParserException(stream.str());
					//throw new ParserException("TODO : " + lexer->getToken() + " " + lexer->getStringVal());
				}
			} else {

				std::stringstream stream;
				stream << "TODO " <<  lexer->getToken() <<  " "  <<  lexer->getStringVal();
				throw new ParserException(stream.str());
				//throw new ParserException("TODO : " + lexer->getToken() + " " + lexer->getStringVal());
			}
		} else if (lexer->getToken() == DROP) {
			lexer->nextToken();
			if (lexer->getToken() == DROP) {
				privilege = "DROP TABLE";
				lexer->nextToken();
			} else if (lexer->getToken() == SESSION) {
				privilege = "DROP SESSION";
				lexer->nextToken();
			} else if (lexer->getToken() == ANY) {
				lexer->nextToken();

				if (lexer->getToken() == TABLE) {
					lexer->nextToken();
					privilege = "DROP ANY TABLE";
				} else if (identifierEquals("MATERIALIZED")) {
					lexer->nextToken();
					accept(VIEW);
					privilege = "DROP ANY MATERIALIZED VIEW";
				} else {

					std::stringstream stream;
					stream << "TODO " <<  lexer->getToken() <<  " "  <<  lexer->getStringVal();
					throw new ParserException(stream.str());
					//throw new ParserException("TODO : " + lexer->getToken() + " " + lexer->getStringVal());
				}
			} else {
				privilege = "DROP";
			}
		} else if (identifierEquals("USAGE")) {
			privilege = "USAGE";
			lexer->nextToken();
		} else if (identifierEquals("EXECUTE")) {
			privilege = "EXECUTE";
			lexer->nextToken();
		} else if (identifierEquals("PROXY")) {
			privilege = "PROXY";
			lexer->nextToken();
		} else if (identifierEquals("QUERY")) {
			lexer->nextToken();
			acceptIdentifier("REWRITE");
			privilege = "QUERY REWRITE";
		} else if (identifierEquals("GLOBAL")) {
			lexer->nextToken();
			acceptIdentifier("QUERY");
			acceptIdentifier("REWRITE");
			privilege = "GLOBAL QUERY REWRITE";
		} else if (identifierEquals("INHERIT")) {
			lexer->nextToken();
			acceptIdentifier("PRIVILEGES");
			privilege = "INHERIT PRIVILEGES";
		} else if (identifierEquals("EVENT")) {
			lexer->nextToken();
			privilege = "EVENT";
		} else if (identifierEquals("FILE")) {
			lexer->nextToken();
			privilege = "FILE";
		} else if (lexer->getToken() == GRANT) {
			lexer->nextToken();
			acceptIdentifier("OPTION");
			privilege = "GRANT OPTION";
		} else if (lexer->getToken() == LOCK) {
			lexer->nextToken();
			acceptIdentifier("TABLES");
			privilege = "LOCK TABLES";
		} else if (identifierEquals("PROCESS")) {
			lexer->nextToken();
			privilege = "PROCESS";
		} else if (identifierEquals("RELOAD")) {
			lexer->nextToken();
			privilege = "RELOAD";
		} else if (identifierEquals("REPLICATION")) {
			lexer->nextToken();
			if (identifierEquals("SLAVE")) {
				lexer->nextToken();
				privilege = "REPLICATION SLAVE";
			} else {
				acceptIdentifier("CLIENT");
				privilege = "REPLICATION CLIENT";
			}
		} else if (lexer->getToken() == SHOW) {
			lexer->nextToken();

			if (lexer->getToken() == VIEW) {
				lexer->nextToken();
				privilege = "SHOW VIEW";
			} else {
				acceptIdentifier("DATABASES");
				privilege = "SHOW DATABASES";
			}
		} else if (identifierEquals("SHUTDOWN")) {
			lexer->nextToken();
			privilege = "SHUTDOWN";
		} else if (identifierEquals("SUPER")) {
			lexer->nextToken();
			privilege = "SUPER";
		}

		if (privilege != "") {
			SQLExpr *expr = new SQLIdentifierExpr(privilege);

			if (lexer->getToken() == LEFTPAREN) {
				expr = this->exprParser->primaryRest(expr);
			}

			expr->setParent(stmt);
			stmt->getPrivileges().push_back(expr);
		}

		if (lexer->getToken() == COMMA) {
			lexer->nextToken();
			continue;
		}
		break;
	}

	if (lexer->getToken() == ON) {
		lexer->nextToken();

		if (lexer->getToken() == PROCEDURE) {
			lexer->nextToken();
			stmt->setObjectType(SQLGrantStatement::PROCEDURE);
		} else if (lexer->getToken() == FUNCTION) {
			lexer->nextToken();
			stmt->setObjectType(SQLGrantStatement::FUNCTION);
		} else if (lexer->getToken() == TABLE) {
			lexer->nextToken();
			stmt->setObjectType(SQLGrantStatement::TABLE);
		} else if (lexer->getToken() == USER) {
			lexer->nextToken();
			stmt->setObjectType(SQLGrantStatement::USER);
		}

		stmt->setOn(this->exprParser->getExpr());
	}

	if (lexer->getToken() == TO) {
		lexer->nextToken();
		stmt->setTo(this->exprParser->getExpr());
	}

	if (lexer->getToken() == WITH) {
		lexer->nextToken();

		for (;;) {
			if (identifierEquals("MAX_QUERIES_PER_HOUR")) {
				lexer->nextToken();
				stmt->setMaxQueriesPerHour(this->exprParser->primary());
				continue;
			}

			if (identifierEquals("MAX_UPDATES_PER_HOUR")) {
				lexer->nextToken();
				stmt->setMaxUpdatesPerHour(this->exprParser->primary());
				continue;
			}

			if (identifierEquals("MAX_CONNECTIONS_PER_HOUR")) {
				lexer->nextToken();
				stmt->setMaxConnectionsPerHour(this->exprParser->primary());
				continue;
			}

			if (identifierEquals("MAX_USER_CONNECTIONS")) {
				lexer->nextToken();
				stmt->setMaxUserConnections(this->exprParser->primary());
				continue;
			}

			break;
		}
	}

	if (identifierEquals("ADMIN")) {
		lexer->nextToken();
		acceptIdentifier("OPTION");
		stmt->setAdminOption(true);
	}

	if (lexer->getToken() == IDENTIFIED) {
		lexer->nextToken();
		accept(BY);
		stmt->setIdentifiedBy(this->exprParser->getExpr());
	}

	return stmt;
}

SQLStatement *SQLStatementParser::parseSavePoint() {

	//std::cout << "\t" <<  __FILE__ << ": " << __LINE__ << ", in SQLStatementParser::parseSavePoint, step 1" << std::endl;
	acceptIdentifier("SAVEPOINT");
	SQLSavePointStatement *stmt = new SQLSavePointStatement();
	stmt->setName(this->exprParser->getName());
	return stmt;
}

SQLStatement *SQLStatementParser::parseReleaseSavePoint() {

	//std::cout << "\t" <<  __FILE__ << ": " << __LINE__ << ", in SQLStatementParser::parseReleaseSavePoint, step 1" << std::endl;
	acceptIdentifier("RELEASE");
	acceptIdentifier("SAVEPOINT");
	SQLReleaseSavePointStatement *stmt = new SQLReleaseSavePointStatement();
	stmt->setName(this->exprParser->getName());
	return stmt;
}

SQLStatement *SQLStatementParser::parseAlter() {
	//std::cout << "\t" <<  __FILE__ << ": " << __LINE__ << ", in SQLStatementParser::parseAlter, step 1" << std::endl;
	accept(ALTER);

	if (lexer->getToken() == TABLE) {
		lexer->nextToken();

		SQLAlterTableStatement *stmt = new SQLAlterTableStatement();
		stmt->setName(this->exprParser->getName());

		for (;;) {
			if (lexer->getToken() == DROP) {
				parseAlterDrop(stmt);
			} else if (identifierEquals("ADD")) {
				lexer->nextToken();

				if (lexer->getToken() == PRIMARY) {
					SQLPrimaryKey *primaryKey = this->exprParser->parsePrimaryKey();
					SQLAlterTableAddConstraint *item = new SQLAlterTableAddConstraint(primaryKey);
					stmt->getItems().push_back(item);
				} else if (lexer->getToken() == IDENTIFIER) {
					SQLAlterTableAddColumn *item = parseAlterTableAddColumn();
					stmt->getItems().push_back(item);
				} else {

					std::stringstream stream;
					stream << "TODO " <<  lexer->getToken() <<  " "  <<  lexer->getStringVal();
					throw new ParserException(stream.str());
					//throw new ParserException("TODO " + lexer->getToken() + " " + lexer->getStringVal());
				}
			} else if (lexer->getToken() == DISABLE) {
				lexer->nextToken();

				if (lexer->getToken() == CONSTRAINT) {
					lexer->nextToken();
					SQLAlterTableDisableConstraint *item = new SQLAlterTableDisableConstraint();
					item->setConstraintName(this->exprParser->getName());
					stmt->getItems().push_back(item);
				} else {
					acceptIdentifier("KEYS");
					SQLAlterTableDisableKeys *item = new SQLAlterTableDisableKeys();
					stmt->getItems().push_back(item);
				}
			} else if (lexer->getToken() == ENABLE) {
				lexer->nextToken();
				if (lexer->getToken() == CONSTRAINT) {
					lexer->nextToken();
					SQLAlterTableEnableConstraint *item = new SQLAlterTableEnableConstraint();
					item->setConstraintName(this->exprParser->getName());
					stmt->getItems().push_back(item);
				} else {
					acceptIdentifier("KEYS");
					SQLAlterTableEnableKeys *item = new SQLAlterTableEnableKeys();
					stmt->getItems().push_back(item);
				}
			} else if (lexer->getToken() == ALTER) {
				lexer->nextToken();
				if (lexer->getToken() == COLUMN) {
					lexer->nextToken();
					SQLColumnDefinition *column = this->exprParser->parseColumn();
					SQLAlterTableAlterColumn *alterColumn = new SQLAlterTableAlterColumn();
					alterColumn->setColumn(column);
					stmt->getItems().push_back(alterColumn);
				} else {

					std::stringstream stream;
					stream << "TODO " <<  lexer->getToken() <<  " "  <<  lexer->getStringVal();
					throw new ParserException(stream.str());
					//throw new ParserException("TODO " + lexer->getToken() + " " + lexer->getStringVal());
				}
			} else if (lexer->getToken() == WITH) {
				lexer->nextToken();
				acceptIdentifier("NOCHECK");
				acceptIdentifier("ADD");
				SQLConstaint *check = this->exprParser->parseConstaint();

				SQLAlterTableAddConstraint *addCheck = new SQLAlterTableAddConstraint();
				addCheck->setWithNoCheck(true);
				addCheck->setConstraint(check);
				stmt->getItems().push_back(addCheck);
			} else {
				break;
			}
		}

		return stmt;
	}

	std::stringstream stream;
	stream << "TODO " <<  lexer->getToken() <<  " "  <<  lexer->getStringVal();
	throw new ParserException(stream.str());
	//throw new ParserException("TODO " + lexer->getToken() + " " + lexer->getStringVal());
}

void SQLStatementParser::parseAlterDrop(SQLAlterTableStatement *stmt) {
	//std::cout << "\t" <<  __FILE__ << ": " << __LINE__ << ", in SQLStatementParser::parseAlterDrop, step 1" << std::endl;
	lexer->nextToken();

	if (lexer->getToken() == CONSTRAINT) {
		lexer->nextToken();
		SQLAlterTableDropConstraint *item = new SQLAlterTableDropConstraint();
		item->setConstraintName(this->exprParser->getName());
		stmt->getItems().push_back(item);
	} else if (lexer->getToken() == COLUMN) {
		lexer->nextToken();
		SQLAlterTableDropColumnItem *item = new SQLAlterTableDropColumnItem();
		this->exprParser->getNames(item->getColumns());
		stmt->getItems().push_back(item);
	} else {

		std::stringstream stream;
		stream << "TODO " <<  lexer->getToken() <<  " "  <<  lexer->getStringVal();
		throw new ParserException(stream.str());
		//throw new ParserException("TODO " + lexer->getToken() + " " + lexer->getStringVal());
	}
}

SQLStatement *SQLStatementParser::parseRename() {

	std::stringstream stream;
	stream << "TODO " <<  lexer->getToken() <<  " "  <<  lexer->getStringVal();
	throw new ParserException(stream.str());
	//throw new ParserException("TODO " + lexer->getToken() + " " + lexer->getStringVal());
}

SQLDropTableStatement *SQLStatementParser::parseDropTable(bool acceptDrop) {
	//std::cout << "\t" <<  __FILE__ << ": " << __LINE__ << ", in SQLStatementParser::parseDropTable, step 1" << std::endl;
	if (acceptDrop) {
		accept(DROP);
	}

	SQLDropTableStatement *stmt = new SQLDropTableStatement();

	if (identifierEquals("TEMPORARY")) {
		lexer->nextToken();
		stmt->setTemporary(true);
	}

	accept(TABLE);

	if (lexer->getToken() == IF) {
		lexer->nextToken();
		accept(EXISTS);
		stmt->setIfExists(true);
	}

	for (;;) {
		SQLName *name = this->exprParser->getName();
		stmt->getTableSources().push_back(new SQLExprTableSource(name));
		if (lexer->getToken() == COMMA) {
			lexer->nextToken();
			continue;
		}
		break;
	}

	for (;;) {
		if (identifierEquals("RESTRICT")) {
			lexer->nextToken();
			stmt->setRestrict(true);
			continue;
		}

		if (identifierEquals("CASCADE")) {
			lexer->nextToken();
			stmt->setCascade(true);

			if (identifierEquals("CONSTRAINTS")) { // for oracle
				lexer->nextToken();
			}

			continue;
		}

		if (lexer->getToken() == PURGE) {
			lexer->nextToken();
			stmt->setPurge(true);
			continue;
		}

		break;
	}

	return stmt;
}

SQLDropSequenceStatement *SQLStatementParser::parseDropSequece(bool acceptDrop) {
	//std::cout << "\t" <<  __FILE__ << ": " << __LINE__ << ", in SQLStatementParser::parseDropSequece, step 1" << std::endl;
	if (acceptDrop) {
		accept(DROP);
	}

	lexer->nextToken();

	SQLName *name = this->exprParser->getName();

	SQLDropSequenceStatement *stmt = new SQLDropSequenceStatement();
	stmt->setName(name);
	return stmt;
}

SQLDropTriggerStatement *SQLStatementParser::parseDropTrigger(bool acceptDrop) {
	//std::cout << "\t" <<  __FILE__ << ": " << __LINE__ << ", in SQLStatementParser::parseDropTrigger, step 1" << std::endl;
	if (acceptDrop) {
		accept(DROP);
	}

	lexer->nextToken();

	SQLName *name = this->exprParser->getName();

	SQLDropTriggerStatement *stmt = new SQLDropTriggerStatement();
	stmt->setName(name);
	return stmt;
}

SQLDropViewStatement *SQLStatementParser::parseDropView(bool acceptDrop) {
	//std::cout << "\t" <<  __FILE__ << ": " << __LINE__ << ", in SQLStatementParser::parseDropView, step 1" << std::endl;
	if (acceptDrop) {
		accept(DROP);
	}

	SQLDropViewStatement *stmt = new SQLDropViewStatement();

	accept(VIEW);

	if (lexer->getToken() == IF) {
		lexer->nextToken();
		accept(EXISTS);
		stmt->setIfExists(true);
	}

	for (;;) {
		SQLName *name = this->exprParser->getName();
		stmt->getTableSources().push_back(new SQLExprTableSource(name));
		if (lexer->getToken() == COMMA) {
			lexer->nextToken();
			continue;
		}
		break;
	}

	if (identifierEquals("RESTRICT")) {
		lexer->nextToken();
		stmt->setRestrict(true);
	} else if (identifierEquals("CASCADE")) {
		lexer->nextToken();

		if (identifierEquals("CONSTRAINTS")) { // for oracle
			lexer->nextToken();
		}

		stmt->setCascade(true);
	}

	return stmt;
}

SQLDropDatabaseStatement *SQLStatementParser::parseDropDatabase(bool acceptDrop) {
	//std::cout << "\t" <<  __FILE__ << ": " << __LINE__ << ", in SQLStatementParser::parseDropDatabase, step 1" << std::endl;
	if (acceptDrop) {
		accept(DROP);
	}

	SQLDropDatabaseStatement *stmt = new SQLDropDatabaseStatement();

	accept(DATABASE);

	if (lexer->getToken() == IF) {
		lexer->nextToken();
		accept(EXISTS);
		stmt->setIfExists(true);
	}

	SQLName *name = this->exprParser->getName();
	stmt->setDatabase(name);

	return stmt;
}

SQLDropFunctionStatement *SQLStatementParser::parseDropFunction(bool acceptDrop) {
	if (acceptDrop) {
		accept(DROP);
	}

	SQLDropFunctionStatement *stmt = new SQLDropFunctionStatement();

	accept(FUNCTION);

	if (lexer->getToken() == IF) {
		lexer->nextToken();
		accept(EXISTS);
		stmt->setIfExists(true);
	}

	SQLName *name = this->exprParser->getName();
	stmt->setName(name);

	return stmt;
}

SQLDropTableSpaceStatement *SQLStatementParser::parseDropTablespace(bool acceptDrop) {
	if (acceptDrop) {
		accept(DROP);
	}

	SQLDropTableSpaceStatement *stmt = new SQLDropTableSpaceStatement();

	accept(TABLESPACE);

	if (lexer->getToken() == IF) {
		lexer->nextToken();
		accept(EXISTS);
		stmt->setIfExists(true);
	}

	SQLName *name = this->exprParser->getName();
	stmt->setName(name);

	return stmt;
}

SQLDropProcedureStatement *SQLStatementParser::parseDropProcedure(bool acceptDrop) {
	if (acceptDrop) {
		accept(DROP);
	}

	SQLDropProcedureStatement *stmt = new SQLDropProcedureStatement();

	accept(PROCEDURE);

	if (lexer->getToken() == IF) {
		lexer->nextToken();
		accept(EXISTS);
		stmt->setIfExists(true);
	}

	SQLName *name = this->exprParser->getName();
	stmt->setName(name);

	return stmt;
}

SQLStatement *SQLStatementParser::parseTruncate() {
	accept(TRUNCATE);
	if (lexer->getToken() == TABLE) {
		lexer->nextToken();
	}
	SQLTruncateStatement *stmt = new SQLTruncateStatement();

	if (lexer->getToken() == ONLY) {
		lexer->nextToken();
		stmt->setOnly(true);
	}

	for (;;) {
		SQLName *name = this->exprParser->getName();
		stmt->addTableSource(name);

		if (lexer->getToken() == COMMA) {
			lexer->nextToken();
			continue;
		}

		break;
	}

	for (;;) {
		if (lexer->getToken() == PURGE) {
			lexer->nextToken();

			if (identifierEquals("SNAPSHOT")) {
				lexer->nextToken();
				acceptIdentifier("LOG");
				stmt->setPurgeSnapshotLog(true);
			} else {

				std::stringstream stream;
				stream << "TODO " <<  lexer->getToken() <<  " "  <<  lexer->getStringVal();
				throw new ParserException(stream.str());
				//throw new ParserException("TODO : " + lexer->getToken() + " " + lexer->getStringVal());
			}
			continue;
		}

		if (lexer->getToken() == RESTART) {
			lexer->nextToken();
			accept(IDENTITY);
			stmt->setRestartIdentity(true);
			continue;
		} else if (lexer->getToken() == SHARE) {
			lexer->nextToken();
			accept(IDENTITY);
			stmt->setRestartIdentity(false);
			continue;
		}

		if (lexer->getToken() == CASCADE) {
			lexer->nextToken();
			stmt->setCascade(true);
			continue;
		} else if (lexer->getToken() == RESTRICT) {
			lexer->nextToken();
			stmt->setCascade(false);
			continue;
		}

		break;
	}

	return stmt;
}

SQLStatement *SQLStatementParser::parseInsert() {
	SQLInsertStatement *insertStatement = new SQLInsertStatement();

	if (lexer->getToken() == TOKEN_INSERT) {
		accept(TOKEN_INSERT);
	}

	parseInsert0(insertStatement);
	return insertStatement;
}

void SQLStatementParser::parseInsert0(SQLInsertInto *insertStatement) {
	parseInsert0(insertStatement, true);
}

void SQLStatementParser::parseInsert0_hinits(SQLInsertInto *insertStatement) {

}

void SQLStatementParser::parseInsert0(SQLInsertInto *insertStatement, bool acceptSubQuery) {
	//std::cout << "\t" <<  __FILE__ << ": " << __LINE__ << ", in SQLStatementParser::parseInsert0, step 1" << std::endl;
	if (lexer->getToken() == INTO) {
		lexer->nextToken();

		SQLName *tableName = this->exprParser->getName();
		insertStatement->setTableName(tableName);

		if (lexer->getToken() == LITERAL_ALIAS) {
			insertStatement->setAlias(as());
		}

		parseInsert0_hinits(insertStatement);

		if (lexer->getToken() == IDENTIFIER) {
			insertStatement->setAlias(lexer->getStringVal());
			lexer->nextToken();
		}
	}

	if (lexer->getToken() == (LEFTPAREN)) {
		lexer->nextToken();
		this->exprParser->exprList(insertStatement->getColumns());
		accept(RPAREN);
	}

	if (lexer->getToken() == VALUES) {
		lexer->nextToken();
		accept(LEFTPAREN);
		ValuesClause *values = new ValuesClause();
		this->exprParser->exprList(values->getValues());
		insertStatement->setValues(values);
		accept(RPAREN);
	} else if (acceptSubQuery && (lexer->getToken() == TOKEN_SELECT || lexer->getToken() == LEFTPAREN)) {
		//SQLQueryExpr *queryExpr = (SQLQueryExpr) this->exprParser->getExpr();
		SQLQueryExpr* queryExpr = dynamic_cast<SQLQueryExpr *>(this->exprParser->getExpr());

		insertStatement->setQuery(queryExpr->getSubQuery());
	}
}

bool SQLStatementParser::parseStatementListDialect(std::list<SQLStatement*> & theStatementList) {
	return false;
}

SQLDropUserStatement *SQLStatementParser::parseDropUser() {
	accept(USER);

	SQLDropUserStatement *stmt = new SQLDropUserStatement();
	for (;;) {
		SQLExpr *expr = this->exprParser->getExpr();
		stmt->getUsers().push_back(expr);
		if (lexer->getToken() == COMMA) {
			lexer->nextToken();
			continue;
		}
		break;
	}

	return stmt;
}

SQLStatement *SQLStatementParser::parseDropIndex() {
	accept(INDEX);
	SQLDropIndexStatement *stmt = new SQLDropIndexStatement();
	stmt->setIndexName(this->exprParser->getName());

	if (lexer->getToken() == ON) {
		lexer->nextToken();
		stmt->setTableName(this->exprParser->getName());
	}
	return stmt;
}

SQLCallStatement *SQLStatementParser::parseCall() {

	bool brace = false;
	if (lexer->getToken() == LBRACE) {
		lexer->nextToken();
		brace = true;
	}

	SQLCallStatement *stmt = new SQLCallStatement();

	if (lexer->getToken() == QUES) {
		lexer->nextToken();
		accept(EQ);
		std::string qm ("?");
		stmt->setOutParameter(new SQLVariantRefExpr(qm));
	}

	acceptIdentifier("CALL");


	stmt->setProcedureName(exprParser->getName());

	if (lexer->getToken() == LEFTPAREN) {
		lexer->nextToken();
		exprParser->exprList(stmt->getParameters());
		accept(RPAREN);
	}

	if (brace) {
		accept(RBRACE);
		stmt->setBrace(true);
	}

	return stmt;
}

SQLStatement *SQLStatementParser::parseSet() {
	accept(SET);
	SQLSetStatement *stmt = new SQLSetStatement();

	parseAssignItems(stmt->getItems(), stmt);

	return stmt;
}

void SQLStatementParser::parseAssignItems(std::list<SQLAssignItem *> & items, SQLObject *parent) {
	//std::cout << "\t" <<  __FILE__ << ": " << __LINE__ << ", in SQLStatementParser::parseAssignItems, step 1" << std::endl;
	for (;;) {
		SQLAssignItem *item = exprParser->parseAssignItem();
		item->setParent(parent);
		items.push_back(item);

		if (lexer->getToken() == COMMA) {
			lexer->nextToken();
			continue;
		} else {
			break;
		}
	}
}

SQLStatement *SQLStatementParser::parseCreate() {
	char markChar = lexer->current();
	int markBp = lexer->bp();

	accept(CREATE);

	Token token = lexer->getToken();

	if (token == TABLE || identifierEquals("GLOBAL")) {
		SQLCreateTableParser *createTableParser = getSQLCreateTableParser();
		return createTableParser->parseCrateTable(false);
	} else if (token == INDEX //
			|| token == UNIQUE //
			|| identifierEquals("NONCLUSTERED") // sql server
			) {
		return parseCreateIndex(false);
	} else if (lexer->getToken() == SEQUENCE) {
		return parseCreateSequence(false);
	} else if (token == OR) {
		lexer->nextToken();
		accept(REPLACE);
		if (lexer->getToken() == PROCEDURE) {
			lexer->reset(markBp, markChar, CREATE);
			return parseCreateProcedure();
		}

		// lexer->reset(mark_bp, mark_ch, CREATE);
		std::stringstream stream;
		stream << "TODO " <<  lexer->getToken() <<  " "  <<  lexer->getStringVal();
		throw new ParserException(stream.str());
		//throw new ParserException("TODO " + lexer->getToken() + " " + lexer->getStringVal());
	} else if (token == DATABASE) {
		lexer->nextToken();
		if (identifierEquals("LINK")) {
			lexer->reset(markBp, markChar, CREATE);
			return parseCreateDbLink();
		}

		lexer->reset(markBp, markChar, CREATE);
		return parseCreateDatabase();
	} else if (identifierEquals("PUBLIC") || identifierEquals("SHARE")) {
		lexer->reset(markBp, markChar, CREATE);
		return parseCreateDbLink();
	} else if (token == VIEW) {
		return parseCreateView();
	} else if (token == TRIGGER) {
		return parseCreateTrigger();
	}

	throw new ParserException("TODO " + lexer->getToken());
}

SQLStatement *SQLStatementParser::parseCreateDbLink() {
	throw new ParserException("TODO " + lexer->getToken());
}

SQLStatement *SQLStatementParser::parseCreateTrigger() {
	accept(TRIGGER);

	SQLCreateTriggerStatement *stmt = new SQLCreateTriggerStatement();
	stmt->setName(this->exprParser->getName());

	if (identifierEquals("BEFORE")) {
		stmt->setTriggerType(SQLCreateTriggerStatement::BEFORE);
		lexer->nextToken();
	} else if (identifierEquals("AFTER")) {
		stmt->setTriggerType(SQLCreateTriggerStatement::AFTER);
		lexer->nextToken();
	} else if (identifierEquals("INSTEAD")) {
		lexer->nextToken();
		accept(OF);
		stmt->setTriggerType(SQLCreateTriggerStatement::INSTEAD_OF);
	}

	for (;;) {
		if (lexer->getToken() == TOKEN_INSERT) {
			lexer->nextToken();
			stmt->getTriggerEvents().push_back(SQLCreateTriggerStatement::TRIGGER_INSERT);
			continue;
		}

		if (lexer->getToken() == UPDATE) {
			lexer->nextToken();
			stmt->getTriggerEvents().push_back(SQLCreateTriggerStatement::TRIGGER_UPDATE);
			continue;
		}

		if (lexer->getToken() == TOKEN_DELETE) {
			lexer->nextToken();
			stmt->getTriggerEvents().push_back(SQLCreateTriggerStatement::TRIGGER_DELETE);
			continue;
		}
		break;
	}

	accept(ON);
	stmt->setOn(this->exprParser->getName());

	if (lexer->getToken() == FOR) {
		lexer->nextToken();
		acceptIdentifier("EACH");
		accept(ROW);
		stmt->setForEachRow(true);
	}

	SQLStatement *body = this->parseBlock();
	stmt->setBody(body);
	return stmt;
}

SQLStatement *SQLStatementParser::parseBlock() {
	throw new ParserException("TODO " + lexer->getToken());
}

SQLStatement *SQLStatementParser::parseCreateDatabase() {
	if (lexer->getToken() == CREATE) {
		lexer->nextToken();
	}

	accept(DATABASE);

	SQLCreateDatabaseStatement *stmt = new SQLCreateDatabaseStatement();
	stmt->setName(this->exprParser->getName());
	return stmt;
}

SQLStatement *SQLStatementParser::parseCreateProcedure() {
	throw new ParserException("TODO " + lexer->getToken());
}

SQLStatement *SQLStatementParser::parseCreateSequence(bool acceptCreate) {
	throw new ParserException("TODO " + lexer->getToken());
}

SQLStatement *SQLStatementParser::parseCreateIndex(bool acceptCreate) {
	if (acceptCreate) {
		accept(CREATE);
	}

	SQLCreateIndexStatement *stmt = new SQLCreateIndexStatement();
	if (lexer->getToken() == UNIQUE) {
		lexer->nextToken();
		if (identifierEquals("CLUSTERED")) {
			lexer->nextToken();
			std::string x = "UNIQUE CLUSTERED";
			stmt->setType(x);
		} else {
			std::string x = "UNIQUE";
			stmt->setType(x);
		}
	} else if (identifierEquals("FULLTEXT")) {
		std::string x = "FULLTEXT";
		stmt->setType(x);
		lexer->nextToken();
	} else if (identifierEquals("NONCLUSTERED")) {
		std::string x = "NONCLUSTERED";
		stmt->setType(x);
		lexer->nextToken();
	}

	accept(INDEX);

	stmt->setName(this->exprParser->getName());

	accept(ON);

	stmt->setTable(this->exprParser->getName());

	accept(LEFTPAREN);

	for (;;) {
		SQLSelectOrderByItem *item = this->exprParser->parseSelectOrderByItem();
		item->setParent(stmt);
		stmt->getItems().push_back(item);
		if (lexer->getToken() == COMMA) {
			lexer->nextToken();
			continue;
		}
		break;
	}
	accept(RPAREN);

	return stmt;
}

SQLCreateTableParser *SQLStatementParser::getSQLCreateTableParser() {
	return new SQLCreateTableParser(this->exprParser);
}

SQLSelectStatement *SQLStatementParser::parseSelect() {
	//std::cout << "\t" <<  __FILE__ << ": " << __LINE__ << ", in SQLStatementParser::parseSelect, step 1" << std::endl;
	SQLSelectParser *selectParser = createSQLSelectParser();
	//std::cout << "\t" <<  __FILE__ << ": " << __LINE__ << ", in SQLStatementParser::parseSelect, step 2" << std::endl;
	SQLSelect *select = selectParser->select();
	//std::cout << "\t" <<  __FILE__ << ": " << __LINE__ << ", in SQLStatementParser::parseSelect, step 3" << std::endl;
	delete selectParser;
	//std::cout << "\t" <<  __FILE__ << ": " << __LINE__ << ", in SQLStatementParser::parseSelect, step 4" << std::endl;
	return new SQLSelectStatement(select);
}

SQLSelectParser *SQLStatementParser::createSQLSelectParser() {
	//std::cout << "\t" <<  __FILE__ << ": " << __LINE__ << ", in SQLStatementParser::createSQLSelectParser, step 1" << std::endl;
	return new OdpsSelectParser(this->exprParser);
}

SQLUpdateStatement *SQLStatementParser::parseUpdateStatement() {
	SQLUpdateStatement *udpateStatement = createUpdateStatement();

	if (lexer->getToken() == UPDATE) {
		lexer->nextToken();

		SQLTableSource *tableSource = this->exprParser->createSelectParser()->parseTableSource();
		udpateStatement->setTableSource(tableSource);
	}

	parseUpdateSet(udpateStatement);

	if (lexer->getToken() == (WHERE)) {
		lexer->nextToken();
		udpateStatement->setWhere(this->exprParser->getExpr());
	}

	return udpateStatement;
}

void SQLStatementParser::parseUpdateSet(SQLUpdateStatement *update) {
	accept(SET);

	for (;;) {
		SQLUpdateSetItem *item = new SQLUpdateSetItem();

		if (lexer->getToken() == (LEFTPAREN)) {
			lexer->nextToken();
			SQLListExpr *list = new SQLListExpr();
			this->exprParser->exprList(list->getItems());
			accept(RPAREN);
			item->setColumn(list);
		} else {
			item->setColumn(this->exprParser->primary());
		}
		accept(EQ);
		item->setValue(this->exprParser->getExpr());
		update->getItems().push_back(item);

		if (lexer->getToken() != COMMA) {
			break;
		}

		lexer->nextToken();
	}
}

SQLUpdateStatement *SQLStatementParser::createUpdateStatement() {
	return new SQLUpdateStatement();
}

SQLDeleteStatement *SQLStatementParser::parseDeleteStatement() {
	SQLDeleteStatement *deleteStatement = new SQLDeleteStatement();

	if (lexer->getToken() == TOKEN_DELETE) {
		lexer->nextToken();
		if (lexer->getToken() == (FROM)) {
			lexer->nextToken();
		}

		if (lexer->getToken() == COMMENT) {
			lexer->nextToken();
		}

		SQLName *tableName = exprParser->getName();

		deleteStatement->setTableName(tableName);
	}

	if (lexer->getToken() == (WHERE)) {
		lexer->nextToken();
		SQLExpr *where = this->exprParser->getExpr();
		deleteStatement->setWhere(where);
	}

	return deleteStatement;
}

SQLCreateTableStatement *SQLStatementParser::parseCreateTable() {
	// SQLCreateTableParser parser = new SQLCreateTableParser(this->lexer);
	// return parser.parseCrateTable();
	throw new ParserException("TODO");
}

SQLCreateViewStatement *SQLStatementParser::parseCreateView() {
	SQLCreateViewStatement *createView = new SQLCreateViewStatement();

	if (lexer->getToken() == CREATE) {
		lexer->nextToken();
	}

	if (lexer->getToken() == OR) {
		lexer->nextToken();
		accept(REPLACE);
		createView->setOrReplace(true);
	}

	this->accept(VIEW);

	createView->setName(exprParser->getName());

	if (lexer->getToken() == LEFTPAREN) {
		lexer->nextToken();
		this->exprParser->exprList(createView->getColumns());
		accept(RPAREN);
	}

	this->accept(AS);

	createView->setSubQuery((new SQLSelectParser(this->exprParser))->select());
	//createView.setSubQuery(new SQLSelectParser(this.exprParser).select());
	return createView;
}

SQLCommentStatement *SQLStatementParser::parseComment() {
	accept(COMMENT);
	SQLCommentStatement *stmt = new SQLCommentStatement();

	accept(ON);

	if (lexer->getToken() == TABLE) {
		stmt->setType(SQLCommentStatement::TABLE);
		lexer->nextToken();
	} else if (lexer->getToken() == COLUMN) {
		stmt->setType(SQLCommentStatement::COLUMN);
		lexer->nextToken();
	}

	stmt->setOn(this->exprParser->getName());

	accept(IS);
	stmt->setComment(this->exprParser->getExpr());

	return stmt;
}

SQLAlterTableAddColumn *SQLStatementParser::parseAlterTableAddColumn() {
	SQLAlterTableAddColumn *item = new SQLAlterTableAddColumn();

	for (;;) {
		SQLColumnDefinition *columnDef = this->exprParser->parseColumn();
		item->getColumns().push_back(columnDef);
		if (lexer->getToken() == COMMA) {
			lexer->nextToken();
			continue;
		}
		break;
	}
	return item;
}

SQLStatement *SQLStatementParser::parseStatement() {
	//std::list<SQLStatement *> *list = new std::list<SQLStatement *>;

	//this->parseStatementList(*list, 1);
	this->parseStatementList(yaList, 1);

	return yaList.front();
}

SQLExplainStatement *SQLStatementParser::parseExplain() {
	accept(EXPLAIN);
	if (identifierEquals("PLAN")) {
		lexer->nextToken();
	}

	if (lexer->getToken() == FOR) {
		lexer->nextToken();
	}

	SQLExplainStatement *explain = new SQLExplainStatement();
	explain->setStatement(parseStatement());

	return explain;
}

SQLAlterTableAddIndex *SQLStatementParser::parseAlterTableAddIndex() {
	SQLAlterTableAddIndex *item = new SQLAlterTableAddIndex();

	if (lexer->getToken() == UNIQUE) {
		item->setUnique(true);
		lexer->nextToken();
		if (lexer->getToken() == INDEX) {
			lexer->nextToken();
		}
	} else {
		accept(INDEX);
	}

	if (lexer->getToken() == LEFTPAREN) {
		lexer->nextToken();
	} else {
		item->setName(this->exprParser->getName());
		accept(LEFTPAREN);
	}

	for (;;) {
		SQLSelectOrderByItem *column = this->exprParser->parseSelectOrderByItem();
		item->getItems().push_back(column);
		if (lexer->getToken() == COMMA) {
			lexer->nextToken();
			continue;
		}
		break;
	}
	accept(RPAREN);
	return item;
}
