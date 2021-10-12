#include <stdio.h>
#include <string.h>
#include <vector>
#include <stdlib.h>
#include <iostream>


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
    char password[20];
    char username[20];
    int birthday[3]; //dd,mm,yyyy
    
} user;

// Page
void display_front_page();
void display_login_pg();
void display_register_pg();

// Functions
void clrscr();
int is_user_exist(char *username); // return -1 if user not found, else return line number of that user (starts from 1)
bool is_credential_valid(char *username, char *password);
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
    char tempUsername[20] = {' '}, tempPassword[20] = {' '};

    // Open user database file
    FILE *userDatabase = fopen("userDatabase.txt", "a");
    if (userDatabase == NULL) {
        printf("Error accessing user database!");
        system("pause");
        display_front_page();
    }
    cout << "> Please enter your credentials" << endl;

    // Get username
    cout << "Username: ";
    cin >> tempUsername;
    
    // Get password
    cout << "Password: ";
    cin >> tempPassword;
    
    // Check credential
    if (is_credential_valid(tempUsername, tempPassword))
        cout << "\nWelcome back, " << tempUsername << "!\n" << endl;
    else
        cout << "\nUsername or password is incorrect! Please try again.\n" << endl;
    system("pause");
    display_front_page();
}

void display_register_pg() {
    clrscr();
    char tempUsername[20] = {' '}, tempPassword[20] = {' '}, tempConfirmPassword[20] = {' '};
    int tempYear, tempMonth, tempDay;

    // Open user database file
    FILE *userDatabase = fopen("userDatabase.txt", "a");
    if (userDatabase == NULL) {
        cout << "Error accessing user database!" << endl;
        system("pause");
        display_front_page();
    }

    cout << "> Please enter your credentials" << endl;
    
    // Get username
    cout << "Username: ";
    cin >> tempUsername;
    if (is_user_exist(tempUsername) != -1) { // Check if username already existed
        printf("\nUsername already exists! Please try again.\n\n");
        system("pause");
        display_front_page();
    }

    // Get password
    cout << "Password: ";
    cin >> tempPassword;
    
    // Get confirm password
    cout << "Confirm Password: ";
    cin >> tempConfirmPassword;
    
    // Check whether password and confirm password matched or not
    if (strcmp(tempPassword, tempConfirmPassword) != 0) {
        cout << "\nPassword mismatch! Please try again.\n" << endl;
        system("pause");
        display_front_page();
    }

    // Get year
    cout << "Birthdate (YYYY): ";
    cin >> tempYear;

    // Get month
    cout << "Birthdate (MM): ";
    cin >> tempMonth;
    if (tempMonth <= 0 || tempMonth > 12) {
        cout << "\nInvalid month! Please try again.\n" << endl;
        system("pause");
        display_front_page();
    }

    // Get date
    cout << "Birthdate (DD): ";
    cin >> tempDay;
    if (tempDay > 0 && tempDay < 32) {
        // check whether it is leap year, entered month is February, and entered date is valid or not
        if (tempYear % 4 != 0 && tempMonth == 2 && tempDay > 28) {
            cout << "\nInvalid date! Please try again.\n" << endl;
            system("pause");
            display_front_page();
        }
    }
    else {
        cout << "\nInvalid date! Please try again.\n" << endl;
        system("pause");
        display_front_page();
    }

    // If all input is valid, store them into user database
    for (int i = 0; i < 20; i++)
        fprintf(userDatabase, "%c", tempUsername[i]);
    fprintf(userDatabase, "\t");

    for (int i = 0; i < 20; i++)
        fprintf(userDatabase, "%c", tempPassword[i]);
    fprintf(userDatabase, "\t");

    fprintf(userDatabase, "%d\t", tempDay);
    fprintf(userDatabase, "%d\t", tempMonth);
    fprintf(userDatabase, "%d\n", tempYear);
    
    fclose(userDatabase);
    cout << "\nAccount Successfully Registered!\n" << endl;
    system("pause");
    display_front_page();
}

int is_user_exist(char *username) { // return -1 if user not found, else return line number of that user (starts from 1)
    char usernameDB[20];
    FILE *userDatabase = fopen("userDatabase.txt", "r");
    if (userDatabase == NULL) {
        cout << "Error accessing user database!" << endl;
        system("pause");
        display_front_page();
    }
    int lineNumber = 0;
    getName:
    lineNumber++;
    fgets(usernameDB, 20, userDatabase);
    if (strcmp(username, usernameDB) != 0)
        if (!feof(userDatabase))
            goto getName;
        else {
            fclose(userDatabase);
            return -1;
        }
    else {
        fclose(userDatabase);
        lineNumber = (lineNumber / 3) + 1;
        return lineNumber;
    }
}

bool is_credential_valid(char *username, char *password) {
    char passwordDB[20];
    FILE *userDatabase = fopen("userDatabase.txt", "r");
    if (userDatabase == NULL) {
        cout << "Error accessing user database!" << endl;
        system("pause");
    }
    int userCheck = is_user_exist(username);
    if (userCheck != -1) {
        getPassword:
        for (int i = 0; i < (userCheck * 3) - 1; i++) // move fgets pointer to the next password in the next line
            fgets(passwordDB, 20, userDatabase);
        char *temp = passwordDB + 2; // Remove '\t' prefix
        if (strcmp(password, temp) == 0) {
            fclose(userDatabase);
            return true;
        }
    }
    fclose(userDatabase);
    return false;
}

int get_choice(int minval, int maxval){// pass min,max to check if user input is in range of choice
    return 0;
}

void clrscr(){
    system("cls");
}