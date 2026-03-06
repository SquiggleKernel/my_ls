#include <iostream>
#include <dirent.h>
#include <cstdint>
void printDir(DIR *dir, std::uint64_t flags, std::string path);

int main(int argc, char ** argv) {

    //opendir(x) → readdir(x) →  sort(x) → stat() → switch() → printf() → close-dir()
    if (argc < 2 ) {
        std::cerr << "[Usage] : "<< /*argv[0]*/"my_ls"  << " <./directoryOrFile>";
        return 1;
    }
    std::string path = argv[1];  // default to current dir
    DIR *dir = opendir((path).c_str());
    std::uint64_t flags{};
    printDir(dir, flags, path);

    //closing the dir
    closedir(dir);



    std::cout << '\n';
}