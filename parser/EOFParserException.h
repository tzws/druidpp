

#if !defined(EOFParserException_HEADER_H)
#define EOFParserException_HEADER_H

#include <boost/smart_ptr.hpp>
#include <exception>
#include <string>
#include <memory>

class EOFParserException : public std::exception  
{
	public:
		EOFParserException() throw();
		EOFParserException(const std::string& msg) throw();
		virtual const char* what() const throw();
		virtual ~EOFParserException() throw();

	protected:

		std::string m_msg; 
};

#endif 

