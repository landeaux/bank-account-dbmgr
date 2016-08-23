/* -----------------------------------------------------------------------------

FILE NAME:         driver.CPP

DESCRIPTION:       This is the driver program for the BankAcct class

PURPOSE:           This program's purpose is to test the member functions of the
                   BankAcct class

USAGE:             In the linux command line, type ./bankacct

EXAMPLES:          To run the program, type ./bankacct in the linux command line

PARAMETERS:        N/A

EXIT CODES:        0 = Success
                   Otherwise = Error

COMPILATION:       Linux GNU

NOTES:             -  
                        
MODIFICATION HISTORY:

Author          Date           Modification(s)
-------------   -----------    ---------------
Adam Landis     04-27-2016     Version 0001
Adam Landis     04-30-2016     Version 0002
Adam Landis     04-30-2016     Version 0003
Adam Landis     04-30-2016     Version 0004
Adam Landis     04-30-2016     Version 0005
Adam Landis     04-30-2016     Version 0006
Adam Landis     05-02-2016     Version 0007
Adam Landis     05-02-2016     Version 0008
Adam Landis     05-02-2016     Version 0009
Adam Landis     05-02-2016     Version 0010
Adam Landis     05-13-2016     Version 0011
Adam Landis     05-13-2016     Version 0012

----------------------------------------------------------------------------- */

#include "BankAcct.hpp"
#include "general.hpp"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <cctype>	// for using c++ library functions for c-strings
#include <fstream>

// iomanip keywords
using std::fixed;
using std::showpoint;
using std::setprecision;
using std::left;
using std::right;
using std::setw;

// vector keywords
using std::vector;

// fstream keywords
using std::ifstream;
using std::ofstream;
using std::ios;

#define LOCAL_SHOW_LOCATION 0

// global constants
const short CHAR_ARR_SIZES[] = {
	ACODE_LEN + 1,
	MAX_NM_LEN + 1,
	PHONE_LEN + 1,
	MAX_NM_LEN + 1,
	1 + 1,
	SSN_LEN + 1,
	ACCT_PWD_LEN + 1,
	ACCT_NUM_LEN + 1,
};

enum Task {ACODE, FNAME, PHONE, LNAME, MDINIT, SSN, PASSWORD, TRANSFER, HELP_0, HELP_1, REPORT, INFO};

const char VALID_PARAM_SETS[][6 + 1] = {
	"ADNP",        // Change Area Code
	"DFNP",        // Change First Name
	"DHNP",        // Change Phone Number
	"DLNP",        // Change Last Name
	"DMNP",        // Change Middle Initial
	"DNPS",        // Change SSN
	"DNPW",        // Change Password
	"DNNPPT",      // Transfer Funds
	"\0",          // Help Menu
	"?",           // Help Menu
	"DR",          // Write Report
	"DINP",        // Get Account Info
};

const char PROMPTS[][MAX_PROMPT_LEN + 1] = {
	"Last Name",
	"First Name",
	"Middle Initial",
	"Social Security Number",
	"Phone Number Area Code",
	"Phone Number",
	"Account Number",
	"Account Password"
};

// the data structure for holding all the command line parameters
struct CmdLineParams
{
	char acode[ACODE_LEN + 1] = "";
	char fname[MAX_NM_LEN + 1] = "";
	char phonenum[PHONE_LEN + 1] = "";
	char lname[MAX_NM_LEN + 1] = "";
	char mdinit[1 + 1] = "";
	char ssn[SSN_LEN + 1] = "";
	char newpwd[ACCT_PWD_LEN + 1] = "";
	char transfer_amt[20 + 1] = "";
	char db_filename[MAX_FILENAME_LEN + 1] = "";
	char rpt_filename[MAX_FILENAME_LEN + 1] = "";
	char acct1num[ACCT_NUM_LEN + 1] = "";
	char acct1pwd[ACCT_PWD_LEN + 1] = "";
	char acct2num[ACCT_NUM_LEN + 1] = "";
	char acct2pwd[ACCT_PWD_LEN + 1] = "";
};

