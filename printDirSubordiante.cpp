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
    static char permissions[9];
    permissions[0] = (*mode&S_IRUSR ? 'r' : '-');
    permissions[1] = (*mode&S_IWUSR ? 'w' : '-');
    permissions[2] = (*mode&S_ISUID ? (*mode&S_IXUSR ? 's' : 'S') : (*mode&S_IXUSR ? 'x' : '-'));

    permissions[3] = (*mode&S_IRGRP ? 'r' : '-');
    permissions[4] = (*mode&S_IWUSR ? 'w' : '-');
    permissions[5] = (*mode&S_ISGID ? (*mode&S_IXGRP ? 's' : 'S') : (*mode&S_IXGRP ? 'x' : '-'));

    permissions[6] = (*mode&S_IROTH ? 'r' : '-');
    permissions[7] = (*mode&S_IWOTH ? 'w' : '-');
    permissions[8] = (*mode&S_ISVTX ? (*mode&S_IXOTH ? 't' : 'T') : (*mode&S_IXOTH ? 'x' : '-'));

    return permissions;
}
Widths calculateMaxWidths(const std::vector<LsLineStructure>& lines) {
    Widths maxW;

    for (const auto& line : lines) {
        maxW.links = std::max<int>(maxW.links, std::to_string(line.hardlinks).length());
        maxW.owner = std::max<int>(maxW.owner, line.ownerName.length());
        maxW.group = std::max<int>(maxW.group, line.groupName.length());
        maxW.size  = std::max<int>(maxW.size,  std::to_string(line.fileSize).length());
        maxW.time  = std::max<int>(maxW.time,  line.fmtTime.length());
    }

    return maxW;
}


char fileClassifier(char x) {
    switch (x) {
        case 'd': return '/';
        case 'l': return '@';
        case 's': return '=';
        case 'p': return '|';
        default: return ' ';
    }
}

