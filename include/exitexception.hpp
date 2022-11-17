#ifndef EXITEXCEPTION_HPP
#define EXITEXCEPTION_HPP

#include <exception>
#include <string>

class ExitException : public std::exception {
private:
    std::string msg;

public:
    ExitException(std::string m) 
        : msg(m)
    {}

    std::string getMessage() const {
        return msg;
    }
};

#endif //EXITEXCEPTION_HPP
