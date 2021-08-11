// ===================================================================================
//  Assignment: 2 
//  Milestone : 3
// ===================================================================================
//  Student Name  : Mohammadhossein Sobhanmanesh
//  Student ID    : 116523200
//  Student Email : msobhanmanesh@myseneca.ca
//  Course Section: IPC-NGG
// ===================================================================================
#ifndef COMMON_HELPERS_H_
#define COMMON_HELPERS_H_

// functionprototypes
/*-------------------------------------------*/

// Get the current 4-digit yearfrom the system
int currentYear(void);

// Empty the standard input buffer
void clearStanadardInputBuffer(void);

// Get Integer function
int getInteger(void);

//Get Positive Integer
int getPositiveInteger(void);

// Get Double
double getDouble(void);

//Get Positive Double
double getPositiveDouble(void);

// Get Int From Range/
int getIntFromRange(int min, int max);

// Get Character
char getCharOption(char validChars[]);

//get c string
void getCString(char *input, int min, int max);

//
void copy(char *input, char *cStringValue);

#endif // !COMMON_HELPERS_H_SafeguardUnique Name: ACCOUNT_H_
