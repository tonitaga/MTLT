#include <fstream>
#include <iostream>


int main() {
    std::ifstream fin("materials/info/info.txt");
    if (!fin.is_open())
        return 0;

    std::string line;
    while(std::getline(fin, line)) {
        std::cout << line << '\n';
    }

    fin.close();
    return 0;
}