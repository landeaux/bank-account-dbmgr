/* -----------------------------------------------------------------------------

FILE NAME:         Acct.HPP

DESCRIPTION:       This is the specification file for the Acct class

PURPOSE:           The purpose of this file is to specify the Acct class
                   and to provide prototypes for its member functions.

USAGE:             In the linux command line, type ./Acct

EXAMPLES:          To run the program, type ./Acct in the linux command line

PARAMETERS:        N/A

EXIT CODES:        0 = Success
                   Otherwise = Error

COMPILATION:       Linux GNU

NOTES:             - 
                     
MODIFICATION HISTORY:

Author          Date           Modification(s)
-------------   -----------    ---------------
Adam Landis     04-28-2016     Version 0001
Adam Landis     04-30-2016     Version 0002
Adam Landis     04-30-2016     Version 0003
Adam Landis     04-30-2016     Version 0004
Adam Landis     05-02-2016     Version 0005
Adam Landis     05-13-2016     Version 0006
Adam Landis     05-13-2016     Version 0007
Adam Landis     05-14-2016     Version 0008

----------------------------------------------------------------------------- */

#ifndef __Acct_HPP__
#define __Acct_HPP__

#include <iostream>
#include <string>

using std::ostream;
using std::istream;
using std::string;

// Global constants
const short MAX_NM_LEN = 20,	// first and last name
            SSN_LEN = 9,
	        ACODE_LEN = 3,
	        PHONE_LEN = 7,
	        NUM_PROMPTS = 8,
	        MAX_PROMPT_LEN = 22,
	        MAX_FILENAME_LEN = 100,
	        NUM_FIELDS = 9,
			MDINIT_LEN = 1;

const unsigned short ALPHA = 0,
                     NUMER = 1,
                     ALNUM = 2;

/* Some compilers require the >> and << operator functions to be prototyped outside 
the class. The following three lines of code are needed to avoid any compilation problems. */
class Acct;   // Forward Declaration

// Function prototypes for Overloaded Stream Operators
ostream &operator << (ostream &, const Acct &);

class Acct
{
    protected: // Everything following this is invisible from the outside
        string _lname, _fname, _mdinit, _ssn, _acode, _phonenum, _acctnum, _acctpwd;
        
    public: // Everything following this is visible from the outside
        
        /***** Constructor(s) *****/
        // Default Constructor
		Acct();
        
        // Overloaded Constructor
        
        // Copy Constructor
        Acct(const Acct &);
        
		/***** Destructor *****/
		~Acct();
        
	    /***** Accessor (Getter) functions *****/
        string getLastName() const;
        string getFirstName() const;
        string getMI() const;
        string getSSN() const;
        string getAreaCode() const;
        string getPhoneNo() const;
        
        /***** Mutator (Setter) functions *****/
        void setLastName(string);
        void setFirstName(string);
        void setMI(string);
        void setSSN(string);
        void setAreaCode(string);
        void setPhoneNo(string);
        // void setAcctNo(string);
        // void setPassword(string);
        virtual void setAcctNo(string) = 0;
        virtual void setPassword(string) = 0;
        
        /***** Work functions *****/   
        char genRandChar();
        string genRandStr(int length);
        bool validAlStr(const char *);
        bool validNumStr(const char *);
        bool validAlNumStr(const char *);
        bool validStr(const char *, const unsigned short, const unsigned short);
        
        /***** Operator functions *****/
        // Object assignment, overloading the = operator
        // Acct operator = (const Acct &);
        
        // Object equality testing, overloading the == operator
        bool operator == (const Acct &);
        
        /***** Friends *****/
        // Object output, overloading the << operator
        // friend ostream &operator << (ostream &, const Acct &);
        
        /***** Exception classes *****/
        class InvalidLastName 
        {
            private:
                string _value;
            public:
                InvalidLastName(string value)
                    { _value = value; }
                string getValue() const
                    { return _value; }
        };
        
        class InvalidFirstName 
        {
            private:
                string _value;
            public:
                InvalidFirstName(string value)
                    { _value = value; }
                string getValue() const
                    { return _value; }
        };
        
        class InvalidMI 
        {
            private:
                string _value;
            public:
                InvalidMI(string value)
                    { _value = value; }
                string getValue() const
                    { return _value; }
        };
        
        class InvalidSSN 
        {
            private:
                string _value;
            public:
                InvalidSSN(string value)
                    { _value = value; }
                string getValue() const
                    { return _value; }
        };
        
        class InvalidAreaCode 
        {
            private:
                string _value;
            public:
                InvalidAreaCode(string value)
                    { _value = value; }
                string getValue() const
                    { return _value; }
        };
        
        class InvalidPhoneNo 
        {
            private:
                string _value;
            public:
                InvalidPhoneNo(string value)
                    { _value = value; }
                string getValue() const
                    { return _value; }
        };
    
};

#endif /* __Acct_HPP__ */