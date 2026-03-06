//
// Created by amrit on 05/03/26.
//

#include <algorithm>
#include <cstdint>
#include <dirent.h>
#include <iostream>
#include <string>
#include <vector>
#include <sys/stat.h>
#include <bitset>
#include <pwd.h>
#include <grp.h>

const char* colorBlue[] {"\x1b[1;34m"};          //for directories
const char* colorGreen[] {"\x1b[1;36m"};         //for symbolic links
const char* colorReset[]  {"\x1b[0m"};           //for resetting

constexpr char isDir{0b0100};
constexpr char isReg{0b1000};
constexpr char isLnk{0b1010};
constexpr char isBlk{0b0110};
constexpr char isChr{0b0010};
constexpr char isFifo{0b0001};
constexpr char isSock{0b1100};





void printFileType(__mode_t * mode) {
    // checking file type;
    char type = (*mode>>12) & 0x0f;
    switch (type) {
        case isDir:       std::cout << 'd'; break;
        case isLnk:       std::cout << 'l'; break;
        case isSock:      std::cout << 's'; break;
        case isBlk:       std::cout << 'b'; break;
        case isChr:       std::cout << 'c'; break;
        case isFifo:      std::cout << 'p'; break;
        case isReg:       std::cout << '-'; break;
        default:          std::cout << '?';
    }
}

void printPermissions(__mode_t * mode) {
    std::bitset<3> ownerPerm = (*mode>>6 & 0b0111);
    std::cout   << (ownerPerm.test(2) ? 'r' : '-')
                << (ownerPerm.test(1) ? 'w' : '-')
                << (ownerPerm.test(0) ? 'x' : '-');

    std::bitset<3> groupPerm = *mode>>3 & 0b0111;
    std::cout   << (groupPerm.test(2) ? 'r' : '-')
                << (groupPerm.test(1) ? 'w' : '-')
                << (groupPerm.test(0) ? 'x' : '-');

    std::bitset<3> othersPerm = *mode & 0b0111;
    std::cout   << (othersPerm.test(2) ? 'r' : '-')
                << (othersPerm.test(1) ? 'w' : '-')
                << (othersPerm.test(0) ? 'x' : '-');

}

void printDir(DIR *dir, std::uint64_t flags, std::string path) {
    struct dirent *entry{};
    std::vector<std::string> entries{};

    //storing entries in a vector
    for (int i{0}; (entry = readdir(dir)) != nullptr; i++) {
        entries.push_back(entry->d_name);
    }

    std::ranges::sort(entries);


    struct stat st{};
    for (int i{0}; i<entries.size(); i++ ) {
        lstat((path + "/" + entries[i]).c_str(), &st);
        __mode_t mode = st.st_mode;

        printFileType(&mode);
        printPermissions(&mode);

        std::cout << " " << st.st_nlink;

        // getting owner name and gorup name and printing
        struct passwd *pw{getpwuid(st.st_uid)};
        if (pw)     std::cout << " " << pw->pw_name;
        else        std::cout << " " << st.st_uid;

        struct group *gr{getgrgid(st.st_gid)};
        if (gr)     std::cout << " " << gr->gr_name;
        else        std::cout << " " << st.st_gid;

        std::cout << " "<< st.st_size << '\t';

        std::cout << " " << st.st_atim.tv_sec;

        std::cout << " " <<entries[i] <<'\n';
    }


}