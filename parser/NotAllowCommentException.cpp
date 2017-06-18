#include "NotAllowCommentException.h"
	NotAllowCommentException::NotAllowCommentException()
throw(): std::exception()
{
}

	NotAllowCommentException::NotAllowCommentException(const std::string& msg) 
throw(): std::exception(), m_msg(msg)
{
}

const char* NotAllowCommentException::what() const throw()
{
	return m_msg.c_str();
}

NotAllowCommentException::~NotAllowCommentException() throw()
{
}
