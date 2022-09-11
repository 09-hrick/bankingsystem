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
    stringstream giveTlog(){
            stringstream oss;
            //AccountToBelogged, CreditedOrDebtedAccount, AmountTransfered, CreditedOrDebted
            oss<<'\n'<<_AccountToBelogged_<<','<<_CreditedOrDebtedAccount_<<','<<_AmountTransfered_<<','<<_CreditedOrDebted_;
            return oss;
    }
    double getloggedAccount(){
        return this->_AccountToBelogged_;
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
    void display(){
        cout<<this->_accountHolderName_;
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
        // const double &i=_amount_;
        return _amount_;
    }
    
    bool operator==(Accounts const &obj){
        return( (this->_account_number_==obj._account_number_ )&&(this->_account_type_==obj._account_type_)&&(this->_accountHolderName_==obj._accountHolderName_)&&(this->_amount_==obj._amount_)&&(this->_atm_pin_ == obj._atm_pin_ ) );
    }
    void operator+(Accounts const &obj){
        this->_amount_+=obj._amount_;
    }
    void operator+(double const &obj){
        this->_amount_+=obj;
    }

    void operator-(Accounts const &obj){
        this->_amount_-=obj._amount_;
    }
    void operator-(int const &obj){
        this->_amount_-=obj;
    }
    void Setpin(int apin1,int apin2){
        if(this->_atm_pin_==apin1){
            this->_atm_pin_=apin2;
        }

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

    Accounts _getaccount(double anum)
    {  
        Accounts a;
        for(auto &i:accountsvector){
            if(i.getaccnum()==anum){
                return i;
            }
            else{continue;}
        }cout<<"Account not Found\n";
        return a;


    }
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
                        return;
                        }
                        
                }cout<<"incorrect Atm pin or Account number\n";
                logincust();
                
                
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
                    cout<<"Welcome customer ";
                    cust.display();
                    return;
                }
        }cout<<"Incorrect password or employee ID\n";
        loginemp();
       

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

    void showbalance(){
        cout<<"Your current balance is: "<<cust.whatismybalance()<<endl;
    }

    void display_tlog(){
    double anum=cust.getaccnum();
    string ret_words[4];
    string buf;
    int x = 2; 
    stringstream ss;

    Accounts aacount = _getaccount(anum);
        for(auto &i:transationlogsvector){
            if(aacount.getaccnum()==i.getloggedAccount()){
               ss=i.giveTlog();
               ss>>ret_words[0];
               ss>>ret_words[1];
               ss>>ret_words[2];
               ss>>ret_words[3];
               //AccountToBelogged, CreditedOrDebtedAccount, AmountTransfered, CreditedOrDebted
               cout<<ret_words[2]<<" has been "<<ret_words[3]<<" from/to your account";

            }
        }

    }
    void display_tlog(double anum){
    string ret_words[4];
    string buf;
    int x = 2; 
    stringstream ss;

    Accounts aacount = _getaccount(anum);
        for(auto &i:transationlogsvector){
            if(aacount.getaccnum()==i.getloggedAccount()){
               ss=i.giveTlog();
               ss>>ret_words[0];
               ss>>ret_words[1];
               ss>>ret_words[2];
               ss>>ret_words[3];
               //AccountToBelogged, CreditedOrDebtedAccount, AmountTransfered, CreditedOrDebted
               cout<<ret_words[2]<<" has been "<<ret_words[3]<<" from/to your account";

            }
        }


       
        
        
    }
    void withdrawl(){
                int money;
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
                    for(auto &i:accountsvector){
                        if(i.loginacc(cust.getaccnum(),temppin)){
                            i-money;
                        }
                    }
                }  
                else{
                    cout<<"Wrong pin\n";
                }
            
    }

    void depositfrom(){
        int money;
        int temppin;
        cout<<"Enter account pin: ";
        cin>>temppin;
        if(cust.loginacc(cust.getaccnum(),temppin)){
            int money;
            double anum;
            cout<<"How much money do you want to deposit?\n";
            cin>>money;
            cust-money;
            cout<<"Please enter the account number you want to deposit the money to: ";
            cin>>anum;
            
            
            for(auto &i:accountsvector){
                if(i.loginacc(cust.getaccnum(),temppin)){
                    i-money;
                    Transationlog T(cust.getaccnum(),cust.getaccnum(),money,"Debted");
                    logTransation(T);
                }
                else{continue;}
            }

            for(auto &i:accountsvector){
                if(i==_getaccount(anum)){
                    i+money;
                    Transationlog T(anum,cust.getaccnum(),money,"Credited");
                    logTransation(T);
                }else{continue;}
            }return;
               
        }  
        else{
            cout<<"Wrong pin\n";
        }
    }
    void changePin(){
        int temppin;
        cout<<"Enter Your current account pin: ";
        cin>>temppin;
        if(cust.loginacc(cust.getaccnum(),temppin)){
            int newpin;
            cout<<"Please enter new pin number: ";
            cust.Setpin(temppin,newpin);
        }

        
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
   
    void getaccountlogin(double anum){
        for(auto &i:accountsvector){
            if(i.getaccnum()==anum){
                cust=i;
                return;
            }
        }
        cout<<"Account not found \n";


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
    
    cout<<"To display balance press 'b'\nTo withdraw money from the account press 'w'\nTo send money from one acconunt to another 'c'\nTo change pin 'p'\ndelete account 'd'\nTo logout press 'L'\nTo Exit the bank Press 'e'\n";
        char customeroperation;
        cin>>customeroperation;
        
        if(customeroperation=='b'|| customeroperation=='B'){
           
            myBank.showbalance();
           
        }
        else if(customeroperation=='w'|| customeroperation=='W'){
           myBank.withdrawl();

        }
        else if(customeroperation=='c'|| customeroperation=='C'){
            myBank.depositfrom();
        }

        else if(customeroperation=='p'|| customeroperation=='P'){
            // change pin
            myBank.changePin();

        }

        else if(customeroperation=='t' || customeroperation =='T'){
         myBank.display_tlog();
         
        }

        else if(customeroperation=='d' || customeroperation =='D'){
            myBank.deleteMyCustomer();
            break;
        }
        
        else if(customeroperation=='l'|| customeroperation=='L'){
            cout<<"logout sucessfully";
            goto logout;
        }
        else if(customeroperation=='e'|| customeroperation=='e'){
            break;
        }

        
        else{continue;}
        
    }
    
    
    
    else{
        //employee operations
        cout<<"Welcome employee ";
        myBank.getemployee().display();


        cout<<"To display balance press 'b'\nTo view Transation log of an account 't'\ndelete customer account 'd'\nTo logout press 'L'\nTo Exit the bank Press 'e'\n";
        char empoperation;
        cin>>empoperation;
        double anum;
        cout<<"Please enter accoun number: ";
        cin>>anum;
        myBank.getaccountlogin(anum);
        
        if(empoperation=='b'|| empoperation=='B'){
           
            myBank.showbalance();
           
        }
       
        else if(empoperation=='T'|| empoperation=='T'){
            myBank.display_tlog(anum);
        }

        else if(empoperation=='d' || empoperation =='D'){
            myBank.deleteMyCustomer();
            break;
        }
        else if(empoperation=='l'|| empoperation=='L'){
            cout<<"logout sucessfully";
            goto logout;
        }
        else if(empoperation=='e'|| empoperation=='e'){
            break;
        }

        
        else{continue;}


    }
    logout:
    cout<<"Do you want to continue Browsing the bank press Y for yes and any key for No: "; 

    
    //only continue if and only if the input is Y 
    char* a=NULL;
    cin>>a[0];
    
    if(a[0]=='Y'||a[0]=='y'){
        exit=false;
    }
    
    else{
            exit=true;
    }
    
    
    
    } while (!exit);
    cout<<"Thanks for choosing our services\n";



   

    return 0;
}
