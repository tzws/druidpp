
#ifndef SQLExpr_HEADER_H
#define SQLExpr_HEADER_H
#include <boost/smart_ptr.hpp>
#include "SQLObject.h"
class SQLExpr : virtual public SQLObject {
	public:
	//virtual void doNothing () = 0;

		virtual ~SQLExpr() {
			
		}
};
typedef boost::shared_ptr<SQLExpr> SQLExpr_ptr;

#endif

