//
// Created by amrit on 08/03/26.
//

#ifndef MY_LS_PRINTDIR_H
#define MY_LS_PRINTDIR_H

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
#include <ctime>
#include <cstring>
#include <iomanip>


//not current priority
constexpr char colorBlue[] {"\x1b[1;34m"};             //for directories(Bold Blue)
constexpr char colorGreen[] {"\x1b[1;36m"};            //for executable files
constexpr char colorCyan[] {"\x1b[0;46m"};             //for symbolic links
constexpr char colorRed[] {"\x1b[0;41m"};              // for archived files with .zip etc. files
constexpr char colorYello[] {"\x1b[0;93m"};            // for FIFO
constexpr char colorReset[]  {"\x1b[0m"};           //for resetting

constexpr char isDir{0b0100};
constexpr char isReg{0b1000};
constexpr char isLnk{0b1010};
constexpr char isBlk{0b0110};
constexpr char isChr{0b0010};
constexpr char isFifo{0b0001};
constexpr char isSock{0b1100};

struct LsLineStructure {
    char permissions[11];     // 1 for type + 9 for permissions + 1 for \00 null terminator
    __nlink_t hardlinks{};

    std::string ownerName{};
    std::string groupName{};
    std::size_t fileSize{};

    std::string fmtTime;
    std::string name;
};

struct Widths {
    int links = 0;
    int owner = 0;
    int group = 0;
    int size  = 0;
    int time  = 0;
};

void printDir(DIR *dir,[[maybe_unused]] std::uint64_t flags, const std::string & path);
char printFileType(const __mode_t * mode);
char* printPermissions(const __mode_t * mode);
Widths calculateMaxWidths(const std::vector<LsLineStructure>& lines);


#endif //MY_LS_PRINTDIR_H