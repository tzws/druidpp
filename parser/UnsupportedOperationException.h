

#if !defined(UnsupportedOperationException_HEADER_H)
#define UnsupportedOperationException_HEADER_H

#include <boost/smart_ptr.hpp>
#include <exception>
#include <string>
#include <memory>

class UnsupportedOperationException : public std::exception  
{
	public:
		UnsupportedOperationException() throw();
		UnsupportedOperationException(const std::string& msg) throw();
		virtual const char* what() const throw();
		virtual ~UnsupportedOperationException() throw();

	protected:

		std::string m_msg; 
};

#endif 

