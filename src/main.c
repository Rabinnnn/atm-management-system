#include "header.h"
#include <unistd.h>

void mainMenu(struct User u)
{
    int option;
    long long int accountNum;
   
   int choice;
    system("clear");
    printf("\n\n\t\t======= ATM MANAGEMENT SYSTEM =======\n\n");
    printf("\n\t\t-->> Feel free to choose one of the options below <<--\n");
    printf("\n\t\t[1]- Create a new account\n");
    printf("\n\t\t[2]- Update account information\n");
    printf("\n\t\t[3]- Check accounts\n");
    printf("\n\t\t[4]- Check list of all owned account\n");
    printf("\n\t\t[5]- Make Transaction\n");
    printf("\n\t\t[6]- Remove existing account\n");
    printf("\n\t\t[7]- Transfer ownership\n");
    printf("\n\t\t[8]- Check account balance\n");
    printf("\n\t\t[9]- Exit\n");
    scanf("%d", &option);

    switch (option)
    {
    case 1:
        createNewAcc(u);
        
        break;
  
    case 2:
        // Update account information function
        clearInputBuffer();
        case2Account:
        printf("\nPlease enter the account number:");
        char doen[20]; 
            if (fgets(doen, sizeof(doen), stdin) != NULL) {
                // Remove the newline character if present
                size_t len = strlen(doen);
                if (len > 0 && doen[len-1] == '\n') {
                    doen[len-1] = '\0';
                }
            }
            if ((strlen(doen) < 1 ) || (strlen(doen) > 18)){
                printf("\nInvalid account number!\n");
                goto case2Account;
            }
            
            if(!is_valid_number(doen)){
                printf("\nInvalid account number!\n");
                goto case2Account;
            }
            
            // Convert to long long int
            accountNum = strtoll(doen, NULL, 10);

        
        //printf("Please enter the account number:");
       // scanf("%lld", &accountNum);
       // while (getchar() != '\n');
        if (!isAccountPresent(accountNum, u)){
            system("clear");
            printf("This account does not exist!");
            sleep(2);
            mainMenu(u);
        }
        clearInputBuffer();
        accountUpdate:
        printf("\nWhich field would you like to change?\n1-> phone number\n2-> country\n");
              
        char change[3]; 
            if (fgets(change, sizeof(change), stdin) != NULL) {
                // Remove the newline character if present
                size_t len = strlen(change);
                if (len > 0 && change[len-1] == '\n') {
                    change[len-1] = '\0';
                }
            }
            if ((strlen(change) != 1 )){
                printf("\nInvalid option!");
                goto accountUpdate;
            }
            
            if(!is_valid_number(change)){
                printf("\nInvalid option!");
                goto accountUpdate;
            }            
            // Convert to long long int
            choice = (int)strtol(change, NULL, 10);
        if (choice == 1 || choice == 2){
            updateAccountInfo(u, accountNum, choice);
        }else{
            printf("Invalid input!\n");
            goto accountUpdate;
        }
        break;
    case 3:
        // Check the details of existing accounts function
      /*  printf("Enter account number:");
        scanf("%lld", &accountNum);
        while (getchar() != '\n');
        if (!isAccountPresent(accountNum, u)){
            system("clear");
            printf("This account does not exist.");
            mainMenu(u);
        }
        checkDetailOfAccount(u, accountNum);
        break; */
         clearInputBuffer();
        case3Account:
        printf("\nPlease enter the account number:");
        char acc3[20]; 
            if (fgets(acc3, sizeof(acc3), stdin) != NULL) {
                // Remove the newline character if present
                size_t len = strlen(acc3);
                if (len > 0 && acc3[len-1] == '\n') {
                    acc3[len-1] = '\0';
                }
            }
            if ((strlen(acc3) < 1 ) || (strlen(acc3) > 18)){
                printf("\nInvalid account number!\n");
                goto case3Account;
            }
            
            if(!is_valid_number(acc3)){
                printf("\nInvalid account number!\n");
                goto case3Account;
            }
            
            accountNum = strtoll(acc3, NULL, 10);

        if (!isAccountPresent(accountNum, u)){
            system("clear");
            printf("This account does not exist!");
            sleep(2);
            mainMenu(u);
        }
        checkDetailOfAccount(u, accountNum);
        break;
    case 4:
        checkAllAccounts(u);
        break;
    case 5:
        // Make transaction function
       /* printf("Enter account number:");
        scanf("%lld", &accountNum);
        while (getchar() != '\n');
        if (!isAccountPresent(accountNum, u)){
            system("clear");
            printf("This account does not exist.");
            mainMenu(u);
        }
        printf("Do you want to:\n        1-> Withdraw\n        2-> Deposit\n\n");
        scanf("%d", &choice);
        while (getchar() != '\n');*/
         clearInputBuffer();
        case5Account:
        printf("\nPlease enter the account number:");
        char acc5[20]; 
            if (fgets(acc5, sizeof(acc5), stdin) != NULL) {
                // Remove the newline character if present
                size_t len = strlen(acc5);
                if (len > 0 && acc5[len-1] == '\n') {
                    acc5[len-1] = '\0';
                }
            }
            if ((strlen(acc5) < 1 ) || (strlen(acc5) > 18)){
                printf("\nInvalid account number!\n");
                goto case5Account;
            }
            
            if(!is_valid_number(acc5)){
                printf("\nInvalid account number!\n");
                goto case5Account;
            }
            
            accountNum = strtoll(acc5, NULL, 10);

        if (!isAccountPresent(accountNum, u)){
            system("clear");
            printf("This account does not exist!");
            sleep(2);
            mainMenu(u);
        }

        transactionType:
        printf("Do you want to:\n        1-> Withdraw\n        2-> Deposit\n\n");
        char transaction[3]; 
            if (fgets(transaction, sizeof(transaction), stdin) != NULL) {
                // Remove the newline character if present
                size_t len = strlen(transaction);
                if (len > 0 && transaction[len-1] == '\n') {
                    transaction[len-1] = '\0';
                }
            }
            if ((strlen(transaction) != 1 )){
                printf("\nInvalid option!\n");
                goto transactionType;
            }
            
            if(!is_valid_number(transaction)){
                printf("\nInvalid option!\n");
                goto transactionType;
            }            
            // Convert to long long int
            choice = (int)strtol(transaction, NULL, 10);
        if (choice == 1 || choice == 2){
            makeTransaction(u, accountNum, choice);
        }else{
            printf("Invalid input!\n");
            goto transactionType;
        }
        break;
    case 6:
        // Remove existing account function
     /*   printf("Enter account number to be deleted:");
        scanf("%lld", &accountNum);
        while (getchar() != '\n');
        if (!isAccountPresent(accountNum, u)){
            system("clear");
            printf("The account does not exist.");
            mainMenu(u);
        } */
        clearInputBuffer();
        removeAccount: 
        printf("Enter account number to be deleted:");
        char acc6[20]; 
            if (fgets(acc6, sizeof(acc6), stdin) != NULL) {
                // Remove the newline character if present
                size_t len = strlen(acc6);
                if (len > 0 && acc6[len-1] == '\n') {
                    acc6[len-1] = '\0';
                }
            }
            if ((strlen(acc6) < 1 ) || (strlen(acc6) > 18)){
                printf("\nInvalid account number!\n");
                goto removeAccount;
            }
            
            if(!is_valid_number(acc6)){
                printf("\nInvalid account number!\n");
                goto removeAccount;
            }
            
            // Convert to long long int
            accountNum = strtoll(acc6, NULL, 10);

        if (!isAccountPresent(accountNum, u)){
            system("clear");
            printf("This account does not exist!");
            sleep(2);
            mainMenu(u);
        }
        removeAccount(u, accountNum);
        break;
    case 7:
        // Transfer owner function
       /*printf("Enter the account number to be transferred:");
        scanf("%lld", &accountNum);
        if (!isAccountPresent(accountNum, u)){
            system("clear");
            printf("The account does not exist.");
            mainMenu(u);
        } */

        clearInputBuffer();
        transferOwner: 
        printf("Enter the account number to be transferred:");
        char acc7[20]; 
            if (fgets(acc7, sizeof(acc7), stdin) != NULL) {
                // Remove the newline character if present
                size_t len = strlen(acc7);
                if (len > 0 && acc7[len-1] == '\n') {
                    acc7[len-1] = '\0';
                }
            }
            if ((strlen(acc7) < 1 ) || (strlen(acc7) > 18)){
                printf("\nInvalid account number!\n");
                goto transferOwner;
            }
            
            if(!is_valid_number(acc7)){
                printf("\nInvalid account number!\n");
                goto transferOwner;
            }
            
            // Convert to long long int
            accountNum = strtoll(acc7, NULL, 10);

        if (!isAccountPresent(accountNum, u)){
            system("clear");
            printf("This account does not exist!");
            sleep(2);
            mainMenu(u);
        }
        transferAccount(u, accountNum);
        break;
    case 8:
        // Check the details of existing accounts function
       /* printf("Enter account number:");
        scanf("%lld", &accountNum);
        while (getchar() != '\n');
        if (!isAccountPresent(accountNum, u)){
            system("clear");
            printf("This account does not exist.");
            mainMenu(u);
        } */
         clearInputBuffer();
        accountBalance: 
        printf("Enter account number:");
        char acc8[20]; 
            if (fgets(acc8, sizeof(acc8), stdin) != NULL) {
                // Remove the newline character if present
                size_t len = strlen(acc8);
                if (len > 0 && acc8[len-1] == '\n') {
                    acc8[len-1] = '\0';
                }
            }
            if ((strlen(acc8) < 1 ) || (strlen(acc8) > 18)){
                printf("\nInvalid account number!\n");
                goto accountBalance;
            }
            
            if(!is_valid_number(acc8)){
                printf("\nInvalid account number!\n");
                goto accountBalance;
            }
            
            // Convert to long long int
            accountNum = strtoll(acc8, NULL, 10);

        if (!isAccountPresent(accountNum, u)){
            system("clear");
            printf("This account does not exist!");
            sleep(2);
            mainMenu(u);
        }
        checkAccountBalance(u, accountNum);
        break;
    case 9:
        exit(1);
        break;
    default:
        printf("Invalid operation! Please choose one of the listed options.\n");
        sleep(2);
        mainMenu(u);
    }
};

void initMenu(struct User *u)
{
    int r = 0;
    int option;
   
    system("clear");
    
    printf("\n\n\t\t============= ATM MANAGEMENT SYSTEM =============\n");
    printf("\n\t\t-->> Welcome! Feel free to login / register <<--\n");
    printf("\n\t\t[1]- login\n");
    printf("\n\t\t[2]- register\n");
    printf("\n\t\t[3]- exit\n");
    while (!r)
    {
        scanf("%d", &option);
        switch (option)
        {
    
        case 1:
            loginMenu(u->name, u->password);
            if (strcmp(u->password, getPassword(u)) == 0)
            {
                printf("\n\nLogin successful.");
            }
            else
            {
                printf("\nYou've entered wrong credentials! Try again\n");
                sleep(2);
                initMenu(u);
               // exit(1);
            }
            r = 1;
            break;
        case 2:
            // Registration function
            signUpMenu(u->name, u->password);
            r = 1;
            break;
        case 3:
            exit(1);
            break;
        default:
            printf("Please insert a valid operation!\n");
            sleep(2);
         initMenu(u);
        
        }
    }
};

int main()
{
    struct User u;
    
    initMenu(&u);
    mainMenu(u);
    return 0;
}
