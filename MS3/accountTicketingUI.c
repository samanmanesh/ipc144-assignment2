// ===================================================================================
//  Assignment: 2
//  Milestone : 3
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
        printf("0) Logout\n");
        printf("\n");
        int ticketNum = 0;
        int ticketNumber = 0;
        int j;
        int i = 0;
        int fund = 0;
        printf("Selection: ");
        choice = getIntFromRange(0, 10);
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
                    // For removing the related ticket if its active
                    for (i = 0; i < acctAndTicket->TICKET_MAX_SIZE; i++)
                    {
                        if ((acctAndTicket->tickets[i].customerAcctNum_Ticket == acctAndTicket->accounts[index].accountNum) && (acctAndTicket->tickets[i].ticketStatusIndicator == 1))
                        {
                           
                            // removing the account number which stored in tickets.customerAcctNum_Ticket //? I doubt I should assign this to 0 too or not
                            acctAndTicket->tickets[i].customerAcctNum_Ticket = 0;

                            // removing the ticketnumber which stored in tickets.uniqueNumTicket
                            acctAndTicket->tickets[i].uniqueNumTicket = 0;

                            
                        }
                    }
                    // remove account
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
                // For showing each message
                // for (i = 0; i < acctAndTicket->TICKET_MAX_SIZE; i++)
                // {
                //     if (acctAndTicket->tickets[i].uniqueNumTicket == 0)
                //     {
                //         break;
                //     }
                //     //Just show the account that are Closed
                //     if (acctAndTicket->tickets[i].ticketStatusIndicator == 0)
                //         displayOneTicketRecordAgent(&acctAndTicket->tickets[i]);
                // }
                // For showing each message
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

void displayOneTicketRecordAgent(const Ticket *ticket)
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

    printf("%06d %-5d %-15s %-6s %-30s %5d\n", ticket->uniqueNumTicket, ticket->customerAcctNum_Ticket, ticket->message->nameOfGivenUser, status, ticket->subjectLine, ticket->counter_numOfMessageTicket);
}
