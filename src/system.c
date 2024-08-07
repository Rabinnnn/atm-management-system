#include "header.h"
#include <unistd.h>  // For sleep()

const char *RECORDS = "./data/records.txt";
const char *USER = "./data/users.txt";


// int getAccountFromFile(FILE *ptr, char name[50], struct Record *r) {
//     return fscanf(ptr, "%s %d", name, &r->accountNbr) == 2;
// }

int getAccountFromFile(FILE *ptr, char name[50], struct Record *r)
{
    return fscanf(ptr, "%d %d %s %d %d/%d/%d %s %d %lf %s",
                  &r->id,
		  &r->userId,
		  name,
                  &r->accountNbr,
                  &r->deposit.month,
                  &r->deposit.day,
                  &r->deposit.year,
                  r->country,
                  &r->phone,
                  &r->amount,
                  r->accountType) != EOF;
}



int getAccountFromUser(FILE *ptr, char name[50], struct User *r)
{
/*int ret =*/return  fscanf(ptr, "%d %s",
                  &r->id,
		          name);
              //  printf("RET: %d\n", ret);
              //  return ret;
}

void saveAccountToAccountFile(FILE *ptr, struct User u, struct Record r)
{
    fprintf(ptr, "%d %d %s %s %d %d/%d/%d %s %d %.2lf %s\n\n",
            r.id,
	        u.id,
	        u.name,
            u.password,
            r.accountNbr,
            r.deposit.month,
            r.deposit.day,
            r.deposit.year,
            r.country,
            r.phone,
            r.amount,
            r.accountType);
}

// void saveAccountToLoginFile(FILE *ptr, struct User u, struct User r)
// {
//     fprintf(ptr, "%d %s %s\n\n",
//             r.id,
// 	        u.name,
//             u.password);
// }

void stayOrReturn(int notGood, void f(struct User u), struct User u)
{
    int option;
    if (notGood == 0)
    {
        system("clear");
        printf("\n✖ Record not found!!\n");
    invalid:
        printf("\nEnter 0 to try again, 1 to return to main menu and 2 to exit:");
        scanf("%d", &option);
        if (option == 0)
            f(u);
        else if (option == 1)
            mainMenu(u);
        else if (option == 2)
            exit(0);
        else
        {
            printf("Insert a valid operation!\n");
            goto invalid;
        }
    }
    else
    {
        printf("\nEnter 1 to go to the main menu and 0 to exit:");
        scanf("%d", &option);
    }
    if (option == 1)
    {
        system("clear");
        mainMenu(u);
    }
    else
    {
        system("clear");
        exit(1);
    }
}

void success(struct User u)
{
    int option;
    printf("\n✔ Success!\n\n");
invalid:
    printf("Enter 1 to go to the main menu and 0 to exit!\n");
    scanf("%d", &option);
    system("clear");
    if (option == 1)
    {
        mainMenu(u);
    }
    else if (option == 0)
    {
        exit(1);
    }
    else
    {
        printf("Insert a valid operation!\n");
        goto invalid;
    }
}

