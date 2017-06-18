
#ifndef SQLASTVisitor_HEADER_H
#define SQLASTVisitor_HEADER_H
//#include "SQLObject.h"

#include <boost/smart_ptr.hpp>
class SQLObject;
class SQLASTVisitor {
	public:

		bool visit(SQLObject * x) {

			return true;
		}
		bool  endVisit(SQLObject * x) {

			return true;
		}

		bool preVisit(SQLObject * x) {

			return true;
		}


		bool postVisit(SQLObject * x) {

			return true;
		}
};

#endif

