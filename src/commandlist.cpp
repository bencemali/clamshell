#include <iostream>
#include <sys/wait.h>
#include "commandlist.hpp"
#include "exitexception.hpp"

CommandList::CommandList(std::vector<std::string>& w)
    : words(w)
{
    if(words.size() == 0) {
        throw EnterException();
    }

    //syntax checking
    int numOfCommands = 1;
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

    //pipe
    pipefds = new int[numOfCommands * 2];
    numOfPipes = numOfCommands * 2;
    for(int i = 0; i < (numOfCommands * 2); i += 2) {
        pipe(pipefds + i);
    }

    //command creation + io redirect
    size_t i = 0;
    for(int cidx = 0; cidx < numOfCommands; ++cidx, ++i) {
        size_t commandNameIdx = i;

        std::shared_ptr<Command> command;
        bool isCommand = false;
        if(i == 0 || (words[i - 1] != ">" && words[i - 1] != ">>" && words[i - 1] != "<")) {
            isCommand = true;
            command = std::make_shared<Command>(words[i], pipefds, numOfCommands * 2);
            ++i;
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
                command->redirectIn(pipefds[cidx * 2]);
            } else if(i < (words.size() - 1) && words[i] == "<") {
                //stdin from file
                command->redirectIn(words[i + 1]);
            }

            //stdout
            if(i < (words.size() - 1)) {
                if(words[i] == "|") {
                    //stdout to other program
                    command->redirectOut((cidx * 2) + 3);
                } else if(words[i] == ">") {
                    //stdout to file
                    //TODO: trace chains
                    command->redirectOut(words[i + 1]);
                } else if(words[i] == ">>") {
                    //append stdout to file
                    //TODO: trace chains
                    command->redirectOut(words[i + 1], true);
                }
            }
        }
    }
}

void CommandList::executeAll() {
    //check for builtins
    if(words[0] == "exit") {
        throw ExitException("exit");
    }

    //execute all
    int rank = -1;
    pid_t parentid = getpid();
    for(int i = 0; (size_t)i < commands.size(); ++i) {
        if(getpid() == parentid) {
            fork();
            if(getpid() != parentid) {
                rank = i;
            }
        }
    }

    if(rank != -1) {
        commands[rank]->execute();
    } else {
        for(size_t i = 0; i < numOfPipes; ++i) {
            close(pipefds[i]);
        }
        for(size_t i = 0; i < commands.size(); ++i) {
            wait(NULL);
        }
    }
}

