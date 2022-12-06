#include <iostream>
#include <sys/wait.h>
#include "commandlist.hpp"
#include "exitexception.hpp"

CommandList::CommandList(std::vector<std::string>& w)
    : words(w)
{
    //Show new prompt if enter was pressed
    if(words.size() == 0) {
        throw EnterException();
    }

    //syntax checking
    numOfCommands = 1; //number of only the commands (program names)
    bool separatorBefore = true;
    for(size_t i = 0; i < words.size(); ++i) {
        if(isSeparator(words[i])) {
            if(separatorBefore) {
                throw InvalidInputException("Invalid separator use");
            }
            if(isNewCommandSeparator(words[i])) {
                ++numOfCommands;
            }
            separatorBefore = true;
        } else {
            separatorBefore = false;
        }
    }
    if(separatorBefore) {
        throw InvalidInputException("Invalid separator use");
    }

    //open pipes for the command io redirection
    pipefds = new int[numOfCommands * 2];
    numOfPipes = numOfCommands * 2;
    for(size_t i = 0; i < (numOfCommands * 2); i += 2) {
        pipe(pipefds + i);
    }

    //Command object creation + io redirection
    size_t i = 0;
    for(size_t cidx = 0; cidx < numOfCommands; ++cidx, ++i) {
        size_t commandNameIdx = i;

        if(i != 0 && (words[i - 1] == ">" || words[i - 1] == ">>" || words[i - 1] == "<")) {
            while(!isNewCommandSeparator(words[i - 1])) {
                ++commandNameIdx;
                ++i;
            }
        }

        //Create the Command object
        std::shared_ptr<Command> command;
        bool isCommand = false;
        if(i == 0 || (words[i - 1] != ">" && words[i - 1] != ">>" && words[i - 1] != "<")) {
            isCommand = true;
            command = std::make_shared<Command>(words[i++], pipefds, numOfPipes);
            while(i < words.size() && !isSeparator(words[i])) {
                command->addArgument(words[i++]);
            }
            commands.push_back(command);
        }

        if(isCommand) {
            //stdin
            if(commandNameIdx != 0 && words[commandNameIdx - 1] == "|") {
                //stdin from other program
                //meaning stdin attached to own read pipe end in pipefds
                command->redirectIn(cidx * 2);
            } else if(i < (words.size() - 1) && words[i] == "<") {
                //stdin from file
                command->redirectIn(words[i + 1]);
            }

            //stdout
            if(i < (words.size() - 1)) {
                if(words[i] == "|") {
                    //stdout to other program
                    command->redirectOut(((cidx + 1) * 2) + 1);
                } else if(words[i] == ">") {
                    //stdout to file
                    command->redirectOut(words[i + 1]);
                } else if(words[i] == ">>") {
                    //append stdout to file
                    command->redirectOut(words[i + 1], true);
                }
            }
        }
    }
}

void CommandList::executeAll() {
    //check for builtins
    for(auto w : words) {
        if(w == "exit") {
            throw ExitException();
        }
    }
    for(int i = 0; i < (int)words.size(); ++i) {
        if(words[i] == "cd") {
            if(i < (int)words.size() - 1 && !isSeparator(words[i + 1])) {
                chdir(words[i + 1].c_str());
            } else {
                chdir(getenv("HOME"));
            }
        }
    }

    //execute all
    for(size_t i = 0; i < numOfCommands; ++i) {
        commands[i]->execute();
    }
}

