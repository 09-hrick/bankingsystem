#include<iostream>
#include<algorithm>
#include<bits/stdc++.h>
#include<fstream>
#include<string>
#include <stdexcept>
using namespace std;



//employee class declaration
class Employee{
    private:
        string _employeeName_; 
        double _employeeId_;
        string _employeePas_;
    public:
    Employee(){}
    Employee(string en,double eid,string ep){
        _employeeName_=en;
        _employeeId_=eid;
        _employeePas_=ep;
    }
    void display(){
        cout<<"hello\n";
        cout<<_employeeName_<<endl;
    }
    bool loginemp(double empId,string emppin){
        return (_employeeId_==empId && _employeePas_==emppin);
    }
   
};

//Transaction log class declaration

class Transationlog{
    private:
        double _AccountToBelogged_; 
        double _CreditedOrDebtedAccount_;
        double _AmountTransfered_;
        string _CreditedOrDebted_;
    public:
    Transationlog(){}
    Transationlog(double AccountToBelogged, double CreditedOrDebtedAccount, double AmountTransfered, string CreditedOrDebted){
        _AccountToBelogged_ = AccountToBelogged; 
        _CreditedOrDebtedAccount_= CreditedOrDebtedAccount;
        _AmountTransfered_= AmountTransfered;
        _CreditedOrDebted_= CreditedOrDebted;
    }
   
};


map<int,string>AccountType={{1,"savings"},{2,"current"},{3,"joint"}};
//account information class declaration
class Accounts
{
private:
    
    double _account_number_;
    int _atm_pin_;
    string _accountHolderName_;
    double _amount_;
    string _account_type_;
public:
    Accounts(){
    }
    Accounts(double  account_number, int    atm_pin,string accountHolderName,double amount,string  account_type){

        _account_number_ = account_number;
        _atm_pin_ = atm_pin;
        _accountHolderName_ = accountHolderName;
        _amount_ = amount;
        _account_type_ = AccountType[stoi(account_type)];
  }
  double getaccnum(){
    return _account_number_;
  }
  bool loginacc(double anum,int apin){
        return(_account_number_==anum && _atm_pin_==apin);
    }

};


//function to split string and returing it in vector
vector<string> getsplitvector(fstream &file) { 
    string str;
    getline(file,str);
    char delimiter=',';
    vector<string> internal; 
    stringstream ss(str); // Turn the string into a stream. 
    string tok; 
 
  while(getline(ss, tok, delimiter)) { 
    internal.push_back(tok); 
  } 
 
  return internal; 
} 




class Bank :private Accounts,private Transationlog,private Employee
{
private:
    Accounts cust;
    Employee emp;

public:
    vector <Accounts> accountsvector;
    vector <Transationlog> transationlogsvector;
    vector <Employee> employeesvector;
    int current_user;
    /* zero customer one employee*/
    Bank(){
        fstream finout;
        vector<string> sepa;
        finout.open("accounts.csv",ios::ate|ios::in|ios::out);
        finout.seekg(0,ios::beg);
        //skipping the first line of the read file
        sepa=getsplitvector(finout);
        //getting data from the file till the end of file and storing it in a vector of class books
        while( !finout.eof() ) {
            sepa=getsplitvector(finout);
            //double  account_number, int    atm_pin,string accountHolderName,double amount,string  account_type)
            Accounts tempacc(stod(sepa[0]),stoi(sepa[1]),sepa[2],stod(sepa[3]),sepa[4]);
            accountsvector.push_back(tempacc);
        } finout.close();

        vector<string> tsep;
        finout.open("translog.csv",ios::ate|ios::in|ios::out);
        finout.seekg(0,ios::beg);
        //skipping the first line of the read file
        tsep=getsplitvector(finout);
        //getting data from the file till the end of file and storing it in a vector of class books
        while( !finout.eof() ) {
            tsep=getsplitvector(finout);
            //double AccountToBelogged, double CreditedOrDebtedAccount, double AmountTransfered, string CreditedOrDebted
            Transationlog temptrans(stod(tsep[0]),stod(tsep[1]),stod(tsep[2]),tsep[3]);
            transationlogsvector.push_back(temptrans);
        }
        finout.close();

        vector<string> esep;
        finout.open("employee.csv",ios::ate|ios::in|ios::out);
        finout.seekg(0,ios::beg);
        //skipping the first line of the read file
        esep=getsplitvector(finout);
        //getting data from the file till the end of file and storing it in a vector of class books
        while( !finout.eof() ) {
            esep=getsplitvector(finout);
            //string en,double eid,string ep
            Employee tempemp(esep[0],stod(esep[1]),esep[2]);
            employeesvector.push_back(tempemp);
        } finout.close();

        }

