#include <stdio.h>
#include <string.h>
#include <vector>
#include <stdlib.h>

using namespace std;

struct Book{
    int id;
    char name[30];
    char author[30];
    int pub_date[3];// [dd,mm,yyyy]
    float price;
    int genre;
    int stock;
    int number_sold;
};

vector<Book> books;

struct user{
    char id[20];
    char password[20] = {0};
    char username[20];
    int birthday[3]; //dd,mm,yyyy
    
} user;

void display_front_page();
void display_login_pg();
void display_register_pg();
void clrscr();
int check_credential(char username, char password);
int get_choice(int minval, int maxval);

int main(){
    display_front_page();
    return 0;
}

void display_front_page() {
    clrscr();
    printf(" ________  ________  ________  ___  __            ________  _________  ________  ________  _______      \n");
    printf("|\\   __  \\|\\   __  \\|\\   __  \\|\\  \\|\\  \\         |\\   ____\\|\\___   ___\\\\   __  \\|\\   __  \\|\\  ___ \\     \n");
    printf("\\ \\  \\|\\ /\\ \\  \\|\\  \\ \\  \\|\\  \\ \\  \\/  /|_       \\ \\  \\___|\\|___ \\  \\_\\ \\  \\|\\  \\ \\  \\|\\  \\ \\   __/|    \n");
    printf(" \\ \\   __  \\ \\  \\\\\\  \\ \\  \\\\\\  \\ \\   ___  \\       \\ \\_____  \\   \\ \\  \\ \\ \\  \\\\\\  \\ \\   _  _\\ \\  \\_|/__  \n");
    printf("  \\ \\  \\|\\  \\ \\  \\\\\\  \\ \\  \\\\\\  \\ \\  \\\\ \\  \\       \\|____|\\  \\   \\ \\  \\ \\ \\  \\\\\\  \\ \\  \\\\  \\\\ \\  \\_|\\ \\ \n");
    printf("   \\ \\_______\\ \\_______\\ \\_______\\ \\__\\\\ \\__\\        ____\\_\\  \\   \\ \\__\\ \\ \\_______\\ \\__\\\\ _\\\\ \\_______\\\n");
    printf("    \\|_______|\\|_______|\\|_______|\\|__| \\|__|       |\\_________\\   \\|__|  \\|_______|\\|__|\\|__|\\|_______|\n");
    printf("                                                    \\|_________|                                        \n");
    printf("=========================================================================================================\n");
    printf("                                         Welcome to Book Store!\n");
    printf("> Please login to continue\n");
    printf("[1] Login into existing account\n");
    printf("[2] Register new account\n");
    printf("[3] Exit\n");
    printf("\nChoice--> ");
    int choice = 0;
    scanf("%d",&choice);
    switch (choice){
    case 1:
        display_login_pg();
        break;
    case 2:
        display_register_pg();
        break;
    case 3:
        exit(0);
    default:
        printf("\nError: Wrong Choice\n\n");
        system("pause");
        main();
    }
}

void display_login_pg() {
    clrscr();
    int c = 0, i = 0;
    printf("> Please enter your credentials\n");
    printf("Username: ");
    while(getchar() != '\n'); // Prevent the \n character that is left behind by previous scanf
    while ((c = getchar()) != EOF && c != '\n')
        user.username[i++] = c;
    printf("Password: ");
    i = 0;
    while ((c = getchar()) != EOF && c != '\n')
        user.password[i++] = c;
}

void display_register_pg() {
    clrscr();
    int c = 0, i = 0;
    printf("> Please enter your credentials\n");
    printf("Username: ");
    while(getchar() != '\n'); // Prevent the \n character that is left behind by previous scanf
    while ((c = getchar()) != EOF && c != '\n')
        user.username[i++] = c;
    printf("Password: ");
    i = 0;
    while ((c = getchar()) != EOF && c != '\n')
        user.password[i++] = c;
    printf("Confirm Password: ");
    i = 0;
    char confirmPassword[20] = {0};
    while ((c = getchar()) != EOF && c != '\n')
        confirmPassword[i++] = c;
    for (int i = 0; i < 20; i++) {
        if (user.password[i] != confirmPassword[i]) {
            printf("\nPassword mismatch! Please try again.\n\n");
            system("pause");
            break;
        }
    }
    display_front_page();
}

int check_credential(char username, char password) {
    return 0;
}

int get_choice(int minval, int maxval){// pass min,max to check if user input is in range of choice
    return 0;
}

void clrscr(){
    system("cls");
}