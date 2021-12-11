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

struct Book
{
    char id[10];
    char name[30];
    char author[30];
    int pub_date[3]; // [dd,mm,yyyy]
    float price;
    int genre;
    int stock;
    int number_sold;
};

vector<Book> books;
vector<Book> cart;

struct User
{
    char username[20];
    char password[20];
};

struct User user_info;

// Page
void display_front_page();
int display_login_pg(); // return 1 if privilege is user, else 2 for admin
void display_register_pg();
void display_admin_pg();
void display_customer_pg();

void clrscr();
int is_user_exist(char *username); // return -1 if user not found, else return line number of that user (starts from 1)
bool is_credential_valid(char *username, char *password);
int get_choice(int minval, int maxval);

void add_book();
void delete_book();
void show_book();
int set_stock();
void buy_book();
void checkout();

int book_id_checker(char* id);
int book_finder(char *id);

int load_books();
void write_books();
int main()
{
    load_books();
    display_front_page();
    return 0;
}

void display_front_page()
{
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
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        display_login_pg();
        break;
    case 2:
        display_register_pg();
        break;
    case 3:
        write_books();
        exit(0);
    case 4: // for testing purpose
        display_admin_pg();
        break;
    default:
        printf("\nError: Wrong Choice\n\n");
        system("pause");
        display_front_page();
    }
}

