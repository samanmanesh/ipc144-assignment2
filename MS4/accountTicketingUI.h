// ===================================================================================
//  Assignment: 2
//  Milestone : 4
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
    struct Account *accounts;   // array of accounts
    const int ACCOUNT_MAX_SIZE; // maximum elements for account array

    struct Ticket *tickets;    // array of tickets
    const int TICKET_MAX_SIZE; // maximum elements for ticket array
};

// Functions Prototypes

// Displays a formatted table header for three column headers
void displayAccountSummaryHeader(void);

// Displays a formatted table header for all 7 column headers
void displayAccountDetailHeader(void);

// Displays the three related record or entered records
void displayAccountSummaryRecord(const struct Account *account);

// Displays all the seven related record or entered records
void displayAccountDetailRecord(const struct Account *account);

void applicationStartup(struct AccountTicketingData *acctTData);

int menuLogin(struct AccountTicketingData *acctTData);

int findAccountIndexByAcctNum(int acctNum, const Account accounts[], int size, int prompt);

void menuAgent(struct AccountTicketingData *acctAndTicket, const Account *thisAgent);

// Pause execution until user enters the enter key
void pauseExecution(void);

//
void menuCustomer(const struct AccountTicketingData *data, Account *account);

//
int isBadAttempt(const struct AccountTicketingData *data, int *index);

//
void displayTicketHeader(void);

//
void displayOneTicketRecord(const Ticket *ticket);

//
void applicationStartup(struct AccountTicketingData *acctTData);

//
void displayAllTicketsForAccount(const struct AccountTicketingData *data, int accountNum);

//
void displayMessage(const Ticket *ticket);

//
void displayAgentMessageHeader();

void archiveCloseTicketsForAccount(struct AccountTicketingData *acctAndTicket, Account *relatedTicket);

void closingTicketsForAccount(struct AccountTicketingData *acctAndTicket, Account *relatedTicket);

void archiveRemovedAccount(struct AccountTicketingData *acctAndTicket, Account *relatedAccount);

#endif