// Function prototypes
void displayHelp();
void writeReport(vector<BankAcct> &, const char *);
void load(ifstream &, ofstream &, vector<BankAcct> &, char[]);
void openFailure(bool);
void readDatabase(ifstream &, vector<BankAcct> &);
BankAcct readRecord(ifstream &);
int login(vector<BankAcct>, char *, char *);
void validateAcct(const int acct1_idx, const int acct2_idx);
CmdLineParams parseCmdLine(int, char * [], char []);
int getCmdIdx(const char[]);
void strToUpper(char *);
void charSort(char []);
void quit(ofstream &, vector<BankAcct>, char *);
void updateDatabase(ofstream &, vector<BankAcct>, char *);
void writeToFile(ofstream &, vector<BankAcct>, unsigned);

int main(
	int argc,
	char * argv[])
{
    #if GLOBAL_SHOW_LOCATION || LOCAL_SHOW_LOCATION
        PRINT_LOCATION("Driver.cpp ... main()");
    #endif
    
	ifstream in_db_file;			// input file for the bank database
	ofstream out_db_file;			// output file for the bank database
	vector<BankAcct> db_vector;		// a vector of BankAcct objects to hold database info when read from file
	char cmd_buffer[100 + 1];		// to hold command line parameters
	
    CLEAR_SCREEN;   // clear the screen
    	
    cmd_buffer[0] = '\0';
    
    srand((unsigned)time(0)); // seed the random number generator

	// Parse the command line and store the data into a data structure
	CmdLineParams input = parseCmdLine(argc, argv, cmd_buffer);

	// Get the index within VALID_PARAM_SETS that corresponds to the command requested by the user
	int cmd_idx = getCmdIdx(cmd_buffer);

	// Instantiate an enumerator and initialize it with an integer value that represents the command chosen
	Task command = static_cast<Task>(cmd_idx);       
	
	// Load the database file into the program
	if (strlen(input.db_filename) != 0)		// if a string exists in input.db_filename
		load(in_db_file, out_db_file, db_vector, input.db_filename);
	
	int acct1_idx = login(db_vector, input.acct1num, input.acct1pwd); // get the index of db_vector that corresponds to the user account1 being worked on
	int acct2_idx = -3;		// -3 represents default non-action value
	if (command == TRANSFER)
		acct2_idx = login(db_vector, input.acct2num, input.acct2pwd); // get the index of db_vector that corresponds to the user account2 being worked on
	
	// if the command requested involves changing or getting account info
	if (command != HELP_0 && command != HELP_1 && command != REPORT)
		validateAcct(acct1_idx, acct2_idx);		// make sure the account(s) exists and password(s) correct
	
	
	
	try
	{
		switch (command)
		{
			case ACODE:
			{
				db_vector[acct1_idx].setAreaCode(input.acode);
				break;
			}
			case FNAME:
			{
				db_vector[acct1_idx].setFirstName(input.fname);
				break;
			}
			case PHONE:
			{
				db_vector[acct1_idx].setPhoneNo(input.phonenum);
				break;
			}
			case LNAME:
			{
				db_vector[acct1_idx].setLastName(input.lname);
				break;
			}
			case MDINIT:
			{
				db_vector[acct1_idx].setMI(input.mdinit);
				break;
			}
			case SSN:
			{
				db_vector[acct1_idx].setSSN(input.ssn);
				break;
			}
			case PASSWORD:
			{
				db_vector[acct1_idx].setPassword(input.newpwd);
				break;
			}
			case TRANSFER:
			{
				string str_transfer_amt = input.transfer_amt;
				double dbl_tranfer_amt = stod(str_transfer_amt);
				db_vector[acct1_idx].transfer(dbl_tranfer_amt, db_vector[acct2_idx]);
				break;
			}
			case HELP_0:
			case HELP_1:
			{
				displayHelp();
				break;
			}
			case REPORT:
			{
				writeReport(db_vector, input.rpt_filename);
				break;
			}
			case INFO:
			{
				cout << db_vector[acct1_idx];
				break;
			}
			default:
				break;
		}
	}
	catch (BankAcct::InvalidLastName e)
	{
		cout << "ERROR: " << e.getValue()
			 << " is an invalid value for"
			 << " setting the last name.\n";
	}
	catch (BankAcct::InvalidFirstName e)
	{
		cout << "ERROR: " << e.getValue()
			 << " is an invalid value for"
			 << " setting the first name.\n";
	}
	catch (BankAcct::InvalidMI e)
	{
		cout << "ERROR: " << e.getValue()
			 << " is an invalid value for"
			 << " setting the middle initial.\n";
	}
	catch (BankAcct::InvalidSSN e)
	{
		cout << "ERROR: " << e.getValue()
			 << " is an invalid value for"
			 << " setting the SSN.\n";
	}
	catch (BankAcct::InvalidAreaCode e)
	{
		cout << "ERROR: " << e.getValue()
			 << " is an invalid value for"
			 << " setting the area code.\n";
	}
	catch (BankAcct::InvalidPhoneNo e)
	{
		cout << "ERROR: " << e.getValue()
			 << " is an invalid value for"
			 << " setting the phone number.\n";
	}
	catch (BankAcct::InvalidAcctNo e)
	{
		cout << "ERROR: " << e.getValue()
			 << " is an invalid value for"
			 << " setting the account number.\n";
	}
	catch (BankAcct::InvalidPassword e)
	{
		cout << "ERROR: " << e.getValue()
			 << " is an invalid value for"
			 << " setting the account password.\n";
	}
	catch (BankAcct::InvalidBalance e)
	{
		cout << "ERROR: " << e.getValue()
			 << " is an invalid value for"
			 << " setting the balance.\n";
	}
	catch (BankAcct::InvalidWithdraw e)
	{
		cout << "ERROR: " << e.getValue()
			 << " is an invalid amount for"
			 << " withdrawing funds.\n";
	}
	catch (BankAcct::InvalidDeposit e)
	{
		cout << "ERROR: " << e.getValue()
			 << " is an invalid amount for"
			 << " depositing funds.\n";
	}
	catch (BankAcct::InvalidTransfer e)
	{
		cout << "ERROR: " << e.getValue()
			 << " is an invalid amount for"
			 << " transferring funds.\n";
	}
		
	quit(out_db_file, db_vector, input.db_filename);

    return 0;
}