int display_login_pg()
{
    clrscr();
    char tempUsername[20] = {' '}, tempPassword[20] = {' '};

    // Open user database file
    FILE *userDatabase = fopen("userDatabase.txt", "a");
    if (userDatabase == NULL)
    {
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
    {
        strcpy(user_info.username, tempUsername);
        strcpy(user_info.password, tempPassword);
        cout << "\nWelcome back, " << tempUsername << "!\n"
             << endl;
        if ((strcmp(tempUsername, ADMIN_USERNAME) == 0) && (strcmp(tempPassword, ADMIN_PASSWORD) == 0))
        {
            system("pause");
            display_admin_pg();
        }
        else
        {
            system("pause");
            display_customer_pg();
        }
    }
    else
        cout << "\nUsername or password is incorrect! Please try again.\n"
             << endl;
    system("pause");
    display_front_page();
    return 0;
}

void display_register_pg()
{
    clrscr();
    char tempUsername[20] = {' '}, tempPassword[20] = {' '}, tempConfirmPassword[20] = {' '};
    int tempYear, tempMonth, tempDay;

    // Open user database file
    FILE *userDatabase = fopen("userDatabase.txt", "a");
    if (userDatabase == NULL)
    {
        cout << "Error accessing user database!" << endl;
        system("pause");
        display_front_page();
    }

    cout << "> Please enter your credentials" << endl;

    // Get username
    cout << "Username: ";
    cin >> tempUsername;
    if (is_user_exist(tempUsername) != -1)
    { // Check if username already existed
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
    if (strcmp(tempPassword, tempConfirmPassword) != 0)
    {
        cout << "\nPassword mismatch! Please try again.\n"
             << endl;
        system("pause");
        display_front_page();
    }

    // Get year
    cout << "Birthdate (YYYY): ";
    cin >> tempYear;

    // Get month
    cout << "Birthdate (MM): ";
    cin >> tempMonth;
    if (tempMonth <= 0 || tempMonth > 12)
    {
        cout << "\nInvalid month! Please try again.\n"
             << endl;
        system("pause");
        display_front_page();
    }

    // Get date
    cout << "Birthdate (DD): ";
    cin >> tempDay;
    if (tempDay > 0 && tempDay < 32)
    {
        // check whether it is leap year, entered month is February, and entered date is valid or not
        if (tempYear % 4 != 0 && tempMonth == 2 && tempDay > 28)
        {
            cout << "\nInvalid date! Please try again.\n"
                 << endl;
            system("pause");
            display_front_page();
        }
    }
    else
    {
        cout << "\nInvalid date! Please try again.\n"
             << endl;
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
    cout << "\nAccount Successfully Registered!\n"
         << endl;
    system("pause");
    display_front_page();
}

void display_admin_pg()
{
    clrscr();
    printf("Logged in as: %s\n", user_info.username);
    printf("[1] Add Book\n");
    printf("[2] Delete Book\n");
    printf("[3] Manage Stock\n");
    printf("[4] Exit\n");
    printf("\nChoice--> ");
    int choice = 0;
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        add_book();
        break;
    case 2:
        delete_book();
        break;
    case 3:
        set_stock();
        break;
    case 4: 
        display_front_page();

        break;
    default:
        printf("\nError: Wrong Choice\n\n");
        system("pause");
        display_front_page();
    }
}

void display_customer_pg()
{
    clrscr();
    printf("Logged in as: %s\n", user_info.username);
    printf("[1] Show Book\n");
    printf("[2] Buy Book\n");
    printf("[3] Checkout\n");
    printf("[4] Exit\n");
    printf("\nChoice--> ");
    int choice = 0;
    cin >> choice;
    switch (choice)
    {
        case 1: 
            show_book();
            break;
        case 2:
            buy_book();
            break;
        case 3:
            checkout();
            break;
        case 4:
            display_front_page();
            break;
        default:
        printf("\nError: Wrong Choice\n\n");
        system("pause");
        display_customer_pg();
    }
}

void show_book() {
    clrscr();
    FILE *userDatabase = fopen("booksDatabase.txt", "r");
    if (userDatabase == NULL) {
        cout << "Error accessing user database!" << endl;
        system("pause");
        display_front_page();
    }
    int i = 0, page = 1;
readEntry:
    int entry = 0;
    printf("Page %d/%d\n", page, books.size() / 10 + (books.size() % 10 != 0));
    printf("ID\tNAME\tAUTHOR\tDATE\tMONTH\tYEAR\tPRICE\tGENRE\tSTOCK\n");
    for (; i < books.size(); i++, entry++){
        if (entry < 10) {
            struct Book book = books[i];
            printf("%s\t%s\t%s\t%d\t%d\t%d\t%.2f\t%d\t%d\n",
            book.id,book.name,book.author,book.pub_date[0],
            book.pub_date[1],book.pub_date[2],book.price,
            book.genre,book.stock);
        }
        else {
            page++;
            char choice;
            printf("Press 'n' to continue to next page or press 'x' to exit: ");
            cin >> choice;
            switch (choice)
            {
                case 'n':
                    printf("\n");
                    goto readEntry;
                    break;
                case 'x':
                    display_customer_pg();
                    break;
                default:
                    printf("\nError: Wrong Choice\n\n");
                    system("pause");
                    display_customer_pg();
            }
        }
    }
    printf("\n");
    system("pause");
    display_customer_pg();
}

void buy_book() {
    clrscr();
    printf("Enter book ID that you want to buy: ");
    char tmp_id[11];
    cin >> tmp_id;
    book_finder(tmp_id);
    int index = book_finder(tmp_id);
    if (index == -1){
        printf("Not found");
        system("pause");
        display_admin_pg();
    }
    if (books[index].stock > 0) {
        printf("\nBook added to cart: %s\n\n",books[index].name);
        cart.push_back(books[index]);
    }
    else
        printf("\n%s is out of stock!\n\n",books[index].name);
    system("pause");
    display_customer_pg();
}

void checkout() {
    clrscr();
    double cost = 0;
    printf("Your cart:\n");
    printf("ID\tNAME\tAUTHOR\tPRICE\n");
    for (int i = 0; i < cart.size(); i++) {
        struct Book bookInCart = cart[i];
        printf("%s\t%s\t%s\t%.2f",
        bookInCart.id,bookInCart.name,bookInCart.author,bookInCart.price);
        cost += bookInCart.price;
    }
    printf("\n\nTotal cost: %lf\n\n", cost);
    printf("Would you like to confirm your order (y/n)?: ");
    char choice;
    cin >> choice;
    switch (choice) {
        case 'y':
            for (int i = 0; i < cart.size(); i++) {
                struct Book bookInCart = cart[i];
                int index = book_finder(bookInCart.id);
                books[index].stock -= 1;
                books[index].number_sold += 1;
            }
            printf("\nSuccessfully checked out!\n\n");
            system("pause");
            display_customer_pg();
            break;
        case 'n':
            display_customer_pg();
            break;
        default:
            printf("\nError: Wrong Choice\n\n");
            system("pause");
            display_customer_pg();
    }
}

int is_user_exist(char *username)
{ // return -1 if user not found, else return line number of that user (starts from 1)
    char usernameDB[20];
    FILE *userDatabase = fopen("userDatabase.txt", "r");
    if (userDatabase == NULL)
    {
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
        else
        {
            fclose(userDatabase);
            return -1;
        }
    else
    {
        fclose(userDatabase);
        lineNumber = (lineNumber / 3) + 1;
        return lineNumber;
    }
}

bool is_credential_valid(char *username, char *password)
{
    char passwordDB[20];
    FILE *userDatabase = fopen("userDatabase.txt", "r");
    if (userDatabase == NULL)
    {
        cout << "Error accessing user database!" << endl;
        system("pause");
    }
    int userCheck = is_user_exist(username);
    if (userCheck != -1)
    {
    getPassword:
        for (int i = 0; i < (userCheck * 3) - 1; i++) // move fgets pointer to the next password in the next line
            fgets(passwordDB, 20, userDatabase);
        char *temp = passwordDB + 2; // Remove '\t' prefix
        if (strcmp(password, temp) == 0)
        {
            fclose(userDatabase);
            return true;
        }
    }
    fclose(userDatabase);
    return false;
}

int get_choice(int minval, int maxval)
{ // pass min,max to check if user input is in range of choice
    return 0;
}


void add_book(){ // get new book info and push into books vector

    struct Book new_book;
    int i = 0, c = 0;
    printf("[Add Book] Enter book info: \n");
  
    while(1){
    printf("ID: ");
    fflush(stdin);
    while((c = getchar()) != EOF && c!= '\n'){
        new_book.id[i++]=c;
    }
    new_book.id[i] = 0;
    char* nameptr = new_book.id;
    if(book_id_checker(nameptr)==-1)
        break;
    else{
        printf("Id error(Redundant) please try again\n");
        i=0;
    }

    }
    printf("Book name: ");
    fflush(stdin);
    i = 0;
    while ((c = getchar()) != EOF && c != '\n')
    {
        new_book.name[i++] = c;
    }
    new_book.name[i] = 0;

    printf("Author name: ");
    fflush(stdin);
    i = 0;
    while ((c = getchar()) != EOF && c != '\n')
    {
        new_book.author[i++] = c;
    }
    new_book.author[i] = 0;

    printf("Published Date(DD): ");
    fflush(stdin);
    scanf("%d", &new_book.pub_date[0]);
    printf("Published Date(MM): ");
    fflush(stdin);
    scanf("%d", &new_book.pub_date[1]);
    printf("Published Date(YYYY): ");
    fflush(stdin);
    scanf("%d", &new_book.pub_date[2]);
    printf("Price($): ");
    scanf("%f", &new_book.price);
    printf("Genre(0-10): ");
    scanf("%d", &new_book.genre);
    printf("Initial Stock: ");
    scanf("%d", &new_book.stock);
    new_book.number_sold = 0;
    books.push_back(new_book);
    clrscr();
    printf("Book ID: %s successfully added\n", new_book.id);
    display_admin_pg();
}

int book_id_checker(char* id){
    for(int i=0;i<books.size();i++){
        if(strcmp(id,books[i].id)==0){
            return i;
        }
    }
    return -1;
}


int book_finder(char *id){
    for(int i=0;i<books.size();i++){
        if(strcmp(id,books[i].id)==0){
            return i;

        }
    }
    return -1;
}

void delete_book(){
    clrscr();
    char tmpID[30];
    printf("[Delete Book]\n");
    printf("Enter Book id: ");
    fflush(stdin);
    scanf("%s",&tmpID);
    if(books.empty()){
        printf("books list empty\n");
        system("pause");
        display_admin_pg();
    }
    int book_index = book_id_checker(tmpID);
    printf("%d\n",book_index);
    if(book_index ==-1){
        printf("Not found\n");
        display_admin_pg();
    }
    else{
        books.erase(books.begin()+book_index);
        printf("Deleted Book ID %s successfully\n",tmpID);
        system("pause");
        
        display_admin_pg();

    }
    

}

int set_stock(){
    clrscr();
    printf("Set stock:\n");
    printf("Enter Book id: ");
    char tmp_id[11];
    cin >> tmp_id;
    int index = book_finder(tmp_id);
    if (index == -1){
        printf("Not found");
        system("pause");
        display_admin_pg();
        return -1;
    }
    printf("Current stock: %d\n",books[index].stock);
    printf("Enter stock to change: ");
    int tmp_stock;
    cin >> tmp_stock;
    books[index].stock = tmp_stock;
    clrscr();
    printf("Book ID: %s successfully set stock\n",tmp_id);
    display_admin_pg();
    return 0;
}
void clrscr()
{
    system("cls");
}


int load_books(){
    FILE *booksDatabase = fopen("booksDatabase.txt","r");
    if(booksDatabase==NULL){
        printf("File not found");
        return -1;
    }
    char line[1024];
    while(fgets(line,sizeof(line),booksDatabase)!= NULL){


        struct Book new_book;
        sscanf(line, "%s\t %[^\t] %[^\t] %d %d %d %f %d %d",
               &new_book.id, &new_book.name, &new_book.author, &new_book.pub_date[0],
               &new_book.pub_date[1], &new_book.pub_date[2], &new_book.price,
               &new_book.genre, &new_book.stock);
        new_book.name[29] = '\0';
        new_book.author[29] = '\0';
        books.push_back(new_book);
        // printf("id:%s\nname:%s\nauthor:%s\npubd %d pubm %d puby %d\nprice: %f\ngenre:%d\nstock %d\n",new_book.id,new_book.name,new_book.author,new_book.pub_date[0],new_book.pub_date[1],new_book.pub_date[2],new_book.price,new_book.genre,new_book.stock);
    }
    fclose(booksDatabase);
    return 0;
}

void write_books(){
    FILE *booksDatabase = fopen("booksDatabase.txt","w");
    for (int i = 0 ; i < books.size(); i++){
        struct Book new_book = books[i];
        fprintf(booksDatabase,"%s\t%s\t%s\t%d\t%d\t%d\t%f\t%d\t%d\t%d\n",
        new_book.id,new_book.name,new_book.author,new_book.pub_date[0],
        new_book.pub_date[1],new_book.pub_date[2],new_book.price,
        new_book.genre,new_book.stock,new_book.number_sold);

    }
    fclose(booksDatabase);
}
