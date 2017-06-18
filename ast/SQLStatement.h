#ifndef SQLStatement_HEADER_H
#define SQLStatement_HEADER_H

#include <boost/smart_ptr.hpp>
class SQLStatement : virtual public SQLObject {
	public:

		virtual ~SQLStatement() {
			
		};
};
typedef boost::shared_ptr<SQLStatement> SQLStatement_ptr;

#endif
