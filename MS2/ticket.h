// ===================================================================================
//  Assignment: 2
//  Milestone : 2
// ===================================================================================
//  Student Name  : Mohammadhossein Sobhanmanesh
//  Student ID    : 
//  Student Email : msobhanmanesh@myseneca.ca
//  Course Section: IPC-NGG
// ===================================================================================
#ifndef TICKET_H_
#define TICKET_H_

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
    Message message[20];
} Ticket;

#endif
