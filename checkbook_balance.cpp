#include <iostream>
#include <string>
using namespace std;

/*Checkbook balancing program
    - Reads in checks as inputs
    - Uses an array with the class(check) as the type
    - Member variable(identifier) of type 'money'
    - Getters, setters, constructors, and functions for ins and outs
    */

   // We construct, we set, we get!

bool checkCashed(string cashed){
    return (cashed == "yes" || cashed == "Yes" || cashed == "Y");       
    }

class Money
{
public:
    // Declarations:
    friend Money operator+(const Money &amount1, const Money &amount2);
    // Returns the sum of the values of amount1 and amount2.
    friend Money operator-(const Money &amount1, const Money &amount2);
    // Returns amount1 minus amount2.
    friend Money operator-(const Money &amount);
    // Returns the negative of the value of amount.
    friend bool operator==(const Money &amount1, const Money &amount2);
    // Returns true if amount1 and amount2 have the same value; false otherwise.
    friend bool operator<(const Money &amount1, const Money &amount2);
    // Returns true if amount1 is less than amount2; false otherwise.
    Money(long dollars, int cents);
    // Initializes the object so its value represents an amount with
    // the dollars and cents given by the arguments. If the amount
    // is negative, then both dollars and cents should be negative.
    Money(long dollars);
    // Initializes the object so its value represents $dollars.00.
    Money();
    // Initializes the object so its value represents $0.00.
    double get_value() const;
    // Returns the amount of money recorded in the data portion of the calling
    // object.
    void set_value(long cents_in);
    // Sets all_cents to cents_in
    void set_value(double amount);
    // Sets all_cents to equivalent integer version of amount
    friend istream &operator>>(istream &ins, Money &amount);
    // Overloads the >> operator so it can be used to input values of type
    // Money. Notation for inputting negative amounts is as in − $100.00.
    // Precondition: If ins is a file input stream, then ins has already been
    // connected to a file.

    friend ostream &operator<<(ostream &outs, const Money &amount);
    // Overloads the << operator so it can be used to output values of type
    // Money. Precedes each output value of type Money with a dollar sign.
    // Precondition: If outs is a file output stream, then outs has already been
    // connected to a file.
private:
    long all_cents; //using this member as a initializer for the operator overloads
};

int digit_to_int(char c);
// Used in the definition of the overloaded input operator >>.
// Precondition: c is one of the digits '0' through '9'.
// Returns the integer for the digit; for example, digit_to_int('3') returns 3.
//Definitions
Money::Money(long dollars, int cents)
{
    if (dollars * cents < 0) // If one is negative and one is positive
    {
        cout << "Illegal values for dollars and cents.\n";
        exit(1);
    }
    all_cents = dollars * 100 + cents;
}
Money::Money(long dollars) : all_cents(dollars * 100)
{
    // Body intentionally blank.
}
Money::Money() : all_cents(0)
{
    // Body intentionally blank.
}
double Money::get_value() const
{
    return (all_cents * 0.01);
}

void Money::set_value(long cents_in)
{
    all_cents = cents_in;
}

void Money::set_value(double amount)
{
    all_cents = amount * 100;
}

Money operator+(const Money &amount1, const Money &amount2) // have to define it outside of the Class, which is here.
{   // Just showing what '+' does using the .all_cents member. 
    Money temp;
    temp.all_cents = amount1.all_cents + amount2.all_cents; //training it, .all_cents because that is the variable in the Money Class
    return temp;
}

bool operator==(const Money &amount1, const Money &amount2)
{
    return (amount1.all_cents == amount2.all_cents);
}

Money operator-(const Money &amount1, const Money &amount2)
{
    Money temp;
    temp.all_cents = amount1.all_cents - amount2.all_cents;
    return temp;
}
Money operator-(const Money &amount)
{
    Money temp;
    temp.all_cents = -amount.all_cents;
    return temp;
}

bool operator<(const Money &amount1, const Money &amount2)
{   //teaching how to return true or false
    if (amount1.all_cents < amount2.all_cents)
        return true; 
    return false;
}


istream &operator>>(istream &ins, Money &amount)
{
    char one_char, decimal_point,
        digit1, digit2; // digits for the amount of cents
    long dollars;
    int cents;
    bool negative; // set to true if input is negative.
    ins >> one_char;
    if (one_char == '-')
    {
        negative = true;
        ins >> one_char; // read '$'
    }
    else
        negative = false;
    // if input is legal, then one_char == '$'
    ins >> dollars >> decimal_point >> digit1 >> digit2;
    if (one_char != '$' || decimal_point != '.' || !isdigit(digit1) || !isdigit(digit2))
    {
        cout << "Error illegal form for money input\n";
        exit(1);
    }
    cents = digit_to_int(digit1) * 10 + digit_to_int(digit2);
    amount.all_cents = dollars * 100 + cents;
    if (negative)
        amount.all_cents = -amount.all_cents;
    return ins;
}

int digit_to_int(char c)
{
    return (static_cast<int>(c) - static_cast<int>('0'));
}
// Uses cstdlib and iostream:
ostream &operator<<(ostream &outs, const Money &amount)
{
    long positive_cents, dollars, cents;
    positive_cents = labs(amount.all_cents);
    dollars = positive_cents / 100;
    cents = positive_cents % 100;

    if (amount.all_cents < 0)
        outs << "− $" << dollars << '.';
    else
        outs << "$" << dollars << '.';

    if (cents < 10)
        outs << '0';
    outs << cents;

    return outs;
}

