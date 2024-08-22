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
                printf("\nInvalid account number!");
                goto case2Account;
            }
            
            if(!is_valid_number(doen)){
                printf("\nInvalid account number!");
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
        accountUpdate:
        printf("\nWhich field would you like to change?\n1-> phone number\n2-> country\n");
        scanf("%d", &choice);
        while (getchar() != '\n');
        if (choice == 1 || choice == 2){
            updateAccountInfo(u, accountNum, choice);
        }else{
            printf("Invalid input!\n");
            goto accountUpdate;
        }
        break;
    case 3:
        // Check the details of existing accounts function
        printf("Enter account number:");
        scanf("%lld", &accountNum);
        while (getchar() != '\n');
        if (!isAccountPresent(accountNum, u)){
            system("clear");
            printf("This account does not exist.");
            mainMenu(u);
        }
        checkDetailOfAccount(u, accountNum);
        break;
    case 4:
        checkAllAccounts(u);
        break;
    case 5:
        // Make transaction function
        printf("Enter account number:");
        scanf("%lld", &accountNum);
        while (getchar() != '\n');
        if (!isAccountPresent(accountNum, u)){
            system("clear");
            printf("This account does not exist.");
            mainMenu(u);
        }
        printf("Do you want to:\n        1-> Withdraw\n        2-> Deposit\n\n");
        scanf("%d", &choice);
        while (getchar() != '\n');
        makeTransaction(u, accountNum, choice);
        break;
    case 6:
        // Remove existing account function
        printf("Enter account number to be deleted:");
        scanf("%lld", &accountNum);
        while (getchar() != '\n');
        if (!isAccountPresent(accountNum, u)){
            system("clear");
            printf("The account does not exist.");
            mainMenu(u);
        }
        removeAccount(u, accountNum);
        break;
    case 7:
        // Transfer owner function
        printf("Enter the account number to be transferred:");
        scanf("%lld", &accountNum);
        if (!isAccountPresent(accountNum, u)){
            system("clear");
            printf("The account does not exist.");
            mainMenu(u);
        }
        transferAccount(u, accountNum);
        break;
    case 8:
        // Check the details of existing accounts function
        printf("Enter account number:");
        scanf("%lld", &accountNum);
        while (getchar() != '\n');
        if (!isAccountPresent(accountNum, u)){
            system("clear");
            printf("This account does not exist.");
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
