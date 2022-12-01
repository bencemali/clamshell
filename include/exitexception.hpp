#ifndef EXITEXCEPTION_HPP
#define EXITEXCEPTION_HPP

#include <exception>
#include <string>

class ExitException : public std::exception {
public:
    ExitException() 
    {}
};

#endif //EXITEXCEPTION_HPP
