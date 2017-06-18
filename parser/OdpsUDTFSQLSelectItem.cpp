#include "OdpsUDTFSQLSelectItem.h"
OdpsUDTFSQLSelectItem::OdpsUDTFSQLSelectItem() {

}

OdpsUDTFSQLSelectItem::~OdpsUDTFSQLSelectItem() {

	//for(std::list<std::string>::iterator it = aliasList.begin(); it != aliasList.end(); ++it) 
	//{
		//std::cout << __FILE__ << ": " << __LINE__ << ", in SQLExprParser::~SQLExprParser, destructor step 1.1" << std::endl;
		//delete *it; 
	//}
	//aliasList.clear();


}
std::string & OdpsUDTFSQLSelectItem::getAlias() {
	//fprintf(stderr, "UnsupportedOperationException in SQLStatementImpl::getAlias\n");
	//assert(false);
	throw new UnsupportedOperationException();
}

void OdpsUDTFSQLSelectItem::setAlias(std::string &alias) {
	throw new UnsupportedOperationException();
	//fprintf(stderr, "UnsupportedOperationException in SQLStatementImpl::setAlias\n");
	//assert(false);
}

std::list<std::string> & OdpsUDTFSQLSelectItem::getAliasList() {
	return aliasList;
}


