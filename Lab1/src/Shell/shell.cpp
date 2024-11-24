#include <unistd.h>
#include <iostream>

#include "shell.h"

int Shell::start() {
    char buff[256];
    cwd = getcwd(buff, 256);

    while (true) {
        std::cout << buff << " > ";
        std::string input; std::cin >> input;

        std::vector<std::string> argv = split(input, ' ');

        if (argv.size() < 1)
            continue;

        if (argv[0] == "exit") {
            return 0;
        }
        else if (argv[0] == "cd") {
            int res = change_dir(argv);
            if (res != 0) {
                std::cout << "Wrong path!" << "\n";
            }
        }
        else {

        }
    }
}

int Shell::change_dir(std::vector<std::string> &argv) {
    int res = chdir(argv[1].c_str());
    if (res != 0) {
        char buff[256];
        cwd = getcwd(buff, 256);
    }
    return res;
}
