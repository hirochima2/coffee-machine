#include "header/library.h"


using namespace std;

int main(){
    try{
        Library lib;
        string password = "";
        cout << "Enter password: ";
        cin >> password;
        lib.SetPassword(password);
        if (lib.CheckPassword(password))
        {
            cout << "Password is correct" << endl;
        }
        else
        {
            cout << "Password is incorrect" << endl;
        }
        getch();
        return 0;
    }
    catch (exception& e){
        cout << e.what() << endl;
        return 1;
    }
    catch (...){
        cout << "Unknown exception" << endl;
        return 2;
    }
}
