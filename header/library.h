#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <conio.h>
// Path: header\library.h
// #include "library.h"
class Library
{
    private:
        std::string password;
    public:
        std::string GetPassword();
        bool CheckPassword(std::string password);
        void SetPassword(std::string password);
};