#include <unistd.h>
#include "command.hpp"

void Command::execute() {
        //redirect io
        //input
        if(inFromFile) {
            infp = freopen(inputFile.c_str(), "r", stdin);
        } else {
            dup2(in, fileno(stdin));
        }
        //output
        if(outToFile) {
            if(!append) {
                outfp = freopen(outputFile.c_str(), "w", stdout);
            } else {
                outfp = freopen(outputFile.c_str(), "a", stdout);
            }
        } else {
            dup2(out, fileno(stdout));
        }

        //close pipes
        for(size_t i = 0; i < numOfPipes; ++i) {
            close(pipefds[i]);
        }
        
        //execvp
        std::vector<char*> args;
        for(size_t i = 0; i < parts.size(); ++i) {
            args.push_back(const_cast<char*>(parts[i].c_str()));
        }
        args.push_back(nullptr);
        execvp(parts[0].c_str(), args.data());
}
