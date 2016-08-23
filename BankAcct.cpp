/* -----------------------------------------------------------------------------

FILE NAME:         BankAcct.CPP

DESCRIPTION:       This is the implementation program for the BankAcct class

PURPOSE:           The purpose of this file is to provide the BankAcct class
                   member function definitions.

USAGE:             In the linux command line, type ./BankAcct

EXAMPLES:          To run the program, type ./BankAcct in the linux command line

PARAMETERS:        N/A

EXIT CODES:        0 = Success
                   Otherwise = Error

COMPILATION:       Linux GNU

NOTES:             - 
                   
MODIFICATION HISTORY:

Author          Date           Modification(s)
-------------   -----------    ---------------
Adam Landis     04-28-2016     Version 0001
Adam Landis     05-02-2016     Version 0002
Adam Landis     05-02-2016     Version 0003
Adam Landis     05-02-2016     Version 0004
Adam Landis     05-02-2016     Version 0005
Adam Landis     05-13-2016     Version 0006
Adam Landis     05-13-2016     Version 0007
Adam Landis     05-13-2016     Version 0008
Adam Landis     05-14-2016     Version 0009

----------------------------------------------------------------------------- */

#include "BankAcct.hpp"

/* -----------------------------------------------------------------------------
FUNCTION NAME:     Acct::BankAcct() 
PURPOSE:           This is the default constructor function for the BankAcct 
                   class.
RETURNS:           Nothing
NOTES:             
----------------------------------------------------------------------------- */
// BankAcct::BankAcct()
// {    
//     #if GLOBAL_SHOW_LOCATION || LOCAL_SHOW_LOCATION
//         PRINT_LOCATION("BankAcct::BankAcct() - default constructor");
//     #endif
    
//     _balance = 0.00;
// }

/* -----------------------------------------------------------------------------
FUNCTION NAME:     ostream &operator<<(ostream &, const BankAcct &)
PURPOSE:           Object output (overloading << operator) member function 
                   for the Acct class
RETURNS:           ostream object containing output statements
NOTES:             
----------------------------------------------------------------------------- */
ostream &operator << (ostream &strm, const BankAcct &obj)
{   
    #if GLOBAL_SHOW_LOCATION || LOCAL_SHOW_LOCATION
        PRINT_LOCATION("ostream &operator << (ostream &strm, const Acct &obj) - Object output");
    #endif
    
    strm << "Last Name:      " << obj.getLastName() << endl;
    strm << "First Name:     " << obj.getFirstName() << endl;
    strm << "MI:             " << obj.getMI() << endl;
    strm << "SSN:            " << obj.getSSN() << endl;
    strm << "Area Code:      " << obj.getAreaCode() << endl;
    strm << "Phone Number:   " << obj.getPhoneNo() << endl;
    strm << "Account Number: " << obj.getAcctNo() << endl;
    strm << "Password:       " << obj.getPassword() << endl;
    strm << setprecision(2) << fixed << showpoint;
    strm << "Balance:        $" << obj.getBalance() << endl;
    
    return strm;
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     BankAcct::getBalance() 
PURPOSE:           Accessor function that gets the balance from the bank account
RETURNS:           A double representing the balance in the account.
NOTES:             
----------------------------------------------------------------------------- */
double BankAcct::getBalance() const
{
    return _balance;   
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     BankAcct::getAcctNo()
PURPOSE:           Accessor function that gets the Account Number for the account
RETURNS:           String representing the Account Number for the account
NOTES:             
----------------------------------------------------------------------------- */
string BankAcct::getAcctNo() const
{
    return _acctnum;
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     BankAcct::getPassword()
PURPOSE:           Accessor function that gets the Password for the account
RETURNS:           String representing the Password for the account
NOTES:             
----------------------------------------------------------------------------- */
string BankAcct::getPassword() const
{
    return _acctpwd;
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     BankAcct::setAcctNo()
PURPOSE:           Mutator function that sets the Account Number for the account
RETURNS:           Nothing (void function)
NOTES:             
----------------------------------------------------------------------------- */
void BankAcct::setAcctNo(string acctnum)
{
    if (!validStr(acctnum.c_str(), ACCT_NUM_LEN, ALNUM))
        throw InvalidAcctNo(acctnum);
    _acctnum = acctnum;
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     BankAcct::setPassword()
PURPOSE:           Mutator function that sets the Password for the account
RETURNS:           Nothing (void function)
NOTES:             
----------------------------------------------------------------------------- */
void BankAcct::setPassword(string acctpwd)
{
    if (!validStr(acctpwd.c_str(), ACCT_PWD_LEN, ALNUM))
        throw InvalidPassword(acctpwd);
    _acctpwd = acctpwd;
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     BankAcct::setBalance() 
PURPOSE:           Mutator function that sets the balance in the bank account
RETURNS:           Nothing (void function)
NOTES:             
----------------------------------------------------------------------------- */
void BankAcct::setBalance(double balance)
{
    string bal_as_str = to_string(balance);
    if (!validAmt(bal_as_str.c_str()))
        throw InvalidBalance(balance);
        
    _balance = balance;
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     BankAcct::deposit() 
PURPOSE:           Mutator function that deposits funds the bank acount
RETURNS:           Nothing (void function)
NOTES:             
----------------------------------------------------------------------------- */
void BankAcct::deposit(double amount)
{
    if (amount < 0.00)
        throw InvalidDeposit(amount);
        
    _balance += amount;
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     BankAcct::withdraw() 
PURPOSE:           Mutator function that withdraws funds the bank acount
RETURNS:           Nothing (void function)
NOTES:             
----------------------------------------------------------------------------- */
void BankAcct::withdraw(double amount)
{
    if (amount < 0.00)
        throw InvalidWithdraw(amount);
    
    if (_balance < amount)
        _balance -= OVERDRAW_FEE;
        
    _balance -= amount;
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     BankAcct::transfer() 
PURPOSE:           Mutator function that transfers funds from the bank account
                   to a recipient's bank account
RETURNS:           Nothing (void function)
NOTES:             
----------------------------------------------------------------------------- */
void BankAcct::transfer(double amount, BankAcct &recipient)
{
    if (amount < 0.00)
        throw InvalidTransfer(amount);
    
    withdraw(amount);
    recipient.deposit(amount);
}

/* -----------------------------------------------------------------------------
FUNCTION:          BankAcct::validAmt()
DESCRIPTION:       validates that a c-string is a valid monetary amount
RETURNS:           a bool that represents whether or not the c-string is a valid
                   monetary amount.
NOTES:
----------------------------------------------------------------------------- */
bool BankAcct::validAmt(const char * strPtr)
{
	unsigned dec_counter = 0;	 // decimal point counter
	unsigned digit_counter = 0;

	for (; *strPtr != 0; strPtr++)
	{
		if (*strPtr == '.')  // if a decimal point is encountered
		{
			dec_counter++;
			if (dec_counter > 1)  // check if there is more than one decimal point
				return false;
			continue;
		}
		digit_counter++;
		if (!isdigit(*strPtr)) 	// check if the char isnt a number
			return false;
		if (digit_counter > 15)  // check if the max number of digits is reached
			return false;
	}

	return true;
}