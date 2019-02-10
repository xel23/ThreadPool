#pragma once
#include <exception>
#include <string>

class FactorizationException : public std::exception {
private:
	std::string text_error;
public:
	FactorizationException(const std::string &message) noexcept;
	~FactorizationException() {};
	const char * what() const noexcept;
};

class ArgumentsError : public FactorizationException {
public:
	ArgumentsError(const std::string & message) : FactorizationException(message) {}
};

class FileNotFound : public FactorizationException {
public:
	FileNotFound(const std::string & message) : FactorizationException(message) {}
};