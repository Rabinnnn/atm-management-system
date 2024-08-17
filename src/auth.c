#include <termios.h>
#include "header.h"
#include <unistd.h>

char *USERS = "./data/users.txt";


void signUpMenu(char a[50], char pass[50]){
    struct termios oflags, nflags;

    system("clear");
    signup:
    printf("\n\n\n\t\t\t\t   Bank Management System");
    
    printf("\n\n\t\t\t\t----------Sign up----------\n\n\t\t\t\tEnter Username (please enter only one name):");
    scanf("%s", a);
     // Discard any remaining input after the first word (name)
    while (getchar() != '\n');
    // disabling echo
    tcgetattr(fileno(stdin), &oflags);
    nflags = oflags;
    nflags.c_lflag &= ~ECHO;
    nflags.c_lflag |= ECHONL;

    if (tcsetattr(fileno(stdin), TCSANOW, &nflags) != 0)
    {
        perror("tcsetattr");
        return exit(1);
    }
    printf("\n\n\t\t\t\tEnter Password (No spaces allowed):");
    scanf("%s", pass);
    while (getchar() != '\n');
    alphamirror(pass);
    // restore terminal
    if (tcsetattr(fileno(stdin), TCSANOW, &oflags) != 0)
    {
        perror("tcsetattr");
        return exit(1);
    }

    FILE *fp;
    char names[100][100]; 
    struct User userChecker;
    char id[5];
    int counter = 0;

    if ((fp = fopen("./data/users.txt", "a+")) == NULL)
    {
        printf("Error! opening file");
        exit(1);
    }

    while (fscanf(fp, "%s %s %s", id, userChecker.name, userChecker.password) != EOF)
    {
        strcpy(names[counter], userChecker.name);
        counter++;
    }

    if (counter != 0){
        fprintf(fp, "\n");
    }

    if(isPresent(names, a)){
        system("clear");
        printf("This user already exists!\n");
        sleep(2);
        goto signup;
       // exit(1);
    }
    else{
        fprintf(fp, "%d %s %s", counter, a, pass);
    }
    
    fclose(fp);

};


void loginMenu(char a[50], char pass[50])
{
    struct termios oflags, nflags;

    system("clear");
    printf("\n\n\n\t\t\t\t   Bank Management System");
    printf("\n\n\t\t\t\t----------Login----------\n\n\t\t\t\tEnter Username:");
    scanf("%s", a);

    // disabling echo
    tcgetattr(fileno(stdin), &oflags);
    nflags = oflags;
    nflags.c_lflag |= ECHO;
    nflags.c_lflag |= ECHONL;

    if (tcsetattr(fileno(stdin), TCSANOW, &nflags) != 0)
    {
        perror("tcsetattr");
        return exit(1);
    }
    printf("\n\n\t\t\t\tEnter Password:");
    scanf("%s", pass);
    alphamirror(pass);

    // restore terminal
    if (tcsetattr(fileno(stdin), TCSANOW, &oflags) != 0)
    {
        perror("tcsetattr");
        return exit(1);
    }
};



const char *getPassword(struct User *u)
{
    FILE *fp;
    struct User userChecker;
    char id[10];
    if ((fp = fopen("./data/users.txt", "r")) == NULL)
    {
        printf("Error! opening file");
        exit(1);
    }

    while (fscanf(fp, "%s %s %s", id, userChecker.name, userChecker.password) != EOF)
    {
        if (strcmp(userChecker.name, u->name) == 0)
        {
            fclose(fp);
            u->id = atoi(id);
            char *buff = userChecker.password;
            return buff;
        }
    }

    fclose(fp);
    return "no user found";
}