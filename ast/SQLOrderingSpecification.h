#ifndef SQLOrderingSpecification_HEADER_H
#define SQLOrderingSpecification_HEADER_H

#include <boost/smart_ptr.hpp>
class SQLOrderingSpecification {
	public:

		static SQLOrderingSpecification ASC;
		static SQLOrderingSpecification DESC;

	private:
		int num;
		SQLOrderingSpecification(int x);
		~SQLOrderingSpecification();

};
typedef boost::shared_ptr<SQLOrderingSpecification> SQLOrderingSpecification_ptr;


//enum SQLOrderingSpecification {
//ASC, 
//DESC
//};

#endif

