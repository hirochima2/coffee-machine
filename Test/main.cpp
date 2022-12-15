#include "header/biblioteka.h"
#include <conio.h>
int main(){
    Biblioteka b;
    b.print();
    cout << "Ovo je print3 iz maina: " << b.print3() << endl;
    print2();
    cout << "Ovo je print6 iz maina: " << print6() << endl;
    cout << "--------------------------------------------" << endl;
    sve();
    cout <<"Ovo je printano iz biblioteka.cpp"<< endl;
    getch();
    return 0;
}