/* -----------------------------------------------------------------------------
FUNCTION:          displayHelp()
DESCRIPTION:       This function displays a list of commands to the user
RETURNS:           Nothing (Void Function)
NOTES:			   
----------------------------------------------------------------------------- */
void displayHelp()
{
	cout << "HELP MENU" << endl << endl;

	cout << "/? \t\t Display ths help menu" << endl;
	cout << "/Aareacode \t Change Area Code (Combine with /D /N & /P)" << endl;
	cout << "/Dfilename \t Database filename. (Combine with /R or /N /P and a command)" << endl;
	cout << "/Ffirstname \t Change Area Code (Combine with /D /N & /P)" << endl;
	cout << "/Hphonenumber \t Change Phone Number (Combine with /D /N & /P)" << endl;
	cout << "/I \t\t Display Account Info (Combine with /D /N & /P)" << endl;
	cout << "/Llastname \t Change Last Name (Combine with /D /N & /P)" << endl;
	cout << "/Minitial \t Change Middle Initial (Combine with /D /N & /P)" << endl;
	cout << "/Nnumber \t Account Number (Combine with /D /P and a command)" << endl;
	cout << "/Ppassword \t Account Number (Combine with /D /N and a command)" << endl;
	cout << "/Rfilename \t Report File Filename (Combine with /D)" << endl;
	cout << "/Sssn \t\t Change SSN (Combine with /D /N & /P" << endl;
	cout << "/Tamount \t Amount to Transfer (Combine with /D /P, two /Ns and two /Ps)" << endl;
	cout << "/Wnewpassword \t Change Password (Combine with /D /N & /P)" << endl << endl;
}

