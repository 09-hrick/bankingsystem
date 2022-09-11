/*

    "To display balance press 'b'\nTo withdraw money from the account press 'w'\nTo send money from one acconunt to another 'c'\nTo change pin 'p'\ndelete account 'd'\nTo logout press 'L'\nTo Exit the bank Press 'e'\n";
    "To display balance press 'b'\nTo view Transation log of an account 't'\ndelete customer account 'd'\nTo logout press 'L'\nTo Exit the bank Press 'e'\n";
*/


/***************************************************************
                   HEADER FILE USED IN PROJECT
****************************************************************/
#include<iostream>
#include<algorithm>
#include<bits/stdc++.h>
#include<fstream>
#include<string>
#include <stdexcept>
using namespace std;

/***************************************************************
                  CLASS USED IN PROJECT
****************************************************************/


//employee class declaration
class Employee{
    private:
        string _employeeName_; 
        double _employeeId_;
        string _employeePas_;
    public:
    //default consrtuctor for employee class
    Employee(){}

    //constructor for employee class
    Employee(string en,double eid,string ep){
        _employeeName_=en;
        _employeeId_=eid;
        _employeePas_=ep;
    }

    //function to display the name of the enmployee
    void display(){
        cout<<_employeeName_<<endl;
    }

    //function to verify if the loging in user
    bool loginemp(double empId,string emppin){
        return (_employeeId_==empId && _employeePas_==emppin);
    }
    //returns an out string stream to be appended in employee.csv file at the time of bank distructor calling
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

    //default constructor of Transationlog class
    Transationlog(){}

    //constructor of  Transationlog class
    Transationlog(double AccountToBelogged, double CreditedOrDebtedAccount, double AmountTransfered, string CreditedOrDebted){
        _AccountToBelogged_ = AccountToBelogged; 
        _CreditedOrDebtedAccount_= CreditedOrDebtedAccount;
        _AmountTransfered_= AmountTransfered;
        _CreditedOrDebted_= CreditedOrDebted;
    }

    //funtion for sending a stream of string which has data of the transation
    stringstream giveTlog(){
            stringstream oss;
            //AccountToBelogged, CreditedOrDebtedAccount, AmountTransfered, CreditedOrDebted
            oss<<'\n'<<_AccountToBelogged_<<','<<_CreditedOrDebtedAccount_<<','<<_AmountTransfered_<<','<<_CreditedOrDebted_;
            return oss;
    }

    //function to get the account number so as to view or log transation
    double getloggedAccount(){
        return this->_AccountToBelogged_;
    }
   
};

// key value pairs for input of account type
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
    //default constructor
    Accounts(){
    }
    //overloaded constructor for manual account making
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

    //prints the current account holder name
    void display(){
        cout<<this->_accountHolderName_;
    }


    //overloaded constructor for accounts class
    Accounts(double account_number, int atm_pin,string accountHolderName,double amount,string  account_type)
    {
        _account_number_ = account_number;
        _atm_pin_ = atm_pin;
        _accountHolderName_ = accountHolderName;
        _amount_ = amount;
        _account_type_ = account_type;
    }

    //returns the balance of current accounts obj
    double whatismybalance(){
        return _amount_;
    }


    //operator overloading adds or subtracts and assigns the value to the amount of current obj
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

    //sets the pin of current user account
    void Setpin(int apin1,int apin2){
        if(this->_atm_pin_==apin1){
            this->_atm_pin_=apin2;
        }

    }
    //sends a stream of values to be logged/printed in employee.csv/console
    ostringstream delAccounts(){
        ostringstream os;
        //account_number, atm_pin, accountHolderName, amount, account_type(savings,current,joint)
        os<<"\n"<<_account_number_<<','<<_atm_pin_<<','<<_accountHolderName_<<','<<_amount_<<','<<_account_type_;
        return os;

    }
    //returns the account number of the current obj
    double getaccnum(){
        return _account_number_;
    }
    //validates the acounts user 
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



//this is the class where all the operations takes place for employees and for the customers
class Bank :private Accounts,private Transationlog,private Employee
{
private:
    //current customer
    Accounts cust;
    //current employee
    Employee emp;

    //returns the accounts obj if the account from that account number exists
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

