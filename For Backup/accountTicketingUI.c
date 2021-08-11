// ===================================================================================
//  Assignment: 1
//  Milestone : 4
// ===================================================================================
//  Student Name  : Mohammadhossein Sobhanmanesh
//  Student ID    : 116523200
//  Student Email : msobhanmanesh@myseneca.ca
//  Course Section: IPC-NGG
// ===================================================================================
#include <stdio.h>
#include "accountTicketingUI.h"
#include "account.h"
#include "commonHelpers.h"

void displayAccountSummaryHeader(void)
{
    printf("Acct# Acct.Type Birth\n");
    printf("----- --------- -----\n");
}

void displayAccountDetailHeader(void)
{ 
    printf("Acct# Acct.Type Birth Income      Country    Disp.Name       Login      Password\n");
    printf("----- --------- ----- ----------- ---------- --------------- ---------- --------\n");
}

void displayAccountSummaryRecord(const struct Account *account)
{
    printf("%05d %-9s %5d\n", account->accountNum, account->accountType == 'A' ? "AGENT" : "CUSTOMER", account->demographic.birthYearCustomer);
}

void displayAccountDetailRecord(const struct Account *account)
{

    char passHide[100] = {0};
    int i;

    for (i = 0; account->userLogin.password[i] != '\0'; i++)
    {

        if (i % 2)
        {
            passHide[i] = '*';
        }
        else
        {
            passHide[i] = account->userLogin.password[i];
        }
    }

    printf("%05d %-9s %5d $%10.2lf %-10s %-15s %-10s %8s\n",
           account->accountNum,
           account->accountType == 'C' ? "CUSTOMER" : "AGENT",
           account->demographic.birthYearCustomer,
           account->demographic.householdIncome,
           account->demographic.residedCountryName,
           account->userLogin.nameOfCustomer,
           account->userLogin.userLoginName,
           passHide);
}

void applicationStartup(Account accounts[], int size)
{
    menuLogin(accounts, size);
    printf("==============================================\n");
    printf("Account Ticketing System - Terminated\n");
    printf("==============================================\n");
}

int menuLogin(Account accounts[], int size)
{
    int choice, acctNum, index = -1;
    char option;
    do
    {
        printf("==============================================\n");
        printf("Account Ticketing System - Login\n");
        printf("==============================================\n");
        printf("1) Login to the system\n");
        printf("0) Exit application\n");
        printf("----------------------------------------------\n");
        printf("\n");
        printf("Selection: ");
        choice = getIntFromRange(0, 1);
        putchar('\n');
        switch (choice)
        {
        case 0:
            printf("Are you sure you want to exit? ([Y]es|[N]o): ");
            option = getCharOption("yYnN");
            if (option == 'N' || option == 'n')
                choice = 1;
            else if (option == 'Y' || option == 'y')
                choice = -1;
            putchar('\n');
            break;
        case 1:
            printf("Enter your account#: ");
            acctNum = getPositiveInteger();
            putchar('\n');
            index = findAccountIndexByAcctNum(acctNum, accounts, size, 0);
            if (index < 0)
            {
                printf("ERROR:  Access Denied.\n");
                printf("\n");
                pauseExecution();
            }
            else
            {
                if (accounts[index].accountType == 'C')
                {
                    printf("CUSTOMER: home menu currently unavailable...\n");
                    printf("\n");
                    pauseExecution();
                }
                else
                {

                    menuAgent(accounts, size, &accounts[index]); //???????
                }
            }
        default:
            break;
        }
    } while (choice == 1);

    return index;
}

int findAccountIndexByAcctNum(int acctNum, const Account accounts[], int size, int prompt)
{
    int i, index = -1;
    if (prompt == 1)
    {
        printf("Enter the account#: ");
        acctNum = getPositiveInteger();
    }
    for (i = 0; i < size; i++)
    {
        if (accounts[i].accountNum == acctNum)
        {
            index = i;
            break;
        }
    }
    return index;
}

