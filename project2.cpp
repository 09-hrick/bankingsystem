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
        cout<<"Hello\n";
        cout<<_employeeName_<<endl;
    }
    bool loginemp(double empId,string emppin){
        return (_employeeId_==empId && _employeePas_==emppin);
    }
    ostringstream delEmployee(){
        ostringstream f;
        f<<"\n"<<_employeeName_<<','<< _employeeId_<<","<< _employeePas_;
        return f;

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
    ostringstream giveTlog(){
            ostringstream oss;
            //AccountToBelogged, CreditedOrDebtedAccount, AmountTransfered, CreditedOrDebted
            oss<<'\n'<<_AccountToBelogged_<<','<<_CreditedOrDebtedAccount_<<','<<_AmountTransfered_<<','<<_CreditedOrDebted_;
            return oss;
    }
   
};


map<string,string>AccountType={{"1","savings"},{"2","current"},{"3","joint"}};

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
   Accounts(int tempAccNum){
           
            cout<<"Welcome New customer\n";
            cout<<"Your account number is: "<< tempAccNum<<endl ;
            _account_number_=tempAccNum;
            cout<<"Please enter account holder name: ";
            cin>>_accountHolderName_;
            cout<<"Please enter 4 digit atm pin: ";
            cin>>_atm_pin_;
            cout<<"1, for savings , 2 for current , 3 for joint\n";
            cout<<"Please enter account type: ";
            string temp;
            cin>>temp;
            _account_type_=AccountType[temp];
            cout<<"Enter the amount you want to deposit: ";
            cin>>_amount_;

    }
    Accounts(double account_number, int atm_pin,string accountHolderName,double amount,string  account_type)
    {

        _account_number_ = account_number;
        _atm_pin_ = atm_pin;
        _accountHolderName_ = accountHolderName;
        _amount_ = amount;
        _account_type_ = account_type;
    }
    double whatismybalance(){
        return _amount_;
    }
    
    bool operator==(Accounts const &obj){
        return( (this->_account_number_==obj._account_number_ )&&(this->_account_type_==obj._account_type_)&&(this->_accountHolderName_==obj._accountHolderName_)&&(this->_amount_==obj._amount_)&&(this->_atm_pin_ == obj._atm_pin_ ) );
    }
    void operator+(Accounts const &obj){
        this->_amount_+obj._amount_;
    }
    void operator+(double const &obj){
        this->_amount_+obj;
    }

    void operator-(Accounts const &obj){
        this->_amount_-obj._amount_;
    }
    void operator-(double const &obj){
        this->_amount_-obj;
    }


    ostringstream delAccounts(){
        ostringstream os;
        //account_number, atm_pin, accountHolderName, amount, account_type(savings,current,joint)
       
        os<<"\n"<<_account_number_<<','<<_atm_pin_<<','<<_accountHolderName_<<','<<_amount_<<','<<_account_type_;
        return os;

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
    // char delimiter=',';
    vector<string> internal; 
    stringstream ss(str); // Turn the string into a stream. 
    string tok; 
 
  while(getline(ss, tok, ',')) { 
    internal.push_back(tok); 
  } 
 
  return internal; 
} 




class Bank :private Accounts,private Transationlog,private Employee
{
private:
    Accounts cust;
    Employee emp;
    void logincust(){
         double anum;int apin;
            cout<<"Entering Customer login portal\n";
            cout<<"Are you a existing customer?\npress y for yes or any other key for no: ";
            char getchary;
            cin>>getchary;

            if(getchary=='y' || getchary=='Y')
            {
                cout<<"Please enter account number: ";
                cin>>anum;
                cout<<"Please enter atm pin: ";
                cin>>apin;
                for(auto &i:accountsvector)
                {
                        if(i.loginacc(anum,apin)){
                        cust=i;
                        cout<<"login sucessful\n";

                        }
                        else
                        {
                            cout<<"incorrect Atm pin or Account number\n";

                        }
                }
                
            }
        else{
            int tempAccNum=accountsvector.back().getaccnum()+1;
            //Accounts(double account_number, int atm_pin,string accountHolderName,double amount,string  account_type)
            Accounts tempaccount=Accounts(tempAccNum);
            cout<<"Account created sucessfully\n";
            accountsvector.push_back(tempaccount);

        }

    }
    void loginemp(){
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
                }else{
                     cout<<"Incorrect password or employee ID\n";
                }
        }
       

    }

