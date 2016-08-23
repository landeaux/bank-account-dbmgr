/* -----------------------------------------------------------------------------

FILE NAME:         BankAcctList.HPP

DESCRIPTION:       This is the specification file for the BankAcctList class

PURPOSE:           The purpose of this file is to specify the BankAcctList class
                   and to provide prototypes for its member functions.

USAGE:             

EXAMPLES:          

PARAMETERS:        N/A

EXIT CODES:        0 = Success
                   Otherwise = Error

COMPILATION:       Linux GNU

NOTES:             - 
                     
MODIFICATION HISTORY:

Author          Date           Modification(s)
-------------   -----------    ---------------
Adam Landis     05-16-2016     Version 0001

----------------------------------------------------------------------------- */

#ifndef __BankAcctList_HPP__
#define __BankAcctList_HPP__

#include "BankAcct.hpp"
#include "general.hpp"

class BankAcctList
{
    private:
        // Declare a structure for the list
        struct ListNode
        {
            BankAcct value;         // The value in this node
            struct ListNode *next;  // To point to the next node
        };
        
        ListNode *head;             // List head pointer
        
    public:
        // Constructor
        BankAcctList()
            { head = nullptr; }
        
        // Destructor
        ~BankAcctList();
        
        // Linked list operations
        void appendNode(BankAcct);
        void insertNode(BankAcct);
        void deleteNode(BankAcct);
        void displayList() const;
};

#endif /* __BankAcctList_HPP__ */