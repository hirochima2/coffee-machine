
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
        fstream outFile,tempFile;
        setPassword(password);
        string backupPass = password;
        outFile.open("header/password.txt", ios::out);
        tempFile.open("header/tempPassword.txt", ios::out);
        if(!outFile){
            cout << "Error opening password file";
            exit(1);
        }
        if(!tempFile){
            cout << "Error opening temp file";
            exit(1);
        }
        int size = backupPass.size();
        for(int i = 0; i < size; i++){
            if(i%2 == 0){
                backupPass[i] = backupPass[i] + 2; //Ovo je neki vid enkripcije sifre
            }
            else backupPass[i] = backupPass[i] - 2;
        }
        tempFile << backupPass;
        //replace tempPassword.txt with password.txt
        outFile.close();
        tempFile.close();
        remove("header/password.txt");
        rename("header/tempPassword.txt", "header/password.txt");

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
void CoffeeFunctions::AddCoffeePrice(double price){
    fstream outFile;
    outFile.open("header/coffeePrices.txt", ios::out | ios::app);
    if(!outFile){
        cout << "Error opening file";
        exit(1);
    }
    outFile << price << endl;
    outFile.close();
}
void CoffeeFunctions::AddCoffeeQuantity(int quantity){
    fstream outFile;
    outFile.open("header/coffeeQuantities.txt", ios::out | ios::app);
    if(!outFile){
        cout << "Error opening file";
        exit(1);
    }
    outFile << quantity << endl;
    outFile.close();
}
void CoffeeFunctions::CoffeeUI(){
    // coffee names from file and in an ordered list
    fstream infile, price, quantity;
    string name;
    double priceOfCoffee;
    int quantityOfCoffee;
    infile.open("header/coffeeNames.txt", ios::in);
    price.open("header/coffeePrices.txt", ios::in);
    quantity.open("header/coffeeQuantities.txt", ios::in);

    if(!price){
        cout << "Error opening file where coffee prices are stored!";
        exit(1);
    }
    if(!quantity){
        cout << "Error opening file where coffee quantities are stored!";
        exit(1);
    }
    if(!infile){
        cout << "Error opening file";
        exit(1);
    }
    int i = 1;
    cout << "Type of coffee - Price - Quantity" << endl;
    
    cout << " -------------------------------" << endl;
    string temp;
   // int w = 5;
    while(infile >> name){
        price >> priceOfCoffee;
        quantity >> quantityOfCoffee;
        // infile << name << endl;
      //  if(i!=1){    
       // if (temp.length() > name.length()) w = 5 - (temp.length() - name.length());
       // else if(temp.length() < name.length()) w = 5 - (name.length() - temp.length());
       // else w = 5;
        //}
        cout << i << ". " << name <<" - " << priceOfCoffee << " - "<< quantityOfCoffee << endl;
        i++;
        temp = name;
    }
    cout << " -------------------------------" << endl;
    infile.close();

}
void CoffeeFunctions::SetTypesOfCoffee(TypesOfCoffee coffee[]){
    string name;
    double price;
    int cups;
    int i = 0;
    char ans;
    
    do{
        CoffeeUI();
        cout << "Enter the name of the coffee: ";
        cin >> name;
        if(name == "exit") return;
        cout << "Enter the price of the coffee: ";
        cin >> price;
        cout << "Enter how many cups of coffee you want to add: ";
        cin >> cups;
        AddCoffeeName(name);
        AddCoffeePrice(price);
        AddCoffeeQuantity(cups);
        system("CLS");

        coffee[i].name = name; // napravi neku mandzu da se napravi niz od elemenata koliko ima kafa i da se moze vremenom povecavati
        CoffeeUI();
        cout << "Do you want to add another coffee? (y/n): ";
        cin >> ans;
        system("CLS");
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
void CoffeeFunctions::ChangeCoffeeName(){
    fstream file, temp_file;
    string choice;
    char ans;
    do{
        CoffeeUI();
        cout << "Enter the name of the coffee you want to change: ";
        cin >> choice;
        if(choice == "exit") return;
        string name;
        int g = 0;
        file.open("header/coffeeNames.txt", ios::in);
        temp_file.open("header/temp.txt", ios::out);
        if(!file){
            cout << "Error opening file where coffee names are stored";
            exit(1);
        }
        if(!temp_file){
            cout << "Error opening temp files are stored";
            exit(1);
        }
        while(file >> name){
            if(name == choice){
                cout << "Enter the new name of the coffee: ";
                cin >> name;
                temp_file << name << endl;
                g++;
            }
            else temp_file << name << endl;
        }
        if (g == 0) cout << "This coffee name doesn't exist!" << endl;
        file.close();
        temp_file.close();
        remove("header/coffeeNames.txt");
        rename("header/temp.txt", "header/coffeeNames.txt");
        system("CLS");
        CoffeeUI();
        cout << "Do you want to change another coffee name? (y/n): ";
        cin >> ans;
        system("CLS");
    }while(ans == 'y');    
}
void CoffeeFunctions::ChangeCoffeeQuantity(){
    fstream file,file2, temp_file;
    string choice;
    char ans;
    do{
        CoffeeUI();
        cout << "Enter the name of the coffee you want to change: ";
        cin >> choice;
        if(choice == "exit") return;
        string name;
        int quantity;
        int g = 0;
        file.open("header/coffeeNames.txt", ios::in);
        file2.open("header/coffeeQuantities.txt", ios::in);
        temp_file.open("header/tempQuantity.txt", ios::out);
        if(!file){
            cout << "Error opening file where coffee names are stored";
            exit(1);
        }
        if(!file2){
            cout << "Error opening file where coffee quantities are stored";
            exit(1);
        }
        if(!temp_file){
            cout << "Error opening temp files are stored";
            exit(1);
        }
        while(file >> name){
            file2 >> quantity;
            if(name == choice){
                cout << "Enter the new quantity of the coffee: ";
                cin >> quantity;
                temp_file << quantity << endl;
                g++;
            }
            else temp_file << quantity << endl;
        }
        if (g == 0) cout << "This coffee name doesn't exist!" << endl;
        file.close();
        file2.close();
        temp_file.close();
        remove("header/coffeeQuantities.txt");
        rename("header/tempQuantity.txt", "header/coffeeQuantities.txt");
        system("CLS");
        CoffeeUI();
        cout << "Do you want to change another coffee name? (y/n): ";
        cin >> ans;
        system("CLS");
    }while(ans == 'y');
}
void CoffeeFunctions::ChangeCoffeePrice(){
    fstream file1, file2, temp_file;
    string choice, name;
    char ans;
    double price;
    int g = 0;
    do{
        CoffeeUI();
        cout << "Enter the name of the coffee you want to change: ";
        cin >> choice;
        if(choice == "exit") return;
        file1.open("header/coffeeNames.txt", ios::in);
        file2.open("header/coffeePrices.txt", ios::in);
        temp_file.open("header/temp.txt", ios::out);
        if(!file1){
            cout << "Error opening file where coffee names are stored";
            exit(1);
        }
        if(!file2){
            cout << "Error opening file where coffee prices are stored";
            exit(1);
        }
        if(!temp_file){
            cout << "Error opening temp files are stored";
            exit(1);
        }
        while(file1 >> name){
            file2 >> price;
            if(name == choice){
                cout << "Enter the new price of the coffee: ";
                cin >> price;
                temp_file << price << endl;
                g++;
            }
            else temp_file << price << endl;
        }
        if (g == 0) cout << "This coffee name doesn't exist!" << endl;
        file1.close();
        file2.close();
        temp_file.close();
        remove("header/coffeePrices.txt");
        rename("header/temp.txt", "header/coffeePrices.txt");
        system("CLS");
        cout << "Do you want to change another coffee price? (y/n): ";
        cin >> ans;
    }while(ans == 'y');
}
/*void CoffeeFunctions::RemoveCoffeeName(string choice){
    fstream file, temp_file;
    string name;
    int g = 0;
    file.open("header/coffeeNames.txt", ios::in);
    temp_file.open("header/temp.txt", ios::out);
    if(!file){
        cout << "Error opening file where coffee names are stored";
        exit(1);
    }
    if(!temp_file){
        cout << "Error opening temp files are stored";
        exit(1);
    }
    while(file >> name){
        if(name == choice) g++;
        if(name != choice) temp_file << name << endl;
    }
    if (g == 0) cout << "This coffee name doesn't exist!" << endl;
    file.close();
    temp_file.close();
    file.open("header/coffeeNames.txt", ios::out);
    temp_file.open("header/temp.txt", ios::in);
    if(!file){
        cout << "Error opening file where coffee names are stored";
        exit(1);
    }
    if(!temp_file){
        cout << "Error opening file where temp coffee names are stored";
        exit(1);
    }
    while(temp_file >> name){
        file << name << endl;
    }
    file.close();
    temp_file.close();
    temp_file.open("header/temp.txt", ios::out);
    temp_file.close();
}

void CoffeeFunctions::RemoveCoffeePrice(string choice){
    fstream file, temp_file;
    string name;
    int g = 0;
    file.open("header/coffeePrices.txt", ios::in);
    temp_file.open("header/temp.txt", ios::out);
    if(!file){
        cout << "Error opening file where coffee names are stored";
        exit(1);
    }
    if(!temp_file){
        cout << "Error opening temp files are stored";
        exit(1);
    }
    while(file >> name){
        if(name == choice) g++;
        if(name != choice) temp_file << name << endl;
    }
    if (g == 0) cout << "This coffee name doesn't exist!" << endl;
    file.close();
    temp_file.close();
    file.open("header/coffeeNames.txt", ios::out);
    temp_file.open("header/temp.txt", ios::in);
    if(!file){
        cout << "Error opening file where coffee names are stored";
        exit(1);
    }
    if(!temp_file){
        cout << "Error opening file where temp coffee names are stored";
        exit(1);
    }
    while(temp_file >> name){
        file << name << endl;
    }
    file.close();
    temp_file.close();
    temp_file.open("header/temp.txt", ios::out);
    temp_file.close();

}*/
void CoffeeFunctions::RemoveTypesOfCoffee(TypesOfCoffee coffee[]){
    fstream file, file_price, file_quantity;
    fstream temp_file, temp_fileprice, temp_filequantity;
    string choice;
    double price;
    int quantity;
    char ans;
    int g = 0;

    do{
        CoffeeUI();
        cout << "Enter the coffee you want to remove: ";
        cin >> choice;
        if(choice == "exit") return;
        system("CLS");
    // copy the file to another file without copying number

        file.open("header/coffeeNames.txt", ios::in);
        file_price.open("header/coffeePrices.txt", ios::in);
        file_quantity.open("header/coffeeQuantities.txt", ios::in);
        temp_file.open("header/temp.txt", ios::out);
        temp_fileprice.open("header/tempPrice.txt", ios::out);
        temp_filequantity.open("header/tempQuantity.txt", ios::out);
        if(!file){
            cout << "Error opening file where coffee names are stored!";
            exit(1);

        }
        if(!file_price){
            cout << "Error opening file where coffee prices are stored!";
            exit(1);
        }
        if(!file_quantity){
            cout << "Error opening file where coffee quantities are stored!";
            exit(1);
        }
        if(!temp_file){
            cout << "Error opening temp file";
            exit(1);
        }
        if(!temp_fileprice){
            cout << "Error opening temp file";
            exit(1);
        }
        if(!temp_filequantity){
            cout << "Error opening temp file";
            exit(1);
        }

        string name;
        while(file >> name){
            file_price >> price;
            file_quantity >> quantity;
            if(name == choice) g++;

            if(name != choice){
                temp_file << name << endl;
                temp_fileprice << price << endl;
                temp_filequantity << quantity << endl;
            }

        }
        if(g == 0){
            cout << "There is no coffee with that name!" << endl;
        }
        
        //clear coffeeNames.txt
        file.close();
        file_price.close();
        file_quantity.close();
        temp_file.close();
        temp_fileprice.close();
        temp_filequantity.close();
        file.open("header/coffeeNames.txt", ios::out);
        file_price.open("header/coffeePrices.txt", ios::out);
        file_quantity.open("header/coffeeQuantities.txt", ios::out);
        temp_file.open("header/temp.txt", ios::in);
        temp_fileprice.open("header/tempPrice.txt", ios::in);
        temp_filequantity.open("header/tempQuantity.txt", ios::in);
        if(!file){
            cout << "Error opening file where coffee names are stored!";
            exit(1);
        }
        if(!file_price){
            cout << "Error opening file where coffee prices are stored!";
            exit(1);
        }
        if(!file_quantity){
            cout << "Error opening file where coffee quantities are stored!";
            exit(1);
        }
        if(!temp_file){
            cout << "Error opening temp file";
            exit(1);
        }
        if(!temp_fileprice){
            cout << "Error opening temp file";
            exit(1);
        }
        if(!temp_filequantity){
            cout << "Error opening temp file";
            exit(1);
        }
        while(temp_file >> name){
            temp_fileprice >> price;
            temp_filequantity >> quantity;
            file << name << endl;
            file_price << price << endl;
            file_quantity << quantity << endl;
        }
        file.close();
        file_price.close();
        file_quantity.close();
    // clear temp.txt
        temp_file.close();
        temp_file.open("header/temp.txt", ios::out);
        temp_file.close();
        temp_fileprice.close();
        temp_fileprice.open("header/tempPrice.txt", ios::out);
        temp_fileprice.close();
        temp_filequantity.close();
        temp_filequantity.open("header/tempQuantity.txt", ios::out);
        temp_filequantity.close();
        CoffeeUI();
        cout << "Do you want to remove another coffee (y/n): ";
        cin >> ans;
        system("CLS");
        g = 0;
    }while(ans == 'y');

}
void ProgramFuncs::AdminMode(){
    PasswordFunctions pass;
    CoffeeFunctions coffee;
    TypesOfCoffee coffeeTypes[100];
    string password, coffeName;
    AdminFuncs admin;
    bool wrongPass = false;
    cout << "---------------------------------------" << endl;
    if(pass.CheckIfFirstPassword()){ cout << "First time running program!" << endl;
   // else cout << "Welcome back!" << endl;
    if(pass.CheckBackupPassIsEmpty()){
        admin.NoBackupPass();
    }
    admin.FirstPassword(password);
    }
    else{
        cout << "Welcome back!" << endl;
        cout << "Enter password: ";
        cin >> password;
    }
    bool check = pass.CheckPassword(password);
    if(check == true){
        cout << "Password is correct!" << endl;
        admin.Operations(coffeeTypes);
    }
    else{
        for(int i = 0; i < 3; i++){
            if(i==2){
                cout << "ERROR: You have entered wrong password 3 times! Please contact system administrator(105)" << endl;
                cout << "Did you forget your password? (y/n): ";
                char ans;
                cin >> ans;
                if(ans == 'y'){
                    admin.ChangePass(password,pass);
                }
                else{
                    wrongPass = true;
                    cout << "Program will now be terminated!" << endl;
                    system("PAUSE");
                    exit(1);
                }
            }
            else if (check == true){
                cout << "Password is correct!" << endl;
                admin.Operations(coffeeTypes);
                i = 4;
                break;
            }
            else{ cout << "Password is incorrect!" << endl;
            cout << "Enter password: ";
            cin >> password;
            check = pass.CheckPassword(password);
            }
        }
    }
    if(wrongPass == true){	
        if(!pass.CheckBackupPassIsEmpty()){
                admin.ChangePass(password,pass);
                }

            }
            
        }
    //}
    // cin.get();
    // cout << "Press any key to continue...";
//}
void ProgramFuncs::UserMode(){
    system("CLS");
    cout << "Coming soon..." << endl;
    cout << "You will be redirected to the main menu!" << endl;
    system("PAUSE");

}
void ProgramFuncs::MainMenUI(){
    system("CLS");
    cout << "----------------------------------------" << endl;
    cout << "Welcome to the coffee machine!" << endl;
    cout << "Choose between the following options: " << endl;
    cout << "1. User mode " << endl;
    cout << "2. Admin mode " << endl;
    cout << "3. Exit program " << endl;
    cout << "----------------------------------------" << endl;
    cout << "Select option: ";
}
void ProgramFuncs::ExitProgram(){
    system("CLS");
    cout << "Thank you for using our program!" << endl;
    cout << "Program will now be terminated!" << endl;
    system("PAUSE");
}
void ProgramFuncs::WrongInput(){
    system("CLS");
    cout << "----------------------------------------" << endl;	
    cout << "Invalid choice!" << endl;
    cout << "You will be redirected to the main menu!" << endl;
    cout << "----------------------------------------" << endl;
    system("PAUSE");
}
void ProgramFuncs::StartProgram(){
    system("CLS");
    cout << "----------------------------------------" << endl;
    cout << "Welcome to the coffee machine!" << endl;
    cout << "Program will now start!" << endl;
    cout << "----------------------------------------" << endl;
    system("PAUSE");
}
void ProgramFuncs::BeginProgram(){
    int choice;
    StartProgram();
    do{
        MainMenUI();
        
        cin >> choice;
        switch(choice){
            case 1:
                UserMode();
                break;
            case 2:
                AdminMode();
                break;
            case 3:
                ExitProgram();
                exit(1);
                break;
            default:
                WrongInput();
                break;
    }
    }while(choice != 3);
}
void AdminFuncs::ChangePass(string password, PasswordFunctions pass){
    string answer;
    fstream file, temp_file;
    ProgramFuncs prog;
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
                    file.open("header/password.txt", ios::out);
                    temp_file.open("header/temp.txt", ios::out);
                    file.close();
                    temp_file.close();
                    remove("header/password.txt");
                    rename("header/temp.txt", "header/password.txt");
                    
                    pass.setFirstPassword(password);
                    cout << "Password has been changed" << endl;
                    repeat=true;
                    system("PAUSE");
                    prog.BeginProgram();
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
                    system("PAUSE");
                    prog.BeginProgram();
                }
        }
   }
   else{
        cout << "Answer is incorrect! " << endl;
        cout << "Program will now be terminated!" << endl;
        system("PAUSE");
        exit(1);
   }
}
void AdminFuncs::NoBackupPass(){
    string answer;
    PasswordFunctions pass;
        cout << "You have not set a backup password! Do so now." << endl;
        cout << "Answer this question: Describe Aldin in one word: ";
        cin >> answer;
        pass.setBackupPassword(answer);
}
void AdminFuncs::FirstPassword(string password){
    string answer;
    PasswordFunctions pass;
    cout << "You have not set a password! Do so now." << endl;
    cout << "Enter password: ";
    cin >> answer;
    pass.setFirstPassword(answer);
    system("PAUSE");
    system("CLS");
    cout << "Welcome back!" << endl;
    cout << "Enter password: ";
    cin >> password;
}

