

#if !defined(NumberFormatException_HEADER_H)
#define NumberFormatException_HEADER_H

#include <boost/smart_ptr.hpp>
#include <exception>
#include <string>
#include <memory>

class NumberFormatException : public std::exception  
{
	public:
		NumberFormatException() throw();
		NumberFormatException(const std::string& msg) throw();
		virtual const char* what() const throw();
		virtual ~NumberFormatException() throw();

	protected:

		std::string m_msg; 
};

#endif 

