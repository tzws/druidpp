#ifndef SQLLiteralExpr_HEADER_H
#define SQLLiteralExpr_HEADER_H

#include <boost/smart_ptr.hpp>
#include "../SQLExpr.h"

class SQLLiteralExpr : virtual public SQLExpr {

	public:
		virtual ~SQLLiteralExpr() {
			
		}


};
#endif

