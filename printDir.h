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

constexpr std::bitset<8> isColor{0b00000001};
constexpr std::bitset<8> isList{0b00000010};
constexpr std::bitset<8> isAll{0b00000100};
constexpr std::bitset<8> isReverse{0b00001000};
constexpr std::bitset<8> isHumanReadable{0b00010000};
constexpr std::bitset<8> isTime{0b00100000};
constexpr std::bitset<8> isSize{0b01000000};
constexpr std::bitset<8> isInode{0xff};


constexpr char colorDir[] {"\x1b[1;34m"};                       //for directories(Bold Blue)
constexpr char colorSymlink[] {"\x1b[1;36m"};                   // bright Cyan
constexpr char colorPipe[] {"\x1b[0;33m"};                      // Yellow
constexpr char colorSocket[] {"\x1b[1;35m"};                    // bright Magenta
constexpr char colorBlockDevice[] {"\x1b[1;33m"};               // bright Yellow
constexpr char colorCharDevice[] {"\x1b[1;33m"};                // bright Yellow
constexpr char colorExecutable[] {"\x1b[01;32m"};               // bright Green
constexpr char colorSuid[] {"\x1b[0;37;41m"};                   // white on red
constexpr char colorSgid[] {"\x1b[0;30;43m"};                   // black on yellow
constexpr char colorSticky[] {"\x1b[0;37;44m"};                 // back on blue
constexpr char colorOtherWritable[] {"\x1b[0;34;42m"};          // blue on green
constexpr char colorOtherWritableSticky[] {"\x1b[0;3;42m"};    // black on green
constexpr char colorReset[]  {"\x1b[0m"};                       //for resetting

constexpr char isDir{0b0100};
constexpr char isReg{0b1000};
constexpr char isLnk{0b1010};
constexpr char isBlk{0b0110};
constexpr char isChr{0b0010};
constexpr char isFifo{0b0001};
constexpr char isSock{0b1100};

struct LsLineStructure {
    unsigned long inodeNo{};
    char permissions[11];     // 9 for permissions + 1 for \00 null terminator
    __nlink_t hardlinks{};

    std::string ownerName{};
    std::string groupName{};
    std::size_t fileSize{};

    std::string fmtTime;
    std::string name;
    bool isExecutable{false};
    char classifier{};

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
char fileClassifier(char x);
void printColor(const char (&permissions)[11]);
void resetColor();


#endif //MY_LS_PRINTDIR_H