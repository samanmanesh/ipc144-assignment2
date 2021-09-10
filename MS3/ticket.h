// ===================================================================================
//  Assignment: 2
//  Milestone : 3
// ===================================================================================
//  Student Name  : Mohammadhossein Sobhanmanesh
//  Student ID    : 
//  Student Email : msobhanmanesh@myseneca.ca
//  Course Section: IPC-NGG
// ===================================================================================
#ifndef TICKET_H_
#define TICKET_H_

#define MAX_NUMBER_MESSAGE 20
typedef struct Message
{
    char accountTypeAuthorMessage;
    char nameOfGivenUser[31];
    char messageDetails[151];

} Message;

typedef struct Ticket
{
    int uniqueNumTicket;
    int customerAcctNum_Ticket;
    int ticketStatusIndicator;
    char subjectLine[31];
    int counter_numOfMessageTicket;
    Message message[MAX_NUMBER_MESSAGE];
} Ticket;

//Functions prototypes
void updateTicket(Ticket *ticket, const struct Account account);

void updateTicketAgent(Ticket *ticket, const struct Account account);

void addAMessage(Ticket *ticket, const struct Account account);

#endif