void menuAgent(Account accounts[], int size, const Account *thisAgent)
{
    int choice = 0;
    int index;
    do
    {
        printf("AGENT: %s (%d)\n", thisAgent->userLogin.nameOfCustomer, thisAgent->accountNum);
        printf("==============================================\n");
        printf("Account Ticketing System - Agent Menu\n");
        printf("==============================================\n");
        printf("1) Add a new account\n");
        printf("2) Modify an existing account\n");
        printf("3) Remove an account\n");
        printf("4) List accounts: summary view\n");
        printf("5) List accounts: detailed view\n");
        printf("----------------------------------------------\n");
        printf("0) Logout\n");
        printf("\n");

        int j;
        printf("Selection: ");
        choice = getIntFromRange(0, 5);
        putchar('\n');
        switch (choice)
        {
        case 1:
            // add new account
            for (j = 0; j < size; j++)
            {
                if (accounts[j].accountNum == 0)
                    break;
            }
            // j is the index that is open for a new account
            if (j < size)
            {

                getAccount(&accounts[j]);
                getUserLogin(&accounts[j].userLogin);
                getDemographic(&accounts[j].demographic);
                printf("*** New account added! ***\n");
                printf("\n");
            }
            else
            {
                printf("ERROR: Account listing is FULL, call ITS Support!\n");
            }
            pauseExecution();
            break;
        case 2:
            // modify the existing account
            index = findAccountIndexByAcctNum(0, accounts, size, 1);
            putchar('\n');
            if (index < 0)
            {
                printf("ERROR:  Access Denied.\n");
                printf("\n");
                pauseExecution();
            }
            updateAccount(&accounts[index]);

            break;
        case 3:
            // remove account
            index = findAccountIndexByAcctNum(0, accounts, size, 1);
            if (index < 0)
            {   
                putchar('\n');
                printf("ERROR:  Access Denied.\n");
                pauseExecution();
            }
            else if (accounts[index].accountNum == thisAgent->accountNum)
            {
                printf("\n");
                printf("ERROR: You can't remove your own account!\n");
                printf("\n");
                pauseExecution();
            }
            else
            {
                displayAccountDetailHeader();
                displayAccountDetailRecord(&accounts[index]);
                putchar('\n');
                printf("Are you sure you want to remove this record? ([Y]es|[N]o): ");
                if (getCharOption("YN") == 'Y')
                {
                    accounts[index].accountNum = 0;
                    printf("\n");
                    printf("*** Account Removed! ***\n");
                    printf("\n");
                }
                else
                {
                    printf("\n");
                    printf("*** No changes made! ***\n");
                    printf("\n");
                }
                pauseExecution();
            }
            break;
        case 4:
            // list accounts
            displayAllAccountSummaryRecords(accounts, size);
            pauseExecution();
            break;
        case 5:
            // detailed view
            displayAllAccountDetailRecords(accounts, size);
            printf("\n");
            pauseExecution();
            break;
        case 0:
            printf("### LOGGED OUT ###\n");
            printf("\n");
            break;
        default:
            break;
        }
    } while (choice != 0);
}

// Pause execution until user enters the enter keyvoid
void pauseExecution(void)
{
    printf("<< ENTER key to Continue... >>");
    clearStanadardInputBuffer();
    putchar('\n');
}

void displayAllAccountSummaryRecords(const Account *account, int size) //?
{

    displayAccountSummaryHeader();
    int i;
    for (i = 0; i < size; i++)
    {
        if (account[i].accountNum != 0)
            displayAccountSummaryRecord(&account[i]);
    }
    putchar('\n');
}

void displayAllAccountDetailRecords(const Account *account, int size)
{

    displayAccountDetailHeader();
    int i;
    for (i = 0; i < size; i++)
    {
        if (account[i].accountNum > 0)
        {
            displayAccountDetailRecord(&account[i]);
        }
    }
}