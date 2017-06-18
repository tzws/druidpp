#include "IllegalArgumentException.h"
	IllegalArgumentException::IllegalArgumentException()
throw(): std::exception()
{
}

	IllegalArgumentException::IllegalArgumentException(const std::string& msg) 
throw(): std::exception(), m_msg(msg)
{
}

const char* IllegalArgumentException::what() const throw()
{
	return m_msg.c_str();
}

IllegalArgumentException::~IllegalArgumentException() throw()
{
}
