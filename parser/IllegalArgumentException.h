

#if !defined(IllegalArgumentException_HEADER_H)
#define IllegalArgumentException_HEADER_H

#include <boost/smart_ptr.hpp>
#include <exception>
#include <string>
#include <memory>

class IllegalArgumentException : public std::exception  
{
	public:
		IllegalArgumentException() throw();
		IllegalArgumentException(const std::string& msg) throw();
		virtual const char* what() const throw();
		virtual ~IllegalArgumentException() throw();

	protected:

		std::string m_msg; 
};

#endif 

