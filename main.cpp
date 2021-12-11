#include <stdio.h>
#include <string.h>
#include <vector>
#include <stdlib.h>
#include <iostream>
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

struct user{
    char id[20];
    char username[20];
    char password[20];
};
 
// Page
void display_front_page();
void display_login_pg();
void display_register_pg();
void display_admin_pg();

void clrscr();
int check_credential(char username, char password);
int get_choice(int minval, int maxval);

void add_book();
void delete_book();
int set_stock();
int book_id_checker(char* id);
int book_finder(char *id);
int load_books();
void write_books();
int main(){
    load_books();
    display_front_page();
    return 0;
}

void display_front_page() {
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
        display_front_page();
    }
}

void display_login_pg() {
    // clrscr();
    // int c = 0, i = 0;
    // printf("> Please enter your credentials\n");
    // printf("Username: ");
    // while(getchar() != '\n'); // Prevent the \n character that is left behind by previous scanf
    // while ((c = getchar()) != EOF && c != '\n')
    //     user.username[i++] = c;
    // printf("Password: ");
    // i = 0;
    // while ((c = getchar()) != EOF && c != '\n')
    //     user.password[i++] = c;
}

void display_register_pg() {
    // clrscr();
    // int c = 0, i = 0;
    // printf("> Please enter your credentials\n");
    // printf("Username: ");
    // while(getchar() != '\n'); // Prevent the \n character that is left behind by previous scanf
    // while ((c = getchar()) != EOF && c != '\n')
    //     user.username[i++] = c;
    // printf("Password: ");
    // i = 0;
    // while ((c = getchar()) != EOF && c != '\n')
    //     user.password[i++] = c;
    // printf("Confirm Password: ");
    // i = 0;
    // char confirmPassword[20] = {0};
    // while ((c = getchar()) != EOF && c != '\n')
    //     confirmPassword[i++] = c;
    // for (int i = 0; i < 20; i++) {
    //     if (user.password[i] != confirmPassword[i]) {
    //         printf("\nPassword mismatch! Please try again.\n\n");
    //         system("pause");
    //         break;
    //     }
    // }
    // display_front_page();
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

int is_user_exist(char *username) { // return -1 if user not found, else return line number of that user (starts from 1)
    char usernameDB[20];
    FILE *userDatabase = fopen("userDatabase.txt", "r");
    if (userDatabase == NULL) {
        cout << "Error accessing user database!" << endl;
        system("pause");
        display_front_page();
    }
}

int check_credential(char username, char password) {
    return 0;
}

int get_choice(int minval, int maxval){// pass min,max to check if user input is in range of choice
    return 0;
}

void add_book(){ // get new book info and push into books vector
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
void clrscr(){
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
        sscanf(line,"%s\t %[^\t] %[^\t] %d %d %d %f %d %d",
        &new_book.id,&new_book.name,&new_book.author,&new_book.pub_date[0],
        &new_book.pub_date[1],&new_book.pub_date[2],&new_book.price,
        &new_book.genre,&new_book.stock);
        new_book.name[29]='\0';
        new_book.author[29]='\0';
        books.push_back(new_book);
        //printf("id:%s\nname:%s\nauthor:%s\npubd %d pubm %d puby %d\nprice: %f\ngenre:%d\nstock %d\n",new_book.id,new_book.name,new_book.author,new_book.pub_date[0],new_book.pub_date[1],new_book.pub_date[2],new_book.price,new_book.genre,new_book.stock);
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

