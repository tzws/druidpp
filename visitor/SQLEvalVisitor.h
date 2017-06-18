#ifndef SQLEvalVisitor_HEADER_H 
#define SQLEvalVisitor_HEADER_H

class SQLEvalVisitor : virtual public SQLASTVisitor {

	public:
		static std::string EVAL_VALUE;
		static std::string EVAL_EXPR;
		static Object * EVAL_ERROR;
		static Object * EVAL_VALUE_COUNT;
		static Object * EVAL_VALUE_NULL;

		virtual ~SQLEvalVisitor();
		virtual Function getFunction(std::string funcName) = 0;

		virtual void registerFunction(std::string funcName, Function function) = 0;

		virtual void unregisterFunction(std::string funcName) = 0;

		virtual List<Object *> getParameters() = 0;

		virtual void setParameters(List<Object *> parameters) = 0;

		virtual int incrementAndGetVariantIndex() = 0;

		virtual bool isMarkVariantIndex() = 0;

		virtual void setMarkVariantIndex(bool markVariantIndex) = 0;
};
#endif

