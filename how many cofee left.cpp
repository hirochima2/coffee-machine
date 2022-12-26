#include<iostream>
#include <stdlib.h>
#include <string.h>
#include <iomanip>
//#include <fstream>
using namespace std;

struct softdrink{
char  name[20];
float price;
unsigned quantity;
};


int main()
{
softdrink drink[5];

strcpy(drink[0].name,"esprsso");drink[0].quantity=20;
strcpy(drink[1].name,"machiato"); drink[1].quantity=20;
strcpy(drink[2].name,"cappuchino");drink[2].quantity=20;
strcpy(drink[3].name,"latte"); drink[3].quantity=20;
strcpy(drink[4].name,"mocchachino"); drink[4].quantity=20;

std::cout << std::fixed;
std::cout << std::setprecision(4);
  
int choice = 1;

while(choice != 6){
cout<<"\n 1) "<<drink[0].name<<"\t("<<drink[0].quantity<<") remaining";
cout<<"\n 2) "<<drink[1].name<<"\t("<<drink[1].quantity<<") remaining";
cout<<"\n 3) "<<drink[2].name<<"\t("<<drink[2].quantity<<") remaining";
cout<<"\n 4) "<<drink[3].name<<"\t("<<drink[3].quantity<<") remaining";
cout<<"\n 5) "<<drink[4].name<<"\t("<<drink[4].quantity<<") remaining";
cout<<"\n 6) Leave the drink machine \n\n";
cout<<"\n Choose one:";
cin>>choice;

if(choice >=1 && choice <=5)
{
    if(drink[choice-1].quantity == 0)
    {
        cout<<"\n No more " << drink[choice-1].name <<" Available ..";
        getchar(); getchar();continue;
    }
}


drink[choice-1].quantity = drink[choice-1].quantity - 1;

cout<<"\n There are "<< drink[choice-1].quantity <<" drinks of that type left";
//ofstream myfile;
 // myfile.open ("brojkafa.txt");
 // myfile << " 1) esprsso     (20) remaining
// 2) machiato    (20) remaining
 //3) cappuchino  (20) remaining
 //4) latte       (20) remaining
 //5) mocchachino (20) remaining
 //6) Leave the drink machine
//";
  //myfile.close();
getchar();
getchar();

}


return 0;
}
