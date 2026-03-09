//
// Created by amrit on 08/03/26.
//
#include "printDir.h"

char printFileType(const __mode_t * mode) {
    // checking file type;
    char type = static_cast<char>((*mode>>12) & 0x0f);
    switch (type) {
        case isDir:       return 'd';
        case isLnk:       return 'l';
        case isSock:      return 's';
        case isBlk:       return 'b';
        case isChr:       return 'c';
        case isFifo:      return 'p';
        case isReg:       return '-';
        default:          return '?';
    }
}

char* printPermissions(const __mode_t * mode) {
    std::bitset<3> ownerPerm = (*mode>>6 & 0b0111);
    static char permissions[9];
    permissions[0] = (ownerPerm.test(2) ? 'r' : '-');
    permissions[1] = (ownerPerm.test(1) ? 'w' : '-');
    permissions[2] = (ownerPerm.test(0) ? 'x' : '-');

    std::bitset<3> groupPerm = *mode>>3 & 0b0111;
    permissions[3] = (groupPerm.test(2) ? 'r' : '-');
    permissions[4] = (groupPerm.test(1) ? 'w' : '-');
    permissions[5] = (groupPerm.test(0) ? 'x' : '-');

    std::bitset<3> othersPerm = *mode & 0b0111;
    permissions[6] = (othersPerm.test(2) ? 'r' : '-');
    permissions[7] = (othersPerm.test(1) ? 'w' : '-');
    permissions[8] = (othersPerm.test(0) ? 'x' : '-');

    return permissions;
}
Widths calculateMaxWidths(const std::vector<LsLineStructure>& lines) {
    Widths maxW;

    for (const auto& line : lines) {
        maxW.links = std::max(maxW.links, std::to_string(line.hardlinks).length());
        maxW.owner = std::max(maxW.owner, line.ownerName.length());
        maxW.group = std::max(maxW.group, line.groupName.length());
        maxW.size  = std::max(maxW.size,  std::to_string(line.fileSize).length());
        maxW.time  = std::max(maxW.time,  line.fmtTime.length());
    }

    return maxW;
}