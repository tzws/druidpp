#ifndef OdpsSelectParser_HEADER_H
#define OdpsSelectParser_HEADER_H

#include <boost/smart_ptr.hpp>
#include "../ast/SQLExpr.h"
#include "../ast/expr/SQLIdentifierExpr.h"
#include "../ast/statement/SQLSelectItem.h"
#include "OdpsUDTFSQLSelectItem.h"
#include "SQLExprParser.h"
#include "SQLSelectParser.h"
#include "Token.h"

class OdpsSelectParser : public SQLSelectParser {
	public:
		OdpsSelectParser(SQLExprParser *exprParser);
		~OdpsSelectParser();
    
	protected:
		SQLSelectItem *parseSelectItem();
};
typedef boost::shared_ptr<OdpsSelectParser> OdpsSelectParser_ptr;

#endif

