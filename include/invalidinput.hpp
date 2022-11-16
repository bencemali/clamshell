#ifndef INVALIDINPUT_H
#define INVALIDINPUT_H

#include <exception>
#include <string>

class InvalidInputException : public std::exception {
private:
    std::string msg;
    using std::exception::what;

public:
    InvalidInputException(std::string m) 
        : msg(m)
    {}

    virtual std::string what() {
        return msg;
    }
};

#endif //INVALIDINPUT_H

