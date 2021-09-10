// ===================================================================================
//  Assignment: 2
//  Milestone : 2
// ===================================================================================
//  Student Name  : Mohammadhossein Sobhanmanesh
//  Student ID    : 
//  Student Email : msobhanmanesh@myseneca.ca
//  Course Section: IPC-NGG
// ===================================================================================
#include <stdio.h>
#include "commonHelpers.h"
#include "account.h"
#include "accountTicketingUI.h"

// Functions

void getAccount(Account *account)
{
    //printf("\n");
    printf("Account Data: New Record\n");
    printf("----------------------------------------\n");
    printf("Enter the account number: ");
    account->accountNum = getInteger();
    putchar('\n');
    printf("Enter the account type (A=Agent | C=Customer): ");
    account->accountType = getCharOption("AC");

    printf("\n");
}

void getUserLogin(UserLogin *userLogin)
{
    printf("User Login Data Input\n");
    printf("----------------------------------------\n");

    int i;
    int numOfSpace;
    do
    {
        numOfSpace = 0;
        printf("Enter user login (10 chars max): ");
        getCString(userLogin->userLoginName, 1, 10);

        for (i = 0; i < 10; i++)
        {
            if (userLogin->userLoginName[i] == ' ')
            {
                printf("ERROR:  The user login must NOT contain whitespace characters.\n");
                numOfSpace++;
            }
        }

    } while (numOfSpace != 0);

    printf("Enter the display name (30 chars max): ");
    getCString(userLogin->nameOfCustomer, 1, 30);

    printf("Enter the password (must be 8 chars in length): ");
    //getCString(userLogin->password, 8, 8);
    getAndValidatePassword(userLogin);
   
    printf("\n");
}

void getDemographic(Demographic *demographic)
{
    printf("Demographic Data Input\n");
    printf("----------------------------------------\n");
    printf("Enter birth year (current age must be between 18 and 110): ");
    demographic->birthYearCustomer = getIntFromRange(1911, 2003);

    printf("Enter the household Income: $");
    demographic->householdIncome = getPositiveDouble();

    printf("Enter the country (30 chars max.): ");
    getCString(demographic->residedCountryName, 1, 30);
    lowerToUpperConverter(demographic);
    
    printf("\n");
}

void updateAccount(Account *account)
{
    int choice = 0;
    // int index;
    do
    {
        printf("Account: %d - Update Options\n", account->accountNum);
        printf("----------------------------------------\n");
        printf("1) Update account type (current value: %c)\n", account->accountType);
        printf("2) Login\n");
        printf("3) Demographics\n");
        printf("0) Done\n");
        printf("Selection: ");
        choice = getIntFromRange(0, 3);
        putchar('\n');
        switch (choice)
        {
        case 1:
            printf("Enter the account type (A=Agent | C=Customer): ");
            account->accountType = getCharOption("AC");
            putchar('\n');
            break;
        case 2:

            updateUserLogin(&account->userLogin);
            // printf("User Login: %s - Update Options\n", account->userLogin.nameOfCustomer);

            break;
        case 3:
            updateDemographic(&account->demographic);

            break;

        default:
            break;
        }
    } while (choice != 0);
}

void updateUserLogin(UserLogin *userlogin)
{
    int choice;
    do
    {

        printf("User Login: %s - Update Options\n", userlogin->userLoginName);
        printf("----------------------------------------\n");
        printf("1) Display name (current value: %s)\n", userlogin->nameOfCustomer);
        printf("2) Password\n");
        printf("0) Done\n");
        printf("Selection: ");
        choice = getIntFromRange(0, 2);
        putchar('\n');
        switch (choice)
        {
        case 1:

            printf("Enter the display name (30 chars max): ");
            getCString(userlogin->nameOfCustomer, 1, 30);
            putchar('\n');
            break;
        case 2:

            printf("Enter the password (must be 8 chars in length): ");
            //getCString(userlogin->password, 8, 8);
            getAndValidatePassword(userlogin);
            putchar('\n');
            break;
        default:
            break;
        }

    } while (choice != 0);
}

void updateDemographic(Demographic *demographic)
{
    int choice;
    do
    {
        printf("Demographic Update Options\n");
        printf("----------------------------------------\n");
        printf("1) Household Income (current value: $%.2lf)\n", demographic->householdIncome);
        printf("2) Country (current value: %s)\n", demographic->residedCountryName);
        printf("0) Done\n");
        printf("Selection: ");
        choice = getIntFromRange(0, 2);
        putchar('\n');
        switch (choice)
        {
        case 1:
            //printf("\n");
            printf("Enter the household Income: $");
            demographic->householdIncome = getPositiveDouble();
            putchar('\n');
            break;
        case 2:
            printf("Enter the country (30 chars max.): ");
            getCString(demographic->residedCountryName, 1, 30);
            lowerToUpperConverter(demographic);
            putchar('\n');
            break;

        default:
            break;
        }
    } while (choice != 0);
}


void getAndValidatePassword(UserLogin *userLogin)
{
     //printf("Enter the password (must be 8 chars in length): ");
    int numUpper;
    int numLower;
    int numDigit;
    int numSymbol;
    int i;
    do
    {
        getCString(userLogin->password, 8, 8); 

        numUpper = 0;
        numLower = 0;
        numDigit = 0;
        numSymbol = 0;

        for (i = 0; i < 9; i++)
        {
            char ch = userLogin->password[i];

            if (ch == '\0')
                break;
            if (ch >= 'A' && ch <= 'Z') // uppercase
            {

                numUpper++;
            }
            else if (ch >= 'a' && ch <= 'z') // lowercase
            {

                numLower++;
            }
            else if (ch >= '0' && ch <= '9') // digits
            {

                numDigit++;
            }
            else
            {
                numSymbol++; //anything else
            }
        }

        if (numUpper != 2 || numDigit != 2 || numSymbol != 2 || numLower != 2)
        {
            printf("SECURITY: Password must contain 2 of each:\n");
            printf("          Digit: 0-9\n");
            printf("          UPPERCASE character\n");
            printf("          lowercase character\n");
            printf("          symbol character: !@#$%%^&*\n");
            printf("Enter the password (must be 8 chars in length): ");
        }
    } while (numUpper != 2 || numDigit != 2 || numSymbol != 2 || numLower != 2);
}

void lowerToUpperConverter(Demographic *demographic)
{
    int i;
    for (i = 0; demographic->residedCountryName[i] != '\0'; i++)
    {

        if (demographic->residedCountryName[i] >= 'a' &&
            demographic->residedCountryName[i] <= 'z')
        {
            demographic->residedCountryName[i] = demographic->residedCountryName[i] - 32;
        }
    }
}
