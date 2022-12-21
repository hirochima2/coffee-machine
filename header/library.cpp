
#include "library.h"
using namespace std;


string PasswordFunctions::getPassword(){ // neka vrsta pointera ne znam radili smo na faksu
    return this->password;
}

bool PasswordFunctions::CheckPassword(string password){  // provjerava da li je password tacan
    fstream inFile;
    string passChecker;
    setPassword(password);
    int size = password.size();
    bool returner;
    inFile.open("header/password.txt", ios::in);
    if(!inFile){
        cout << "Error opening file";
        exit(1);
    }
    while(inFile >> passChecker){
        for(int i = 0; i < size; i++){
            if(i%2 == 0){
                passChecker[i] = passChecker[i] - 2;
            }
            else passChecker[i] = passChecker[i] + 2;
        }
        if(passChecker == password){
                returner = true;
            }
        else returner = false;
    
    }
    inFile.close();
    return returner;

    }
    void PasswordFunctions::setPassword(string password){ // i ovo smo radili na faksu
    this->password = password;
}
bool PasswordFunctions::CheckIfFirstPassword(){ // Provjerava da li je prvi put da se kuca sifra tako sto gleda da li je 
    fstream inFile;                             // fajl prazan ili ne
    bool returner;
    inFile.open("header/password.txt", ios::in);
    // check if the file is empty
    if(inFile.peek() == std::ifstream::traits_type::eof()){
        returner = true;
    }
    else returner = false;
    inFile.close();
    return returner;
}
void PasswordFunctions::setFirstPassword(string password){ // Ako je prvi put da se ulazi u program, onda se pomocu
    if(CheckIfFirstPassword()){                           // ove funkcije postavlja prva sifra
        fstream outFile;
        setPassword(password);
        string backupPass = password;
        outFile.open("header/password.txt", ios::out);
        if(!outFile){
            cout << "Error opening file";
            exit(1);
        }
        int size = backupPass.size();
        for(int i = 0; i < size; i++){
            if(i%2 == 0){
                backupPass[i] = backupPass[i] + 2; //Ovo je neki vid enkripcije sifre
            }
            else backupPass[i] = backupPass[i] - 2;
        }
        outFile << backupPass;
        outFile.close();
    }
}
void PasswordFunctions::setForgottenPassword(string password){ // Ako se zaboravi sifra, onda se pomocu ove funkcije
    fstream outFile;                                           // postavlja nova sifra, tako sto se brise stara
    setPassword(password);
    string backupPass = password;
    // delete the old password
    outFile.open("header/password.txt", ios::out | ios::trunc);
    cout << "Old password deleted!" << endl;
    if(!outFile){
        cout << "Error opening file";
        exit(1);
    }
    outFile.close();
    // write the new password
    outFile.open("header/password.txt", ios::out);
    if(!outFile){
        cout << "Error opening file";
        exit(1);
    }
    int size = backupPass.size();
    for(int i = 0; i < size; i++){
        if(i%2 == 0){
            backupPass[i] = backupPass[i] + 2;
        }
        else backupPass[i] = backupPass[i] - 2;
    }
    outFile << backupPass;
    cout << "Password changed!" << endl;
    outFile.close();
}
bool PasswordFunctions::CheckBackupPassIsEmpty(){ // Provjerava da li postoji odgovor na hajmo reci "Sigurnosno pitanje"
    fstream inFile;
    bool returner;
    inFile.open("header/backupPassword.txt", ios::in);
    // check if the file is empty
    if(inFile.peek() == std::ifstream::traits_type::eof()){
        returner = true;
    }
    else returner = false;
    inFile.close();
    return returner;
}