    //customer/account login portal
    void logincust()
    {
        double anum;
        int apin;
        //takes account number and pin number from the console
        cout<<string(20,'>')<<string(20,'<')<<endl;
        cout<<"Entering Customer login portal\n";
        cout<<"Are you a existing customer?\npress y for yes or any other key for no: ";
        //validates if the customer is existing or not
        char getchary;
        cin>>getchary;
        cout<<string(20,'>')<<string(20,'<')<<endl;
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
                cout<<string(20,'>')<<string(20,'<')<<endl;
                return;
                }
                    
            }cout<<"Incorrect Atm pin or Account number\n";
            logincust(); 
        }
        //if the customer id new it promts to make a new account
        else
        {
            int tempAccNum=accountsvector.back().getaccnum()+1;
            //Accounts(double account_number, int atm_pin,string accountHolderName,double amount,string  account_type)
            Accounts tempaccount=Accounts(tempAccNum);
            cout<<"Account created sucessfully\n";
            accountsvector.push_back(tempaccount);
            cout<<string(20,'>')<<string(20,'<')<<endl;


        }

    }
    //employee login portal login from the console
    void loginemp()
    {
        cout<<"Entering Employee login Portal\n";
        cout<<'\n'<<string(20,'>')<<string(20,'<')<<endl;
        double empid;
        string emppass;
        cout<<"Please enter employee ID: ";
        cin>>empid;
        cout<<"Please enter password: ";
        cin>>emppass;
        //empid take in employee id and emppass take in employee password

        //the for loop validates the employee
        for(auto i:employeesvector)
        {
            if(i.loginemp(empid,emppass)){
                emp=i;
                cout<<"login sucessful\n";
                cout<<string(20,'>')<<string(20,'<')<<endl;
                cust.display();
                return;
            }
        }cout<<"Incorrect password or employee ID\n";
        loginemp();
       

    }


