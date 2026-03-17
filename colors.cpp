//
// Created by amrit on 17/03/26.
//
#include "printDir.h"


//permission have format drwxrwxrwx  1st rwx is for owner then grp then other 11th char is \n;
void printColor(const LsLineStructure& i) {
    if (i.permissions[0] == 'd')
        std::cout << colorBlue ;
    else if (i.permissions[0] == 'l')
        std::cout << colorCyan;
    else if (i.permissions[0] == 's')
        std::cout << colorPurple ;
    else if (i.permissions[0] == 'p')
        std::cout << colorYellow ;
    else if (i.isExecutable)
        std::cout << colorGreen ;
}

void resetColor() {
    std::cout << colorReset;
}