#include "SQLStatementImpl.h"
#include <assert.h> 
#include <stdio.h>

SQLStatementImpl::SQLStatementImpl(){

}

SQLStatementImpl::~SQLStatementImpl(){

}
std::string &SQLStatementImpl::toString() {


#if WIN32
			std::string x = "";
			return x;
#else

#endif		
}

void SQLStatementImpl::accept0(SQLASTVisitor *visitor) {

	fprintf(stderr, "UnsupportedOperationException in SQLStatementImpl::accept0\n");
	assert(false);
	//throw new UnsupportedOperationException(this.getClass().getName());

}

