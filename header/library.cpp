#include "library.h"

using namespace std;

string Library::GetPassword()
{
    return password;
}

void Library::SetPassword(string password)
{
    this->password = password;
}


bool Library::CheckPassword(string password)
{
    string passwordCheck;
    ifstream inFile;
    SetPassword(password);
    string password2 = GetPassword();
    inFile.open("password.txt");
    if (inFile.fail())
    {
        cerr << "Error opening file" << endl;
        exit(1);
    }
    try {
        // Read the password from the file
        inFile >> passwordCheck;
        //check if the password is correct
        if (password == passwordCheck)
        {
            return true;
        }
        else
        {
            return false;
        }
        inFile.close();
    }
    catch (const exception& e) {
        // An error occurred while reading the file
        // Return false to indicate that the password was incorrect
        cerr << "Error: " << e.what() << endl;
        
        return false;
    }
    inFile.close();
    return false;
    }
/*   // Read the password from the file
    getline(inFile, passwordCheck);
    //check if the password is correct
    if (password == passwordCheck || password2 == passwordCheck)
    {
        return true;
    }
    else
    {
        return false;
    }
}*/
