

#if !defined(NOTALLOWCOMMENTEXCEPTION_HEADER_H)
#define NOTALLOWCOMMENTEXCEPTION_HEADER_H

#include <boost/smart_ptr.hpp>
#include <exception>
#include <string>
#include <memory>

class NotAllowCommentException : public std::exception  
{
	public:
		NotAllowCommentException() throw();
		NotAllowCommentException(const std::string& msg) throw();
		virtual const char* what() const throw();
		virtual ~NotAllowCommentException() throw();

	protected:



		std::string m_msg; 
};

#endif 

