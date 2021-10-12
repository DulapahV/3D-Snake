#include <stdio.h>
#include <string.h>
#include <vector>
#include <stdlib.h>

using namespace std;

#define ID_LIMIT 10
#define NAME_LIMIT 30
FILE *booksDatabase = fopen("booksDatabase.txt","a");
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
    char password[20] = {0};
    char username[20];
    int birthday[3]; //dd,mm,yyyy
    
} user;

void display_front_page();
void display_login_pg();
void display_register_pg();
void display_admin_pg();

void clrscr();
int check_credential(char username, char password);
int get_choice(int minval, int maxval);

int add_book();
int delete_book();
int set_stock();
int add_stock();
int book_id_checker(char* id);
void update_books();
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
    case 4: //for testing purpose
        add_book();
        break;
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

int add_book(){
    struct Book new_book;
    int i = 0,c=0;
    printf("[Add Book] Enter book info: \n");
    // while(1){
    printf("ID: ");
    fflush(stdin);
    while((c = getchar()) != EOF && c!= '\n'){
        new_book.id[i++]=c;
    }
    new_book.id[i] = 0;
    // if(book_id_checker(new_book.id)!=-1)
    //     break;
    // else{
    //     printf("Id error(Redundant) please try again\n");
    // }
    // }
    printf("Book name: ");
    fflush(stdin);
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
    books.push_back(new_book);
    printf("%c",new_book.name[0]);

    //Storing this book to booksDatabase.txt
    for (int i = 0; i < 10 && new_book.id[i] != 0; i++){
        fprintf(booksDatabase,"%c",new_book.id[i]);
    }
    fprintf(booksDatabase,"\t");

    for (int i = 0; i < NAME_LIMIT && new_book.name[i]!=0; i++){
        
        fprintf(booksDatabase,"%c",new_book.name[i]); 
    }
    fprintf(booksDatabase,"\t");

    for (int i = 0; i < NAME_LIMIT && new_book.author[i]!=0; i++){
        fprintf(booksDatabase,"%c",new_book.author[i]);
    }
    fprintf(booksDatabase,"\t");

    for (int i = 0; i < 3; i++){
        fprintf(booksDatabase,"%d",new_book.pub_date[i]);
        fprintf(booksDatabase,"\t");
    }
    
    fprintf(booksDatabase,"%f",new_book.price);
    fprintf(booksDatabase,"\t");

    fprintf(booksDatabase,"%d",new_book.genre);
    fprintf(booksDatabase,"\t");

    fprintf(booksDatabase,"%d\n",new_book.stock);
}

void clrscr(){
    system("cls");
}