/* -----------------------------------------------------------------------------
FUNCTION:          writeReport()
DESCRIPTION:	   Writes a human-readable report file from the bank database
RETURNS:           Nothing (Void Function)
NOTES:
----------------------------------------------------------------------------- */
void writeReport(vector<BankAcct> & db_vector, const char * filename)
{
	ofstream rptfile;

	rptfile.open(filename);

	rptfile << "-------    ----            -----        --    ------       ------                -------\n";
	rptfile << "Account    Last            First        MI    SS           Phone                 Account\n";
	rptfile << "Number     Name            Name               Number       Number                Balance\n";
	rptfile << "-------    ----            -----        --    ------       ------                -------\n";


	for (unsigned int idx = 0; idx < db_vector.size(); idx++)
	{
		rptfile << left << fixed << showpoint << setprecision(2);
		rptfile << setw(ACCT_NUM_LEN + 6) << db_vector[idx].getAcctNo()
			    << setw(MAX_NM_LEN - 4)   << db_vector[idx].getLastName()
			    << setw(MAX_NM_LEN - 7)   << db_vector[idx].getFirstName()
			    << setw(6)                << db_vector[idx].getMI()
			    << setw(SSN_LEN + 4)      << db_vector[idx].getSSN() << '(' 
			    << setw(ACODE_LEN)        << db_vector[idx].getAreaCode() << ')'
			    << setw(PHONE_LEN + 1)    << db_vector[idx].getPhoneNo()
			    << setw(16) << right      << db_vector[idx].getBalance();
		if (idx != db_vector.size() - 1)
			rptfile << endl;
	}

	rptfile.close();
}

/* -----------------------------------------------------------------------------
FUNCTION:			 load()
DESCRIPTION:		 Loads the data from the database file into a vector of
                     BankAcct structs
RETURNS:			 nothing (void function)
NOTES:
----------------------------------------------------------------------------- */
void load(ifstream & in_db_file, ofstream & out_db_file, vector<BankAcct> & db_vector, char * filename)
{
	bool is_input = true;
	in_db_file.open(filename);  // Attempt to open the input file

	if (!in_db_file.fail())		// If the input file exists and opens successfully ...
	{
		readDatabase(in_db_file, db_vector);		// read the input file into the db_vector variable,
		in_db_file.close();							// close the file 
		out_db_file.open(filename, ios::app);	// re-open as an output file in append mode
	}
	else    // if the input file does not exist or fails to open
		openFailure(is_input);
	
	if (out_db_file.fail())		// if the output file fails to open
		openFailure(!is_input);
}

/* -----------------------------------------------------------------------------
FUNCTION:			 openFailure()
DESCRIPTION:	     Displays an error message when a file doesn't open, and
                     then exits the program
RETURNS:			 nothing (void function)
NOTES:
----------------------------------------------------------------------------- */
void openFailure(bool is_input)
{
	cout << "The ";
	if (is_input)
		cout << "in";
	else
		cout << "out";
	cout << "put file failed to open.\n\n";
	exit(EXIT_FAILURE);	// exit the program
}

/* -----------------------------------------------------------------------------
FUNCTION:			 readDatabase()
DESCRIPTION:	     Reads the contents of a database structure into the database
                     vector (db_vector)
RETURNS:			 nothing (void function)
NOTES:
----------------------------------------------------------------------------- */
void readDatabase(ifstream & in_db_file, vector<BankAcct> & db_vector)
{
	BankAcct acct;

	while (!in_db_file.eof())
	{
		acct = readRecord(in_db_file);
		db_vector.push_back(acct);
	}
}

