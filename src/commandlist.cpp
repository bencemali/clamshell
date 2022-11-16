#include "commandlist.hpp"

CommandList::CommandList(std::vector<std::string>& w)
    : words(w)
{
    if(words.size() == 0) {
        throw InvalidInputException("Please provide valid input");
    }

    int numOfCommands = 0;
    bool separatorBefore = true;
    for(size_t i = 0; i < words.size(); ++i) {
        if(isSeparator(words[i])) {
            if(separatorBefore) {
                throw InvalidInputException("Invalid separator use");
            }
            ++numOfCommands;
            separatorBefore = true;
        } else {
            separatorBefore = false;
        }
    }
    if(separatorBefore) {
        throw InvalidInputException("Invalid separator use");
    }

    pipefds = new int[numOfCommands * 2];
    for(int i = 0; i < (numOfCommands * 2); i += 2) {
        pipe(pipefds + i);
    }

    size_t i = 0;
    for(int cidx = 0; cidx < numOfCommands; ++cidx) {
        int commandNameIdx = i;
        std::unique_ptr<Command> command = std::make_unique<Command>(words[i++]);
        while(!isSeparator(words[i]) && i < words.size()) {
            command->addArgument(words[i]);
        }
        if(commandNameIdx != 0) {
            //Redirect io
        }
        
        commands.push_back(command);
    }
}

void CommandList::executeAll() {
    //execute all
}

