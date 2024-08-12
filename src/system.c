#include "header.h"
#include <unistd.h>  // For sleep()

const char *RECORDS = "./data/records.txt";
const char *USER = "./data/users.txt";


int getAccountFromFile(FILE *ptr, char name[50], struct Record *r)
{
    return fscanf(ptr, "%d %d %s %lld %d/%d/%d %s %s %lf %s",
                  &r->id,
		  &r->userId,
		  name,
                  &r->accountNbr,
                  &r->deposit.month,
                  &r->deposit.day,
                  &r->deposit.year,
                  r->country,
                  r->phone,
                  &r->amount,
                  r->accountType) != EOF;
}



int getAccountFromUser(FILE *ptr, char name[50], struct User *r)
{
return  fscanf(ptr, "%d %s",
                  &r->id,
		          name);
            
}
//int ind = 0;
 
void saveAccountToFile(FILE *ptr, struct User u, struct Record r)
{
   //int ind = getRecordId(u.name);
    fprintf(ptr, "%d %d %s %lld %d/%d/%d %s %s %.2lf %s\n\n",        
            r.id,
	        u.id,
	        u.name,
            r.accountNbr,
            r.deposit.month,
            r.deposit.day,
            r.deposit.year,
            r.country,
            r.phone,
            r.amount,
            r.accountType);
} 

