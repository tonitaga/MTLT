#include <fstream>
#include <vector>
#include <iterator>
#include "termcolor.h"

using namespace termcolor;

int main() {
    std::ifstream fin("materials/info/info.txt");
    if (!fin.is_open())
        return 0;

    std::string line;
    while(std::getline(fin, line)) {
        std::cout << red << line << reset << '\n';
    }

    fin.close();
    return 0;
}