#ifndef OdpsUDTFSQLSelectItem_HEADER_H
#define OdpsUDTFSQLSelectItem_HEADER_H

#include <boost/smart_ptr.hpp>
#include <string>
#include <list>

#include "../ast/statement/SQLSelectItem.h"
#include "UnsupportedOperationException.h"

class OdpsUDTFSQLSelectItem : virtual public SQLSelectItem {

	private:
		std::list<std::string> aliasList;

	public:
		OdpsUDTFSQLSelectItem();
		~OdpsUDTFSQLSelectItem();
		std::string &getAlias();

		void setAlias(std::string &alias);

		std::list<std::string> & getAliasList();

};
typedef boost::shared_ptr<OdpsUDTFSQLSelectItem> OdpsUDTFSQLSelectItem_ptr;

#endif

