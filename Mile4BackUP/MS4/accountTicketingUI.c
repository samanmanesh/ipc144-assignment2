// ===================================================================================
//  Assignment: 2
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
#include <string.h>

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

void displayTicketHeader(void)
{
    printf("------ ------ ------------------------------ --------\n");
    printf("Ticket Status Subject                        Messages\n");
    printf("------ ------ ------------------------------ --------\n");
}

void displayOneTicketRecord(const Ticket *ticket)
{
    char status[7];
    if (ticket->ticketStatusIndicator == 1)
    {
        strcpy(status, "ACTIVE");
    }
    else
    {
        strcpy(status, "CLOSED");
    }

    printf("%06d %-6s %-30s %5d\n", ticket->uniqueNumTicket, status, ticket->subjectLine, ticket->counter_numOfMessageTicket);
}

void displayAllTicketsForAccount(const struct AccountTicketingData *data, int accountNum)
{
    int i;
    displayTicketHeader();
    for (i = 0; i < data->TICKET_MAX_SIZE; i++)
    {
        if (data->tickets[i].customerAcctNum_Ticket == accountNum)
        {
            displayOneTicketRecord(&data->tickets[i]);
        }
    }
    printf("------ ------ ------------------------------ --------\n");
}

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
    int choice, index = -1;
    int attempts;
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
            attempts = 0;
            int result = 0;
            do
            {
                result = isBadAttempt(acctTData, &index);

                if (result == 1)
                {
                    attempts++;
                    printf("INVALID user login/password combination! [attempts remaining:%d]\n", 3 - attempts);
                    putchar('\n');
                }

            } while (result == 1 && attempts < 3);

            if (result == 1)
            {
                printf("ERROR:  Login failed!\n");
                printf("\n");
                pauseExecution();
                choice = 1;
            }
            else
            {
                printf("\n");
                if (acctTData->accounts[index].accountType == 'C')
                {
                    menuCustomer(acctTData, &acctTData->accounts[index]);
                    printf("\n");
                }
                else
                {
                    menuAgent(acctTData, &acctTData->accounts[index]);
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
        printf(" 1) Add a new account\n");
        printf(" 2) Modify an existing account\n");
        printf(" 3) Remove an account\n");
        printf(" 4) List accounts: summary view\n");
        printf(" 5) List accounts: detailed view\n");
        printf("----------------------------------------------\n");
        printf(" 6) List new tickets\n");
        printf(" 7) List active tickets\n");
        printf(" 8) List closed tickets\n");
        printf(" 9) Manage a ticket\n");
        printf("10) Archive closed tickets\n");
        printf("----------------------------------------------\n");
        printf("11) View archived account statistics\n");
        printf("12) View archived tickets statistics\n");
        printf("----------------------------------------------\n");
        printf("0) Logout\n");
        printf("\n");
        int ticketNum = 0;
        int ticketNumber = 0;
        int j;
        int i = 0;
        int fund = 0;
        int numbOfTicketsArched = 0;
        printf("Selection: ");
        choice = getIntFromRange(0, 12);
        putchar('\n');
        switch (choice)
        {
        // Add a new account
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
                getUserLogin(&acctAndTicket->accounts[j].userLogin);
                getDemographic(&acctAndTicket->accounts[j].demographic);
                printf("*** New account added! ***\n");
                printf("\n");
            }
            else
            {
                printf("ERROR: Account listing is FULL, call ITS Support!\n");
                printf("\n");
            }
            pauseExecution();
            break;
        // Modify an existing account
        case 2:
            // modify the existing account
            index = findAccountIndexByAcctNum(0, acctAndTicket->accounts, acctAndTicket->ACCOUNT_MAX_SIZE, 1);
            putchar('\n');
            if (index < 0)
            {
                printf("ERROR:  Access Denied.\n");
                printf("\n");
                pauseExecution();
                break;
            }
            //(&accounts[index])
            updateAccount(&acctAndTicket->accounts[index]);

            break;
        // Remove an account
        case 3:
            // remove account
            index = findAccountIndexByAcctNum(0, acctAndTicket->accounts, acctAndTicket->ACCOUNT_MAX_SIZE, 1);
            if (index < 0)
            {
                putchar('\n');
                printf("ERROR:  Access Denied.\n");
                pauseExecution();
            }
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
                displayAccountDetailRecord(&acctAndTicket->accounts[index]);
                putchar('\n');
                printf("Are you sure you want to remove this record? ([Y]es|[N]o): ");
                if (getCharOption("YN") == 'Y')
                {

                    // put archivedTickets into tickets_arc.txt
                    //* Archiving done
                    archiveCloseTicketsForAccount(acctAndTicket, &acctAndTicket->accounts[index]);

                    //* Closing both closed & Active related tickets
                    closingTicketsForAccount(acctAndTicket, &acctAndTicket->accounts[index]);

                    // put removedAccount into accounts_arc.txt
                    //*first Archive the account data
                    archiveRemovedAccount(acctAndTicket, &acctAndTicket->accounts[index]);

                    //* Remove the Account
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
        // List accounts: summary view
        case 4:
            // list accounts
            displayAllAccountSummaryRecords(acctAndTicket->accounts, acctAndTicket->ACCOUNT_MAX_SIZE);
            pauseExecution();
            break;
        // List accounts: detailed view
        case 5:
            // detailed view
            displayAllAccountDetailRecords(acctAndTicket->accounts, acctAndTicket->ACCOUNT_MAX_SIZE);
            printf("\n");
            pauseExecution();
            break;
        // List new tickets
        case 6:

            do
            {
                displayAgentMessageHeader();
                for (i = 0; i < acctAndTicket->TICKET_MAX_SIZE; i++)
                {
                    if (acctAndTicket->tickets[i].ticketStatusIndicator == 1 && acctAndTicket->tickets[i].counter_numOfMessageTicket == 1)
                    {
                        displayOneTicketRecordAgent(&acctAndTicket->tickets[i]);
                    }
                }
                printf("------ ----- --------------- ------ ------------------------------ --------\n");
                printf("\n");
                printf("Enter the ticket number to view the messages or\n");
                printf("0 to return to previous menu: ");

                do
                {
                    ticketNum = getInteger();
                    //putchar('\n');
                    if (ticketNum < 0)
                    {
                        printf("ERROR: Value must be positive or zero: ");
                    }
                } while (ticketNum < 0);

                int foundTicket = 0;
                for (i = 0; i < acctAndTicket->TICKET_MAX_SIZE; i++)
                {
                    if (acctAndTicket->tickets[i].uniqueNumTicket == ticketNum && ticketNum != 0)
                    {
                        displayMessage(&acctAndTicket->tickets[i]);
                        //pauseExecution();
                        foundTicket = 1;
                        break;
                    }
                }

                if (foundTicket == 0 && ticketNum != 0)
                {
                    printf("\n");
                    printf("ERROR: Invalid ticket number.\n");
                    printf("\n");
                    pauseExecution();
                }

            } while (ticketNum != 0);
            printf("\n");
            break;
        // List active tickets
        case 7:
            do
            {
                displayAgentMessageHeader();
                // For showing each message
                for (i = 0; i < acctAndTicket->TICKET_MAX_SIZE; i++)
                {
                    //Just show the account that are Active and ticket number non zero
                    if (acctAndTicket->tickets[i].ticketStatusIndicator == 1 && acctAndTicket->tickets[i].uniqueNumTicket != 0)
                        displayOneTicketRecordAgent(&acctAndTicket->tickets[i]);
                }

                printf("------ ----- --------------- ------ ------------------------------ --------\n");
                printf("\n");
                printf("Enter the ticket number to view the messages or\n");
                printf("0 to return to previous menu: ");

                do
                {
                    ticketNum = getInteger();
                    if (ticketNum < 0)
                    {
                        printf("ERROR: Value must be positive or zero: ");
                    }
                } while (ticketNum < 0);

                int foundTicket = 0;
                int i;
                for (i = 0; i < acctAndTicket->TICKET_MAX_SIZE; i++)
                {
                    if (acctAndTicket->tickets[i].uniqueNumTicket == ticketNum && ticketNum != 0)
                    {
                        displayMessage(&acctAndTicket->tickets[i]);
                        foundTicket = 1;
                        break;
                    }
                }

                if (foundTicket == 0 && ticketNum != 0)
                {
                    printf("\n");
                    printf("ERROR: Invalid ticket number.\n");
                    printf("\n");
                    pauseExecution();
                }

            } while (ticketNum != 0);

            printf("\n");

            break;
        // List closed tickets
        case 8:
            do
            {
                displayAgentMessageHeader();
                for (i = 0; i < acctAndTicket->TICKET_MAX_SIZE; i++)
                {
                    //Just show the account that are Closed and ticket number non zero
                    if (acctAndTicket->tickets[i].ticketStatusIndicator == 0 && acctAndTicket->tickets[i].uniqueNumTicket != 0)
                        displayOneTicketRecordAgent(&acctAndTicket->tickets[i]);
                }

                printf("------ ----- --------------- ------ ------------------------------ --------\n");
                printf("\n");
                printf("Enter the ticket number to view the messages or\n");
                printf("0 to return to previous menu: ");

                do
                {
                    ticketNum = getInteger();
                    // putchar('\n');
                    if (ticketNum < 0)
                    {
                        printf("ERROR: Value must be positive or zero: ");
                    }
                } while (ticketNum < 0);

                int foundTicket = 0;
                int i;
                for (i = 0; i < acctAndTicket->TICKET_MAX_SIZE; i++)
                {
                    if (acctAndTicket->tickets[i].uniqueNumTicket == ticketNum && ticketNum != 0)
                    {
                        displayMessage(&acctAndTicket->tickets[i]);
                        //pauseExecution();
                        foundTicket = 1;
                        break;
                    }
                }

                if (foundTicket == 0 && ticketNum != 0)
                {
                    printf("\n");
                    printf("ERROR: Invalid ticket number.\n");
                    printf("\n");
                    pauseExecution();
                }

            } while (ticketNum != 0);

            printf("\n");
            break;
        // Manage a ticket
        case 9:

            printf("Enter ticket number: ");
            ticketNumber = getPositiveInteger();
            putchar('\n');
            for (i = 0; i < acctAndTicket->TICKET_MAX_SIZE; i++)
            {
                if (ticketNumber == acctAndTicket->tickets[i].uniqueNumTicket)
                {
                    updateTicketAgent(&acctAndTicket->tickets[i], *thisAgent);
                    fund = 1;
                }
            }
            if (fund == 0)
            {
                printf("ERROR: Invalid ticket number - you may only modify your own ticket.\n");
            }

            printf("\n");
            break;
        // Archive closed tickets
        case 10:

            printf("Are you sure? This action cannot be reversed. ([Y]es|[N]o): ");
            choice = getCharOption("YN");
            if (choice == 'Y')
            {
                // numbOfTicketsArched = archiveClosedTickets(acctAndTicket); // for accountTicketingUI
                numbOfTicketsArched = archiveClosedTickets(acctAndTicket->tickets, acctAndTicket->TICKET_MAX_SIZE); // for ticket.c
                putchar('\n');
                printf("*** %d tickets archived ***\n", numbOfTicketsArched);
            }
            else
            {
            }

            printf("\n");
            pauseExecution();
            break;
        // View archived account statistics
        case 11:

            viewArchivedAccountStatistics();
            putchar('\n');
            pauseExecution();
            break;

        // View archived tickets statistics
        case 12:

            viewArchivedTicketStatus();
            putchar('\n');
            pauseExecution();
            break;

        case 0:

            printf("Saving session modifications...\n");
            printf("  %d account saved.\n", savingAccountChanges(acctAndTicket->accounts, acctAndTicket->ACCOUNT_MAX_SIZE));

            printf("  %d tickets saved.\n", savingTicketChanges(acctAndTicket->tickets, acctAndTicket->TICKET_MAX_SIZE));
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

// moved to account.c
// void displayAllAccountSummaryRecords(const Account *account, int size) //?
// {

//     displayAccountSummaryHeader();
//     int i;
//     for (i = 0; i < size; i++)
//     {
//         if (account[i].accountNum != 0)
//             displayAccountSummaryRecord(&account[i]);
//     }
//     putchar('\n');
// }

// moved to account.c
// void displayAllAccountDetailRecords(const Account *account, int size)
// {

//     displayAccountDetailHeader();
//     int i;
//     for (i = 0; i < size; i++)
//     {
//         if (account[i].accountNum > 0)
//         {
//             displayAccountDetailRecord(&account[i]);
//         }
//     }
// }

void menuCustomer(const struct AccountTicketingData *data, Account *account)
{
    int choice;
    do
    {
        printf("CUSTOMER: %s (%d)\n", account->userLogin.nameOfCustomer, account->accountNum);
        printf("==============================================\n");
        printf("Customer Main Menu\n");
        printf("==============================================\n");
        printf("1) View your account detail\n");
        printf("2) Create a new ticket\n");
        printf("3) Modify an active ticket\n");
        printf("4) List my tickets\n");
        printf("----------------------------------------------\n");
        printf("0) Logout\n");
        printf("\n");
        printf("Selection: ");
        choice = getIntFromRange(0, 4);
        putchar('\n');
        int ticketNum = 0;
        int ticketNumber = 0;
        int j, i;
        int fund = 0;
        switch (choice)
        {
        // View your account detail
        case 1:
            displayAccountDetailHeader();
            displayAccountDetailRecord(account);
            printf("\n");
            pauseExecution();
            break;
        // Create a new ticket
        case 2:
            // add new ticket
            for (j = 0; j < data->TICKET_MAX_SIZE; j++)
            {
                if (data->tickets[j].uniqueNumTicket == 0)
                    break;
            }
            // j is the index that is open for a new ticket account
            if (j < data->TICKET_MAX_SIZE)
            {
                int biggest = 0;
                int i;
                for (i = 0; i < data->TICKET_MAX_SIZE; i++)
                {
                    if (data->tickets[i].uniqueNumTicket > biggest)
                    {
                        biggest = data->tickets[i].uniqueNumTicket;
                    }
                }
                data->tickets[j].uniqueNumTicket = biggest + 1;
                data->tickets[j].customerAcctNum_Ticket = account->accountNum;

                printf("New Ticket (Ticket#:%06d)\n", data->tickets[j].uniqueNumTicket);
                printf("----------------------------------------\n");
                printf("Enter the ticket SUBJECT (30 chars. maximum): ");
                getCString(data->tickets[j].subjectLine, 1, 30);
                printf("\n");
                printf("Enter the ticket message details (150 chars. maximum). Press the ENTER key to\n");
                printf("submit:\n");
                getCString(data->tickets[j].message->messageDetails, 1, 150);
                // Number of message for ticket
                data->tickets[j].counter_numOfMessageTicket = 1;

                // Put the Stauts of ticket active for new ticket account
                data->tickets[j].ticketStatusIndicator = 1;

                // Put the account type to Customer
                data->tickets[j].message->accountTypeAuthorMessage = account->accountType;

                // Put the name of the related Customer
                strncpy(data->tickets[j].message->nameOfGivenUser, account->userLogin.nameOfCustomer, 31);
                printf("\n");
                printf("*** New ticket created! ***\n\n");
            }
            else
            {
                printf("ERROR: Ticket listing is FULL, call ITS Support!\n\n");
            }
            pauseExecution();
            break;
        // Modify an active ticket
        case 3:
            printf("Enter ticket number: ");
            ticketNumber = getPositiveInteger();
            putchar('\n');
            for (i = 0; i < data->TICKET_MAX_SIZE; i++)
            {
                if (ticketNumber == data->tickets[i].uniqueNumTicket && data->tickets[i].customerAcctNum_Ticket == account->accountNum)
                {

                    if (data->tickets[i].ticketStatusIndicator == 0) // Check if the ticket status is CLOSED
                    {
                        printf("ERROR: Ticket is closed - changes are not permitted.\n");
                        printf("\n");
                        fund = 1;
                        break;
                    }
                    else if (data->tickets->ticketStatusIndicator == 1) // check if the ticket status is Active
                    {
                        updateTicket(&data->tickets[i], *account);
                        fund = 1;
                        break;
                    }
                }
            }
            if (fund == 0)
            {
                printf("ERROR: Invalid ticket number - you may only modify your own ticket.\n\n");
            }

            pauseExecution();
            break;
        // List my tickets
        case 4:
            do
            {
                displayAllTicketsForAccount(data, account->accountNum);
                printf("\n");
                printf("Enter the ticket number to view the messages or\n");
                printf("0 to return to previous menu: ");

                do
                {
                    ticketNum = getInteger();
                    while (ticketNum < 0)
                        if (ticketNum < 0 && ticketNum != 0)
                        {
                            printf("ERROR: Value must be positive or zero: ");
                            ticketNum = getInteger();
                            if (ticketNum != 0)
                            {
                                putchar('\n');
                            }
                        }

                } while (ticketNum < 0);

                int foundTicket = 0;
                int i;
                for (i = 0; i < data->TICKET_MAX_SIZE; i++)
                {
                    if (data->tickets[i].customerAcctNum_Ticket == account->accountNum && data->tickets[i].uniqueNumTicket == ticketNum && ticketNum != 0)
                    {
                        displayMessage(&data->tickets[i]);
                        foundTicket = 1;
                        break;
                    }
                }

                if (foundTicket == 0 && ticketNum != 0)
                {
                    printf("\n");
                    printf("ERROR: Invalid ticket number - you may only access your own tickets.\n");
                    printf("\n");
                    pauseExecution();
                }

            } while (ticketNum != 0);
            printf("\n");
            break;
        // Logout
        case 0:
            printf("Saving session modifications...\n");
            printf("   %d tickets saved.\n", saveTickets(data->tickets, data->TICKET_MAX_SIZE));
            printf("### LOGGED OUT ###\n");
            break;

        default:
            break;
        }
    } while (choice != 0);
}

int isBadAttempt(const struct AccountTicketingData *data, int *index)
{
    int acctNum, badAttempt = 0;
    char aLine[100];

    printf("Enter the account#: ");
    acctNum = getInteger();

    *index = findAccountIndexByAcctNum(acctNum, data->accounts, data->ACCOUNT_MAX_SIZE, 0);

    if (*index < 0)
    {
        badAttempt = 1;
    }

    printf("User Login    : ");
    getCString(aLine, 1, 99);
    if (*index >= 0)
    {
        if (strcmp(aLine, data->accounts[*index].userLogin.userLoginName))
        {
            badAttempt = 1;
        }
    }

    printf("Password      : ");
    getCString(aLine, 1, 99);
    if (*index >= 0)
    {
        if (strcmp(aLine, data->accounts[*index].userLogin.password))
        {
            badAttempt = 1;
        }
    }
    return badAttempt;
}

void displayMessage(const Ticket *ticket)
{
    int true = 1;
    char status[7];
    if (ticket->ticketStatusIndicator == 1)
    {
        strcpy(status, "ACTIVE");
    }
    else
    {
        strcpy(status, "CLOSED");
    }
    printf("\n");
    printf("================================================================================\n");
    printf("%06d (%s) Re: %s\n", ticket->uniqueNumTicket, status, ticket->subjectLine);
    printf("================================================================================\n");
    int i;
    for (i = 0; i < ticket->counter_numOfMessageTicket; i++)
    {
        if ((i + 1) % 5 != 0)
        {
            printf("%s (%s):\n", ticket->message[i].accountTypeAuthorMessage == 'C' ? "CUSTOMER" : "AGENT", ticket->message[i].nameOfGivenUser);
            printf("   %s\n\n", ticket->message[i].messageDetails);
            true = 1;
        }
        else
        {
            printf("%s (%s):\n", ticket->message[i].accountTypeAuthorMessage == 'C' ? "CUSTOMER" : "AGENT", ticket->message[i].nameOfGivenUser);
            printf("   %s\n\n", ticket->message[i].messageDetails);
            true = 0;
            pauseExecution();
        }
    }
    if (true == 1)
    {
        pauseExecution();
    }
}

void displayAgentMessageHeader()
{
    printf("------ ----- --------------- ------ ------------------------------ --------\n");
    printf("Ticket Acct# Display Name    Status Subject                        Messages\n");
    printf("------ ----- --------------- ------ ------------------------------ --------\n");
}

// moved to ticket.c
// void displayOneTicketRecordAgent(const Ticket *ticket)
// {
//     char status[7];
//     if (ticket->ticketStatusIndicator == 1)
//     {
//         strcpy(status, "ACTIVE");
//     }
//     else
//     {
//         strcpy(status, "CLOSED");
//     }

//     printf("%06d %-5d %-15s %-6s %-30s %5d\n", ticket->uniqueNumTicket, ticket->customerAcctNum_Ticket, ticket->message->nameOfGivenUser, status, ticket->subjectLine, ticket->counter_numOfMessageTicket);
// }

//for accountTicketingUi move to account
// int loadAccounts(Account accounts[], int accountMaxSize)
// {

//     int i = 0;
//     FILE *fp = fopen("accounts.txt", "r"); // read

//     if (fp != NULL)
//     {
//         // while (!feof(fp))
//         for (i = 0; i < accountMaxSize; i++)
//         {

//             fscanf(fp, "%d~%c~%[^~]~%[^~]~%[^~]~%d~%lf~%30[^\n]",
//                    &accounts[i].accountNum,
//                    &accounts[i].accountType,
//                    accounts[i].userLogin.nameOfCustomer,
//                    accounts[i].userLogin.userLoginName,
//                    accounts[i].userLogin.password,
//                    &accounts[i].demographic.birthYearCustomer,
//                    &accounts[i].demographic.householdIncome,
//                    accounts[i].demographic.residedCountryName);
//         }
//         fclose(fp);
//         fp = NULL;
//     }
//     else
//     {
//         printf("ERROR: Unable to open file for reading.\n");
//     }
//     return i;
// }

// from here moved to ticket.c
// int loadTickets(Ticket tickets[], int ticketMaxSize)
// {
//     int i = 0;
//     int j = 0;
//     FILE *fp = NULL;
//     fp = fopen("tickets.txt", "r");
//     if (fp != NULL)
//     {
//         while (fscanf(fp, "%d|%d|%d|%[^|]|%d|",
//                       &tickets[i].uniqueNumTicket,
//                       &tickets[i].customerAcctNum_Ticket,
//                       &tickets[i].ticketStatusIndicator,
//                       tickets[i].subjectLine,
//                       &tickets[i].counter_numOfMessageTicket) != EOF)
//         {
//             if (i == ticketMaxSize - 1)
//             {
//                 i = ticketMaxSize;
//                 break;
//             }

//             if (tickets[i].counter_numOfMessageTicket > MAX_NUMBER_MESSAGE)
//             {
//                 tickets[i].counter_numOfMessageTicket = MAX_NUMBER_MESSAGE;
//                 for (j = 0; j < tickets[i].counter_numOfMessageTicket; j++)
//                 {
//                     fscanf(fp, "%c|%[^|]|%[^|]|",
//                            &tickets[i].message[j].accountTypeAuthorMessage,
//                            tickets[i].message[j].nameOfGivenUser,
//                            tickets[i].message[j].messageDetails);
//                 }
//                 fscanf(fp, "%*[^\n]"); // skip to end of line
//             }
//             else
//             {
//                 for (j = 0; j < tickets[i].counter_numOfMessageTicket; j++)
//                 {
//                     fscanf(fp, "%c|%[^|]|%[^|]|",
//                            &tickets[i].message[j].accountTypeAuthorMessage,
//                            tickets[i].message[j].nameOfGivenUser,
//                            tickets[i].message[j].messageDetails);
//                 }
//             }

//             i++;
//         }
//     }
//     else
//     {
//         printf("ERROR: Unable to open file for reading.\n");
//     }
//     return i;
// }

// moved to ticket.c
// int saveTickets(Ticket *tickets, int maxArraySize)
// {
//     int i = 0;
//     int j = 0;
//     FILE *fp = NULL;
//     fp = fopen("tickets.txt", "w"); // rewrite to textfile

//     if (fp != NULL)
//     {
//         for (i = 0; i < maxArraySize; i++)
//         {
//             //printf("\n");
//             fprintf(fp, "%d|%d|%d|%s|%d|", tickets[i].uniqueNumTicket,
//                     tickets[i].customerAcctNum_Ticket,
//                     tickets[i].ticketStatusIndicator,
//                     tickets[i].subjectLine,
//                     tickets[i].counter_numOfMessageTicket);
//             for (j = 0; j < tickets[i].counter_numOfMessageTicket; j++)
//             {
//                 fprintf(fp, "%c|%s|%s|", tickets[i].message[j].accountTypeAuthorMessage,
//                         tickets[i].message[j].nameOfGivenUser,
//                         tickets[i].message[j].messageDetails);
//             }
//             fprintf(fp, "\n");
//         }
//         fclose(fp);
//     }
//     else
//     {
//         printf("ERROR: Unable to open file for reading.\n");
//     }

//     return i;
// }

void archiveCloseTicketsForAccount(struct AccountTicketingData *acctAndTicket, Account *relatedTicket)
{
    int i;
    int j;
    //* must check if it is closed and is related to account
    for (i = 0; i < acctAndTicket->TICKET_MAX_SIZE; i++)
    {
        if (acctAndTicket->tickets[i].customerAcctNum_Ticket == relatedTicket->accountNum)
        { // check if related ticket is closed
            if (acctAndTicket->tickets[i].ticketStatusIndicator == 0)
            {
                // archive that

                FILE *fp;
                fp = NULL;
                fp = fopen("tickets_arc.txt", "a");
                if (fp == NULL)
                    printf("ERROR: Can't open tickets_arc file.\n");

                printf("adding %d|%d|%d|%s|%d|\n\n", acctAndTicket->tickets[i].uniqueNumTicket,
                       acctAndTicket->tickets[i].customerAcctNum_Ticket,
                       acctAndTicket->tickets[i].ticketStatusIndicator,
                       acctAndTicket->tickets[i].subjectLine,
                       acctAndTicket->tickets[i].counter_numOfMessageTicket);
                fprintf(fp, "%d|%d|%d|%s|%d|",
                        acctAndTicket->tickets[i].uniqueNumTicket,
                        acctAndTicket->tickets[i].customerAcctNum_Ticket,
                        acctAndTicket->tickets[i].ticketStatusIndicator,
                        acctAndTicket->tickets[i].subjectLine,
                        acctAndTicket->tickets[i].counter_numOfMessageTicket);

                for (j = 0; j < acctAndTicket->tickets[i].counter_numOfMessageTicket; j++)
                {
                    fprintf(fp, "%c|%s|%s|\n",
                            acctAndTicket->tickets[i].message[j].accountTypeAuthorMessage,
                            acctAndTicket->tickets[i].message[j].nameOfGivenUser,
                            acctAndTicket->tickets[i].message[j].messageDetails);
                }

                fclose(fp);
            }
        }
    }
}

void closingTicketsForAccount(struct AccountTicketingData *acctAndTicket, Account *relatedTicket)
{
    int i;
    for (i = 0; i < acctAndTicket->TICKET_MAX_SIZE; i++)
    {
        if (acctAndTicket->tickets[i].customerAcctNum_Ticket == relatedTicket->accountNum)
        {
            acctAndTicket->tickets[i].uniqueNumTicket = 0; // close the ticket for both Actives and Closed ones
        }
    }
}

void archiveRemovedAccount(struct AccountTicketingData *acctAndTicket, Account *relatedAccount)
{
    int i = 0;
    for (i = 0; i < acctAndTicket->ACCOUNT_MAX_SIZE; i++)
    {
        if (acctAndTicket->accounts[i].accountNum == relatedAccount->accountNum)
        {
            // archive that

            FILE *fp;
            fp = NULL;
            fp = fopen("accounts_arc.txt", "a");
            if (fp == NULL)
                printf("ERROR: Can't open accounts_arc.txt file.\n");

            fprintf(fp, "%d~%c~%s~%s~%s~%d~%lf~%s\n",
                    acctAndTicket->accounts[i].accountNum,
                    acctAndTicket->accounts[i].accountType,
                    acctAndTicket->accounts[i].userLogin.nameOfCustomer,
                    acctAndTicket->accounts[i].userLogin.userLoginName,
                    acctAndTicket->accounts[i].userLogin.password,
                    acctAndTicket->accounts[i].demographic.birthYearCustomer,
                    acctAndTicket->accounts[i].demographic.householdIncome,
                    acctAndTicket->accounts[i].demographic.residedCountryName);

            fclose(fp);
        }
    }
}
// this for accountTicketingUI
// int archiveClosedTickets(struct AccountTicketingData *acctAndTicket)
// {
//     int i = 0;
//     int j = 0;
//     int numbOfTicketsArched = 0;
//     for (i = 0; i < acctAndTicket->TICKET_MAX_SIZE; i++)
//     { //* All tickets in closed state should append to tickets_arc.txt
//         if (acctAndTicket->tickets[i].ticketStatusIndicator == 0 && acctAndTicket->tickets[i].uniqueNumTicket != 0)
//         {
//             FILE *fp;
//             fp = NULL;
//             fp = fopen("tickets_arc.txt", "a");
//             if (fp == NULL)
//                 printf("ERROR: Can't open tickets_arc file.\n");

//             fprintf(fp, "%d|%d|%d|%s|%d|",
//                     acctAndTicket->tickets[i].uniqueNumTicket,
//                     acctAndTicket->tickets[i].customerAcctNum_Ticket,
//                     acctAndTicket->tickets[i].ticketStatusIndicator,
//                     acctAndTicket->tickets[i].subjectLine,
//                     acctAndTicket->tickets[i].counter_numOfMessageTicket);

//             for (j = 0; j < acctAndTicket->tickets[i].counter_numOfMessageTicket; j++)
//             {
//                 fprintf(fp, "%c|%s|%s|\n",
//                         acctAndTicket->tickets[i].message[j].accountTypeAuthorMessage,
//                         acctAndTicket->tickets[i].message[j].nameOfGivenUser,
//                         acctAndTicket->tickets[i].message[j].messageDetails);
//             }

//             fclose(fp);
//             acctAndTicket->tickets[i].uniqueNumTicket = 0; //empty the closed tickets
//             numbOfTicketsArched++;
//         }
//     }
//     return numbOfTicketsArched;
// }

// moved to account.c
// void viewArchivedAccountStatistics()
// {
//     struct Account accounts[15] = {{0}};
//     int i = 0;
//     //char ch = '\0';
//     FILE *fp = fopen("accounts_arc.txt", "r"); // read

//     if (fp == NULL)

//         printf("ERROR: Unable to open file for reading.\n");

//     while (!feof(fp))
//     {
//         fscanf(fp, "%d~%c~%[^~]~%[^~]~%[^~]~%d~%lf~%30[^\n]",
//                &accounts[i].accountNum,
//                &accounts[i].accountType,
//                accounts[i].userLogin.nameOfCustomer,
//                accounts[i].userLogin.userLoginName,
//                accounts[i].userLogin.password,
//                &accounts[i].demographic.birthYearCustomer,
//                &accounts[i].demographic.householdIncome,
//                accounts[i].demographic.residedCountryName);

//         i++;
//     }
//     fclose(fp);
//     printf("There are %d account(s) currently archived.\n", i - 1);
//     return;
// }

//moved to ticket.c
// void viewArchivedTicketStatus()
// {
//     int i = 0;
//     int j = 0;
//     FILE *fp = NULL;
//     fp = fopen("tickets_arc.txt", "r");
//     struct Ticket bufferTicket;
//     int previousUnique = 0;
//     int numArchivedTickets = 0;
//     int numArchivedMessages = 0;
//     if (fp != NULL)
//     {
//         while (fscanf(fp, "%d|%d|%d|%[^|]|%d|",
//                       &bufferTicket.uniqueNumTicket,
//                       &bufferTicket.customerAcctNum_Ticket,
//                       &bufferTicket.ticketStatusIndicator,
//                       bufferTicket.subjectLine,
//                       &bufferTicket.counter_numOfMessageTicket) != EOF)
//         {

//             if (bufferTicket.uniqueNumTicket != previousUnique)
//             {
//                 numArchivedTickets++;
//                 numArchivedMessages += bufferTicket.counter_numOfMessageTicket;
//                 previousUnique = bufferTicket.uniqueNumTicket;
//             }

//             if (bufferTicket.counter_numOfMessageTicket > MAX_NUMBER_MESSAGE)
//             {
//                 bufferTicket.counter_numOfMessageTicket = MAX_NUMBER_MESSAGE;
//                 for (j = 0; j < bufferTicket.counter_numOfMessageTicket; j++)
//                 {
//                     fscanf(fp, "%c|%[^|]|%[^|]|",
//                            &bufferTicket.message[j].accountTypeAuthorMessage,
//                            bufferTicket.message[j].nameOfGivenUser,
//                            bufferTicket.message[j].messageDetails);
//                 }
//                 fscanf(fp, "%*[^\n]"); // skip to end of line
//             }
//             else
//             {
//                 for (j = 0; j < bufferTicket.counter_numOfMessageTicket; j++)
//                 {
//                     fscanf(fp, "%c|%[^|]|%[^|]|",
//                            &bufferTicket.message[j].accountTypeAuthorMessage,
//                            bufferTicket.message[j].nameOfGivenUser,
//                            bufferTicket.message[j].messageDetails);
//                 }
//             }

//             i++;
//         }
//         fclose(fp);
//         printf("There are %d ticket(s) and a total of %d message(s) archived.\n", numArchivedTickets, numArchivedMessages);
//     }
//     else
//     {
//         printf("ERROR: Unable to open file for reading.\n");
//     }
// }

//moved to ticket.c
// int savingTicketChanges(struct Ticket *tickets, int maxArraySize)
// {
//     int i = 0;
//     int j = 0;
//     int numberOfTicketSaved = 0;
//     FILE *fp = NULL;
//     fp = fopen("tickets.txt", "w"); // rewrite to textfile

//     if (fp != NULL)
//     {
//         for (i = 0; i < maxArraySize; i++)
//         {
//             //printf("\n");
//             if (tickets[i].uniqueNumTicket != 0)
//             {

//                 fprintf(fp, "%d|%d|%d|%s|%d|", tickets[i].uniqueNumTicket,
//                         tickets[i].customerAcctNum_Ticket,
//                         tickets[i].ticketStatusIndicator,
//                         tickets[i].subjectLine,
//                         tickets[i].counter_numOfMessageTicket);
//                 for (j = 0; j < tickets[i].counter_numOfMessageTicket; j++)
//                 {
//                     fprintf(fp, "%c|%s|%s|", tickets[i].message[j].accountTypeAuthorMessage,
//                             tickets[i].message[j].nameOfGivenUser,
//                             tickets[i].message[j].messageDetails);
//                 }
//                 fprintf(fp, "\n");
//                 if (tickets[i].uniqueNumTicket != 0)
//                 {
//                     numberOfTicketSaved++;
//                 }
//             }
//         }
//         fclose(fp);
//     }
//     else
//     {
//         printf("ERROR: Unable to open file for reading.\n");
//     }

//     return numberOfTicketSaved;
// }

// moved to account.c
// int savingAccountChanges(struct Account *accounts, int sizeAccount)
// {
//     int i = 0;
//     int numberOfAccountSaved = 0;
//     FILE *fp = NULL;
//     fp = fopen("accounts.txt", "w"); // rewrite to textfile

//     if (fp != NULL)
//     {
//         for (i = 0; i < sizeAccount; i++)
//         {
//             //printf("\n");
//             if (accounts[i].accountNum != 0)
//             {

//                 fprintf(fp, "%d~%c~%s~%s~%s~%d~%lf~%s\n",
//                         accounts[i].accountNum,
//                         accounts[i].accountType,
//                         accounts[i].userLogin.nameOfCustomer,
//                         accounts[i].userLogin.userLoginName,
//                         accounts[i].userLogin.password,
//                         accounts[i].demographic.birthYearCustomer,
//                         accounts[i].demographic.householdIncome,
//                         accounts[i].demographic.residedCountryName);
//                 // fprintf(fp, "\n");
//                 if (accounts[i].accountNum != 0)
//                 {
//                     numberOfAccountSaved++;
//                 }
//             }
//         }
//         fclose(fp);
//     }
//     else
//     {
//         printf("ERROR: Unable to open file for reading.\n");
//     }

//     return numberOfAccountSaved;
// }
