// ===================================================================================
//  Assignment: 2
//  Milestone : 3
// ===================================================================================
//  Student Name  : Mohammadhossein Sobhanmanesh
//  Student ID    : 
//  Student Email : msobhanmanesh@myseneca.ca
//  Course Section: IPC-NGG
// ===================================================================================
#include <stdio.h>
#include "commonHelpers.h"
#include <time.h>

/* function definitions*/
/*------------------------------------*/

// Uses the time.h library to obtain current year information
// Get the current 4-digit year from the systemint
int currentYear(void)
{
    time_t currentTime = time(NULL);
    return localtime(&currentTime)->tm_year + 1900;
}

// Empty the standard input buffer
void clearStanadardInputBuffer(void)
{
    while (getchar() != '\n')
    {
        ; // On purpose: do nothing
    }
}
// Get Integer function
int getInteger(void)
{
    char newLine = 'x';
    int value = 0;
    do
    {
        scanf("%d%c", &value, &newLine);
        if (newLine != '\n')
        {
            clearStanadardInputBuffer();
            printf("ERROR: Value must be an integer: ");
        }

    } while (newLine != '\n');
    return value;
}
//Get Positive Integer
int getPositiveInteger(void)
{
    char newLine = 'x';
    int value = 0;
    do
    {
        scanf("%d%c", &value, &newLine);
        if (value <= 0 || newLine != '\n')
        {
            clearStanadardInputBuffer(); //??
            printf("ERROR: Value must be a positive integer greater than zero: ");
        }

    } while (value <= 0 || newLine != '\n');
    return value;
}
// Get Double
double getDouble(void)
{
    char newLine = 'x';
    double value = 0.0;
    do
    {
        scanf("%lf%c", &value, &newLine);
        if (newLine != '\n')
        {
            clearStanadardInputBuffer();
            printf("ERROR: Value must be a double floating-point number: ");
        }

    } while (newLine != '\n');
    return value;
}
//Get Positive Double
double getPositiveDouble(void)
{
    char newLine = 'x';
    double value = 0.0;
    do
    {
        scanf("%lf%c", &value, &newLine);
        if (newLine != '\n')
        {
            clearStanadardInputBuffer();
            printf("ERROR: Value must be a double floating-point number: ");
        }
        if (value <= 0.0)
        {
            
            printf("ERROR: Value must be a positive double floating-point number: ");
        }

    } while (value <= 0 || newLine != '\n');
    return value;
}





//Get Int From Range
int getIntFromRange(int min, int max)
{
    // char newLine = 'x';
    int value = 0;
    do
    {   
    
        value = getInteger();
        //scanf("%d%c", &value, &newLine);   
            if (value > max || value < min )
            {   
                
                printf("ERROR: Value must be between %d and %d inclusive: ", min, max);
            }
            
    } while (value > max || value < min );
    return value;
}


char getCharOption(char validChars[])
{
    int sizeArray = 10;
    char inputChar[sizeArray];
    int isValid = 0; //false
    while (isValid == 0)
    {
        scanf("%s", inputChar);
        int i = 0;
        while (validChars[i] != '\0')
        {
            if (validChars[i] == inputChar[0])
                isValid = 1;
            i++;
        }
        if (inputChar[1] != '\0')
            isValid = 0;
        if (isValid == 0)
        {
            clearStanadardInputBuffer();
            printf("ERROR: Character must be one of [%s]: ", validChars);
        }
    }
    clearStanadardInputBuffer();
    return inputChar[0];
}

void copy(char *input, char *cStringValue)
{
    int i = 0;
    while (cStringValue[i] != 0)
    {
        input[i] = cStringValue[i];
        i++;
    }
    input[i] = 0;
}

//get c string
void getCString(char *input, int min, int max)
{
    // clearStanadardInputBuffer();
    //char newLine = 'x';
    char cstringValue[100] = "\0";
    int len = 0;
    int i = 0;
    //int isValid = 0; //false
    int check=0;
    do
    {   
    
        if (check == 1)
        {
            clearStanadardInputBuffer();
        }
        
        scanf("%[^\n]", cstringValue);
        check = 1;
        i = 1;
        while (cstringValue[i] != '\0')
        {
            i++;
            len = i;
        }
        
        if (min == max && len != min )
        {
             
            printf("ERROR: String length must be exactly %d chars: ", max);
            // if(newLine != '\n')
            //clearStanadardInputBuffer();
            check = 1;
        }
        else if (len < min )
        {   
            //clearStanadardInputBuffer();
            printf("ERROR: String length must be between %d and %d chars: ",
                   min, max);
                check = 1;
        }
        else if (len > max )
        {   
            //clearStanadardInputBuffer();
            printf("ERROR: String length must be no more than %d chars: ", max);
            check = 1;
        }
  
    } while (len < min || len > max);
    clearStanadardInputBuffer();
    copy(input, cstringValue);
}