/* -----------------------------------------------------------------------------
FUNCTION:			 readRecord()
DESCRIPTION:		 Reads an individual record into a BankAcct struct inside the
                     database vector (db_vector) and returns it
RETURNS:			 BankAcct structure containing bank account data
NOTES:
----------------------------------------------------------------------------- */
BankAcct readRecord(ifstream & in_db_file)
{
	BankAcct temp_acct;
	string arr[NUM_FIELDS];
	float balance;

	for (int i = 0; i < NUM_FIELDS; i++)
		in_db_file >> arr[i];
	
	balance = stod(arr[6]);
	
	temp_acct.setLastName(arr[0]);
	temp_acct.setFirstName(arr[1]);
	temp_acct.setMI(arr[2]);
	temp_acct.setSSN(arr[3]);
	temp_acct.setAreaCode(arr[4]);
	temp_acct.setPhoneNo(arr[5]);
	temp_acct.setBalance(balance);
	temp_acct.setAcctNo(arr[7]);
	temp_acct.setPassword(arr[8]);

	return temp_acct;
}

/* -----------------------------------------------------------------------------
FUNCTION:          login()
DESCRIPTION:       Checks account number and password from command line input 
                   against all accounts and their corresponding passwords for a
				   match.
RETURNS:           Returns account index if account was found and password is
                   correct. Returns -1 if account not found. Returns -2 if 
				   password was incorrect.
NOTES:
----------------------------------------------------------------------------- */
int login(vector<BankAcct> db_vector, char * acct_num, char * acct_pwd)
{
	bool acct_found = false;
	unsigned idx;
	string str_acct_num = acct_num;
	string str_acct_pwd = acct_pwd;
	
	for (idx = 0; idx < db_vector.size(); idx++)
	{
		if (str_acct_num == db_vector[idx].getAcctNo())	// if there is a match
		{
			acct_found = true;
			break;
		}
	}

	if (!acct_found)
		return -1;	// -1 will indicate that an account was not found

	if (str_acct_pwd != db_vector[idx].getPassword()) // if password incorrect
		return -2;	// -2 will indicate that the password was incorrect

	return idx;	// return the index of the account, indicates log in success
}

/* -----------------------------------------------------------------------------
FUNCTION:          validateAcct()
DESCRIPTION:       Checks if the account(s) and the password(s) sent in by the
                   user are valid, and if not, exits the program. If valid, the 
				   program continues as normal.
RETURNS:           Nothing (void function)
NOTES:
----------------------------------------------------------------------------- */
void validateAcct(const int acct1_idx, const int acct2_idx)
{
	if (acct1_idx == -1 || acct2_idx == -1)
	{
		cout << endl << "Account not found." << endl << endl;
		exit(EXIT_FAILURE);
	}
	else if (acct1_idx == -2 || acct2_idx == -2)
	{
		cout << endl << "Incorrect password." << endl << endl;
		exit(EXIT_FAILURE);
	}
}

