// This screen will appear after successful login or successful register.

#include <stdio.h>

int main() {
    printf("=========================================================================================================\n");
    printf("                                        Welcome back, [username]!\n"); // Might design some algorithm to center text (username has various length)
    printf("What would you like to do:\n");
    printf("[1] Buy books\n");
    printf("[2] Search books\n");
    printf("[3] View promotion\n");
    printf("[4] Check your cart\n");
    printf("[5] Checkout\n");
    printf("[6] Logout\n"); // returns to main menu
    printf("[7] Exit\n");
    printf("\nChoice--> ");
}