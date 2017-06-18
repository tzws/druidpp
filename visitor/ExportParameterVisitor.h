#ifndef ExportParameterVisitor_HEADER_H 
#define ExportParameterVisitor_HEADER_H

#include <list>

class ExportParameterVisitor : virtual public SQLASTVisitor {
	public:
		virtual std::list<Object *> getParameters() = 0;
		virtual ~ExportParameterVisitor() {
			
		}
};

#endif

