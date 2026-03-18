//
// Created by amrit on 05/03/26.
//

#include "printDir.h"


void printDir(DIR *dir, std::bitset<noOfFlags> flags, const std::string & path, int outputWidth) {
    struct dirent *entry{};
    std::vector<std::string> entries{};
    std::vector<LsLineStructure> lines{};

    //storing entries in a vector
    while ((entry = readdir(dir)) != nullptr) {
        entries.emplace_back(entry->d_name);
    }

    if ((flags & isReverse )== isReverse) {
        std::ranges::sort(entries, std::ranges::greater{});
    }
    else std::ranges::sort(entries);



    struct stat st{};
    LsLineStructure temp{};
    for (auto i{0}; static_cast<unsigned long>(i) < entries.size(); i++ ) {
        if (entries[i][0] == '.' && (flags &isAll)!= isAll ) {
            continue;
        }

        temp = {};
        lstat((path + "/" + entries[i]).c_str(), &st);
        temp.inodeNo = st.st_ino;
        __mode_t mode = st.st_mode;

        temp.permissions[0] = printFileType(&mode);
        memcpy(temp.permissions + 1, printPermissions(&mode), 9);
        temp.permissions[10] = '\00';

        if (mode & S_IXUSR) temp.isExecutable = true;

        temp.hardlinks = st.st_nlink;

        // getting owner name and group name and printing
        struct passwd *pw{getpwuid(st.st_uid)};
        if (pw)     temp.ownerName = pw->pw_name;
        else        temp.ownerName = std::to_string(st.st_uid);

        struct group *gr{getgrgid(st.st_gid)};
        if (gr)     temp.groupName =  gr->gr_name;
        else        temp.groupName =  std::to_string(st.st_gid);

        temp.fileSize = st.st_size;

        // converting time since epoch 0 given in sec to normal date format
        struct tm *timeInfo{};
        char timeString[20];

        timeInfo  = localtime(&st.st_atim.tv_sec);
        strftime(timeString, 20,  "%b %d %H:%M", timeInfo);
        temp.fmtTime = timeString ;


        temp.name = entries[i] ;
        lines.emplace_back(temp);
    }
    Widths columnsWidths{calculateMaxWidths(lines)};

    int index{0};
    int maxEntriesInLine{outputWidth/columnsWidths.name};
    if (((flags&isInode)==isInode)) {
        maxEntriesInLine = outputWidth/(columnsWidths.name + columnsWidths.inode +1);
    }
    for (const auto& i : lines) {
        if ((flags&isInode)==isInode)
            std::cout << std::setw(columnsWidths.inode) << i.inodeNo << ' ';

        if ((flags&isList)==isList) {
            std::cout << i.permissions << ' ';
            std::cout << std::setw(columnsWidths.links) << i.hardlinks << ' ';
            std::cout << std::setw(columnsWidths.owner) << i.ownerName << ' ';
            std::cout << std::setw(columnsWidths.group) << i.groupName << ' ';
        }
        if ((flags&isList)==isList || ((flags&isSize)==isSize))
            std::cout << std::setw(columnsWidths.size) << i.fileSize << ' ';
        if ((flags&isList)==isList)
            std::cout << std::setw(columnsWidths.time) << i.fmtTime << ' ';

        if ((flags & isColor)== isColor )
            printColor(i.permissions);

        std::cout << i.name;
        if ((flags & isColor)== isColor )
            resetColor();


        //classifier
        if ((flags & isClassify)== isClassify)
            std::cout << fileClassifier(i.permissions[0], i.permissions[3]) ;
        if ((flags &isList)==isList) {
            std::cout << '\n';
        }



        if ((flags&isList)!=isList) {

            int actualPadding = (columnsWidths.name + 2) - static_cast<int>(i.name.length());
            for (int s = 0; s < actualPadding; ++s) {
                std::cout << ' ';
            }
            if (++index%maxEntriesInLine == 0) {
                std::cout << '\n';
            }
        }
    }

}