    void loginportal(){
    int chooseportal;
    cout<<"To enter Customer login portal press '0'"<<"\nTo enter Employee login Portal press '1'\n";
    cin>>chooseportal;
    while((chooseportal!=0||chooseportal!=1) )
    {
    if (chooseportal== 0)
    {
            double anum;int apin;
            cout<<"Entering Customer login portal\n";
            cout<<"Are you a existing customer?\npress y for yes or any other key for no: ";
            if(getchar()=='y' || getchar()=='Y')
            {
                cout<<"Please enter account number: ";
                cin>>anum;
                cout<<"Please enter atm pin: ";
                cin>>apin;
                for(auto i:accountsvector)
                {
                        if(i.loginacc(anum,apin)){
                        cust=i;
                        cout<<"login sucessful\n";

                        }
                }
                cout<<"incorrect Atm pin or Account number\n"<<
                "Do you still want to continue? \n"<<
                "Press y to continue or any other key to exit the login portal: ";
                if(getchar()=='y' || getchar()=='Y'){
                    loginportal();
                }
                else{cout<<"paatanhi kya hogya";}
            }
        else{
            
            double tempAccNum;
            int tempPin;
            string tempAccountHolderName;
            double tempAmount=0;
            string tempaccount_type;
            cout<<"Welcome New customer\n";
            tempAccNum=accountsvector.back().getaccnum()+1;
            cout<<"Your account number is: "<< tempAccNum<<endl ;
            cout<<"Please enter account holder name: ";
            cin>>tempAccountHolderName;
            cout<<"Please enter 4 digit atm pin: ";
            cin>>tempPin;
            cout<<"1, for savings , 2 for current , 3 for joint\n";
            cout<<"Please enter account type: ";
            cin>>tempaccount_type;
            cout<<"Enter the amount you want to deposit";
            cin>>tempAmount;
            Accounts tempaccount(tempAccNum,tempPin,tempAccountHolderName,tempAmount,tempaccount_type);
            cout<<"Account created sucessfully";
            accountsvector.push_back(tempaccount);  

        }
        break;
    }
    else if(chooseportal== 1){
        cout<<"Entering Employee login Portal\n";
        double empid;
        string emppass;
        cout<<"Please enter employee ID: ";
        cin>>empid;
        cout<<"Please enter password: ";
        cin>>emppass;

        // this->employeesvector[0].display();
        for(auto i:employeesvector)
        {
                if(i.loginemp(empid,emppass)){
                    emp=i;
                cout<<"login sucessful\n";
                employeesvector.back();

                }else{
                     cout<<"Incorrect password or Account number\n"
                    <<"Do you still want to continue? \n"<<
                    "Press y to continue or any other key to exit the login portal: ";
                    if(getchar()=='y' || getchar()=='Y'){
                        loginportal();
                     }
                }
        }
       


        break;
    }
    
    else{
       cout<<"Please enter a valid expression\n";
       cout<<"To enter Customer login portal press '0'"<<"\nTo enter Employee login Portal press '1'\n";
       cin>>chooseportal;
    }
    }
    current_user = chooseportal;
    
    }
    Accounts getAccount(){
        return cust;
    }
    Employee getemployee(){
        return emp;
    }
    

    void getcurrentuser(){
    if(current_user==1)
    {
        getAccount();

    }
    else
    {
       getemployee();
    }
    }

};


int main()
{
    //declaration
    Bank myBank;

    bool exit;
    //driver code
    do
    {
    cout<<'\n'<<string(20,'>')
    <<string(20,'<')<<"\n"
    <<">>"<<"        Welcome to Our Bank         "
    <<"<<"<<"\n"<<string(20,'>')
    <<string(20,'<')<<endl;
    myBank.loginportal();


    cout<<"Do you want to continue Browsing the bank press 0 for yes and 1 for No: ";
    cin>>exit;
    } while (!exit);
   

    return 0;
}
