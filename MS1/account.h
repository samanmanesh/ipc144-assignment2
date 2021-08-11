// ===================================================================================
//  Assignment: 2
//  Milestone : 1
// ===================================================================================
//  Student Name  : Mohammadhossein Sobhanmanesh
//  Student ID    : 116523200
//  Student Email : msobhanmanesh@myseneca.ca
//  Course Section: IPC-NGG
// ===================================================================================
#ifndef ACCOUNT_H_
#define ACCOUNT_H_

typedef struct Demographic
{
    int birthYearCustomer;
    double householdIncome;
    char residedCountryName[31];
} Demographic;

typedef struct UserLogin
{
    char nameOfCustomer[31];
    char userLoginName[11];
    char password[9];
} UserLogin;

typedef struct Account
{
    int accountNum;
    char accountType;
    UserLogin userLogin;
    Demographic demographic;
} Account;

//Functions prototypes

// Ask for entering and getting account number, account type 
void getAccount(Account *account);

// Ask for entering and getting name of customer, user login name and password
void getUserLogin(UserLogin *userLogin);

// Ask for entering and getting birth year of customer, household income and country name
void getDemographic(Demographic *demographic);

//
void updateAccount(Account *account);

//
void updateUserLogin(UserLogin *userlogin);

//
void updateDemographic(Demographic *demographic);

//
void getAndValidatePassword(UserLogin *userLogin);
//
void lowerToUpperConverter(Demographic *demographic);
#endif // !ACCOUNT_H_