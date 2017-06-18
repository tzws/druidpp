
#ifndef SQLName_HEADER_H
#define SQLName_HEADER_H
#include <boost/smart_ptr.hpp>
#include "SQLExpr.h"
class SQLName : virtual public SQLExpr {
	public:
		virtual std::string &getSimleName() = 0;

		virtual ~SQLName() {

		}
};
typedef boost::shared_ptr<SQLName> SQLName_ptr;

#endif