void saveRecordToFile(FILE *ptr, struct Record r)
{
    fprintf(ptr, "%d %d %s %lld %d/%d/%d %s %s %.2lf %s\n\n",
            r.id,
	        r.userId,
	        r.name,
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
        printf("\n Record not found!!\n");
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
        exit(1);
         //TO DO
        // sleep(2);
       // goto date;
        
         
    }
    

accountNo:
    printf("\nEnter the account number:");
    char doen[10];
    scanf("%10s", doen);
   // printf("\ndoen:%s",doen);
    if(!is_valid_number(doen)){
        printf("\nInvalid account number!");
        goto accountNo;
    }
        r.accountNbr = strtoll(doen, NULL, 10);
        //r.accountNbr = atoi(doen);
    //printf("\ndoen2:%d",r.accountNbr);
    
   /*  if (r.accountNbr <= 0)
    {
        printf("Invalid account number! Use only positive numbers e.g 1, 2..\n");
       //  sleep(1);
        goto accountNo;
    } */
  
     while (getAccountFromFile(pf, userName, &cr))
    {
        if (strcmp(userName, u.name) == 0 && cr.accountNbr == r.accountNbr)
        {
            printf("\n This Account already exists for this user\n\n");
            sleep(2);
            goto accountNo;
        }else if (cr.accountNbr == r.accountNbr)
        {
            printf("\n This Account number is already taken\n\n");
            sleep(2);
            goto accountNo;
        }

      ind++;
    }
   
    r.id = ind;
   // r.id = getRecordId(r.name);
    u.id = getUserId(u.name);
    printf("\nEnter the country:");
    scanf("%s", r.country);
phone:
    printf("\nEnter the phone number:");
    scanf("%s", r.phone);
    if(!is_valid_number(r.phone)){
        printf("\nInvalid phone number:");
        goto phone;
    }
amount:
    printf("\nEnter amount to deposit: $");
    scanf("%lf", &r.amount);
    if(r.amount <= 0 || r.amount > 999999){
        printf("\nInvalid amount! (min allowed:$1, max allowed: $999999)\n");
        exit(1);
       /* TO DO */
       //  sleep(2);
       // goto amount;
    }
accType:
    printf("\nChoose the type of account:\n\t-> savings\n\t-> current\n\t-> fixed01(for 1 year)\n\t-> fixed02(for 2 years)\n\t-> fixed03(for 3 years)\n\n\tEnter your choice:");
    scanf("%s", r.accountType);
     if (strcmp(r.accountType, "current") != 0 &&
        strcmp(r.accountType, "savings") != 0 &&
        strcmp(r.accountType, "fixed01") != 0 &&
        strcmp(r.accountType, "fixed02") != 0 &&
        strcmp(r.accountType, "fixed03") != 0){
        printf("\nPlease choose and enter one of the listed options.\n");
         sleep(2);
        goto accType;
    }

    //ind++; 
   // r.id = ind;
    saveAccountToFile(pf, u, r);
    fclose(pf);
    success(u);
}



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
            printf("\nOwner:%s\nAccount number:%lld\nDeposit Date:%d/%d/%d \ncountry:%s \nPhone number:%s \nAmount deposited: $%.2f \nType Of Account:%s\n",
                   userName,
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

/*int getRecordId(char *name){
    FILE *pg = fopen("./data/records.txt", "r+");

    char id[5];
    struct Record temp;
    while(fscanf(pg, "%s %s\n\n", id, temp.name) != EOF){
        if(strcmp(temp.name, name) == 0){
           return atoi(id);
          
        }
    }

    return -1;
} */

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

void updateAccountInfo(struct User u, long long int accountNum, int choice){
    char userName[100];
    struct Record r;
    struct Record arr[100];
    FILE *pf = fopen(RECORDS, "a+");

    system("clear");

    int index = 0;
    while (getAccountFromFile(pf, userName, &r))
    {   
        strcpy(r.name, userName);

        if(strcmp(userName, u.name) == 0 &&
            r.accountNbr == accountNum){
            if(choice == 1){
                printf("Enter the new phone number:");
                scanf("%s", r.phone);
            }
            else if(choice == 2){
                printf("Enter the new country:");
                scanf("%s", r.country);
            }
        }

        arr[index] = r;
        index++;
    }

    // clear the file
    fclose(fopen(RECORDS, "w"));

    for (int i = 0; i < index; i++){
        saveRecordToFile(pf, arr[i]);
    }

    fclose(pf);
    success(u);
}

void checkDetailOfAccount(struct User u, long long int accountNum){
    char userName[100];
    struct Record r;
    FILE *pf = fopen(RECORDS, "r");

    system("clear");
    while (getAccountFromFile(pf, userName, &r))
    {
        if (strcmp(userName, u.name) == 0 &&
            r.accountNbr == accountNum)
        {
            printf("\nOwner:%s\nAccount number:%lld\nDeposit Date:%d/%d/%d \ncountry:%s \nPhone number:%s \nAmount deposited: $%.2f \nType Of Account:%s\n",
                    userName,
                    r.accountNbr,
                    r.deposit.day,
                    r.deposit.month,
                    r.deposit.year,
                    r.country,
                    r.phone,
                    r.amount,
                    r.accountType);

            float rate;
            if(strcmp(r.accountType, "savings") == 0){
                rate = 0.07;
                float interest = r.amount * (1 + rate / 12) - r.amount;
                printf(" -> You will get $%.2f as interest on day 10 of every month\n", interest);
            }
            else if(strcmp(r.accountType, "fixed01") == 0){
                rate = 0.04;
                float interest = r.amount * (1 + rate / 12) - r.amount;
                interest *= 12;
                printf(" -> You will get $%.2f as interest on %d/%d/%d\n", interest, 
                    r.deposit.month, r.deposit.day, r.deposit.year+1);
            }
            else if(strcmp(r.accountType, "fixed02") == 0){
                rate = 0.05;
                float interest = r.amount * (1 + rate / 12) - r.amount;
                interest *= 24;
                printf(" -> You will get $%.2f as interest on %d/%d/%d\n", interest, 
                    r.deposit.month, r.deposit.day, r.deposit.year+2);
            }
            else if(strcmp(r.accountType, "fixed03") == 0){
                rate = 0.08;
                float interest = r.amount * (1 + rate / 12) - r.amount;
                interest *= 36;
                printf(" -> You will get $%.2f as interest on %d/%d/%d\n", interest, 
                    r.deposit.month, r.deposit.day, r.deposit.year+3);
            }
            else{
                printf("You will not get interests because the account is of type current\n");
            }

            fclose(pf);
            success(u);
        }
    }

}

void makeTransaction(struct User u, long long int accountNum, int choice){
    char userName[100];
    struct Record r;
    struct Record arr[100];
    FILE *pf = fopen(RECORDS, "a+");

    int index = 0;
    double available = 0;
    double input = 0;
    while (getAccountFromFile(pf, userName, &r))
    {
        strcpy(r.name, userName);

        if(strcmp(userName, u.name) == 0 &&
            r.accountNbr == accountNum){
            if(strcmp(r.accountType, "fixed01") == 0 ||
            strcmp(r.accountType, "fixed02") == 0 ||
            strcmp(r.accountType, "fixed03") == 0){
                system("clear");
                printf(" Sorry! Transactions are not allowed on fixed accounts.");
                mainMenu(u);
            }

            available = r.amount;

            
            if(choice == 1){
                printf("Enter the amount you want to withdraw:");
                scanf("%lf", &input);
            }
            else if(choice == 2){
                printf("Enter the amount you want to deposit:");
                scanf("%lf", &input);
            }else{
                printf("Invalid choice! Try again.");
                mainMenu(u);
            }

            if (input <= available && input > 0 && choice == 1){
                r.amount -= input;
            }
            else if (choice == 1 && input > available){
                system("clear");
                printf(" Sorry! You don't have enough funds to withdraw %.2lf. Your account balance is %.2lf", input, available);
                mainMenu(u);
            }
            else if(choice == 1 && input <= 0){
                system("clear");
                printf(" Please enter amount greater than 0.");
                mainMenu(u);
            }
            else if (choice == 2 && input > 0 && input <= 999999){
                r.amount += input;
            }
            else if(choice == 2 && input > 999999){
                system("clear");
                printf(" You cannot deposit more than $999,999.");
                mainMenu(u);
            }
            else if (choice == 2 && input <= 0){
                system("clear");
                printf(" Please enter amount more than 0.");
                mainMenu(u);
            }
        }

        arr[index] = r;
        index++;
    }

    // clear the file
    fclose(fopen(RECORDS, "w"));

    for (int i = 0; i < index; i++){
        saveRecordToFile(pf, arr[i]);
    }

    system("clear");
    fclose(pf);
    success(u);
}

void removeAccount(struct  User u, long long int accountNum){
    char userName[100];
    struct Record r;
    struct Record deleted;
    struct Record arr[100];
    FILE *pf = fopen(RECORDS, "a+");

    int index = 0;
    while (getAccountFromFile(pf, userName, &r))
    {
        strcpy(r.name, userName);

        if(strcmp(userName, u.name) == 0 &&
            r.accountNbr == accountNum){
            deleted = r;
        }
        else{
            arr[index] = r;
            index++;
        }
        
    }

    system("clear");
    printf("                       ===== Deleted account =====\n");
    printf("\nOwner:%s\nAccount number:%lld\nDeposit Date:%d/%d/%d \ncountry:%s \nPhone number:%s \nAmount deposited: $%.2f \nType Of Account:%s\n",
        deleted.name,
        deleted.accountNbr,
        deleted.deposit.day,
        deleted.deposit.month,
        deleted.deposit.year,
        deleted.country,
        deleted.phone,
        deleted.amount,
        deleted.accountType);
    
    // clear the file
    fclose(fopen(RECORDS, "w"));

    for (int i = 0; i < index; i++){
        saveRecordToFile(pf, arr[i]);
    }

    fclose(pf);
    success(u);
}

void transferAccount(struct User u, long long int accountNum){
    char userName[100];
    char newOwnerName[100];
    struct Record r;
    struct Record arr[100];
    FILE *pf = fopen(RECORDS, "a+");

    int index = 0;
    while (getAccountFromFile(pf, userName, &r))
    {
        strcpy(r.name, userName);
        if (strcmp(userName, u.name) == 0 &&
            r.accountNbr == accountNum)
        {
            system("clear");
            printf("                       ===== Transfering account:\n");
            printf("\nAccount number:%lld\nDeposit Date:%d/%d/%d \ncountry:%s \nPhone number:%s \nAmount deposited: $%.2f \nType Of Account:%s\n",
                    r.accountNbr,
                    r.deposit.day,
                    r.deposit.month,
                    r.deposit.year,
                    r.country,
                    r.phone,
                    r.amount,
                    r.accountType);
        }

        arr[index] = r;
        index++;
    }
    
    fclose(pf);

    printf("Enter the name of the person you wish to transfer to:");
    scanf("%s", newOwnerName);
    if(!isNamePresent(newOwnerName)){
        printf("The user does not exist.");
        mainMenu(u);
    }
    int newOwnerId;
    newOwnerId = getUserId(newOwnerName);

    for(int i = 0; i < index; i++){
        if(strcmp(arr[i].name, u.name) == 0 &&
            arr[i].accountNbr == accountNum){
            strcpy(arr[i].name, newOwnerName);
            arr[i].userId = newOwnerId;
        }
    }
    
    // clear the file
    fclose(fopen(RECORDS, "w"));
    
    pf = fopen(RECORDS, "a+");
    for (int i = 0; i < index; i++){
        saveRecordToFile(pf, arr[i]);
    }

    fclose(pf);
    success(u);
    
}