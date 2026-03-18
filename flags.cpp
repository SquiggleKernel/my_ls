//
// Created by amrit on 18/03/26.
//
#include <getopt.h>
#include "printDir.h"

void printHelp() {
    std::cout
        <<"Usage: ls [OPTION]... [FILE/DIR] \n\n"
        <<"  -a          do not ignore entries starting with .\n"
        <<"  -h          with -l, print sizes like 1K 234M 2G etc.\n"
        <<"  -i          print the index number of each file\n"
        <<"  -l          use a long listing format\n"
        <<"  -r          reverse order while sorting\n"
        <<"  -s          print the allocated size of each file, in blocks\n"
        <<"  -t          sort by time, newest first\n"
        <<"  -F          append indicator (one of */=>@|) to entries\n"
        <<"  --color[=WHEN]  colorize the output; WHEN can be 'always'\n";
}

int getflags(int argc,char ** argv, std::bitset<noOfFlags>& flags, std::string& path) {
    int opt{};
    int longIndex{};
    struct option longOptions[] {
        {"color", required_argument, 0, 'C'},
        {0,0,0,0}
    };

    while ((opt = getopt_long(argc, argv, "ahilrstF", longOptions, &longIndex)) !=-1) {
        switch (opt) {
            case 'a': flags |= isAll;           break;      // done
            case 'h': flags |= isHumanReadable; break;
            case 'i': flags |= isInode;         break;      //done
            case 'l': flags |= isList;          break;      //done
            case 'r': flags |= isReverse;       break;      //done
            case 's': flags |= isSize;          break;
            case 't': flags |= isTime;          break;
            case 'F': flags |= isClassify;      break;      //done
            case 'C': {                                     //done
                if (isatty(STDOUT_FILENO) && static_cast<std::string>(optarg)=="auto")
                    flags |= isColor;
                else if (static_cast<std::string>(optarg) == "always")
                    flags |= isColor;
                else if (static_cast<std::string>(optarg) == "never")
                    flags &= ~isColor;
                break;
            }
            case '?':
                std::cerr << "Unknown flag\n";
                printHelp();
                return 1;
        }

    }
    if (optind == argc) {
        path = ".";
    } else {
        path = argv[optind];
    }
    return 0;
}