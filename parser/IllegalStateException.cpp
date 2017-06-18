#include "IllegalStateException.h"
	IllegalStateException::IllegalStateException()
throw(): std::exception()
{
}

	IllegalStateException::IllegalStateException(const std::string& msg) 
throw(): std::exception(), m_msg(msg)
{
}

const char* IllegalStateException::what() const throw()
{
	return m_msg.c_str();
}

IllegalStateException::~IllegalStateException() throw()
{
}
