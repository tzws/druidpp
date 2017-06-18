
//import com.alibaba.druid.sql.visitor.SQLASTVisitor;

#ifndef SQLCommentHint_HEADER_H
#define SQLCommentHint_HEADER_H
#include <boost/smart_ptr.hpp>
#include "SQLObject.h"
#include "SQLObjectImpl.h"
#include "SQLHint.h"
#include "SQLCommentHint.h"
#include "../visitor/SQLASTVisitor.h"

//http://stackoverflow.com/questions/137282/how-can-you-avoid-the-diamond-of-death-in-c-when-using-multiple-inheritance
class SQLCommentHint : virtual public SQLObjectImpl, virtual public SQLHint {

	private:
		std::string text;

	public:
		SQLCommentHint();
		virtual ~SQLCommentHint();

		SQLCommentHint(std::string &text);

		std::string& getText();

		void setText(std::string &text);

		virtual std::string & getClass()
		{
			static std::string className = "SQLCommentHint";
			return className;
		} 


	protected:
		virtual	void accept0(SQLASTVisitor *visitor);
};
typedef boost::shared_ptr<SQLCommentHint> SQLCommentHint_ptr;

#endif

