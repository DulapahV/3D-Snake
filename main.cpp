#include <stdio.h>
#include <string.h>
#include <vector>
#include <stdlib.h>
#include <iostream>

#define ADMIN_USERNAME "admin"
#define ADMIN_PASSWORD "password"

using namespace std;

#define ID_LIMIT 10
#define NAME_LIMIT 30


struct Book{
    char id[10];
    char name[30];
    char author[30];
    int pub_date[3];// [dd,mm,yyyy]
    float price;
    int genre;
    int stock;
    int number_sold;
};

vector<Book> books;

struct User{
    char username[20];
    char password[20];
};

// Page
void display_front_page();
int display_login_pg(); // return 1 if privilege is user, else 2 for admin
void display_register_pg();
void display_admin_pg();

void clrscr();
int is_user_exist(char *username); // return -1 if user not found, else return line number of that user (starts from 1)
bool is_credential_valid(char *username, char *password);
int get_choice(int minval, int maxval);

int add_book();
int delete_book();
int set_stock();
int book_id_checker(char* id);
int load_books();
void write_books();
int main(){
    load_books();
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
        write_books();
        exit(0);
    case 4: //for testing purpose
        display_admin_pg();
        break;
    default:
        printf("\nError: Wrong Choice\n\n");
        system("pause");
        main();
    }
}

int display_login_pg() {
    struct User user_info;
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
    if (is_credential_valid(tempUsername, tempPassword)) {
        for (int i = 0; i < 20; i++) {
            user_info.username[i] = tempUsername[i];
            user_info.password[i] = tempPassword[i];
        }
        cout << "\nWelcome back, " << tempUsername << "!\n" << endl;
        if (tempUsername == ADMIN_USERNAME && tempPassword == ADMIN_PASSWORD)
            return 2; // admin
        else
            return 1; // user
    }
    else
        cout << "\nUsername or password is incorrect! Please try again.\n" << endl;
    system("pause");
    display_front_page();
    return 0;
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

void display_admin_pg(){
    clrscr();
    printf("ADMIN\n");
    printf("[1] Add Book\n");
    printf("[2] Delete Book\n");
    printf("[3] Manage Stock\n");
    printf("[4] Exit\n");
    printf("\nChoice--> ");
    int choice = 0;
    scanf("%d",&choice);
    switch (choice){
    case 1:
        add_book();
        break;
    case 2:
        // delete_book();
        break;
    case 3:
        // set_stock();
        break;
    case 4: 
        main();
        break;
    default:
        printf("\nError: Wrong Choice\n\n");
        system("pause");
        main();
    }
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

int add_book(){ // get new book info and push into books vector
    struct Book new_book;
    int i = 0,c=0;
    printf("[Add Book] Enter book info: \n");
    while(1){
    printf("ID: ");
    fflush(stdin);
    while((c = getchar()) != EOF && c!= '\n'){
        new_book.id[i++]=c;
    }
    new_book.id[i] = 0;
    char* nameptr = new_book.id;
    if(book_id_checker(nameptr)!=-1)
        break;
    else{
        printf("Id error(Redundant) please try again\n");
        i=0;
    }
    }
    printf("Book name: ");
    fflush(stdin);
    i = 0;
    while((c=getchar())!= EOF && c!= '\n'){
        new_book.name[i++]=c;
    }
    new_book.name[i] = 0;

    printf("Author name: ");
    fflush(stdin);
    i = 0;
    while((c=getchar())!= EOF && c!= '\n'){
        new_book.author[i++]=c;
    }
    new_book.author[i] = 0;

    printf("Published Date(DD): ");
    fflush(stdin);
    scanf("%d",&new_book.pub_date[0]);
    printf("Published Date(MM): ");
    fflush(stdin);
    scanf("%d",&new_book.pub_date[1]);
    printf("Published Date(YYYY): ");
    fflush(stdin);
    scanf("%d",&new_book.pub_date[2]);
    printf("Price($): ");
    scanf("%f",&new_book.price);
    printf("Genre(0-10): ");
    scanf("%d",&new_book.genre);
    printf("Initial Stock: ");
    scanf("%d",&new_book.stock);
    new_book.number_sold = 0;
    books.push_back(new_book);
    clrscr();
    printf("Book ID: %s successfully added\n",new_book.id);
    display_admin_pg();
}

int book_id_checker(char* id){
    for(int i=0;i<books.size();i++){
        if(strcmp(id,books[i].id)==0){
            return -1;
        }
    }
    return 0;
}
void clrscr(){
    system("cls");
}

int load_books(){
    FILE *booksDatabaseR = fopen("booksDatabase.txt","r");
    char line[1024];
    while(fgets(line,sizeof(line),booksDatabaseR)!= NULL){

        struct Book new_book;
        sscanf(line,"%s\t %[^\t] %[^\t] %d %d %d %f %d %d",
        &new_book.id,&new_book.name,&new_book.author,&new_book.pub_date[0],
        &new_book.pub_date[1],&new_book.pub_date[2],&new_book.price,
        &new_book.genre,&new_book.stock);
        new_book.name[29]='\0';
        new_book.author[29]='\0';
        books.push_back(new_book);
        //printf("id:%s\nname:%s\nauthor:%s\npubd %d pubm %d puby %d\nprice: %f\ngenre:%d\nstock %d\n",new_book.id,new_book.name,new_book.author,new_book.pub_date[0],new_book.pub_date[1],new_book.pub_date[2],new_book.price,new_book.genre,new_book.stock);
    }
    fclose(booksDatabaseR);
    return 0;
}

void write_books(){
    FILE *booksDatabase = fopen("booksDatabase.txt","w+");
    for (int i = 0 ; i < books.size(); i++){
        struct Book new_book = books[i];
        fprintf(booksDatabase,"%s\t%s\t%s\t%d\t%d\t%d\t%f\t%d\t%d\n",
        new_book.id,new_book.name,new_book.author,new_book.pub_date[0],
        new_book.pub_date[1],new_book.pub_date[2],new_book.price,
        new_book.genre,new_book.stock);
    }
    fclose(booksDatabase);
    }

