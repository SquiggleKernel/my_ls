#include "printDir.h"




int main(int argc, char ** argv) {

    //opendir(x) → readdir(x) →  sort(x) → stat(x) → switch(x) → printf(x) → close-dir(x)

    std::string path;

    int outputWidth{getTerminalWidth()};




    std::bitset<noOfFlags> flags{};
    if (getflags(argc, argv, flags, path) != 0 ) {
        return 1;
    }
    DIR *dir = opendir((path).c_str());

    printDir(dir, flags, path, outputWidth);

    //closing the dir
    closedir(dir);



    std::cout << '\n';
}