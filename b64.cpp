#include <iostream>
#include <string>
#include <array>
#include <bitset>
#include "b64encode.h"

//Reference:
//  b64 
//      by Lepus Hare.
//  https://en.wikipedia.org/wiki/Base64

int main()
{
    std::string _input;
    std::getline(std::cin, _input);
    std::cin.clear();
    //Funky Console stuff
    if(_input.compare(0, 3, "´╗┐") > 0){
        _input = _input.substr(3);
    }
    std::cout << encode(_input);
    return 0;
}