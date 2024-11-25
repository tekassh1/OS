#ifndef SHELL_H
#define SHELL_H

#include <vector>
#include <string>

#define STACK_SIZE 1024*1024

class Shell {
private:
    char* cwd = nullptr;

    int changeDir(std::vector<std::string>& argv);
    std::vector<std::string> split(const std::string& s, char delim);

    static int executeProcess(void* args);
    static int childProcess(void* args);

    static char** stringArrayToCharArray(std::vector<std::string> arr);
    static void clearDynaArgs(char** argv, size_t size);
public:
    int start();
};

#endif  // SHELL_H
