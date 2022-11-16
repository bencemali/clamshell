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
        size_t commandNameIdx = i;

        bool isCommand = false;
        if(i == 0 || (words[i - 1] != ">" && words[i - 1] != ">>" && words[i - 1] != "<")) {
            isCommand = true;
            std::unique_ptr<Command> command = std::make_unique<Command>(words[i++], pipefds + (cidx * 2));
            while(!isSeparator(words[i]) && i < words.size()) {
                command->addArgument(words[i++]);
            }
            commands.push_back(command);
        }

        if(isCommand) {
            //stdin
            if(commandNameIdx != 0 && words[commandNameIdx - 1] == "|") {
                //stdin from other program
            } else if(commandNameIdx < (words.size() - 1) && words[i] == "<") {
                //stdin from file
            }

            //stdout
            if(commandNameIdx < (words.size() - 1)) {
                if(words[i] == "|") {
                    //stdout to other program
                } else if(words[i] == ">") {
                    //stdout to file
                } else if(words[i] == ">>") {
                    //append stdout to file
                }
            }
        }
        
    }

    //close all pipes
}

void CommandList::executeAll() {
    //execute all
}

