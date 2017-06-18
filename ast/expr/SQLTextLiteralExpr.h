#ifndef SQLTextLiteralExpr_HEADER_H
#define SQLTextLiteralExpr_HEADER_H

#include <boost/smart_ptr.hpp>
#include <string>
#include "../SQLExprImpl.h"
#include "SQLLiteralExpr.h"


class SQLTextLiteralExpr : virtual public SQLExprImpl, virtual public SQLLiteralExpr {

	protected:
		std::string text;

	public:
		SQLTextLiteralExpr();

		SQLTextLiteralExpr(std::string &text);

		std::string &getText();

		void setText(std::string &text);

		virtual ~SQLTextLiteralExpr();

		//int hashCode();
		//bool equals(Object obj);
};
#endif

