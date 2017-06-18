// g++ x.cpp -std=c++11
// clearing vectors
#include <iostream>
#include <vector>
#include <typeinfo>
/* isalpha example */
#include <stdio.h>
#include <ctype.h>
#include <assert.h> 

#include "SQLASTVisitor.h"
#include "ExportParameterVisitor.h"
#include "ExportParameterVisitorUtils.h"
#include "SQLASTVisitorAdapter.h"
#include "SQLASTOutputVisitor.h"
#include "PrintableVisitor.h"

class A {

	public:
		int num;
		A () : num(0) {};
		A (int x) : num(x) {};
		void showNum() {
			
			std::cout << "num is: " << num << std::endl;
		}
		~A() {
			
			std::cout << "in A's destructor, num is: " << num << std::endl;
		}
	
};
int main ()
{
	ExportParameterVisitorUtils *a = new ExportParameterVisitorUtils();
	std::cout << "in main function " << std::endl;

	std::list<A *> theList;
	theList.push_back(new A(1));
	theList.push_back(new A(2));
	theList.push_back(new A(3));


	int counter = 4;

	for (std::list<A *>::iterator it = theList.begin(); it != theList.end(); it++)
	{
		//(*it)->showNum();
		//it = theList.erase(it);
		//it = theList.insert(it, (new A(counter++)));

		delete (*it);
		(*it) = new A(counter++);
	}


	for (std::list<A *>::iterator it = theList.begin(); it != theList.end(); it++)
	{
		(*it)->showNum();
	}

	for (std::list<A *>::iterator it = theList.begin(); it != theList.end(); it++)
	{
		delete (*it);
	}

	std::cout << '\n';



	return 0;
}

