#include "prompt.hpp"
#include "exitexception.hpp"

int main(void) {
    int retval = 0;
    try {
        while(retval == 0) {
            retval = prompt();
        }
    } catch(const ExitException& e) {}

    return 0;
}
