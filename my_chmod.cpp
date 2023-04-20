#include <iostream>
#include <set>
#include <algorithm>
#include <sys/stat.h>


bool is_valid(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << "argc != 3" << std::endl;
        return false;
    }
    if (sizeof(argv[1]) != 8) {
        std::cout << "argv[1] count != 4" << std::endl;
        return false;
    }

    const auto valid_value = std::set<char>{ '0', '1', '2', '4', '7' };

    for (auto i = 0; i < 4; i++)
        if (valid_value.find(argv[1][i]) == valid_value.end())
            return false;

    return true;
}


int string_to_filemode(const char* str, mode_t* mode) {
    char* end = NULL;
    *mode = (mode_t)strtol(str, &end, 8);
    if (!end) return 0;
    while(isspace(*end)) end++;
    return *end == '\0' && (unsigned)*mode < 010000;
}

int main(int argc, char *argv[]) {

    if(!is_valid(argc, argv))
        return -1;
    mode_t mode;

    auto new_mode = (const char*)argv[1];
    auto response = string_to_filemode(new_mode, &mode);

    if (chmod(argv[2], mode) != 0) {
        perror("chmod() error");
        return -1;
    }
    std::cout << "Successfully!" << std::endl;

}
