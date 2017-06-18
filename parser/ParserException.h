

#if !defined(PARSER_HEADER_H)
#define PARSER_HEADER_H

#include <boost/smart_ptr.hpp>
#include <exception>
#include <string>
#include <memory>

class ParserException : public std::exception  
{
	public:
		ParserException() throw();
		ParserException(const std::string& msg) throw();
		virtual const char* what() const throw();
		virtual ~ParserException() throw();

	protected:

		std::string m_msg; 
};

#endif 

