#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <sstream>
#include "prompt.hpp"
#include "commandlist.hpp"
#include "exitexception.hpp"

int prompt() {
    printPrompt();

    std::string line;
    getline(std::cin, line, '\n');
    if(std::cin.eof()) {
        std::cout << std::endl;
        return -1;
    }

    std::vector<std::string> words;
    std::istringstream iss(line);
    std::string word;
    while(iss >> word) {
        words.push_back(word);
    }

    //process + exception handling
    std::shared_ptr<CommandList> list;
    try {
        list = std::make_shared<CommandList>(words);
    }
    catch(const EnterException& e) {
        return 0;
    }
    catch(const InvalidInputException& e) {
        std::cout << e.getMessage() << std::endl;
        return 0;
    }


    //execute
    try {
        list->executeAll();
    }
    catch(const ExitException& e) {
        return -1;
    }

    //return
    return 0;
}

void printPrompt() {
    char hostname[_SC_HOST_NAME_MAX];
    gethostname(hostname, _SC_HOST_NAME_MAX);
    char cwd[256];
    getcwd(cwd, sizeof(cwd));
    std::cout << "[" << getenv("USER") << "@" << hostname << "]:" << cwd << "$ ";
}
