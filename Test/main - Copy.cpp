#include "header/library.h"
// include library that is needed for system pause
#include <iostream>
#include <conio.h>

using namespace std;

int main(){
    PasswordFunctions pass;
    CoffeeFunctions coffee;
    TypesOfCoffee coffe[3];
    string password, coffeeName;
    bool wrongPass = false;
   
    if(pass.CheckIfFirstPassword()) cout << "First time running program." << endl;
    else cout << "Welcome back." << endl;
    if(pass.CheckBackupPassIsEmpty()){
        string answer;
         cout << "You have not set a backup password. Do so now." << endl;
         cout << "Answer this question: Describe Aldin in one word: ";
         cin >> answer;
        pass.setBackupPassword(answer);
    }
         
    
    cout << "Enter password: ";
    cin >> password;
    pass.setFirstPassword(password);
    bool check = pass.CheckPassword(password);
    if(check == true){
         cout << "Password is correct" << endl;
         coffee.SetTypesOfCoffee(coffe);
         coffee.RemoveTypesOfCoffee(coffe);
    }
         else{
            for(int i =0; i < 3; i++){
                if(i == 2){
                    cout << "ERROR:You have entered the wrong password 3 times. Please contact the administrator(105)." << endl;
                    wrongPass = true;
                    break;
                }
                else if (check == true){
                    cout << "Password is correct" << endl;
                    i = 4;
                    break;
                }
                else cout << "Password is incorrect" << endl;
                cout << "Enter password: ";
                cin >> password;
            }
         }
    if(wrongPass == true){	
        if(!pass.CheckBackupPassIsEmpty()){
            string answer;
            bool repeat = false;
            cout << "Answer this question: Describe Aldin in one word: ";
            cin >> answer;
            bool check = pass.CheckForgottenPassword(answer);
            if(check == true){
                cout << "Answer is correct" << endl;
                cout << "Enter new password: ";
                cin >> answer;
                cout << "Enter new password again: ";
                cin >> password;
                if(answer == password){
                    pass.setFirstPassword(password);
                    cout << "Password has been changed" << endl;
                    repeat=true;
                }
                else{
                    //enter password until they match
                    while(answer != password){
                        cout << "Passwords do not match. Enter new password: ";
                        cin >> answer;
                        cout << "Enter new password again: ";
                        cin >> password;
                    }
                }
                if(!repeat){
                if(answer == password){
                    pass.setFirstPassword(password);
                    cout << "Password has been changed" << endl;
                }
                }

            }
            
        }
    }
    // cin.get();
    // cout << "Press any key to continue...";
    getch();
    return 0;
}