public:
    
    //public members of bank class
    vector <Accounts> accountsvector;
    vector <Transationlog> transationlogsvector;
    vector <Employee> employeesvector;
    int current_user;
    /* zero customer one employee*/

    //returns current account user account number
    double whatsmyaccountnum(){
        return cust.getaccnum();
    }
    //default constructor of bank class
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
    //Bank class destructor
    ~Bank(){

        fstream finout;
        vector<string> sepa;
        //open accounts.csv file and append all the elements
        finout.open("accounts.csv",ios::out);
        finout.seekg(0,ios::beg);
        finout<<"account_number, atm_pin, accountHolderName, amount, account_type(savings/current/joint)";
        for(auto i:accountsvector){
            finout<<i.delAccounts().str();
        }
        finout.close();

        //open employee.csv file and append all the elements
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


    //prints balance of current accounts user
    void showbalance(){
        cout<<"Your current balance is: "<<cust.whatismybalance()<<endl;
    }

    //prints out transaction log of current account user
    void display_tlog(){
    double anum=cust.getaccnum();
    vector<string> ret_words;
    string buf;
    stringstream ss;
    //aacount Stores the account of Current account user 
    Accounts aacount = _getaccount(anum);
    cout<<"Printing account statement of account number "<<aacount.getaccnum()<<endl;
        for(auto &i:transationlogsvector){
            //checks if account is valid
            if(aacount.getaccnum()==i.getloggedAccount()){
                string temp;
                ss=i.giveTlog();
                 while(getline(ss, temp, ',')) { 
                    ret_words.push_back(temp); 
                } 
               //AccountToBelogged, CreditedOrDebtedAccount, AmountTransfered, CreditedOrDebted
               cout<<ret_words[2]<<" has been "<<ret_words[3]<<" from/to your account to/from Account number "<< ret_words[1]<<endl;
            }
        }

    }
    //Prince of transaction log of the given account number 
    void display_tlog(double anum){
    vector<string> ret_words;
    string buf;
    stringstream ss;
    
    //aacount Stores the account of Current account user 
    Accounts aacount = _getaccount(anum);
    cout<<"Printing account statement of account number "<<aacount.getaccnum()<<endl;
        for(auto &i:transationlogsvector){
            //checks if account is valid
            if(aacount.getaccnum()==i.getloggedAccount()){
                string temp;
                ss=i.giveTlog();
                 while(getline(ss, temp, ',')) { 
                    ret_words.push_back(temp); 
                } 
               //AccountToBelogged, CreditedOrDebtedAccount, AmountTransfered, CreditedOrDebted
               cout<<ret_words[2]<<" has been "<<ret_words[3]<<" from/to your account to/from Account number "<< ret_words[1]<<endl;
            }
        }


       
        
        
    }

    //takes input from user and substracts the entered amonunt from the enterd amount
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
                    //logs the transation in transaction vector
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
//takes input from useri.e. money and account details and adds the amount to balance
    void depositfrom(){
        int money;
        int temppin;
        cout<<"Enter account pin: ";
        cin>>temppin;
        //validates the current user account
        if(cust.loginacc(cust.getaccnum(),temppin)){
            int money;
            double anum;
            cout<<"How much money do you want to deposit?\n";
            cin>>money;
            cust-money;
            cout<<"Please enter the account number you want to deposit the money to: ";
            cin>>anum; 
            
            //subtract money from the given account
            for(auto &i:accountsvector){
                if(i.loginacc(cust.getaccnum(),temppin)){
                    i-money;
                    //logs the transaction in translog.csv file
                    Transationlog T(cust.getaccnum(),cust.getaccnum(),money,"Debted");
                    logTransation(T);
                }
                else{continue;}
            }

            //add money from the given account to the other account
            for(auto &i:accountsvector){
                if(i==_getaccount(anum)){
                    i+money; 
                    //logs the transaction in transactionlog vector
                    Transationlog T(anum,cust.getaccnum(),money,"Credited");
                    logTransation(T);
                }else{continue;}
            }return;
               
        }  
        else{
            cout<<"Wrong pin\n";
        }
    }

    //takes user input and changes the current password to the inputed password  
    void changePin(){
        int temppin;
        cout<<"Enter Your current account pin: "; 
        cin>>temppin;
        //validates the user account 
        if(cust.loginacc(cust.getaccnum(),temppin)){
            int newpin;
            cout<<"Please enter new pin number: ";
            cust.Setpin(temppin,newpin);
        }

        
    }

    //appends thetransaction log object in transaction log vector
    void logTransation(Transationlog t){
        transationlogsvector.push_back(t);
    }
    //Ask the user if he/she Is an employee or a customer And ask for inputs accordingly
    void loginportal(){
    int chooseportal;
    cout<<"To enter Customer login portal press '0'"<<"\nTo enter Employee login Portal press '1'\n";
    cout<<string(20,'>')<<string(20,'<')<<endl;
    cin>>chooseportal;
    current_user = chooseportal;

    //Ask the user if he/she is employee or customer 0 for customer and 1 for employee
    while((chooseportal!=0||chooseportal!=1) )
    {
        if (chooseportal== 0)
        { 
            logincust();
            break;
        }
        else if(chooseportal== 1)
        {
            loginemp();
            break;
        }
        
        else
        {
            //promts the user to enter the expression if the user enter values other than 0 or 1
            cout<<"Please enter a valid expression\n";
            cout<<"To enter Customer login portal press '0'"<<"\nTo enter Employee login Portal press '1'\n";
            cout<<string(20,'>')<<string(20,'<')<<endl;
            cin>>chooseportal;
        }
    }
    
}
   //updates current user account
    void getaccountlogin(double anum){
        //validates user
        for(auto &i:accountsvector){
            if(i.getaccnum()==anum){
                cust=i;
                return;
            }
        }
        cout<<"Account not found \n";


    }

    //returns current employee user
    Employee getemployee(){
        return emp;
    }

    //deletes the customer account from the accounts vector
    void deleteMyCustomer(){
        //verfies if the customer/employee is sure to delete the account
        cout<<"Are you sure you want to delete your account\n";
        char c;
        cout<<"Press 'y' and hit enter to confirm: ";
        cin>>c;
        if(c=='y'||c=='Y'){
            cout<<string(20,'>')<<string(20,'<')<<endl;
            cout<<"Account deleted successfully\n";
            cout<<string(20,'>')<<string(20,'<')<<endl;

            //itrates the vector and finds the account obj in accounts vector and erase it from the vector
            vector<Accounts>::iterator i;
            for(i=accountsvector.begin(); i != accountsvector.end(); i++){
                if(cust==*i){
                // cout<<"Account Found";
                accountsvector.erase(i);
                    break;
                }
            }
        }
        else{
            cout<<string(20,'>')<<string(20,'<')<<endl;
            cout<<"Account termination obstructed\n";
            cout<<string(20,'>')<<string(20,'<')<<endl;
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

    if(myBank.current_user==0)
    {
        //customer operations   
        while(true){
        cout<<string(20,'>')<<string(20,'<')<<endl;
        cout<<"To display balance press 'b'\nTo withdraw money from the account press 'w'\nTo send money from one acconunt to another 'c'\nTo change pin 'p'\ndelete account 'd'\nTo logout press 'L'\nTo Exit the bank Press 'e'\n";
        cout<<string(20,'>')<<string(20,'<')<<endl;
        
        char customeroperation;
        cin>>customeroperation;

        //show balance of the current account
        if(customeroperation=='b'|| customeroperation=='B'){
            myBank.showbalance();
           
        }
        //withdraw from the current account 
        else if(customeroperation=='w'|| customeroperation=='W'){
           myBank.withdrawl();

        }
        //deposit from the current account
        else if(customeroperation=='c'|| customeroperation=='C'){
            myBank.depositfrom();
        }
        //changes pin of the current account
        else if(customeroperation=='p'|| customeroperation=='P'){
            // change pin
            myBank.changePin();

        }
        //logs the transation in translog.csv file
        else if(customeroperation=='t' || customeroperation =='T'){
         myBank.display_tlog();
         
        }
        //deletes the current customer account and exits the customer login driver code
        else if(customeroperation=='d' || customeroperation =='D'){
            myBank.deleteMyCustomer();
            break;
        }
        //exits the customer login code and goes to logout label
        else if(customeroperation=='l'|| customeroperation=='L'){
            cout<<"logout sucessfully";
            goto logout;
        }
        //breaks the main loop and exits the driver code
        else if(customeroperation=='e'|| customeroperation=='e'){
            break;
        }

        
        else{continue;}
        }
        
    }
    
    
    
    else{
        //employee operations
        cout<<"Welcome employee ";
        myBank.getemployee().display();
        //keeps promting the user emloyee to do operations untill or unless exited by the promt 
        while(true){
        cout<<string(20,'>')<<string(20,'<')<<endl;
        cout<<"To display balance press 'b'\nTo view Transation log of an account 't'\ndelete customer account 'd'\nTo logout press 'L'\nTo Exit the bank Press 'e'\n";
        cout<<string(20,'>')<<string(20,'<')<<endl;
        
        char empoperation;
        cin>>empoperation;
        double anum;        
        //logins the account and the displays the balance
        if(empoperation=='b'|| empoperation=='B'){
            cout<<"Please enter account number: ";
            cin>>anum;
            myBank.getaccountlogin(anum);
            myBank.showbalance();
           
        }

        //logins the account and then shows the transation log of that account
        else if(empoperation=='T'|| empoperation=='t'){
            cout<<"Please enter account number: ";
            cin>>anum;
            myBank.getaccountlogin(anum);
            myBank.display_tlog(anum);
        }

        //logins the account and deletes that accoun
        else if(empoperation=='d' || empoperation =='D'){
            cout<<"Please enter account number: ";
            cin>>anum;
            myBank.getaccountlogin(anum);
            myBank.deleteMyCustomer();
            break;
        }
        //exits the loop and goto login label
        else if(empoperation=='l'|| empoperation=='L'){
            goto logout;
        }
        //exits the driver code
        else if(empoperation=='e'|| empoperation=='e'){
            break;
        }
        //ignore all other keys        
        else{continue;}
        }


    }
    logout:
    cout<<"Do you want to continue Browsing the bank press Y for yes and any key for No: "; 

    
    //only continue if and only if the input is Y 
    char a;
    cin>>a;
    
    if(a=='Y'||a=='y'){
        exit=false;
    }
    
    else{
            exit=true;
    }
    } while (!exit);

    //greets the user
    cout<<"Thanks for choosing our services\n";
    return 0;
}