class Check{
private:
    int checkNum;
    Money checkAmount;
    bool notCashed;

public:
    Check(){ checkNum = 0; checkAmount = 0.0; notCashed = true; } //constructor initializer
    int getcheckNum() const{ return checkNum;}
    void setcheckNum(int num ){ checkNum = num; } //setting new check amount
    double getcheckAmount() const{ return checkAmount.get_value();}
    void setcheckAmount(double num){ checkAmount = num;}
    bool getCashedOrNot() const { return notCashed; }// does this value return to notCashed OR are we returning
    void setCashedOrNot(string cashed) { notCashed = (cashed == "yes" || cashed == "Yes" || cashed == "Y");}
};

int main(){
    int userChecks = 0;
    double checkAmount = 0.0;
    string cashed;
    double oldBalance = 0.0;

    double total = 0.0;

    cout<<"What is your current account balance?"<<endl;
    cin>>oldBalance;

    cout<<"How many checks will you deposit today?"<<endl;
    cin>>userChecks;

    const int size = userChecks;
    Check money[size];
    int checkNumber;
     //FULL OBJECT with all members. so 5 of each variable. for each index create the const size variable for the array 
    // I'm interacting with internal Check objects inside the array
    // - calling their methods and setting their internal data. 

    // I got the amount of checks that need to be inputted.
    // Now iterate through and use the Class.
    // what do I want to do in the iterations for the index's of the array
    for(int i = 0; i < size; i++){
        cout<<"Has the check been cashed?(Yes/No): "<<endl;
        cin>>cashed;
        
        money[i].setCashedOrNot(cashed);

        if(money[i].getCashedOrNot()){ //third requirement
            cout<<"Please only insert checks that have not been cashed."<<endl;
        }

        cout<<"Please input the check amount: "<<endl;
        cin>>checkAmount;
        money[i].setcheckAmount(checkAmount); //second requirement

        cout<<"Please enter your check number(e.g. 123): "<<endl;
        cin>>checkNumber;
        money[i].setcheckNum(checkNumber); //first requirement


    }

    double totalCashedChecks = 0.0;
    double totalUncashedChecks = 0.0;
    int cashedChecksCount = 0;
    int uncashedChecksCount = 0;
    //sums and count of cashed and uncashed
    
    for(int i = 0; i < size; i++){
        if(money[i].getCashedOrNot()){
            totalCashedChecks += money[i].getcheckAmount(); 
            cashedChecksCount++;
        }
        else{
            totalUncashedChecks += money[i].getcheckAmount(); //total deposit
            uncashedChecksCount++;
        }

    }
    int totalChecks = 0;
    double totalCash = 0.0;
    totalChecks = cashedChecksCount + uncashedChecksCount;
    totalCash = totalCashedChecks + totalUncashedChecks;

    
    double newAccountBalance = 0.0;
    newAccountBalance = (oldBalance + totalUncashedChecks);


    double newAccountBalanceReal = 0.0;
    newAccountBalanceReal = newAccountBalance - totalUncashedChecks;

    newAccountBalanceReal = oldBalance;
    
    double theDifference = 0.0;
    theDifference = newAccountBalance - newAccountBalanceReal;

    cout<<"Checks cashed and not cashed: "<<totalChecks<<endl;

    cout<<"Sum of cashed and not cashed: "<<totalCash<<endl;

    cout<<"Total deposit: "<<totalUncashedChecks<<endl;

    cout<<"New account balance: "<<newAccountBalance<<endl;

    cout<<"Actual new balance: "<<newAccountBalanceReal<<endl;

    cout<<"The difference of account balances: "<<theDifference<<endl;




    return 0;
}




/*int main(){
    double newAccountBalance;
    double oldAccountBalance;
    double totalDeposit;
    double difference;
    string cashed;
    int checkCount;
    int checkAmount;
    int notCashedCount;


    //read in value
    //we can do a count for this 
    //cout<<"Please enter your check number: "<<endl;
    //cin>>checkNum;
    // this is the program without oop
    checkAmount = 0;
    checkCount = 0;
    notCashedCount = 0;
    while(checkAmount >= 0 ){

        cout<<"Please input the check amount (input -1 when you are finished): "<<endl;
        cin>>checkAmount;
            if (checkAmount == -1)
                break;
        totalDeposit += checkAmount;
        

        cout<<"Has the check been cashed?(Yes/No): "<<endl;
        cin>>cashed;
            if (!checkCashed(cashed)){
                notCashedCount++;

            }
            else{
                cout<<"Please only insert checks that have not been cashed. Thank you!"<<endl;
            //return to the first input. (checkAmount)
        }
        cout<<endl;
    }

    cout<<totalDeposit<<" "<<notCashedCount<<endl;

    return 0;
}

*/












// --------------------------------------
/*
   while(checkAmount > 0){

    int getLine(cin, checkAmount[]); // reading in the line

    }
    newAccountBalance = (oldAccountBalance + deposits) - cashed;

    cout<<"total checks cashed = "<<cashed<<endl;
    cout<<"total deposits = " <<deposits<<endl;
    cout<<"New Balance = "<<newAccountBalance<<endl;
    cout<<"Difference = "<<difference<<endl;

    //print both lists of checks in order from lowest to highest CHECK NUMBER


    return 0;
}*/