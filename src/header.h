#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


struct Date
{
    int month, day, year;
};

// all fields for each record of an account
struct Record
{
    int id;
    int userId;
    char name[100];
    char country[100];
    char phone[11];
    char accountType[10];
    long long int accountNbr;
    double amount;
    struct Date deposit;
    struct Date withdraw;
};

struct User
{
    int id;
    char name[50];
    char password[50];
};

// authentication functions
void loginMenu(char a[50], char pass[50]);
void signUpMenu(char a[50], char pass[50]);
const char *getPassword(struct User *u);

// system functions
void mainMenu(struct User u);
void createNewAcc(struct User u);
void transferAccount(struct User u, long long int accountNum);
void checkDetailOfAccount(struct User u, long long int accountID);
void updateAccountInfo(struct User u, long long int accountNum, int choice);
void makeTransaction(struct User u, long long int accountNum, int choice);
void removeAccount(struct  User u, long long int accountNum);
void checkAllAccounts(struct User u);



//secondary functions
bool isNamePresent(char *name);
bool isPresent(char array[100][100], char* str);
bool isAccountPresent(long long int num, struct User u);
bool isAccountPresentAny(long long int num, struct User u);
int getUserId(char *name);
int getRecordId(char *name);
bool checkUsers();
bool checkRecords();
bool is_valid_number();
