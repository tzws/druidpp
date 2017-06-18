
#include "SQLOrderingSpecification.h" 

SQLOrderingSpecification SQLOrderingSpecification::ASC = SQLOrderingSpecification(1);
SQLOrderingSpecification SQLOrderingSpecification::DESC = SQLOrderingSpecification(2);

SQLOrderingSpecification::SQLOrderingSpecification(int x)
{
	this->num = x;
}


SQLOrderingSpecification::~SQLOrderingSpecification()
{

}



