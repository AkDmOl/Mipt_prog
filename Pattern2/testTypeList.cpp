#include "typeList.hpp"
#include <iostream>

int main() {

    using empty = typename MakeTypeList<>::res;
    using notEmpty = typename MakeTypeList<char, int>::res;

    std::cout << Length<empty>::value << "\n";
    std::cout << Length<notEmpty>::value << "\n";


    TypeAt<notEmpty, 1>::Result a;
    a = 'a';

    std::cout << IndexOf<notEmpty, int>::value << "\n";
    std::cout << IndexOf<empty, char>::value << "\n";


    using oneEl = typename MakeTypeList<char>::res;

    using addEmpty = typename Append<empty, bool>::Result;
    using addNotEmpty = typename Append<notEmpty, bool>::Result;
    using addOneEl = typename Append<oneEl, bool>::Result;

    std::cout <<"AddEmpty " << IndexOf<addEmpty, bool>::value << " Len " << Length<addEmpty>::value  << "\n";
    std::cout << "AddNotEmpty " << IndexOf<addNotEmpty, bool>::value << " Len " << Length<addNotEmpty>::value << "\n";
    std::cout << "AddOneEl " << IndexOf<addOneEl, bool>::value << " Len " << Length<addOneEl>::value  << "\n";


    using eraseEmpty = typename Erase<empty, int>::Result;
    using eraseNotEmpty = typename Erase<notEmpty, int>::Result;
    using eraseOneEl = typename Erase<oneEl, int>::Result;

    std::cout <<"EraseEmpty Len " << Length<eraseEmpty>::value  << "\n";
    std::cout << "EraseNotEmpty " << IndexOf<eraseNotEmpty, bool>::value << " Len " << Length<eraseNotEmpty>::value << "\n";
    std::cout << "EraseOneEl " << IndexOf<eraseOneEl, bool>::value << " Len " << Length<eraseOneEl>::value  << "\n";

    return 0;
}
