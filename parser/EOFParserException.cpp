#include "EOFParserException.h"
	EOFParserException::EOFParserException()
throw(): std::exception()
{
}

	EOFParserException::EOFParserException(const std::string& msg) 
throw(): std::exception(), m_msg(msg)
{
}

const char* EOFParserException::what() const throw()
{
	return m_msg.c_str();
}

EOFParserException::~EOFParserException() throw()
{
}
