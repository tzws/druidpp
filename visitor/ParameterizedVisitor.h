#ifndef ParameterizedVisitor_HEADER_H
#define ParameterizedVisitor_HEADER_H

class ParameterizedVisitor : virtual public PrintableVisitor {

	public:

		virtual int getReplaceCount() = 0;

		virtual void incrementReplaceCunt() = 0;

};

#endif