void createNewAcc(struct User u)
{
    struct Record r;
    struct Record cr;
    char userName[50];
    FILE *pf = fopen(RECORDS, "a+");
    if (pf == NULL) {
        printf("Error opening file.\n");
        return;
    }
    int ind = 0;
  
noAccount:
    system("clear");
    printf("\t\t\t===== New record =====\n");
date:
    printf("\nEnter today's date(mm/dd/yyyy):");
    scanf("%d/%d/%d", &r.deposit.month, &r.deposit.day, &r.deposit.year);
    if(r.deposit.month <= 0 || r.deposit.month > 12 ||
        r.deposit.day <= 0 || r.deposit.day > 31 ||
        r.deposit.year < 1900 || r.deposit.year > 3000){
        printf("Invalid date. Usage Example: 8/8/2024\n");
         sleep(2);
        goto date;
    }
    
   /* printf("\nEnter username:");
    scanf("%49s", u.name);

    while (getAccountFromFile(pf, userName, &cr) != EOF)
    {
        // printf("file:%s\n", u.name);
        // printf("user:%s\n", userName);
   
        if (strcmp(userName, u.name) == 0)
        {       
                printf("✖ This name has already been taken!\n\n");
                sleep(3);  // Sleep for 2 seconds
                goto noAccount;      
        }
      
      
    } */
    // printf("\nEnter password:");
    // scanf("%49s", u.password);
accountNo:
    printf("\nEnter the account number:");
    scanf("%d", &r.accountNbr);
    if (r.accountNbr <= 0)
    {
        printf("Invalid account number. Use only positive numbers!\n");
         sleep(2);
        goto accountNo;
    }
  
     while (getAccountFromFile(pf, userName, &cr))
    {
        if (strcmp(userName, u.name) == 0 && cr.accountNbr == r.accountNbr)
        {
            printf("\n✖ This Account already exists for this user\n\n");
            goto noAccount;
        }
        ind++;
    }
    r.id = ind;
    printf("\nEnter the country:");
    scanf("%s", r.country);
phone:
    printf("\nEnter the phone number:");
    scanf("%d", &r.phone);
    if(r.phone == 0){
        printf("Invalid phone number.\n");
         sleep(2);
        goto phone;
    }
amount:
    printf("\nEnter amount to deposit: $");
    scanf("%lf", &r.amount);
    if(r.amount <= 0 || r.amount > 999999){
        printf("\nInvalid amount! You can only deposit in the range 1 - 999999\n");
         sleep(2);
        goto amount;
    }
accType:
    printf("\nChoose the type of account:\n\t-> saving\n\t-> current\n\t-> fixed01(for 1 year)\n\t-> fixed02(for 2 years)\n\t-> fixed03(for 3 years)\n\n\tEnter your choice:");
    scanf("%s", r.accountType);
     if (strcmp(r.accountType, "current") != 0 &&
        strcmp(r.accountType, "saving") != 0 &&
        strcmp(r.accountType, "fixed01") != 0 &&
        strcmp(r.accountType, "fixed02") != 0 &&
        strcmp(r.accountType, "fixed03") != 0){
        printf("\nPlease choose and enter one of the listed options.\n");
         sleep(2);
        goto accType;
    }

    saveAccountToAccountFile(pf, u, r);

    fclose(pf);
    success(u);
}

// void signUp(struct User u)
// {
//     struct User r;
//     struct User cr;
//     char userName[50];

//         FILE *pg = fopen(USER, "a+");
//           if (pg == NULL) {
//              printf("Error opening file.\n");
//              return;
//           }
//     noUser:
//     system("clear");
//     printf("\t\t\t===== Sign Up =====\n");

//     printf("\nEnter username:");
//     scanf("%49s", u.name);
//     // while (getAccountFromUser(pg, userName, &cr) != EOF)
//     // {
       
//     //     if (strcmp(userName, u.name) == 0)
//     //     {
//     //             printf("✖ This name has already been taken!\n\n");
//     //             sleep(2);  // Sleep for 2 seconds
//     //             goto noUser;     
           
//     //     }
       
//     // } 
    
//     printf("\nEnter password:");
//     scanf("%49s", u.password);

//     saveAccountToLoginFile(pg, u, r);
//     fclose(pg);
//     success(u);

// }

void checkAllAccounts(struct User u)
{
    char userName[100];
    struct Record r;

    FILE *pf = fopen(RECORDS, "r");

    system("clear");
    printf("\t\t====== All accounts from user, %s =====\n\n", u.name);
    while (getAccountFromFile(pf, userName, &r))
    {
        if (strcmp(userName, u.name) == 0)
        {
            printf("_____________________\n");
            printf("\nAccount number:%d\nDeposit Date:%d/%d/%d \ncountry:%s \nPhone number:%d \nAmount deposited: $%.2f \nType Of Account:%s\n",
                   r.accountNbr,
                   r.deposit.day,
                   r.deposit.month,
                   r.deposit.year,
                   r.country,
                   r.phone,
                   r.amount,
                   r.accountType);
        }
    }
    fclose(pf);
    success(u);
}


int getUserId(char *name){
    FILE *pf = fopen("./data/users.txt", "r+");

    char id[5];
    struct User temp;
    while(fscanf(pf, "%s %s %s", id, temp.name, temp.password) != EOF){
        if(strcmp(temp.name, name) == 0){
            return atoi(id);
        }
    }

    return -1;
}