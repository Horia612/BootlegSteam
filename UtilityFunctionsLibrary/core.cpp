#include "pch.h"
#include "core.h"

std::shared_ptr<std::vector<std::string>> core::string::split_str(const std::string& str, const std::string& delimiter)
{
    std::shared_ptr<std::vector<std::string>> res(
        new std::vector<std::string>
    );
    auto start{ 0 };
    auto end{ str.find(delimiter) };
    if (end == -1)
    {
        if (str.length())
        {
            res->push_back(str);
        }
        return res;
    }
    while (end != -1)
    {
        //print(str.substr(start, end - start), '\n');
        res->push_back(str.substr(start, end - start));
        start = end + delimiter.size();
        end = str.find(delimiter, start);
    }
    res->push_back(str.substr(start, end - start));
    return res;
}

void core::clear_screen()
{
    system("cls");
}
