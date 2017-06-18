
#ifndef SQLHint_HEADER_H
#define SQLHint_HEADER_H
#include <boost/smart_ptr.hpp>
#include "SQLObject.h"
class SQLHint : virtual public SQLObject {
	public:
		virtual ~SQLHint() {
			
		}

};
typedef boost::shared_ptr<SQLHint> SQLHint_ptr;

#endif
