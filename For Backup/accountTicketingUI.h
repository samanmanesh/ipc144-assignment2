// ===================================================================================
//  Assignment: 1
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

// Displays a formatted table header for three column headers
void displayAccountSummaryHeader(void);

// Displays a formatted table header for all 7 column headers
void displayAccountDetailHeader(void);

// Displays the three related record or entered records
void displayAccountSummaryRecord(const struct Account *account);

// Displays all the seven related record or entered records
void displayAccountDetailRecord(const struct Account *account);

void applicationStartup(Account accounts[], int size);

int menuLogin( Account accounts[], int size);

int findAccountIndexByAcctNum(int acctNum, const Account accounts[], int size, int prompt);

void menuAgent(Account *accounts, int size, const Account *thisAgent);

// Pause execution until user enters the enter key
void pauseExecution(void);

void displayAllAccountSummaryRecords(const Account *account , int size);

void displayAllAccountDetailRecords(const Account *account, int size);

#endif