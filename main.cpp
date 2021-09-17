#include <stdio.h>
#include <string.h>
#include<vector>
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

struct Account{
    char id[20];
    char password[20];
    char name[20];
    int birthday[3]; //dd,mm,yyyy
    
};
void clrscr(){
    system("cls");
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
}

void display_login_pg(){
    clrscr();
    printf("LOGIN PG");
}

void display_register_pg(){
    clrscr();
    printf("REGISTER PG");
}




int get_choice(int minval, int maxval){// pass min,max to check if user input is in range of choice
    return 0;
}

int main(){
    display_front_page();
    int choice = 0;
    do{
        scanf("%d",&choice);
        switch (choice){
            case 1:
                display_login_pg();
                break;
            case 2:
                display_register_pg();
                break;
            case 3:
                return 0;
            default:
                print("Error: Wrong Choice");
                break;
        }
    }while(choice!=3);

}