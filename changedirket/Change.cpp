#include <fstream>
#include <iostream>

using namespace std;

class ChangeCalculator 
{
private:
    double due;
    double rec;
    double recc;
    double change;
    double sve;
    int petak;
    int dvicak;
    int marka;
    int polco;
    int dvaes;
    int des;
    

public:
    ChangeCalculator(const std::string& input_file)
	 {
	 	
      	double due=1.0, rec=2.0, recc=0;
        // Calculate the change
        change = (rec - due);
        //modifies change in file
	    ifstream input("input.txt");
	    int num;
	    input >> num;
	    input.close();
	    
		if (change>num)
	    {
	    	cout<<"We are sorry we cannot give you your change"<<endl;
		}
	    
	    while(1)
	    {
	    if(change>=0)
		{
			break;
		}
	    if (change<0)
	    {
	    	cout<<"You have to add more money"<<endl;
	    	cin>>recc;
		}
		rec=recc+rec;
		change = (rec - due);
	
	}
        cout << "Your change is: " << change <<" KM"<< " \n";

        petak = change / 5.00;
        change = change - petak;

        dvicak = change / 2.00;
        change = change - dvicak;

        marka = change / 1.00;
        change = change - marka;

        polco = change / .50;
        change = change - polco;

        dvaes = change / .20;
        change = change - dvaes;

        des = change / .10;
        change = change - des;
     
	    num=num-change;
	   	
		ofstream output("input.txt");
	    output << num << endl;
	    output.close();
	    }

    void printChange() 
	{
        if (petak > 0)
            std::cout << "5KM: " << petak << " \n";
        if (dvicak > 0)
            std::cout << "2KM: " << dvicak << " \n";
        if (marka > 0)
            std::cout << "1KM: " << marka << " \n";
        if (polco > 0)
            std::cout << "50KF: " << polco << " \n";
        if (dvaes > 0)
            std::cout << "20KF: " << dvaes << " \n";
        if (des > 0)
            std::cout << "10KF: " << des << " \n";
    }
};

int main() 
{
    ChangeCalculator cc("input.txt");
    cc.printChange();
    return 0;
}
