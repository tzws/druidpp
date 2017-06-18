#ifndef Ascii_HEADER_H 
#define Ascii_HEADER_H

#include "SQLEvalVisitor.h"
#include "SQLExpr.h"
#include "SQLMethodInvokeExpr.h"

class Ascii : virtual public Function {

	private:
		//static bool _init;
		//static bool init();
		Ascii();
		Ascii(Ascii const&);              // Don't Implement
		void operator=(Ascii const&); // Don't implement
	public:

		//static Ascii &instance();
		static Ascii *instance();
		//static Ascii *ins;
		virtual ~Ascii();

		Object *eval(SQLEvalVisitor *visitor, SQLMethodInvokeExpr *x);
};
#endif

