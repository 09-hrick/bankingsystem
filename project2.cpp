#include<iostream>
#include<algorithm>
#include<bits/stdc++.h>
#include<fstream>
using namespace std;
enum TypeOfAccount{savings,current,joint};


//employee class declaration
class Employee{
    private:
        string _employeeName_; 
        double _employeeId_;
        string _employeePas_;
    public:
    Employee(string en,string eid,string ep){
        _employeeName_=en;
        _employeeId_=stod(eid);
        _employeePas_=ep;
    }
};

//Transaction log class declaration
class Tansationlog{
    private:
        double _AccountToBelogged_; 
        double _CreditedOrDebtedAccount_;
        double _AmountTransfered_;
        bool _CreditedOrDebted_;
    public:
    Tansationlog(string AccountToBelogged, string CreditedOrDebtedAccount, string AmountTransfered, string CreditedOrDebted)= {
        _CreditedOrDebtedAccount_= ;
        _AmountTransfered_= ;
        _CreditedOrDebted_= ;
    }
    
};


//account information class declaration
class Accounts
{
private:
  double account_number;
  int atm_pin;
  string accountHolderName;
  double amount;
  TypeOfAccount account_type;
public:

};


//function to split string and returing it in vector
vector<string> split(string str, char delimiter) { 
  vector<string> internal; 
  stringstream ss(str); // Turn the string into a stream. 
  string tok; 
 
  while(getline(ss, tok, delimiter)) { 
    internal.push_back(tok); 
  } 
 
  return internal; 
} 

//taking input from file buffer to be given vector
void openfileAndinputdatainVector(fstream &finout,string filename){
    string temp;
    finout.open(filename,ios::ate|ios::in|ios::out);
    finout.seekg(0,ios::beg);
    //skipping the first line of the read file
    getline(finout,temp );

    //getting data from the file till the end of file and storing it in a vector of class books
    while( !finout.eof() ) {
        getline(finout,temp);
        vector<string> sep = split(temp, ','); 
        //fuction to enter the values from file to the object
        //f(vector<obj>)
    }
}
//fuction for taking a vector and storing it in a object
template<class T> 
void appendToObject(vector<T> &vectorOfObj,vector<string>VectorStrData){
 typeof(vectorOfObj[0]) tempobj;


}


int main()
{	
    //declaration
    fstream inoutfile;
    vector <Accounts> accounts;
    vector <Tansationlog> tansationlog;
    vector <Employee> employee; 
 
    bool exit;
    do
    {

    



    cout<<"Do you want to continue Browsing the bank press 0 for yes and 1 for No: ";
    cin>>exit;
    } while (!exit);
    


    
    return 0;
}