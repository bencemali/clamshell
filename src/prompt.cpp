#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <sstream>
#include "prompt.hpp"

int prompt() {
    printPrompt();

    std::string line;
    getline(std::cin, line, '\n');


    std::vector<std::string> words;
    std::istringstream iss(line);
    std::string word;
    while(iss >> word) {
        words.push_back(word);
    }

    //process + exception handling

    //execute

    //return
    return -1;
}

void printPrompt() {
    char hostname[_SC_HOST_NAME_MAX];
    gethostname(hostname, _SC_HOST_NAME_MAX);
    char cwd[256];
    getcwd(cwd, sizeof(cwd));
    std::cout << "[" << getenv("USER") << "@" << hostname << "]:" << cwd << "$ ";
}
