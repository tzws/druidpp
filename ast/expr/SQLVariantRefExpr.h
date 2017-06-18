#ifndef SQLVariantRefExpr_HEADER_H 
#define SQLVariantRefExpr_HEADER_H

#include <boost/smart_ptr.hpp>
#include <string>

#include "../SQLExpr.h"
#include "../SQLExprImpl.h"
#include "../../visitor/SQLASTVisitor.h"



class SQLVariantRefExpr : virtual public SQLExprImpl {

	private:
		std::string  name;

		bool global;

		int  index;

	public:
		SQLVariantRefExpr(std::string &name);
		SQLVariantRefExpr(const char * x);
		virtual ~SQLVariantRefExpr();

		SQLVariantRefExpr(std::string &name, bool global);

		SQLVariantRefExpr();

		int getIndex();

		void setIndex(int index);

		std::string &getName();

		void setName(std::string &name);

		void output(std::string &buf);

		//int hashCode();
		//bool equals(Object obj);
		bool isGlobal();
		void setGlobal(bool global);
	protected:
		void accept0(SQLASTVisitor *visitor);


};
typedef boost::shared_ptr<SQLVariantRefExpr> SQLVariantRefExpr_ptr;

#endif

