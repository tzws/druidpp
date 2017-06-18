#include "NumberFormatException.h"
	NumberFormatException::NumberFormatException()
throw(): std::exception()
{
}

	NumberFormatException::NumberFormatException(const std::string& msg) 
throw(): std::exception(), m_msg(msg)
{
}

const char* NumberFormatException::what() const throw()
{
	return m_msg.c_str();
}

NumberFormatException::~NumberFormatException() throw()
{
}
