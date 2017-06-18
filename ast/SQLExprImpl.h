
#ifndef SQLExprImpl_HEADER_H
#define SQLExprImpl_HEADER_H

#include <boost/smart_ptr.hpp>
#include "Object.h"
#include "SQLObject.h"
#include "SQLObjectImpl.h"
#include "SQLExpr.h"

class SQLExprImpl : virtual public SQLObjectImpl, virtual public SQLExpr {

	public:
		SQLExprImpl(){
			
		};
		~SQLExprImpl(){

		};
		//virtual bool equals(Object *o) = 0;

		//virtual int hashCode() = 0;
};
typedef boost::shared_ptr<SQLExprImpl> SQLExprImpl_ptr;

#endif

