#include "UnsupportedOperationException.h"
	UnsupportedOperationException::UnsupportedOperationException()
throw(): std::exception()
{
}

	UnsupportedOperationException::UnsupportedOperationException(const std::string& msg) 
throw(): std::exception(), m_msg(msg)
{
}

const char* UnsupportedOperationException::what() const throw()
{
	return m_msg.c_str();
}

UnsupportedOperationException::~UnsupportedOperationException() throw()
{
}
