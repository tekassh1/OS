#include <unistd.h>
#include <iostream>
#include <csignal>
#include <sys/wait.h>
#include <cstring>
#include <sstream>
#include <chrono>

#include "shell.h"

std::vector<std::string> Shell::split(const std::string& s, char delim) {
    std::vector<std::string> tokens;
    std::string token;
    std::stringstream tokenStream(s);

    while (std::getline(tokenStream, token, delim)) {
        tokens.push_back(token);
    }
    return tokens;
}

char** Shell::stringArrayToCharArray(std::vector<std::string> arr) {
    char** res = new char*[arr.size() + 1];
    for (int i = 0; i < arr.size(); i++) {
        res[i] = new char[arr[i].size() + 1];
        strcpy(res[i], arr[i].c_str());
    }
    res[arr.size()] = nullptr;
    return res;
}

void Shell::clearDynaArgs(char** argv, size_t size) {
    for (int i = 0; i < size; i++) {
        delete[] argv[i];
    }
    delete[] argv;
}

int Shell::start() {
    cwd = getcwd(nullptr, 256);

    while (true) {
        std::cout << cwd << " > ";
        std::string input;
        std::getline(std::cin, input);

        std::vector<std::string> argv_s = split(input, ' ');

        if (argv_s.empty())
            continue;

        if (argv_s[0] == "exit") {
            return 0;
        }
        else if (argv_s[0] == "cd") {
            int res = changeDir(argv_s);
            if (res != 0) {
                perror("cd");
            }
        }
        else {
            char** argv = stringArrayToCharArray(argv_s);
            executeProcess(argv);
            clearDynaArgs( argv, argv_s.size());
        }
    }
}

int Shell::changeDir(std::vector<std::string> &argv) {
    int res = chdir(argv[1].c_str());
    if (res == 0) {
        cwd = getcwd(nullptr, 256);
    }
    return res;
}

int Shell::childProcess(void* arg) {
    char** args = static_cast<char**>(arg);

    if (execvp(args[0], args) == -1) {
        if (errno == ENOENT) {
            std::cerr << "Unknown command: " << args[0] << std::endl;
        } else {
            perror("execvp");
        }
        _exit(EXIT_FAILURE);
    }
}


int Shell::executeProcess(void* arg) {
    auto start = std::chrono::high_resolution_clock::now();
    char* child_stack = new char[STACK_SIZE];
    pid_t pid = clone(childProcess, child_stack + STACK_SIZE, SIGCHLD, arg);

    pid_t res = -1;
    if (pid == -1) {
        perror("clone");
    }
    else {
        res = waitpid(pid, nullptr, 0);
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    std::cout << elapsed.count() << "ms" << std::endl;

    delete[] child_stack;
    return res;
}
