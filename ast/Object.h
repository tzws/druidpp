
#ifndef OBJECT_HEADER_H
#define OBJECT_HEADER_H
#include <boost/smart_ptr.hpp>
#include <string>
class Object {
	private:
		//static std::string x;
		//static std::string x;
	public:

		//virtual std::string  toString();

		virtual std::string  &toString()
		{
#if WIN32
			std::string x = "";
			return x;
#else

#endif		
			//return x;
		}

		virtual std::string & getClass()
		{
			static std::string className = "Object";
			return className;
		} 

		//virtual ~Object() = 0;
};
typedef boost::shared_ptr<Object> Object_ptr;

#endif

