/* -----------------------------------------------------------------------------

FILE NAME:         Acct.CPP

DESCRIPTION:       This is the implementation program for the Acct class

PURPOSE:           The purpose of this file is to provide the Acct class
                   member function definitions.

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
Adam Landis     04-30-2016     Version 0005
Adam Landis     04-30-2016     Version 0006
Adam Landis     05-02-2016     Version 0007
Adam Landis     05-13-2016     Version 0008
Adam Landis     05-13-2016     Version 0009
Adam Landis     05-14-2016     Version 0010

----------------------------------------------------------------------------- */

#include "Acct.hpp"
#include "general.hpp"
#include <vector>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;
using std::to_string;

/* -----------------------------------------------------------------------------
FUNCTION NAME:     Acct::Acct() 
PURPOSE:           This is the default constructor function for the Acct 
                   class.
RETURNS:           Nothing
NOTES:             
----------------------------------------------------------------------------- */
Acct::Acct() 
{    
    #if GLOBAL_SHOW_LOCATION || LOCAL_SHOW_LOCATION
        PRINT_LOCATION("Acct::Acct() - default constructor");
    #endif
    
    _lname      = "";
    _fname      = "";
    _mdinit     = "";
    _ssn        = "";
    _acode      = "";
    _phonenum   = "";
    _acctnum    = "";
    _acctpwd    = "";
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     Acct::Acct() 
PURPOSE:           This is an overloaded constructor function for the Acct 
                   class
RETURNS:           Nothing
NOTES:             
----------------------------------------------------------------------------- */


/* -----------------------------------------------------------------------------
FUNCTION NAME:     Acct::Acct() 
PURPOSE:           This is the copy constructor function for the Acct class
RETURNS:           Nothing
NOTES:             
----------------------------------------------------------------------------- */
Acct::Acct(const Acct &obj) 
{    
    #if GLOBAL_SHOW_LOCATION || LOCAL_SHOW_LOCATION
        PRINT_LOCATION("Acct::Acct(const Acct &obj) - copy constructor");
    #endif
    
    _lname      = obj._lname;
    _fname      = obj._fname;
    _mdinit     = obj._mdinit;
    _ssn        = obj._ssn;
    _acode      = obj._acode;
    _phonenum   = obj._phonenum;
    _acctnum    = obj._acctnum;
    _acctpwd    = obj._acctpwd;
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     Acct::~Acct() 
PURPOSE:           This is the destructor function for the Acct class
RETURNS:           Nothing
NOTES:             
----------------------------------------------------------------------------- */
Acct::~Acct() 
{    
    #if GLOBAL_SHOW_LOCATION || LOCAL_SHOW_LOCATION
        PRINT_LOCATION("Acct::Acct() - destructor");
    #endif
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     Acct::operator=()
PURPOSE:           Object assignment (overloading = operator) member function 
                   for the Acct class. Copys the member variables of the object 
                   to the right of the = sign into the member variables of the 
                   object to the left.
RETURNS:           modified Acct object that called the function.
NOTES:             
----------------------------------------------------------------------------- */
// Acct Acct::operator = (const Acct &right)
// {   
//     #if GLOBAL_SHOW_LOCATION || LOCAL_SHOW_LOCATION
//         PRINT_LOCATION("Acct::operator = (const Acct &right) - Object assignment");
//     #endif
    
//     _lname      = right._lname;
//     _fname      = right._fname;
//     _mdinit     = right._mdinit;
//     _ssn        = right._ssn;
//     _acode      = right._acode;
//     _phonenum   = right._phonenum;
//     _acctnum    = right._acctnum;
//     _acctpwd    = right._acctpwd;
    
//     return *this;
// }

/* -----------------------------------------------------------------------------
FUNCTION NAME:     Acct::operator==()
PURPOSE:           Object equality testing (overloading == operator) member function 
                   for the Acct class. checks to see if two Acct objects are equal 
                   (i.e. all member variables are equal)
RETURNS:           Boolean value representing whether they are equal or not.
NOTES:             
----------------------------------------------------------------------------- */
bool Acct::operator == (const Acct &right)
{   
    #if GLOBAL_SHOW_LOCATION || LOCAL_SHOW_LOCATION
        PRINT_LOCATION("Acct::operator == (const Acct &right) - Object equality testing");
    #endif
    
    if (   _lname      != right._lname 
        || _fname      != right._fname 
        || _mdinit     != right._mdinit 
        || _ssn        != right._ssn 
        || _acode      != right._acode 
        || _phonenum   != right._phonenum 
        || _acctnum    != right._acctnum 
        || _acctpwd    != right._acctpwd)
        return false;    
    
    return true;
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     ostream &operator<<(ostream &, const Acct &)
PURPOSE:           Object output (overloading << operator) member function 
                   for the Acct class
RETURNS:           ostream object containing output statements
NOTES:             
----------------------------------------------------------------------------- */
// ostream &operator << (ostream &strm, const Acct &obj)
// {   
//     #if GLOBAL_SHOW_LOCATION || LOCAL_SHOW_LOCATION
//         PRINT_LOCATION("ostream &operator << (ostream &strm, const Acct &obj) - Object output");
//     #endif
    
//     strm << "Last Name:      " << obj.getLastName() << endl;
//     strm << "First Name:     " << obj.getFirstName() << endl;
//     strm << "MI:             " << obj.getMI() << endl;
//     strm << "SSN:            " << obj.getSSN() << endl;
//     strm << "Area Code:      " << obj.getAreaCode() << endl;
//     strm << "Phone Number:   " << obj.getPhoneNo() << endl;
//     strm << "Account Number: " << obj.getAcctNo() << endl;
//     strm << "Password:       " << obj.getPassword() << endl;
    
//     return strm;
// }

/* -----------------------------------------------------------------------------
FUNCTION NAME:     Acct::getLastName()
PURPOSE:           Accessor function that gets the Last Name from the account
RETURNS:           String representing the Last Name from the account
NOTES:             
----------------------------------------------------------------------------- */
string Acct::getLastName() const
{
    return _lname;
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     Acct::getFirstName()
PURPOSE:           Accessor function that gets the First Name from the account
RETURNS:           String representing the First Name from the account
NOTES:             
----------------------------------------------------------------------------- */
string Acct::getFirstName() const
{
    return _fname;
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     Acct::getMI()
PURPOSE:           Accessor function that gets the Middle Initial from the account
RETURNS:           String representing the Middle Initial from the account
NOTES:             
----------------------------------------------------------------------------- */
string Acct::getMI() const
{
    return _mdinit;
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     Acct::getSSN()
PURPOSE:           Accessor function that gets the Social Security Number from 
                   the account
RETURNS:           String representing the Social Security Number from 
                   the account
NOTES:             
----------------------------------------------------------------------------- */
string Acct::getSSN() const
{
    return _ssn;
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     Acct::getAreaCode()
PURPOSE:           Accessor function that gets the Area Code from the account
RETURNS:           String representing the Area Code from the account
NOTES:             
----------------------------------------------------------------------------- */
string Acct::getAreaCode() const
{
    return _acode;
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     Acct::getPhoneNo()
PURPOSE:           Accessor function that gets the Phone Number from the account
RETURNS:           String representing the Phone Number from the account
NOTES:             
----------------------------------------------------------------------------- */
string Acct::getPhoneNo() const
{
    return _phonenum;
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     Acct::setLastName()
PURPOSE:           Mutator function that sets the Last Name for the account
RETURNS:           Nothing (void function)
NOTES:             
----------------------------------------------------------------------------- */
void Acct::setLastName(string lname)
{
    if (!validStr(lname.c_str(), MAX_NM_LEN, ALPHA))
        throw InvalidLastName(lname);
    _lname = lname;
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     Acct::setFirstName()
PURPOSE:           Mutator function that sets the First Name for the account
RETURNS:           Nothing (void function)
NOTES:             
----------------------------------------------------------------------------- */
void Acct::setFirstName(string fname)
{
    if (!validStr(fname.c_str(), MAX_NM_LEN, ALPHA))
        throw InvalidFirstName(fname);
    _fname = fname;
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     Acct::setMI()
PURPOSE:           Mutator function that sets the Middle Initial for the account
RETURNS:           Nothing (void function)
NOTES:             
----------------------------------------------------------------------------- */
void Acct::setMI(string mdinit)
{
    if (!validStr(mdinit.c_str(), MDINIT_LEN, ALPHA))
        throw InvalidMI(mdinit);
    _mdinit = mdinit;
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     Acct::setSSN()
PURPOSE:           Mutator function that sets the Social Security Number for the
                   account
RETURNS:           Nothing (void function)
NOTES:             
----------------------------------------------------------------------------- */
void Acct::setSSN(string ssn)
{
    if (!validStr(ssn.c_str(), SSN_LEN, NUMER))
        throw InvalidSSN(ssn);
    _ssn = ssn;
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     Acct::setAreaCode()
PURPOSE:           Mutator function that sets the Area Code for the account
RETURNS:           Nothing (void function)
NOTES:             
----------------------------------------------------------------------------- */
void Acct::setAreaCode(string acode)
{
    if (!validStr(acode.c_str(), ACODE_LEN, NUMER))
        throw InvalidAreaCode(acode); 
    _acode = acode;
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     Acct::setPhoneNo()
PURPOSE:           Mutator function that sets the Phone Number for the account
RETURNS:           Nothing (void function)
NOTES:             
----------------------------------------------------------------------------- */
void Acct::setPhoneNo(string phonenum)
{
    if (!validStr(phonenum.c_str(), PHONE_LEN, NUMER))
        throw InvalidPhoneNo(phonenum); 
    _phonenum = phonenum;
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     Acct::setAcctNo()
PURPOSE:           Mutator function that sets the Account Number for the account
RETURNS:           Nothing (void function)
NOTES:             
----------------------------------------------------------------------------- */
// void Acct::setAcctNo(string acctnum)
// {
//     _acctnum = acctnum;
// }

/* -----------------------------------------------------------------------------
FUNCTION NAME:     Acct::setPassword()
PURPOSE:           Mutator function that sets the Password for the account
RETURNS:           Nothing (void function)
NOTES:             
----------------------------------------------------------------------------- */
// void Acct::setPassword(string acctpwd)
// {
//     _acctpwd = acctpwd;
// }

/* -----------------------------------------------------------------------------
FUNCTION NAME:     Acct::genRandChar()
PURPOSE:           Work function that generates a random character from 0 - 9 
                   and A - Z. Used in conjuntction with the 
                   Acct::genRandStr(int) function
RETURNS:           A char representing the random character generated
NOTES:             
----------------------------------------------------------------------------- */
char Acct::genRandChar()
{
    return (GEN_RAND_INT(0,1) == true ? (char)GEN_RAND_INT(48,57) : (char)GEN_RAND_INT(65,90));
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     Acct::genRandStr()
PURPOSE:           Work function that takes in an integer length and generates a 
                   random string of that length made of characters from 0 - 9 
                   and A - Z 
RETURNS:           A string representing the random string generated
NOTES:             
----------------------------------------------------------------------------- */
string Acct::genRandStr(int length)
{
    string result = "";
    
    for (int i = 0; i < length; i++)
        result += genRandChar();
    
    return result;
}

/* -----------------------------------------------------------------------------
FUNCTION:          Acct::validAlStr()
DESCRIPTION:       Validates that all the characters in a c-string are 
                   letters (a - z, A - Z)
RETURNS:           a bool that represents whether or not the c-string is 
                   alphabetical
NOTES:
----------------------------------------------------------------------------- */
bool Acct::validAlStr(const char * strPtr)
{
	for (; *strPtr != 0; strPtr++)
	{
		if (!isalpha(*strPtr))
			return false;
	}
	return true;
}

/* -----------------------------------------------------------------------------
FUNCTION:          Acct::validNumStr()
DESCRIPTION:       Validates that all the characters in a c-string are
                   digits (0 - 9)
RETURNS:           a bool that represents whether or not the c-string is
				   numerical
NOTES:
----------------------------------------------------------------------------- */
bool Acct::validNumStr(const char * strPtr)
{
	for (; *strPtr != 0; strPtr++)
	{
		if (!isdigit(*strPtr))
			return false;
	}
	return true;
}

/* -----------------------------------------------------------------------------
FUNCTION:          Acct::validAlNumStr()
DESCRIPTION:       Validates that all the characters in a c-string are
                   digits (0 - 9) or letters (a - z, A - Z)
RETURNS:           a bool that represents whether or not the c-string alphabetical 
                   and/or numerical
NOTES:
----------------------------------------------------------------------------- */
bool Acct::validAlNumStr(const char * strPtr)
{
	for (; *strPtr != 0; strPtr++)
	{
		if (!isalnum(*strPtr))
			return false;
	}
	return true;
}

/* -----------------------------------------------------------------------------
FUNCTION:          Acct::validStr()
DESCRIPTION:       calls the correct c-string validation function base on which 
                   field type it is (alphabetical, numerical, or alpha-numerical) 
RETURNS:           a bool that represents whether or not the c-string is valid
NOTES:
----------------------------------------------------------------------------- */
bool Acct::validStr(const char * strPtr, const unsigned short len, const unsigned short type)
{
	if (len == MAX_NM_LEN)	// identify if the program is validating a name -- via the value sent in for len
	{
		if (strlen(strPtr) > len)	// only needs to return false if greater than MAX_NM_LEN
			return false;
	}
	else
	{
		if (strlen(strPtr) != len)	// check if the string is not the correct length
			return false;
	}

	switch (type)
	{
	case ALPHA:		// alphabetical check
	{
		return validAlStr(strPtr);
		break;
	}
	case NUMER:		// numerical check
	{
		return validNumStr(strPtr);
		break;
	}
	case ALNUM:		// alphabetical & numerical check
	{
		return validAlNumStr(strPtr);
		break;
	}
	default:
		break;
	}

	return false;
}