/* -----------------------------------------------------------------------------

FILE NAME:         BankAcct.HPP

DESCRIPTION:       This is the specification file for the BankAcct class

PURPOSE:           The purpose of this file is to specify the BankAcct class
                   and to provide prototypes for its member functions.

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
Adam Landis     05-14-2016     Version 0007

----------------------------------------------------------------------------- */

#ifndef __BankAcct_HPP__
#define __BankAcct_HPP__

#include "Acct.hpp"
#include "general.hpp"
#include <string>
#include <iomanip>

// string namespace keywords
using std::string;
using std::to_string;
using std::stod;

// iomanip namespace keywords
using std::setprecision;
using std::fixed;
using std::showpoint;

const double OVERDRAW_FEE = 30.00;
const short ACCT_NUM_LEN = 5, ACCT_PWD_LEN = 6;

/* Some compilers require the >> and << operator functions to be prototyped outside 
the class. The following three lines of code are needed to avoid any compilation problems. */
class BankAcct;   // Forward Declaration

// Function prototypes for Overloaded Stream Operators
ostream &operator << (ostream &, const Acct &);

class BankAcct : public Acct
{
    private: // Everything following this is invisible from the outside
        double _balance;
        
    public: // Everything following this is visible from the outside
        
        /***** Constructor(s) *****/
        // Default Constructor
        BankAcct() : Acct()
        { _balance = 0;}
        
        // Overloaded Constructor
        
        // Copy Constructor
        
		/***** Destructor *****/
        
	    /***** Accessor (Getter) functions *****/
        double getBalance() const;
        string getAcctNo() const;
        string getPassword() const;
        
        /***** Mutator (Setter) functions *****/
        virtual void setAcctNo(string);
        virtual void setPassword(string);
        void setBalance(double);
        void deposit(double);
        void withdraw(double);
        void transfer(double, BankAcct &);
        
        /***** Work functions *****/  
        bool validAmt(const char *);
        
        /***** Operator functions *****/
        // Object output, overloading the << operator
        friend ostream &operator << (ostream &, const BankAcct &);
        
        /***** Exception classes *****/
        class InvalidAcctNo 
        {
            private:
                string _value;
            public:
                InvalidAcctNo(string value)
                    { _value = value; }
                string getValue() const
                    { return _value; }
        };
        
        class InvalidPassword
        {
            private:
                string _value;
            public:
                InvalidPassword(string value)
                    { _value = value; }
                string getValue() const
                    { return _value; }
        };
        
        class InvalidBalance
        {
            private:
                double _value;
            public:
                InvalidBalance(double value)
                    { _value = value; }
                double getValue() const
                    { return _value; }
        };
        
        class InvalidDeposit
        {
            private:
                double _value;
            public:
                InvalidDeposit(double value)
                    { _value = value; }
                double getValue() const
                    { return _value; }
        };
        
        class InvalidWithdraw
        {
            private:
                double _value;
            public:
                InvalidWithdraw(double value)
                    { _value = value; }
                double getValue() const
                    { return _value; }
        };
        
        class InvalidTransfer
        {
            private:
                double _value;
            public:
                InvalidTransfer(double value)
                    { _value = value; }
                double getValue() const
                    { return _value; }
        };
};

#endif /* __BankAcct_HPP__ */