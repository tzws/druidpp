#include "ParserException.h"
#include <iostream>
#include <stdio.h>
	ParserException::ParserException()
throw(): std::exception()
{
}

	ParserException::ParserException(const std::string& msg) 
throw(): std::exception(), m_msg(msg)
{
}

const char* ParserException::what() const throw()
{
	return m_msg.c_str();
}

ParserException::~ParserException() throw()
{
	fprintf(stderr, "%s\n", m_msg.c_str());
}