void AdminFuncs::AdminUI(){
            cout << "----------------------------------------" << endl;
            cout << "Welcome to admin mode!" << endl;
            cout << "Choose between the following options: " << endl;
            cout << "1. Add coffee " << endl;
            cout << "2. Remove coffee " << endl;
            cout << "3. Change price of coffee" << endl;
            cout << "4. Change how many cups are left" << endl;
            cout << "5. Change coffee name" << endl;
            cout << "6. Display what coffees are available" << endl;
            cout << "7. Check coin state" << endl;
            cout << "8. Weekly report " << endl;
            cout << "9. Exit admin mode" << endl;
            cout << "----------------------------------------" << endl;
            cout << "Choose option: ";
            
}
void AdminFuncs::Operations(TypesOfCoffee coffeeTypes[]){
        CoffeeFunctions coffee;
        ProgramFuncs prog;
        int choice;
        system("PAUSE");
        system("CLS");
        do{
           AdminUI();
           cin >> choice;
           system("CLS");
           switch(choice){
            case 1:
                cout << "Type exit to go back to main menu" << endl;
                coffee.SetTypesOfCoffee(coffeeTypes);
                break;
            case 2:
                cout << "Type exit to go back to main menu" << endl;
                coffee.RemoveTypesOfCoffee(coffeeTypes);
                break;
            case 3:
                cout << "Type exit to go back to main menu" << endl;
                coffee.ChangeCoffeePrice();
                break;
            case 4:
                //cout << "Coming soon!" << endl;
                cout << "Type exit to go back to main menu" << endl;
                coffee.ChangeCoffeeQuantity();
                break;
            case 5:
                cout << "Type exit to go back to main menu" << endl;
                coffee.ChangeCoffeeName();
                break;
            case 6:
                coffee.CoffeeUI();
               // system("PAUSE");
               // system("CLS");
                break;
            case 7:
               // cout << "Coming soon!" << endl;
               ManipulateCoinState();
                break;
            case 8:
                cout << "Coming soon!" << endl;
                break;
            case 9:
                system("CLS");
                cout << "Exiting admin menu..." << endl;
                system("PAUSE");
                break;
            default:
                int choi;
               // while(choi > 7 || choi < 1){
                    cout << "Invalid choice!" << endl;
                    cout << "You will be redirected to the admin menu!" << endl;
                  //  system("PAUSE");
                   // system("CLS");
                 //   AdminUI();
                  //  cin >> choi;
               // }
                break;
           }
        if(choice != 9){
            system("PAUSE");
            system("CLS");
        }
        }while(choice != 9);

        //coffee.SetTypesOfCoffee(coffeeTypes);
        //coffee.RemoveTypesOfCoffee(coffeeTypes); 
}
void AdminFuncs::CoinUI(int coins[]){
    system("CLS");
    cout << "----------------------------------------" << endl;
    cout << "Coins in machine: " << endl;
    cout << "1. 0.5 KM: " << coins[0] << endl;
    cout << "2. 1 KM: " << coins[1] << endl;
    cout << "3. 2 KM: " << coins[2] << endl;
    cout << "4. 5 KM: " << coins[3] << endl;
    cout << "----------------------------------------" << endl;
}
void AdminFuncs::AddCoins(int coins[]){ // uradi UI
    int choice;
    int amount;
    CoinUI(coins);
    cout << "Choose which coin you want to add: ";
    cin >> choice;
    cout << "How many coins do you want to add? ";
    cin >> amount;
    switch(choice){
        case 1:
            coins[0] += amount;
            break;
        case 2:
            coins[1] += amount;
            break;
        case 3:
            coins[2] += amount;
            break;
        case 4:
            coins[3] += amount;
            break;
        default:
            cout << "Invalid choice!" << endl;
            break;
    }
    fstream file;
    file.open("header/coins.txt", ios::out);
    for(int i = 0; i < 4; i++){
        file << coins[i] << endl;
    }
    file.close();
    file.open("header/coins.txt", ios::in);
    for(int i = 0; i < 4; i++){
        file >> coins[i];
    }
    CoinUI(coins);
    system("PAUSE");
    system("CLS");
}
void AdminFuncs::RemoveCoins(int coins[]){ // uradi UI
    // cout << "Coming soon! " << endl;
    int choice, amount;
    char answer;
    do{
        system("CLS");
        CoinUI(coins);
        cout << "Choose which coin you want to remove: ";
        cin >> choice;
        cout << "----------------------------------------" << endl;
        cout << "How many coins do you want to remove? ";
        cin >> amount;
        switch(choice){
            case 1:
                if(coins[0] - amount < 0){
                    cout << "You can't remove more coins than there are in the machine!" << endl;
                    system("PAUSE");
                    system("CLS");
                    break;
                }
                else coins[0] -= amount;
                break;
            case 2:
                if(coins[1] - amount < 0){
                    cout << "You can't remove more coins than there are in the machine!" << endl;
                    system("PAUSE");
                    system("CLS");
                    break;
                }
                else coins[1] -= amount;
                break;
            case 3:
                if(coins[2] - amount < 0){
                    cout << "You can't remove more coins than there are in the machine!" << endl;
                    system("PAUSE");
                    system("CLS");
                    break;
                }
                else coins[2] -= amount;
                break;
            case 4:
                if(coins[3] - amount < 0){
                    cout << "You can't remove more coins than there are in the machine!" << endl;
                    system("PAUSE");
                    system("CLS");
                    break;
                }
                else coins[3] -= amount;
                break;
            default:
                cout << "Invalid choice!" << endl;
                break;
        }
        fstream file;
        file.open("header/coins.txt", ios::out);
        for(int i = 0; i < 4; i++){
            file << coins[i] << endl;
        }
        file.close();
        file.open("header/coins.txt", ios::in);
        for(int i = 0; i < 4; i++){
            file >> coins[i];
        }
        CoinUI(coins);
        cout << "----------------------------------------" << endl;
        cout << "Do you want to remove more coins? (y/n)" << endl;
        cin >> answer;
    }while(answer == 'y' || answer == 'Y');
}
void AdminFuncs::ManipulateCoinState(){ // uradi UI
    fstream file;
    int choice;
    do{
        file.open("header/coins.txt", ios::in);
        int coins[4];
        for(int i = 0; i < 4; i++){
            file >> coins[i];
        }
        file.close();
        CoinUI(coins);
        cout << "Do you want to add or remove coins? " << endl;
        cout << "----------------------------------------" << endl;
        cout << "1. Add coins " << endl;
        cout << "2. Remove coins " << endl;
        cout << "3. Exit " << endl;
        cout << "----------------------------------------" << endl;
        cout << "Choose option: ";
        cin >> choice;
        switch(choice){
            case 1:
                AddCoins(coins);
                break;
            case 2:
                RemoveCoins(coins);
                break;
            case 3:
                system("CLS");
                cout << "Exiting to admin menu..." << endl;
                break;
            default:
                system("CLS");
                cout << "Invalid choice!" << endl;
                break;
        }

    }while(choice != 3);
}