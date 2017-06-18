#ifndef PrintableVisitor_HEADER_H 
#define PrintableVisitor_HEADER_H

#include <string>
class PrintableVisitor : virtual public SQLASTVisitor {
	public:
		virtual void print(char value) = 0;

		virtual void print(std::string &text) = 0;

		virtual ~PrintableVisitor() {
			
		}
};
#endif

