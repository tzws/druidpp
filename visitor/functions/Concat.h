#ifndef Concat_HEADER_H 
#define Concat_HEADER_H

class Concat : virtual public Function {


	public:
	
		static Concat *instance();
		virtual ~Concat();
		virtual Object *eval(SQLEvalVisitor *visitor, SQLMethodInvokeExpr *x);
};
#endif

