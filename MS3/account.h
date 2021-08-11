// ===================================================================================
//  Assignment: 2
//  Milestone : 3
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

// Functions Prototypes

// Ask for entering and getting account number, account type 
void getAccount(Account *account);

// Ask for entering and getting name of customer, user login name and password
void getUserLogin(UserLogin *userLogin);

// Ask for entering and getting birth year of customer, household income and country name
void getDemographic(Demographic *demographic);

// Updating Account 
void updateAccount(Account *account);

// Updating UserLogin
void updateUserLogin(UserLogin *userlogin);

// Updating Demographic
void updateDemographic(Demographic *demographic);

// Get and validate password for having 2 of each 
void getAndValidatePassword(UserLogin *userLogin);

// Convert lowe letters to Upper letters
void lowerToUpperConverter(Demographic *demographic);
#endif // !ACCOUNT_H_