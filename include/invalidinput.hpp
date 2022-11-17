#ifndef INVALIDINPUT_H
#define INVALIDINPUT_H

#include <exception>
#include <string>

class InvalidInputException : private std::exception {
private:
    std::string msg;

public:
    InvalidInputException(std::string m) 
        : msg(m)
    {}

    std::string getMessage() const {
        return msg;
    }
};

class EnterException : private std::exception {
public:
    EnterException() {}
};

#endif //INVALIDINPUT_H

