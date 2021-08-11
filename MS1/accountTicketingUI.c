// ===================================================================================
//  Assignment: 2
//  Milestone : 1
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
//void applicationStartup(Account accounts[], int size)
void applicationStartup(struct AccountTicketingData *acctTData)
{
    //menuLogin(accounts, size);
    menuLogin(acctTData);
    printf("==============================================\n");
    printf("Account Ticketing System - Terminated\n");
    printf("==============================================\n");
}

//int menuLogin(Account accounts[], int size)
int menuLogin(struct AccountTicketingData *acctTData)
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
            //index = findAccountIndexByAcctNum(acctNum, accounts, size, 0);
            index = findAccountIndexByAcctNum(acctNum, acctTData->accounts, acctTData->ACCOUNT_MAX_SIZE, 0);
            if (index < 0)
            {
                printf("ERROR:  Access Denied.\n");
                printf("\n");
                pauseExecution();
            }
            else
            {
                //if (accounts[index].accountType == 'C')
                if (acctTData->accounts[index].accountType == 'C')
                {
                    //printf("CUSTOMER: home menu currently unavailable...\n");
                    menuCustomer(&acctTData->accounts[index], acctTData->tickets, acctTData->TICKET_MAX_SIZE);
                    printf("\n");
                    //pauseExecution();
                }
                else
                {
                    //menuAgent(accounts,size, &accounts[index]);
                    menuAgent(acctTData, &acctTData->accounts[index]); //??????
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
//void menuAgent(Account accounts[], int size, const Account *thisAgent)
void menuAgent(struct AccountTicketingData *acctAndTicket, const Account *thisAgent)
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
        printf("6) List new tickets\n");
        printf("7) List active tickets\n");
        printf("8) Manage a ticket\n");
        printf("9) Archive closed tickets\n");
        printf("----------------------------------------------\n");
        printf("0) Logout\n");
        printf("\n");

        int j;
        printf("Selection: ");
        choice = getIntFromRange(0, 9);
        putchar('\n');
        switch (choice)
        {
        case 1:
            // add new account
            for (j = 0; j < acctAndTicket->ACCOUNT_MAX_SIZE; j++)
            {
                if (acctAndTicket->accounts[j].accountNum == 0)
                    break;
            }
            // j is the index that is open for a new account
            if (j < acctAndTicket->ACCOUNT_MAX_SIZE)
            {
                int biggest = 0;
                int i;
                for (i = 0; i < acctAndTicket->ACCOUNT_MAX_SIZE; i++)
                {
                    if (acctAndTicket->accounts[i].accountNum > biggest)
                    {
                        biggest = acctAndTicket->accounts[i].accountNum;
                    }
                }
                acctAndTicket->accounts[j].accountNum = biggest + 1;
                printf("New Account Data (Account#:%d)\n", acctAndTicket->accounts[j].accountNum);
                printf("----------------------------------------\n");
                printf("Enter the account type (A=Agent | C=Customer): ");
                acctAndTicket->accounts[j].accountType = getCharOption("AC");
                printf("\n");
                //getAccount(&acctAndTicket->accounts[j]);
                getUserLogin(&acctAndTicket->accounts[j].userLogin);
                getDemographic(&acctAndTicket->accounts[j].demographic);

                // for (i = 0; acctAndTicket->accounts->demographic.residedCountryName[i] != '\0'; i++)
                // {

                //     if (acctAndTicket->accounts->demographic.residedCountryName
                //     [i] >= 'a' && acctAndTicket->accounts->demographic.
                //     residedCountryName[i] <= 'z')
                //     {
                //         acctAndTicket->accounts->demographic.residedCountryName
                //         [i] = acctAndTicket->accounts->demographic.
                //         residedCountryName[i] - 32;
                //     }
                // }

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
            index = findAccountIndexByAcctNum(0, acctAndTicket->accounts, acctAndTicket->ACCOUNT_MAX_SIZE, 1);
            putchar('\n');
            if (index < 0)
            {
                printf("ERROR:  Access Denied.\n");
                printf("\n");
                pauseExecution();
            }
            //(&accounts[index])
            updateAccount(&acctAndTicket->accounts[index]);

            break;
        case 3:
            // remove account
            index = findAccountIndexByAcctNum(0, acctAndTicket->accounts, acctAndTicket->ACCOUNT_MAX_SIZE, 1);
            if (index < 0)
            {
                putchar('\n');
                printf("ERROR:  Access Denied.\n");
                pauseExecution();
            }
            //(accounts[index].accounts->accountNum == thisAgent->accountNum)
            else if (acctAndTicket->accounts[index].accountNum == thisAgent->accountNum)
            {
                printf("\n");
                printf("ERROR: You can't remove your own account!\n");
                printf("\n");
                pauseExecution();
            }
            else
            {
                displayAccountDetailHeader();
                //&accounts->accounts[index]
                displayAccountDetailRecord(&acctAndTicket->accounts[index]);
                putchar('\n');
                printf("Are you sure you want to remove this record? ([Y]es|[N]o): ");
                if (getCharOption("YN") == 'Y')
                {
                    //accounts->accounts[index].accountNum
                    acctAndTicket->accounts[index].accountNum = 0;
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
            displayAllAccountSummaryRecords(acctAndTicket->accounts, acctAndTicket->ACCOUNT_MAX_SIZE);
            pauseExecution();
            break;
        case 5:
            // detailed view
            displayAllAccountDetailRecords(acctAndTicket->accounts, acctAndTicket->ACCOUNT_MAX_SIZE);
            printf("\n");
            pauseExecution();
            break;
        case 6:
            printf("Feature #6 currently unavailable!\n");
            printf("\n");
            pauseExecution();
            break;

        case 7:
            printf("Feature #7 currently unavailable!\n");
            printf("\n");
            pauseExecution();
            break;

        case 8:
            printf("Feature #8 currently unavailable!\n");
            printf("\n");
            pauseExecution();
            break;

        case 9:
            printf("Feature #9 currently unavailable!\n");
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

void menuCustomer(const Account *account, struct Ticket *tickets, int ticketSize)
{
    int choice;
    do
    {
        printf("CUSTOMER: %s (%d)\n", account->userLogin.nameOfCustomer, account->accountNum);
        printf("==============================================\n");
        printf("Customer Main Menu\n");
        printf("==============================================\n");
        printf("1) View your account detail\n");
        printf("2) List my tickets\n");
        printf("3) Create a new ticket\n");
        printf("4) Manage a ticket\n");
        printf("----------------------------------------------\n");
        printf("0) Logout\n");
        printf("\n");
        printf("Selection: ");
        choice = getIntFromRange(0, 4);
        //putchar('\n');
        switch (choice)
        {
        case 1:
            printf("\n");
            displayAccountDetailHeader();
            displayAccountDetailRecord(account);
            printf("\n");
            pauseExecution();
            break;

        case 2:
            printf("\n");
            printf("Feature #2 currently unavailable!\n\n");
            pauseExecution();
            break;

        case 3:
            printf("\n");
            printf("Feature #3 currently unavailable!\n\n");
            pauseExecution();
            break;

        case 4:
            printf("\n");
            printf("Feature #4 currently unavailable!\n\n");
            pauseExecution();
            break;

        case 0:
            printf("\n");
            printf("### LOGGED OUT ###\n");
            //printf("\n");
            break;

        default:
            break;
        }

    } while (choice != 0);
}