/* -----------------------------------------------------------------------------
FUNCTION:          parseCmdLine()
DESCRIPTION:       Parses the parameters sent into the program by the user.
RETURNS:           CmdLineParams structure that holds all of the data sent in.
NOTES:
----------------------------------------------------------------------------- */
CmdLineParams parseCmdLine(
	int argc,
	char * argv[], 
	char cmd_buffer[])
{
	CmdLineParams input;
	const char SLASH = '/';
	char valid_options[] = "?ADFHILMNPRSTW";
	unsigned acct_counter = 0;
	unsigned pwd_counter = 0;

	int i;

	for (i = 1; i < argc; ++i)
	{
		char * p = valid_options;
		char * argument = argv[i];

		// test the command line parameter's first character
		bool first_char = argument[0] == SLASH;

		// test the command line parameter's second character
		bool second_char = false;

		for (; *p != 0; ++p)
		{
			second_char = argument[1] == *p;

			if (second_char == true)
				break;
		}

		if (first_char == false || second_char == false)
		{
			cout << "Invalid command line parameter found.\n\n";
			exit(EXIT_FAILURE);
		}

		// look for a string
		bool string_found = argument[2] != 0;

		if (string_found)
		{
			switch (argument[1])
			{
			case 'A':	// Area code
			{
				strncpy(input.acode, argument + 2, ACODE_LEN + 1);
				input.acode[ACODE_LEN] = 0;		//put null byte at the end
				break;
			}
			case 'D':	// Database filename
			{
				strncpy(input.db_filename, argument + 2, MAX_FILENAME_LEN + 1);
				input.db_filename[MAX_FILENAME_LEN] = 0;
				break;
			}
			case 'F':	// First name
			{
				strncpy(input.fname, argument + 2, MAX_NM_LEN + 1);
				input.fname[MAX_NM_LEN] = 0;
				break;
			}
			case 'H':	// pHone number
			{
				strncpy(input.phonenum, argument + 2, PHONE_LEN + 1);
				input.phonenum[PHONE_LEN] = 0;
				break;
			}
			case 'L':	// Last name
			{
				strncpy(input.lname, argument + 2, MAX_NM_LEN + 1);
				input.lname[MAX_NM_LEN] = 0;
				break;
			}
			case 'M':	// Middle initial
			{
				strncpy(input.mdinit, argument + 2, 1 + 1);
				input.mdinit[1] = 0;
				break;
			}
			case 'N':	// account Number
			{
				if (acct_counter == 0)
				{
					strncpy(input.acct1num, argument + 2, ACCT_NUM_LEN + 1);
					input.acct1num[ACCT_NUM_LEN] = 0;
					strToUpper(input.acct1num);
					acct_counter++;
				}
				else
				{
					strncpy(input.acct2num, argument + 2, ACCT_NUM_LEN + 1);
					input.acct2num[ACCT_NUM_LEN] = 0;
					strToUpper(input.acct2num);
					acct_counter++;
				}
				break;
			}
			case 'P':	// account Password
			{
				if (pwd_counter == 0)
				{
					strncpy(input.acct1pwd, argument + 2, ACCT_PWD_LEN + 1);
					input.acct1pwd[ACCT_PWD_LEN] = 0;
					strToUpper(input.acct1pwd);
					pwd_counter++;
				}
				else
				{
					strncpy(input.acct2pwd, argument + 2, ACCT_PWD_LEN + 1);
					input.acct2pwd[ACCT_PWD_LEN] = 0;
					strToUpper(input.acct2pwd);
					pwd_counter++;
				}
				break;
			}
			case 'R':	// Report filename
			{
				strncpy(input.rpt_filename, argument + 2, MAX_FILENAME_LEN + 1);
				input.rpt_filename[MAX_FILENAME_LEN] = 0;
				break;
			}
			case 'S':	// Ssn
			{
				strncpy(input.ssn, argument + 2, SSN_LEN + 1);
				input.ssn[SSN_LEN] = 0;
				break;
			}
			case 'T':	// amounT
			{
				strncpy(input.transfer_amt, argument + 2, 20 + 1);
				input.transfer_amt[20] = 0;
				break;
			}
			case 'W':	// new passWord
			{
				strncpy(input.newpwd, argument + 2, ACCT_PWD_LEN + 1);
				input.newpwd[ACCT_PWD_LEN] = 0;
				strToUpper(input.newpwd);
				break;
			}
			default:
				break;
			}
		}
		else if (argument[1] == 'R')
			strncpy(input.rpt_filename, "BankAcct.Rpt", 13);
		else if (argument[1] != 'I' && argument[1] != '?')
		{
			cout << "No string following /" << argument[1] << " parameter\n\n";
			exit(EXIT_FAILURE);
		}

		cmd_buffer[i - 1] = argument[1];
	}

	cmd_buffer[i - 1] = '\0';	// set last index to a null byte
	charSort(cmd_buffer);		// sort the c-string

	return input;
}

