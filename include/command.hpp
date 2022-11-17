#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <string>
#include <vector>

class Command {
private:
    std::vector<std::string> parts;
    int* pipefds;
    size_t numOfPipes;

    bool inFromFile;
    int in;
    std::string inputFile;
    FILE* infp;

    bool outToFile;
    int out;
    std::string outputFile;
    bool append;
    FILE* outfp;

public:
    Command(std::string name, int* fds, size_t n)
        : parts()
        , pipefds(fds)
        , numOfPipes(n)
        , inFromFile(false)
        , in(0)
        , inputFile()
        , infp(NULL)
        , outToFile(false)
        , out(0)
        , outputFile()
        , append(false)
        , outfp(NULL)
    {
        parts.push_back(name);
    }

    std::string getName() { return parts[0]; }

    void addArgument(std::string arg) { parts.push_back(arg); }

    void execute();

    void redirectIn(int fd) {
        inFromFile = false;
        in = fd;
    }

    void redirectIn(std::string filename) {
        inFromFile = true;
        inputFile = filename;
    }

    void redirectOut(int fd) {
        outToFile = false;
        out = fd;
    }

    void redirectOut(std::string filename, bool a = false) {
        outToFile = true;
        outputFile = filename;
        append = a;
    }

    ~Command() {
        if(inFromFile && infp != NULL) {
            fclose(infp);
        }
        if(outToFile && outfp != NULL) {
            fclose(outfp);
        }
    }
};

#endif //COMMAND_HPP

