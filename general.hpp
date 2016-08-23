/* -----------------------------------------------------------------------------

FILE NAME:         general_ver3.HPP

DESCRIPTION:       General stuff for all files

PURPOSE:           The purpose of this file is to provide useful macros for the
                   rest of the program to utilize.

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
Adam Landis     05-14-2016     Version 0003

----------------------------------------------------------------------------- */

#ifndef __GENERAL_HPP__
#define __GENERAL_HPP__

#include <iostream>
#include <cstring> // Brings in the C-string handling functions

// URL:  http://stackoverflow.com/questions/4062045/clearing-terminal-in-linux-with-c-code
#define CLEAR_SCREEN \
    std::cout << "\033[2J\033[1;1H"

#define PRINT_LOCATION(x) \
    std::cout << "We are here: " << x << std::endl

#define PRINT_VALUE(x) \
    std::cout << # x << " = " << x << std::endl

#define GLOBAL_SHOW_LOCATION 0

#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0])

#define MAX(x,y) ((x) > (y) ? (x) : (y))

#define MIN(x,y) ((x) < (y) ? (x) : (y))

#define GEN_RAND_INT(a,z) (rand() % (z - a + 1)) + a

// iostream keywords
using std::cout;
using std::cin;
using std::endl;

#endif /* __GENERAL_HPP__ */