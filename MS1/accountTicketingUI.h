// ===================================================================================
//  Assignment: 2
//  Milestone : 1
// ===================================================================================
//  Student Name  : Mohammadhossein Sobhanmanesh
//  Student ID    : 116523200
//  Student Email : msobhanmanesh@myseneca.ca
//  Course Section: IPC-NGG
// ===================================================================================
#ifndef ACCOUNT_TICKETING_UI_H_
#define ACCOUNT_TICKETING_UI_H_
#include "account.h"
#include "ticket.h"

struct AccountTicketingData
{
    struct Account* accounts;   // array of accounts
    const int ACCOUNT_MAX_SIZE; // maximum elements for account array

    struct Ticket* tickets;    // array of tickets
    const int TICKET_MAX_SIZE; // maximum elements for ticket array
};

// Displays a formatted table header for three column headers
void displayAccountSummaryHeader(void);

// Displays a formatted table header for all 7 column headers
void displayAccountDetailHeader(void);

// Displays the three related record or entered records
void displayAccountSummaryRecord(const struct Account *account);

// Displays all the seven related record or entered records
void displayAccountDetailRecord(const struct Account *account);

//void applicationStartup(Account accounts[], int size);
void applicationStartup(struct AccountTicketingData * acctTData);

//int menuLogin(Account accounts[], int size);
int menuLogin(struct AccountTicketingData * acctTData);

int findAccountIndexByAcctNum(int acctNum, const Account accounts[], int size, int prompt);

//void menuAgent(struct AccountTicketingData *accounts, int size, const Account *thisAgent);
//void menuAgent(struct AccountTicketingData *accounts, const Account *thisAgent);
//void menuAgent(struct AccountTicketingData *accounts, const Account *thisAgent);
void menuAgent(struct AccountTicketingData *acctAndTicket, const Account *thisAgent);

// Pause execution until user enters the enter key
void pauseExecution(void);

//
void displayAllAccountSummaryRecords(const Account *account, int size);

//
void displayAllAccountDetailRecords(const Account *account, int size);

//
void menuCustomer(const Account *account, struct Ticket *tickets, int ticketSize);

#endif