//
// Created by amrit on 05/03/26.
//

#include "printDir.h"


void printDir(DIR *dir,[[maybe_unused]] std::uint64_t flags, const std::string & path) {
    struct dirent *entry{};
    std::vector<std::string> entries{};
    std::vector<LsLineStructure> lines{};

    //storing entries in a vector
    for (int i{0}; (entry = readdir(dir)) != nullptr; i++) {
        entries.emplace_back(entry->d_name);
    }

    std::ranges::sort(entries);


    struct stat st{};
    LsLineStructure temp{};
    for (auto i{0}; static_cast<unsigned long>(i) < entries.size(); i++ ) {
        lstat((path + "/" + entries[i]).c_str(), &st);
        __mode_t mode = st.st_mode;

        temp.permissions[0] = printFileType(&mode);
        memcpy(temp.permissions + 1, printPermissions(&mode), 9);
        temp.permissions[10] = '\00';
        // temp.permissions[1] = printPermissions(&mode);

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
    for (const auto& i : lines) {
        std::cout << i.permissions << " ";   std::cout << std::flush;
        std::cout << std::setw(columnsWidths.links) << i.hardlinks << " ";
        std::cout << std::setw(columnsWidths.owner) << i.ownerName << " ";
        std::cout << std::setw(columnsWidths.group) << i.groupName << " ";
        std::cout << std::setw(columnsWidths.size) << i.fileSize << " ";
        std::cout << std::setw(columnsWidths.time) << i.fmtTime << " ";


        std::cout << entries[index] << '\n';

        index++;
    }

}