#ifndef SHELL_H
#define SHELL_H

#include <vector>
#include <string>

class Shell {
private:
    char* cwd = nullptr;

    int change_dir(std::vector<std::string>& argv);
    std::vector<std::string> split(const std::string& s, char delim);

public:
    int start();
};

#endif  // SHELL_H
