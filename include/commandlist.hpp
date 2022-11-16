#ifndef COMMANDLIST_HPP
#define COMMANDLIST_HPP

#include <unistd.h>
#include <string>
#include <vector>
#include <memory>
#include "command.hpp"
#include "invalidinput.hpp"

class CommandList {
private:
    std::vector<std::string>& words;
    std::vector<std::unique_ptr<Command>> commands;
    int* pipefds;
    bool isSeparator(std::string str) {
        return str == "&&"
            || str == "|"
            || str == ">"
            || str == ">>"
            || str == "<";
    }

public:
    CommandList(std::vector<std::string>& w);

    ~CommandList() {
        delete[] pipefds;
    }

    void executeAll();
};

#endif //COMMANDLIST_HPP

