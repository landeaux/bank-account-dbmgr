/* -----------------------------------------------------------------------------

FILE NAME:         BankAcctList.CPP

DESCRIPTION:       This is the implementation program for the BankAcctList class

PURPOSE:           The purpose of this file is to provide the BankAcctList class
                   member function definitions.

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

#include "BankAcctList.hpp"

/* -----------------------------------------------------------------------------
FUNCTION:          BankAcctList::appendNode()
DESCRIPTION:       Adds a node to the end of a list
RETURNS:           Nothing (Void Function)
NOTES:			   
----------------------------------------------------------------------------- */
void BankAcctList::appendNode(BankAcct acct)
{
    ListNode *newNode;  // To point to a new node
    ListNode *nodePtr;  // To move through the list
    
    // Allocate a new node and store acct there
    newNode = new ListNode;
    newNode->value = acct;
    newNode->next = nullptr;
    
    // If there are no nodes in the list
    // make newNode the first node
    if (!head)
        head = newNode;
    else // otherwise, insert newNode at end
    {
        // Initialize nodePtr to head of list
        nodePtr = head;
        
        // Find the last node in the list
        while (nodePtr->next)
            nodePtr = nodePtr->next;
            
        // Insert newNode as the last node.
        nodePtr->next = newNode;
    }
}

/* -----------------------------------------------------------------------------
FUNCTION:          BankAcctList::insertNode()
DESCRIPTION:       Inserts a node into the list in it's alphabetized order
RETURNS:           Nothing (Void Function)
NOTES:			   
----------------------------------------------------------------------------- */
void BankAcctList::insertNode(BankAcct acct)
{
    ListNode *newNode;                  // A new node
    ListNode *nodePtr;                  // To traverse the list
    ListNode *previousNode = nullptr;   // The previous node
    
    // Allocate a new node and store num there.
    newNode = new ListNode;
    newNode->value = acct;
    
    // If there are no nodes in the list
    // make newNode the first node
    if (!head)
    {
        head = newNode;
        newNode->next = nullptr;
    }
    else // Otherwise, insert newNode
    {
        // Position nodePtr at the head of list
        nodePtr = head;
        
        // Initialize previousNode to nullptr
        previousNode = nullptr;
        
        // Skip all nodes whose value is less than
    }
}

/* -----------------------------------------------------------------------------
FUNCTION:          BankAcctList::deleteNode()
DESCRIPTION:       Deletes a particular node from the list
RETURNS:           Nothing (Void Function)
NOTES:			   
----------------------------------------------------------------------------- */
void BankAcctList::deleteNode(BankAcct acct)
{
    
}

/* -----------------------------------------------------------------------------
FUNCTION:          BankAcctList::displayList()
DESCRIPTION:       Displays all elements in the list
RETURNS:           Nothing (Void Function)
NOTES:			   
----------------------------------------------------------------------------- */
void BankAcctList::displayList() const
{
    
}
