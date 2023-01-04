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
struct TypesOfCoffee{
    std::string name;
    double price;
    int quantity;
    int id;
};

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
   /* void RemoveCoffeeName(std::string); // Brise ime kafe iz fajla
    void RemoveCoffeePrice(std::string); // Brise cijenu kafe iz fajla
    void RemoveCoffeeQuantity(std::string); // Brise kolicinu kafe iz fajla */
    void ChangeCoffeeName(); // Mijenja ime kafe
    void ChangeCoffeePrice(); // Mijenja cijenu kafe
    void ChangeCoffeeQuantity(); // Mijenja kolicinu kafe
    void CoffeeUI();
    void SetTypesOfCoffee(TypesOfCoffee[]); // Postavlja podatke o kafama
    void RemoveTypesOfCoffee(TypesOfCoffee[]); // Brise podatke o kafama
    int SizeOfTypesOfCoffee(); // Vraca broj vrsta kafe
    bool CheckIfCoffeeNameExists(std::string); // Provjerava da li kafa postoji

};
class ProgramFuncs{
    public:
    void BeginProgram(); // Ova funkcija se poziva na pocetku programa i ona provjerava da li je prvi put da se ulazi u program
    void AdminMode();
    
};
class AdminFuncs{
    public: 
    void ChangePass(std::string, PasswordFunctions);
    void NoBackupPass();
    void FirstPassword(std::string);
    void Operations(TypesOfCoffee[]);
    // create a function that uses int as parameter and returns int
    void AdminUI();
};