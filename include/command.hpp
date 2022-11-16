#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <string>
#include <vector>

class Command {
private:
    std::vector<std::string> parts;
    int in;
    int out;
public:
    Command(std::string name) {
        parts.push_back(name);
    }

    void addArgument(std::string arg) {
        parts.push_back(arg);
    }

    void execute();

    void redirectOut(int o) {
        out = o;
    }

    void redirectIn(int i) {
        in = i;
    }
};

#endif //COMMAND_HPP

