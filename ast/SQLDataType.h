
#ifndef SQLDataType_HEADER_H
#define SQLDataType_HEADER_H
#include <boost/smart_ptr.hpp>
#include <string>
#include "SQLObject.h"
#include "SQLExpr.h"

class SQLDataType : virtual public SQLObject {

	public:

		virtual std::string & getName() = 0;

		virtual void setName(std::string &name) = 0;

		virtual std::list<SQLExpr *> &getArguments() = 0;

		virtual ~SQLDataType() {
			
		}
};
typedef boost::shared_ptr<SQLDataType> SQLDataType_ptr;

#endif

