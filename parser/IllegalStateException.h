

#if !defined(ILLEGALSTATEXCEPTION_HEADER_H)
#define ILLEGALSTATEXCEPTION_HEADER_H

#include <boost/smart_ptr.hpp>
#include <exception>
#include <string>
#include <memory>

class IllegalStateException : public std::exception  
{
	public:
		IllegalStateException() throw();
		IllegalStateException(const std::string& msg) throw();
		virtual const char* what() const throw();
		virtual ~IllegalStateException() throw();

	protected:

		std::string m_msg; 
};

#endif 

