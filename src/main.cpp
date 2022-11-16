#include "prompt.hpp"

int main(void) {
    int retval = 0;
    while(retval == 0) {
        retval = prompt();
    }

    return 0;
}
