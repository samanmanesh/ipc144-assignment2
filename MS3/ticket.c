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
#include "ticket.h"
#include "account.h"
#include "commonHelpers.h"
#include <string.h>

// update Ticket
void updateTicket(Ticket *ticket, const struct Account account)
{
    int choice = 0;
    char option, closingMessageChoice;
    do
    {
        printf("----------------------------------------\n");
        printf("Ticket %06d - Update Options\n", ticket->uniqueNumTicket);
        printf("----------------------------------------\n");
        printf("Status  : %s\n", ticket->ticketStatusIndicator == 1 ? "ACTIVE" : "CLOSED");
        printf("Subject : %s\n", ticket->subjectLine);
        printf("----------------------------------------\n");
        printf("1) Modify the subject\n");
        printf("2) Add a message\n");
        printf("3) Close ticket\n");
        printf("0) Done\n");
        printf("Selection: ");
        choice = getIntFromRange(0, 3);
        switch (choice)
        {
        case 1:
            printf("\n");
            printf("Enter the revised ticket SUBJECT (30 chars. maximum): ");
            getCString(ticket->subjectLine, 1, 30);
            putchar('\n');
            break;
        case 2:
            printf("\n");
            if (ticket->counter_numOfMessageTicket + 1 > MAX_NUMBER_MESSAGE)
            {
                printf("ERROR: Message limit has been reached, call ITS Support!\n");
                printf("\n");
                break;
            }
            addAMessage(ticket, account);

            break;
        // Close Ticket
        case 3:
            printf("\n");
            if (ticket->ticketStatusIndicator == 1)
            {
                printf("Are you sure you CLOSE this ticket? ([Y]es|[N]o): ");
                option = getCharOption("YN");
                putchar('\n');
                if (option == 'Y')
                {
                    ticket->ticketStatusIndicator = 0; // Close the ticket
                    choice = 0;                        // to return to customer menu
                    if (ticket->counter_numOfMessageTicket == MAX_NUMBER_MESSAGE)
                    {
                        printf("*** Ticket closed! ***\n\n");
                    }

                    if (ticket->counter_numOfMessageTicket != MAX_NUMBER_MESSAGE)
                    {
                        printf("Do you want to leave a closing message? ([Y]es|[N]o): ");
                        closingMessageChoice = getCharOption("YN");
                        if (closingMessageChoice == 'Y')
                        {
                            putchar('\n');
                            addAMessage(ticket, account);
                            printf("*** Ticket closed! ***\n\n");
                        }
                        else
                            printf("\n*** Ticket closed! ***\n\n");
                    }
                }
                else
                    ticket->ticketStatusIndicator = 1; // Open the ticket
            }

            //pauseExecution();
            break;
        case 0:
            putchar('\n');
            break;

        default:
            break;
        }
    } while (choice != 0);
}

void addAMessage(Ticket *ticket, const struct Account account)
{

    // Find spot to put new message
    int i; // index of empty spot
    for (i = 0; i < MAX_NUMBER_MESSAGE; i++)
    {
        if (ticket->message[i].messageDetails[0] == '\0')
        {
            break;
        }
    }
    printf("Enter the ticket message details (150 chars. maximum). Press the ENTER key to\n");
    printf("submit:\n");
    getCString(ticket->message[i].messageDetails, 1, 150);
    putchar('\n');
    // Assigning the Name of customer
    strncpy(ticket->message[i].nameOfGivenUser, account.userLogin.nameOfCustomer, 31);
    // Assigning the type of account which must be customer
    ticket->message[i].accountTypeAuthorMessage = account.accountType;
    // Each time a massage is added, number of message ticket is increased by one
    ticket->counter_numOfMessageTicket++;
}

void updateTicketAgent(Ticket *ticket, const struct Account account)
{
    int choice = 0;
    do
    {
        printf("----------------------------------------\n");
        printf("Ticket %06d - Update Options\n", ticket->uniqueNumTicket);
        printf("----------------------------------------\n");
        printf("Status  : %s\n", ticket->ticketStatusIndicator == 1 ? "ACTIVE" : "CLOSED");
        printf("Subject : %s\n", ticket->subjectLine);
        printf("Acct#   : %d\n", ticket->customerAcctNum_Ticket);
        printf("Customer: %s\n", ticket->message->nameOfGivenUser);
        printf("----------------------------------------\n");
        printf("1) Add a message\n");
        printf("2) Close ticket\n");
        printf("3) Re-open ticket\n");
        printf("0) Done\n");
        printf("Selection: ");
        choice = getIntFromRange(0, 3);
        // putchar('\n');
        switch (choice)
        {
        // Add a message
        case 1:
            
            if (ticket->counter_numOfMessageTicket + 1 > MAX_NUMBER_MESSAGE)
            {
                printf("\n");
                printf("ERROR: Message limit has been reached, call ITS Support!\n");
                printf("\n");
                break;
            }
            if (ticket->ticketStatusIndicator == 0)
            {
                printf("\n");
                printf("ERROR: Ticket is closed - new messages are not permitted.\n");
                printf("\n");
                break;
            }
            else
            {
                printf("\n");
                addAMessage(ticket, account);
            }

            break;
        // Close ticket
        case 2:

            if (ticket->ticketStatusIndicator == 0)
            {
                printf("\n");
                printf("ERROR: Ticket is already closed!\n");
                printf("\n");
            }
            else
            {   
                printf("\n");
                printf("Are you sure you CLOSE this ticket? ([Y]es|[N]o): ");
                if (getCharOption("YN") == 'Y')
                {
                    putchar('\n');
                    ticket->ticketStatusIndicator = 0; // Close the ticket

                    if (ticket->counter_numOfMessageTicket == MAX_NUMBER_MESSAGE)
                    {
                        printf("*** Ticket closed! ***\n\n");
                    }

                    if (ticket->counter_numOfMessageTicket != MAX_NUMBER_MESSAGE)
                    {
                        printf("Do you want to leave a closing message? ([Y]es|[N]o): ");
                        ;
                        if (getCharOption("YN") == 'Y')
                        {
                            putchar('\n');
                            addAMessage(ticket, account);
                            printf("*** Ticket closed! ***\n\n");
                        }
                        else
                        {
                            putchar('\n');
                            printf("*** Ticket closed! ***\n\n");
                        }
                    }
                }
                else
                {
                    putchar('\n');
                    ticket->ticketStatusIndicator = 1; // Open the ticket
                }

                break;
            // Re-open ticket
            case 3:

                if (ticket->ticketStatusIndicator == 1)
                {
                    printf("\n");
                    printf("ERROR: Ticket is already active!\n");
                    printf("\n");
                }
                else
                {
                    printf("\n");
                    printf("Are you sure you RE-OPEN this closed ticket? ([Y]es|[N]o): ");
                    if (getCharOption("YN") == 'Y')
                    {
                        putchar('\n');
                        ticket->ticketStatusIndicator = 1; // Active the ticket
                        printf("*** Ticket re-opened! ***\n");
                        printf("\n");
                    }
                    else
                    {
                        putchar('\n');
                        ticket->ticketStatusIndicator = 0; // Stay closed
                    }
                    break;
                // Done
                case 0:

                    break;

                default:
                    break;
                }
            }
        }

    } while (choice != 0);
}