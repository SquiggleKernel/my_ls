//
// Created by amrit on 17/03/26.
//
#include "printDir.h"


//permission have format drwxrwxrwx  1st rwx is for owner then grp then other 11th char is \n;
void printColor(const char (&perms)[11]) {
    if (perms[0] == 'l') {
        std::cout << colorSymlink;
    }
    else if (perms[0] == 'p') {
        std::cout << colorPipe;
    }
    else if (perms[0] == 's') {
        std::cout << colorSocket;
    }
    else if (perms[0] == 'b') {
        std::cout << colorBlockDevice;
    }
    else if (perms[0] == 'c') {
        std::cout << colorCharDevice;
    }
    else if (perms[0] == 'd') {
        if (perms[9] == 't') {
            std::cout << ((perms[8]=='w') ? colorOtherWritableSticky : colorSticky);
        }
        else
            std::cout << ((perms[8] =='w') ? colorOtherWritable : colorDir);
    }

    else if (perms[3] == 's' || perms[3] == 'S') {
        std::cout << colorSuid;
    }
    else if (perms[6] == 's' || perms[6] == 'S') {
        std::cout << colorSgid;
    }
    else if (perms[3] == 'x') {
        std::cout << colorExecutable;
    }
}

void resetColor() {
    std::cout << colorReset;
}