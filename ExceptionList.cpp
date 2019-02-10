#include "ExceptionList.h"

FactorizationException::FactorizationException(const std::string & message) noexcept : text_error(message) {}

const char * FactorizationException::what() const noexcept
{
	return text_error.c_str();
}