/* -----------------------------------------------------------------------------
FUNCTION:          getCmdIdx()
DESCRIPTION:       Gets the appropriate index from VALID_PARAM_SETS that
                   corresponds to the command the user is requesting. The index
				   is later used with other parallel arrays.
RETURNS:           an integer representing the array index
NOTES:
----------------------------------------------------------------------------- */
int getCmdIdx(const char cmd_buffer[])
{
	int index;
	bool match = false;

	for (index = 0; index < 12; index++)
	{
		// if string in cmd_buffer is a valid parameter set
		if (!strcmp(VALID_PARAM_SETS[index], cmd_buffer))
		{
			match = true;
			break;
		}
	}

	if (!match)		// if no match is found
	{
		cout << "Invalid set of parameters.\n\n";
		exit(EXIT_FAILURE);
	}

	return index;
}

/* -----------------------------------------------------------------------------
FUNCTION:          strToUpper()
DESCRIPTION:	   Converts a Cstring to uppercase letters
RETURNS:           Nothing (Void Function)
NOTES:
----------------------------------------------------------------------------- */
void strToUpper(char * strPtr)
{
	while (*strPtr != '\0')
	{
		if (isalpha(*strPtr) && islower(*strPtr))
			*strPtr = toupper(*strPtr);
		strPtr++;
	}
}

/* -----------------------------------------------------------------------------
FUNCTION:          charSort()
DESCRIPTION:       This function sorts the characters in a c-string
RETURNS:           Nothing (Void Function)
NOTES:
----------------------------------------------------------------------------- */
void charSort(char arr[])
{
	char temp;
	int n, i, j;
	
	n = strlen(arr);

	for (i = 0; i < n - 1; i++)
	{
		for (j = i + 1; j < n; j++)
		{
			if (arr[i] > arr[j])
			{
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}
}

/* -----------------------------------------------------------------------------
FUNCTION:          quit()
DESCRIPTION:       This function says goodbye to the user before exiting the
                   program, updates the database from db_vector, and closes
                   out_db_file.
RETURNS:           Nothing (Void Function)
NOTES:
----------------------------------------------------------------------------- */
void quit(ofstream & out_db_file, vector<BankAcct> db_vector, char * filename)
{
	updateDatabase(out_db_file, db_vector, filename);
	out_db_file.close();
	exit(EXIT_SUCCESS);
}

/* -----------------------------------------------------------------------------
FUNCTION:          updateDatabase()
DESCRIPTION:	   Updates the database file with the contents of all BankAcct
                   structs
RETURNS:           Nothing (Void Function)
NOTES:
----------------------------------------------------------------------------- */
void updateDatabase(ofstream & out_db_file, vector<BankAcct> db_vector, char * filename)
{
	out_db_file.close();		// close the file so it can be reopened not in append mode
	out_db_file.open(filename);
	unsigned n = db_vector.size();

	for (unsigned int i = 0; i < n; i++)
	{
		writeToFile(out_db_file, db_vector, i);
		if (i != n - 1)
			out_db_file << endl << endl;
	}
}

/* -----------------------------------------------------------------------------
FUNCTION:          writeToFile()
DESCRIPTION:	   Writes to the output database file the contents of a BankAcct
                   struct at the specified vector index (idx).
RETURNS:           Nothing (Void Function)
NOTES:
----------------------------------------------------------------------------- */
void writeToFile(ofstream & out_db_file, vector<BankAcct> db_vector, unsigned idx)
{
	if (idx == db_vector.size())
		out_db_file << endl << endl;

	out_db_file << db_vector[idx].getLastName() << endl;
	out_db_file << db_vector[idx].getFirstName() << endl;
	out_db_file << db_vector[idx].getMI() << endl;
	out_db_file << db_vector[idx].getSSN() << endl;
	out_db_file << db_vector[idx].getAreaCode() << endl;
	out_db_file << db_vector[idx].getPhoneNo() << endl;
	out_db_file << db_vector[idx].getBalance() << endl;
	out_db_file << db_vector[idx].getAcctNo() << endl;
	out_db_file << db_vector[idx].getPassword();
}