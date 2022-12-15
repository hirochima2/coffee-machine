#include "biblioteka.h"

void Biblioteka::print()
{
    cout << "Hi from Biblioteka::print()" << endl;
}
int Biblioteka::print3()
{
    return 3;
}
void print2()
{
    cout << "Hi from print2()" << endl;
}
int print6()
{
    return 6;
}

void sve(){
    Biblioteka b;
    b.print();
    cout << "Ovo je print3: " << b.print3() << endl;
    print2();
    cout << "Ovo je print6: " << print6() << endl;
    getch();
}