public:
    vector <Accounts> accountsvector;
    vector <Transationlog> transationlogsvector;
    vector <Employee> employeesvector;
    int current_user;
    /* zero customer one employee*/

    double whatsmyaccountnum(){
        return cust.getaccnum();
    }
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
    
    


   
    ~Bank(){

        fstream finout;
        vector<string> sepa;
        finout.open("accounts.csv",ios::out);
        finout.seekg(0,ios::beg);
        finout<<"account_number, atm_pin, accountHolderName, amount, account_type(savings,current,joint)";
        for(auto i:accountsvector){
            finout<<i.delAccounts().str();
        }
        finout.close();

        finout.open("employee.csv",ios::out);
        finout.seekg(0,ios::beg);
        finout<<"employeeName, employeeId, employeePas";
        for(auto i:employeesvector){
            finout<<i.delEmployee().str();
        }
        finout.close();

        //putting back the transation log back in translog.csv
        finout.open("translog.csv",ios::out);
        finout.seekg(0,ios::beg);
        finout<<"AccountToBelogged, CreditedOrDebtedAccount, AmountTransfered, CreditedOrDebted";
        for(auto i:transationlogsvector){
            finout<<i.giveTlog().str();
        }
        finout.close();


    }


    void withdrawl(){
                double money;
                int temppin;
                cout<<"Enter account pin: ";
                cin>>temppin;
                if(cust.loginacc(cust.getaccnum(),temppin)){
                    int money;
                    cout<<"How much money do you want to withdraw?\n";
                    cin>>money;
                    cust-money;
                    Transationlog T(cust.getaccnum(),cust.getaccnum(),money,"Debted");
                    logTransation(T);
                }else{
                    cout<<"Wrong pin\n";
                }
            
    }
    void depositfrom(){
        int money;
        int apin1;
        double anum1;
        double anum2;
        cout<<"Enter Account number: ";
        cin>>anum1;
        cout<<"Enter account pin: ";
        cin>>apin1;

        cout<<"Enter the account number you want to deposit to ";
        cin>>anum2;

        
            for(auto &i:accountsvector)
            {
                if(i.loginacc(anum1,apin1)){
                 
                    for(auto &j:accountsvector){
                       if(!(j.getaccnum()==anum2)){
                        cout<<"Sorry the account doesnot exist";
                       }
                       else{
                            j+money;
                            Transationlog T1(anum1,anum2,money,"Credited");
                            Transationlog T2(anum2,anum1,money,"Debted");
                            logTransation(T1);
                            logTransation(T2);
                       } 
                    }
                }
                else
                {
                    cout<<"incorrect Atm pin or Account number\n";

                }
            }
        
        // if(cust.loginacc(accountnum,temppin)){
        //     int money;
        //     cout<<"How much money do you want to withdraw?\n";
        //     cin>>money;
        //     cust-money;
        //     Transationlog T(cust.getaccnum(),cust.getaccnum(),money,"credited");
        //     logTransation(T);
        // }else{
        //     cout<<"Wrong pin\n";
        // }
    }



    void logTransation(Transationlog t){
        transationlogsvector.push_back(t);
    }

    void loginportal(){
    int chooseportal;
    cout<<"To enter Customer login portal press '0'"<<"\nTo enter Employee login Portal press '1'\n";
    cin>>chooseportal;
    current_user = chooseportal;
    while((chooseportal!=0||chooseportal!=1) )
    {
    if (chooseportal== 0)
    { 
        logincust();
        break;
    }
    else if(chooseportal== 1){
        loginemp();
        break;
    }
    
    else{
       cout<<"Please enter a valid expression\n";
       cout<<"To enter Customer login portal press '0'"<<"\nTo enter Employee login Portal press '1'\n";
       cin>>chooseportal;
    }
    }
    

    
    }
    Accounts getAccount(){
        return cust;
    }
    Employee getemployee(){
        return emp;
    }
    void deleteMyCustomer(){
        //cust
        cout<<"Are you sure you want to delete your account\n";
        char c;
        
       
            cout<<"Press 'y' and hit enter to confirm";
            cin>>c;
            if(c=='y'||c=='Y'){
                cout<<"Account deleted successfully\n";

                vector<int>::iterator index;
                for(vector<Accounts>::iterator i=accountsvector.begin(); i != accountsvector.end(); i++){
                   if(cust==*i){
                    accountsvector.erase(i);
                   }
                }
            }
            else{
                cout<<"Account termination obstructed\n";
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

    if(myBank.current_user==0){
    //customer operations
    cout<<"To display balance press 'b'\nTo withdraw money from the account press 'w'\nTo send money from one acconunt to another 'c'\nTo change pin 'p'\ndelete account 'd' ";
    char customeroperation;
        cin>>customeroperation;
        if(customeroperation=='b'|| customeroperation=='B'){
            cout<<"Your current balance is: "<<myBank.getAccount().whatismybalance()<<endl;
        }
        else if(customeroperation=='w'|| customeroperation=='W'){
           myBank.withdrawl();

        }
        else if(customeroperation=='c'|| customeroperation=='C'){
            myBank.depositfrom();
        }
        else if(customeroperation=='d' || customeroperation =='B'){
            myBank.deleteMyCustomer();
            cout<<"Thanks for choosing our services\n";
            break;
        }else{continue;}
        
    }
    
    
    
    else{
        //employee operations

    }

    cout<<"Do you want to continue Browsing the bank press 0 for yes and 1 for No: ";
    cin>>exit;
    } while (!exit);



   

    return 0;
}
