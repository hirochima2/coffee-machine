#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <conio.h>

// Path: header\library.h
// Compare this snippet from main.cpp:
// #include "header/library.h"

class PasswordFunctions{
    private:
        std::string password;
    public:
        std::string getPassword(); // neka vrsta pointera ne znam radili smo na faksu
        bool CheckPassword(std::string); // Ova funkcija provjerava da li je unesena sifra tacna
        bool CheckIfFirstPassword(); //  Provjerava da li je prvi put da se kuca sifra tako sto gleda da li je fajl prazan ili ne
        bool CheckForgottenPassword(std::string); // Ova funkcija gleda da li je unesen tacan odgovor na "Sigurnosno pitanje"
        bool CheckBackupPassIsEmpty(); // Provjerava da li postoji odgovor na hajmo reci "Sigurnosno pitanje"
        void setBackupPassword(std::string); // Ako nema odgovora na sigurnosno pitanje, onda se pomocu ove funkcije postavlja odgovor na sigurnosno pitanje
        void setFirstPassword(std::string); // Ako je prvi put da se ulazi u program, onda se pomocu ove funkcije postavlja prva sifra
        void setForgottenPassword(std::string); // Ako se zaboravi sifra, onda se pomocu ove funkcije postavlja nova sifra a stara se brise
        void setPassword(std::string); // ovo smo radili na faksu
};

class CoffeeFunctions{
    public:
    void AddCoffeeName(std::string); // Dodaje ime kafe u fajl
    void AddCoffeePrice(double); // Dodaje cijenu kafe u fajl
    void AddCoffeeQuantity(int); // Dodaje kolicinu kafe u fajl
    void AddBoughtCoffee();
    void ChangeCoffeeName(); // Mijenja ime kafe
    void ChangeCoffeePrice(); // Mijenja cijenu kafe
    void ChangeCoffeeQuantity(); // Mijenja kolicinu kafe
    void CoffeeUI();
    void UserCoffeeUI();
    void SetTypesOfCoffee(); // Postavlja podatke o kafama
    void RemoveTypesOfCoffee(); // Brise podatke o kafama
    int SizeOfTypesOfCoffee(); // Vraca broj vrsta kafe
    bool CheckIfCoffeeNameExists(std::string); // Provjerava da li kafa postoji
    int CheckHowManyCoffeeTypes(); // Provjerava koliko vrsta kafe ima

};
class ProgramFuncs{
    public:
    void BeginProgram();
    void AdminMode();
    void UserMode();
    void MainMenUI();
    void ExitProgram();
    void WrongInput();
    void StartProgram();
    void WeeklyReport();
    void WeeklyReportCount();
};
class AdminFuncs{
    public: 
    void ChangePass(std::string, PasswordFunctions);
    void NoBackupPass();
    void FirstPassword(std::string);
    void Operations();
    void AdminUI();
    void ManipulateCoinState();
    void AddCoins(int[]);
    void RemoveCoins(int[]);
    void CoinUI(int[]);
};
class UserFuncs{
    public:
    void UserUI();
    void BuyCoffee(int);
    void BeginBuying(int);
    bool CheckIfEnoughMoney(int);
    void PayingUI(double, double);
    bool CheckIfCoffeeisAvailable(int);
    void ReturnChange(double);
    bool CheckCoins();
    void MakingCoffeeUI(double, std::string);
    void DisplayMissingCoffee();
    void DisplayMissingCoins();
    void RegisterBoughtCoffee(int);
};