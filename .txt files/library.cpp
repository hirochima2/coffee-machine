
#include "library.h"
using namespace std;
int count = 0;

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
void CoffeeFunctions::AddBoughtCoffee(){
    fstream outFile;
    outFile.open("header/boughtCoffee.txt", ios::out | ios::app);
    if(!outFile){
        cout << "Error opening file" << endl;
        system("PAUSE");
        exit(1);
    }
    outFile << "0" << endl;
    outFile.close();
}
void CoffeeFunctions::UserCoffeeUI(){
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
    if(!infile){
        cout << "Error opening file where coffee names are stored!";
        exit(1);
    }
    int i = 1;
    cout << "---------------------------------------" << endl;
    cout << "Type of coffee - Price " << endl;
    
    cout << "---------------------------------------" << endl;
    string temp;
   // int w = 5;
    while(infile >> name){
        price >> priceOfCoffee;
        quantity >> quantityOfCoffee;
        if(quantityOfCoffee > 0) cout << i << ". " << name <<": " << priceOfCoffee <<" KM"<< endl;
        else cout << i << ". "<<"**"<< name <<"*"<<"*:*" <<"*"<< priceOfCoffee <<"*"<<"*KM**" << " (Out of stock)" << endl;
        i++;
        temp = name;
    }
    cout << "---------------------------------------" << endl;
    infile.close();
    price.close();
    quantity.close();
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
    price.close();
    quantity.close();

}
int CoffeeFunctions::CheckHowManyCoffeeTypes(){
    fstream infile;
    string name;
    int counter = 0;
    infile.open("header/coffeeNames.txt", ios::in);
    if(!infile){
        cout << "Error opening file";
        exit(1);
    }
    while(infile >> name){
        counter++;
    }
    infile.close();
    return counter;
}
void CoffeeFunctions::SetTypesOfCoffee(TypesOfCoffee coffee[]){
    string name;
    double price;
    int cups;
    int i = 0, j = 0,k = 0;
    int a = CheckHowManyCoffeeTypes();
    char ans;
   // fstream file;
   // file.open("header/boughtCoffee.txt", ios::out | ios::app);
   /* if(!file){
        cout << "Error opening file where bought coffee is stored!" << endl;
        system("PAUSE");
        exit(1);
    }*/
    
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
        AddBoughtCoffee();
        system("CLS");

        coffee[i].name = name; // napravi neku mandzu da se napravi niz od elemenata koliko ima kafa i da se moze vremenom povecavati
        CoffeeUI();
        //file << a << endl;
        cout << "Do you want to add another coffee? (y/n): ";
        cin >> ans;
        system("CLS");
        if(ans == 'y'){
            i++;
        }
    }while(ans == 'y');
  //  file.close();

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
        cout << "Do you want to change another coffee quantity? (y/n): ";
        cin >> ans;
        //system("CLS");
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
    system("CLS");
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
        cout << "---------------------------------------" << endl;
    }
    bool check = pass.CheckPassword(password);
    if(check == true){
        system("CLS");
        cout << "Password is correct!" << endl;
        admin.Operations(coffeeTypes);
    }
    else{
        for(int i = 0; i < 3; i++){
            if(i==2 && check == false){
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
                system("CLS");
                cout << "Password is correct!" << endl;
                admin.Operations(coffeeTypes);
                i = 4;
                break;
            }
            else{ cout << "Password is incorrect!" << endl;
            cout << "Enter password: ";
            cin >> password;
            cout << "---------------------------------------" << endl;
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
bool UserFuncs::CheckCoins(){
    fstream file;
    int coins[4];
    bool returner;
    file.open("header/coins.txt", ios::in);
    if(!file){
        cout << "Error opening file where coins are stored!";
        system("PAUSE");
        exit(1);
    }
    for(int i = 0; i < 4; i++){
        file >> coins[i];
    }
    file.close();
    if(coins[0] == 0 && coins[1] == 0 && coins[2] == 0 && coins[3] == 0){
        returner = false;
    }
    else returner = true;
    return returner;
}
void UserFuncs::DisplayMissingCoins(){
    int coins[4];
    fstream file;
    file.open("header/coins.txt", ios::in);
    if(!file){
        cout << "Error opening file where coins are stored!";
        system("PAUSE");
        exit(1);
    }
    for(int i = 0; i < 4; i++){
        file >> coins[i];
    }
    file.close();
    if(coins[0] <= 3 && coins[0] != 0){
        cout << "---------------------------------------" << endl;
        cout << coins[0] << "* 0.5 KM coins left!" << endl;
        cout << "Please refill!" << endl;
        }
    else if (coins[1] <= 3 && coins[1] != 0){
        cout << "---------------------------------------" << endl;
        cout << coins[1] << "* 1 KM coins left!" << endl;
        cout << "Please refill!" << endl;
    }
    else if (coins[2] <= 3 && coins[2] != 0){
        cout << "---------------------------------------" << endl;
        cout << coins[2] << "* 2 KM coins left!" << endl;
        cout << "Please refill!" << endl;
    }
    else if (coins[3] <= 3 && coins[3] != 0){
        cout << "---------------------------------------" << endl;
        cout << coins[3] << "* 5 KM coins left!" << endl;
        cout << "Please refill!" << endl;
    } 
    if(coins[0] == 0 ){
        cout << "---------------------------------------" << endl;
        cout << "There are no 0.5 KM coins left!" << endl;
        cout << "Please refill!" << endl;
    }
    else if (coins[1] == 0){
        cout << "---------------------------------------" << endl;
        cout << "There are no 1 KM coins left!" << endl;
        cout << "Please refill!" << endl;
    }
    else if (coins[2] == 0){
        cout << "---------------------------------------" << endl;
        cout << "There are no 2 KM coins left!" << endl;
        cout << "Please refill!" << endl;
    }
    else if (coins[3] == 0){
        cout << "---------------------------------------" << endl;
        cout << "There are no 5 KM coins left!" << endl;
        cout << "Please refill!" << endl;
    }
}
void UserFuncs::DisplayMissingCoffee(){
    fstream file, file_quantity, file_coins;
    string names;
    int quantity, coins[4],g = 0;
    file.open("header/coffeeNames.txt",ios::in);
    file_quantity.open("header/coffeeQuantities.txt",ios::in);
    file_coins.open("header/coins.txt",ios::in);
    if(!file){
        cout << "Error opening file where coffee names are stored!";
        system("PAUSE");
        exit(1);
    }
    if(!file_quantity){
        cout << "Error opening file where coffee quantities are stored!";
        system("PAUSE");
        exit(1);
    }
    if(!file_coins){
        cout << "Error opening file where coins are stored!";
        system("PAUSE");
        exit(1);
    }
    for(int i = 0; i < 4; i++){
        file_coins >> coins[i];
    }
    file_coins.close();
    while(file >> names){
        file_quantity >> quantity;
        if(quantity  <= 3){
            cout << "There is only " << quantity << " cups of " << names << " left!" << endl;
            cout << "Please refill!" << endl;
            cout << "---------------------------------------" << endl;
            g++;
        }
    }
    file.close();
    file_quantity.close();
    
}
void UserFuncs::UserUI(){
    CoffeeFunctions coffee;
    bool coin = CheckCoins();
    cout << "---------------------------------------" << endl;
    cout << "Welcome dear user!" << endl;
    if(!coin){
        cout << "There are no coins in the machine!" << endl;
        cout << "Contact system administrator immediately!" << endl;
        cout << "Program will be terminated!" << endl;
        cout << "---------------------------------------" << endl;
        system("PAUSE");
        exit(1);
    }
    cout << "Choose what coffee you want to buy: " << endl;
    cout << "---------------------------------------" << endl;
    cout << "0. Weekly report " << endl;
    cout << "404. Exit" << endl;
    cout << "---------------------------------------" << endl;
    DisplayMissingCoffee();
    DisplayMissingCoins();
    coffee.UserCoffeeUI();
}
void UserFuncs::PayingUI(double money, double price2){
    double price3;
    cout << "You have entered " << money << " KM!" << endl;
    cout << "---------------------------------------" << endl;
    if(price2 > 0){
        cout << "You need to enter " << price2 << " KM more" << endl;
        cout << "---------------------------------------" << endl;
    }
    else if(price2 == 0){
        cout << "You have entered enough money!" << endl;
        cout << "---------------------------------------" << endl;
    }
    else{
        ReturnChange(price2);
    }

}
bool UserFuncs::CheckIfCoffeeisAvailable(int userChoice){
    int g = 1;
    fstream quantity;
    int quantity2;
    bool returner;
    quantity.open("header/coffeeQuantities.txt", ios::in);
    if(!quantity){
        cout << "Error opening file where coffee quantity is stored!" << endl;
        system("PAUSE");
        exit(1);
    }
    while(quantity >> quantity2){
        if(g == userChoice){
            break;
        }
        g++;
    }
    quantity.close();
    if(quantity2 > 0){
        returner = true;
    }
    else{
        returner = false;
    }
    
    return returner;
}
bool UserFuncs::CheckIfEnoughMoney(int userChoice){
    bool returner, nomoney = false;
    int coin[4],g = 1;
    fstream prices, coins;
    double money, price, price2;
    
    prices.open("header/coffeePrices.txt", ios::in);
    coins.open("header/coins.txt", ios::in);
    if(!prices){
        cout << "Error opening file where coffee prices are stored!" << endl;
        system("PAUSE");
        exit(1);
    }
    while(prices >> price){
        if(g == userChoice){
            break;
        }
        g++;
    }
    prices.close();
    for(int i = 0; i<4; i++){
        coins >> coin[i];
    }
    coins.close();
    price2 = price;
    do{
        system("CLS");
        cout << "---------------------------------------" << endl;
        cout << "Total cost of your coffee is " << price << " KM" << endl;
        cout << "---------------------------------------" << endl;
        cout << "You enter money coin by coin, for example: " << endl;
        cout << "If the coffee is 1.50 KM, you enter 1 KM, then 0.50 KM" << endl;
        cout << "Or you enter 0.5 KM and then 1 KM" << endl;
        cout << "---------------------------------------" << endl;
        cout << "If you don't have enough money enter 0 " << endl;
        cout << "---------------------------------------" << endl; 
        cout << "Enter money: ";
        cin >> money;
        if(money == 0){
            nomoney = true;
            price2 = 0;
            break;
        }
        if(money == 0.5){
            price2-=0.5;
            PayingUI(money,price2);
            nomoney = false;
            coin[0]++;
            system("PAUSE");
        }
        else if(money == 1){
            price2 -= 1;
            PayingUI(money,price2);
            nomoney = false;
            coin[1]++;
            system("PAUSE");
        }
        else if(money == 2) {
            price2 -= 2;
            PayingUI(money,price2);
            nomoney = false;
            coin[2]++;
            system("PAUSE");
        }
        else if(money == 5) {
            price2 -= 5;
            PayingUI(money,price2);
            nomoney = false;
            coin[3]++;
            system("PAUSE");
        }
        else{
            cout << "Coin not supported!" << endl;
            cout << "Please enter 0.5, 1, 2 or 5 KM" << endl;
            cout << "---------------------------------------" << endl;
            system("PAUSE");

        }
    }while(price2 > 0);
    coins.open("header/coins.txt", ios::out);
    if(!coins){
        cout << "Error opening file where coins are stored!" << endl;
        system("PAUSE");
        exit(1);
    }
    for(int i = 0; i < 4; i++){
        coins << coin[i] << endl;
    }
    coins.close();
    if(price2 <= 0 && !nomoney ) returner = true;
    else if(price2 == 0 && nomoney) returner = false;
    return returner;
}
void UserFuncs::ReturnChange(double price2){
  fstream change;
  price2 = price2 * (-1);
  int five = 0,two = 0,one = 0 ,half = 0;
  int coins[4];
  change.open("header/coins.txt", ios::in);
    if(!change){
        cout << "Error opening file where coins are stored!" << endl;
        system("PAUSE");
        exit(1);
    }
    for(int i = 0; i < 4; i++){
        change >> coins[i];
    }
    change.close();
    do{
        if(price2 >= 5 && coins[3] > 0){
            price2 -= 5;
            coins[3]--;
            five++;
        }
        else if(price2 >= 2 && coins[2] > 0){
            price2 -= 2;
            coins[2]--;
            two++;
            
        }
        else if(price2 >= 1 && coins[1] > 0){
            price2 -= 1;
            coins[1]--;
            one++;
        }
        else if(price2 >= 0.5 && coins[0] > 0){
            price2 -= 0.5;
            coins[0]--;
            half++;
        }
        else{
            cout << "Not enough change!" << endl;
            cout << "Please contact the administrator!" << endl;
            cout << "---------------------------------------" << endl;
            cout << "Your money is returned!" << endl;
            cout << "Program will be terminated now!" << endl;
            cout << "---------------------------------------" << endl;
            system("PAUSE");
            exit(1);
        }
    }while(price2 != 0);
    cout << "---------------------------------------" << endl;
    cout << "Your change is: " << endl;
    cout << "---------------------------------------" << endl;
    if(five > 0) cout << five << " x 5 KM" << endl;
    if(two > 0) cout << two << " x 2 KM" << endl;
    if(one > 0) cout << one << " x 1 KM" << endl;
    if(half > 0) cout << half << " x 0.5 KM" << endl;
    cout << "---------------------------------------" << endl;
    change.open("header/coins.txt", ios::out);
    if(!change){
        cout << "Error opening file where coins are stored!" << endl;
        system("PAUSE");
        exit(1);
    }
    for(int i = 0; i < 4; i++){
        change << coins[i] << endl;
    }
    change.close();
    
}
void UserFuncs::MakingCoffeeUI(double price, string name){
    cout << "---------------------------------------" << endl;
    cout << "Your coffee is being prepared..." << endl;
    cout << "---------------------------------------" << endl;
    cout << "Adding coffee..." << endl;
    cout << "Adding sugar..." << endl;
    cout << "Adding milk..." << endl;
    cout << "Adding love..." << endl;
    cout << "---------------------------------------" << endl;
    system("PAUSE");
    cout << "Your coffee is ready!" << endl;
    cout << "---------------------------------------" << endl;
    cout << "You have bought " << name << " for " << price << " KM" << endl;
    cout << "---------------------------------------" << endl;
    cout << "Thank you for your purchase!" << endl;
    cout << "---------------------------------------" << endl;
    cout << "Thank you for using our coffee machine!" << endl;
    cout << "---------------------------------------" << endl;
    cout << "Have a nice day! :)" << endl;
    cout << "---------------------------------------" << endl;
}
void UserFuncs::BuyCoffee(int userChoice){
    CoffeeFunctions coffee;
    fstream file, file_price, file_quantity;
    fstream temp_file, temp_fileprice, temp_filequantity;
    string name;
    double price;
    bool enoughMoney;
    int quantity;
    int g = 0;
    bool available = CheckIfCoffeeisAvailable(userChoice);
   
    if(!available){
        cout << "Coffee currently not available, please select another one!" << endl;
        cout << "Thank you for your understanding!" << endl;
        system("PAUSE");
    }
   else if(available){
        enoughMoney = CheckIfEnoughMoney(userChoice);
        if(enoughMoney){
                file.open("header/coffeeNames.txt", ios::in);
                file_price.open("header/coffeePrices.txt", ios::in);
                file_quantity.open("header/coffeeQuantities.txt", ios::in);
                temp_filequantity.open("header/tempQuantity.txt", ios::out);
                if(!file){
                    cout << "Error opening file where coffee names are stored" << endl;
                    system("PAUSE");
                    exit(1);
                }
                if(!file_price){
                    cout << "Error opening file where coffee prices are stored" << endl;
                    system("PAUSE");
                    exit(1);
                }
                if(!file_quantity){
                    cout << "Error opening file where coffee quantities are stored" << endl;
                    system("PAUSE");
                    exit(1);
                }
                if(!temp_filequantity){
                    cout << "Error opening temp file for coffee quantity" << endl;
                    system("PAUSE");
                    exit(1);
                }
            	while(file >> name){
                    file_price >> price;
                    file_quantity >> quantity;
                    if(g == userChoice-1){
                       /* if(quantity == 0){
                            cout << "Coffee currently not available, please select another one!" << endl;
                            cout << "Thank you for your understanding!" << endl;
                            quantity = 0;
                        }*/
                    
                  //  else{
                        RegisterBoughtCoffee(userChoice);
                        system("CLS");
                        MakingCoffeeUI(price, name);
                        quantity--;
                    }
                    temp_filequantity << quantity << endl;
                    g++;
                }
                
            file.close();
            file_price.close();
            file_quantity.close();
            temp_filequantity.close();
            remove("header/coffeeQuantities.txt");
            rename("header/tempQuantity.txt", "header/coffeeQuantities.txt");
        }
            if(!enoughMoney){
            cout << "You don't have enough money to buy this coffee!" << endl;
           // system("PAUSE");
           // system("CLS");
            }
            system("PAUSE");
            system("CLS");
        }
       
    }
void UserFuncs::RegisterBoughtCoffee(int userChoice){
    fstream file;
    CoffeeFunctions coffee;
    int num = coffee.CheckHowManyCoffeeTypes();
    int state[num];
    file.open("header/boughtCoffee.txt", ios::in);
    if(!file){
        cout << "Error opening file where bought coffee is stored!" << endl;
        system("PAUSE");
        exit(1);
    }
    for(int i = 0; i < num; i++){
        file >> state[i];
    }
    file.close();
    for(int i = 0; i < num; i++){
        if(i == userChoice-1) state[i]++;
    }
    file.open("header/boughtCoffee.txt", ios::out);
    for(int i = 0; i < num; i++){
        file << state[i] << endl;
    }
    file.close();
}
void UserFuncs::BeginBuying(int userChoice){
    CoffeeFunctions coffee;
    int coffeeTypes = coffee.CheckHowManyCoffeeTypes();
    if(userChoice > 0 && userChoice <= coffeeTypes) BuyCoffee(userChoice);
    else{
        system("CLS");
        cout << "Error: Invalid input!" << endl;
        system("PAUSE");
        system("CLS");
    }
}
void ProgramFuncs::WeeklyReportCount(){
    fstream file;
    file.open("header/reportCount.txt", ios::in);
    if(!file){
        cout << "Error opening file where report count is stored!" << endl;
        system("PAUSE");
        exit(1);
    }
    file >> count;
    file.close();
}
void ProgramFuncs::WeeklyReport(){
    system("CLS");
    CoffeeFunctions coffee;
    fstream file,file_price, file_quantity,file_bought, file_coin,file_count, weeklyReport;
    string name,countr;
    string wr = "weeklyReport";
    string txt = ".txt";
    double price,profit,totalprofit;
    int quantity,bought;
    int coffeeTypes = coffee.CheckHowManyCoffeeTypes();
   // int coffa[coffeeTypes];
    int g = 1;
    count++;
    file.open("header/coffeeNames.txt", ios::in);
    file_price.open("header/coffeePrices.txt", ios::in);
    file_quantity.open("header/coffeeQuantities.txt", ios::in);
    file_bought.open("header/boughtCoffee.txt", ios::in);
    file_count.open("header/reportCount.txt", ios::out);
    if(!file_count){
        cout << "Error opening file where report count is stored!" << endl;
        system("PAUSE");
        exit(1);
    }
    file_count << count;
    file_count.close();
    file_count.open("header/reportCount.txt", ios::in);
    file_count >> countr;
    file_count.close();
    string filename = wr + countr + txt;
    if(!file){
        cout << "Error opening file where coffee names are stored" << endl;
        system("PAUSE");
        exit(1);
    }
    if(!file_price){
        cout << "Error opening file where coffee prices are stored" << endl;
        system("PAUSE");
        exit(1);
    }
    if(!file_quantity){
        cout << "Error opening file where coffee quantities are stored" << endl;
        system("PAUSE");
        exit(1);
    }
    if(!file_bought){
        cout << "Error opening file where bought coffee is stored" << endl;
        system("PAUSE");
        exit(1);
    }
    weeklyReport.open(filename.c_str(), ios::out);
    if(!weeklyReport){
        cout << "Error opening file where weekly report is stored" << endl;
        system("PAUSE");
        exit(1);
    }
    weeklyReport << "***************************************" << endl;
    weeklyReport << "Weekly report " <<count << ":" << endl;
    weeklyReport << "***************************************" << endl;
    weeklyReport << "Coffee name - Price - Quantity" << endl;
    while(file >> name){
      //  coffa[g] = 0;
        file_price >> price;
        file_quantity >> quantity;
        file_bought >> bought;
        profit = price * bought;
        weeklyReport <<g<<". "<< name << " - " << price << " - " << quantity << endl;
        g++;
    }
    weeklyReport << "***************************************" << endl;
    weeklyReport << "Profit per coffee type:" << endl;
    weeklyReport << "***************************************" << endl;
    weeklyReport << "Coffee - Number of coffee sold - Profit" << endl;
    file.close();
    file_price.close();
    file_quantity.close();
    file_bought.close();
    file.open("header/coffeeNames.txt", ios::in);
    file_price.open("header/coffeePrices.txt", ios::in);
    file_quantity.open("header/coffeeQuantities.txt", ios::in);
    file_bought.open("header/boughtCoffee.txt", ios::in);
    g = 1;
    while(file >> name){
        file_price >> price;
        file_quantity >> quantity;
        file_bought >> bought;
        profit = price * bought;
        totalprofit += profit;
        weeklyReport <<g<<". "<< name <<" - "<< bought<< " - " << profit << endl;
        g++;
    }
    file.close();
    file_price.close();
    file_quantity.close();
    file_bought.close();
    
    weeklyReport << "***************************************" << endl;
    weeklyReport << "Total profit: " << totalprofit << endl;
    weeklyReport << "***************************************" << endl;
    weeklyReport << "State of coins: " << endl;
    weeklyReport << "***************************************" << endl;
    file_coin.open("header/coins.txt", ios::in);
    if(!file_coin){
        cout << "Error opening file where coins are stored!" << endl;
        system("PAUSE");
        exit(1);
    }
    int coin[4];
    for(int i = 0; i < 4; i++){
        file_coin >> coin[i];
    }
    weeklyReport << "0.5 KM: " << coin[0] << endl;
    weeklyReport << "1 KM: " << coin[1] << endl;
    weeklyReport << "2 KM: " << coin[2] << endl;
    weeklyReport << "5 KM: " << coin[3] << endl;
    weeklyReport << "***************************************" << endl;
    file_coin.close();
    weeklyReport.close();
    file_bought.open("header/boughtCoffee.txt", ios::out);
    for(int i = 0; i < coffeeTypes; i++){
        file_bought << 0 << endl;
    }
    file_bought.close();
    cout << "---------------------------------------" << endl;
    cout << "Weekly report is generated!" << endl;
    cout << "Filename: " << filename << endl;
    cout << "Profit and count of sold coffee is reseted!" << endl;
    cout << "You will be redirected to the main menu!" << endl;
    cout << "---------------------------------------" << endl;
    system("PAUSE");
    system("CLS");
}
void ProgramFuncs::UserMode(){
    UserFuncs user;
    CoffeeFunctions coffee;
    int userChoice;
    int coffeeTypes = coffee.CheckHowManyCoffeeTypes();
    do{
        system("CLS");
        user.UserUI();
        cout << "Select coffee: ";
        cin >> userChoice;
        switch(userChoice){
            case 0:
                WeeklyReport();
                //user.WeeklyReport();
                break;
            case 404:
                system("CLS");
                cout << "You will be redirected to the main menu!" << endl;
                system("PAUSE");
                break;
            default:
                system("CLS");
                user.BeginBuying(userChoice);
                break;
        }
    }while(userChoice != 404);
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
    WeeklyReportCount();
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
                prog.WeeklyReport();
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
    char answy;
    do{
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
        cout << "Do you want to add more coins? (y/n)? " << endl;
        cout << "----------------------------------------" << endl;
        cout << "Your choice: ";
        cin >> answy;
    }while(answy == 'y' || answy == 'Y');
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
        cout << "How many coins do you want to remove: ";
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
        cout << "Do you want to remove more coins? (y/n)?" << endl;
        cout << "----------------------------------------" << endl;
        cout << "Your choice: ";
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