void PasswordFunctions::setBackupPassword(string password){ // Ako nema odgovora na sigurnosno pitanje, onda se pomocu ove
    if(CheckBackupPassIsEmpty()){                          // funkcije postavlja odgovor na sigurnosno pitanje
        fstream outFile;
        setPassword(password);
        string backupPass = password;
        outFile.open("header/backupPassword.txt", ios::out);
        if(!outFile){
            cout << "Error opening file";
            exit(1);
        }
        int size = backupPass.size();
        for(int i = 0; i < size; i++){
            if(i%2 == 0){
                backupPass[i] = backupPass[i] + 2;
            }
            else backupPass[i] = backupPass[i] - 2;
        }	
        outFile << backupPass;
        cout << "Thank you, your answer has been saved!" << endl;
        cout << "If you forget your password, you can use this answer to recover your password!" << endl;
        outFile.close();
    }
}
bool PasswordFunctions::CheckForgottenPassword(string password){ // Ova funkcija gleda da li je unesen tacan odgovor na "Sigurnosno pitanje"
    fstream inFile;
    string passChecker;
    setPassword(password);
    int size = password.size();
    bool returner;
    inFile.open("header/backupPassword.txt", ios::in);
    if(!inFile){
        cout << "Error opening file";
        exit(1);
    }
    while(inFile >> passChecker){
        for(int i = 0; i < size; i++){
            if(i%2 == 0){
                passChecker[i] = passChecker[i] - 2;
            }
            else passChecker[i] = passChecker[i] + 2;
        }
        if(passChecker == password){
                returner = true;
            }
        else returner = false;
    
    }
    inFile.close();
    return returner;
}
bool CoffeeFunctions::CheckIfCoffeeNameExists(string name){
    fstream inFile;
    string nameChecker;
    bool returner;
    inFile.open("header/coffeeNames.txt", ios::in);
    if(!inFile){
        cout << "Error opening file";
        exit(1);
    }
    while(inFile >> nameChecker){
        if(nameChecker == name){
            returner = true;
        }
        else returner = false;
    }
    inFile.close();
    return returner;
}
void CoffeeFunctions::AddCoffeeName(string name){ // Ova funkcija dodaje ime kafe u fajl
    fstream outFile;
    outFile.open("header/coffeeNames.txt", ios::out | ios::app);
    if(!outFile){
        cout << "Error opening file";
        exit(1);
    }
    cin.ignore(100, '\n'); // da bi se izbjeglo da se ime kafe ucita u isti red kao i prethodno ime kafe
    // check if type of coffee already exists
    if(CheckIfCoffeeNameExists(name)){
        cout << "This coffee name already exists!" << endl;
        cout << "Please enter a different name!" << endl;
        return;
    }
    outFile << name << endl;
    outFile.close();
}
void CoffeeFunctions::CoffeeUI(){
    // coffee names from file and in an ordered list
    fstream infile;
    string name;
    infile.open("header/coffeeNames.txt", ios::in);
    if(!infile){
        cout << "Error opening file";
        exit(1);
    }
    int i = 1;
    while(infile >> name){
    
        // infile << name << endl;
        cout << i << ". " << name << endl;
        i++;
    }
    cout << " -------------------------------" << endl;
    infile.close();

}
void CoffeeFunctions::SetTypesOfCoffee(TypesOfCoffee coffee[]){
    string name;
    int i = 0;
    char ans;
    do{
        
        cout << "Enter the name of the coffee: ";
        cin >> name;
    
        AddCoffeeName(name);
        coffee[i].name = name; // napravi neku mandzu da se napravi niz od elemenata koliko ima kafa i da se moze vremenom povecavati
        CoffeeUI();
        cout << "Do you want to add another coffee? (y/n): ";
        cin >> ans;
        if(ans == 'y'){
            i++;
        }
    }while(ans == 'y');

    


}
int CoffeeFunctions::SizeOfTypesOfCoffee(){
    fstream infile;
    string name;
    infile.open("header/coffeeNames.txt", ios::in);
    if(!infile){
        cout << "Error opening file";
        exit(1);
    }
    int i = 0;
    while(infile >> name){
        i++;
    }
    infile.close();
    return i;
}
void CoffeeFunctions::RemoveTypesOfCoffee(TypesOfCoffee coffee[]){
    fstream file;
    fstream temp_file;
    string choice;
    char ans;
    int g = 0;
    do{
        cout << "Enter the coffee you want to remove: ";
        cin >> choice;
    // copy the file to another file without copying number
        file.open("header/coffeeNames.txt", ios::in);
        temp_file.open("header/temp.txt", ios::out);
        if(!file){
            cout << "Error opening file";
            exit(1);

        }
        if(!temp_file){
            cout << "Error opening file";
            exit(1);
        }
        string name;
        while(file >> name){
            if(name == choice) g++;

            if(name != choice){
                temp_file << name << endl;
            }

        }
        if(g == 0){
            cout << "There is no coffee with that name!" << endl;
        }
        
        //clear coffeeNames.txt
        file.close();
        temp_file.close();
        file.open("header/coffeeNames.txt", ios::out);
        temp_file.open("header/temp.txt", ios::in);
        if(!file){
            cout << "Error opening file";
            exit(1);
        }
        if(!temp_file){
            cout << "Error opening file";
            exit(1);
        }
        while(temp_file >> name){
            file << name << endl;
        }
        file.close();
    // clear temp.txt
        temp_file.close();
        temp_file.open("header/temp.txt", ios::out);
        temp_file.close();
        CoffeeUI();
        cout << "Do you want to remove another coffee (y/n): ";
        cin >> ans;
        g = 0;
    }while(ans == 'y');

}