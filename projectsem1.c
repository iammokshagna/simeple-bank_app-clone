#include <stdio.h>
#include <string.h>

#define data_file "account_s.txt"

int main() {
    FILE *file;
    char username[20], password[5];
    char stored_username[20], stored_password[5];
    int account_number, stored_account_number;
    float balance, amount;
    int option, found = 0;

    while (1) {
        printf("Welcome to IIITDMK Bank\n");
        printf("1 -- Login(if you already have an account)\n");
        printf("2 -- Signup(if you do not have an account)\n");
        printf("Enter your choice: ");
        scanf("%d", &option);

        if (option == 2) { 
            printf("Enter a username: ");
            scanf("%s", username);
            file =fopen(data_file, "r");
            if (file != NULL) {
                while (fscanf(file, "%s %s %d %f", stored_username, stored_password, &stored_account_number, &balance) != EOF) {
                    if (strcmp(stored_username, username) == 0) {
                        printf("Username already exists. Try a different one.\n");
                        fclose(file);
                        break;
                    }
                }
                fclose(file);
            }

            if (strcmp(stored_username, username) != 0) { 
                printf("enter a 4-digit password: ");
                scanf("%s", password);
                printf("enter your 11 digit account number: ");
                scanf("%d", &account_number);
                balance = 0.0;

                file = fopen(data_file, "a");
                fprintf(file, "%s %s %d %.2f\n", username, password, account_number, balance);
                fclose(file);
                printf("account created successfully.\n");
                printf(" Please login to continue.\n");
            }
        }

        else if (option == 1) { 
            printf("enter username: ");
            scanf("%s", username);
            printf("enter password: ");
            scanf("%s", password);

            
            file = fopen(data_file, "r");
            if (file == NULL) {
                printf("no accounts found. please sign up\n");
                continue;
            }
            while (fscanf(file, "%s %s %d %f", stored_username, stored_password, &stored_account_number, &balance) != EOF) {
                if (strcmp(stored_username, username) == 0 && strcmp(stored_password, password) == 0) {
                    printf("login successful!\n");
                    found = 1;
                    break;
                }
            }
            
            if (!found) {
                printf("invalid username or password\n");
                continue;
            }
            fclose(file);
            
            while (1) {
                printf("\nIIITdmk Bank HOME PAGE \n");
                printf("1. VIEW BALANCE\n");
                printf("2. WITHDRAW MONEY\n");
                printf("3. DEPOSIT MONEY\n");
                printf("4. EXIST\n");
                printf("Enter your choice: ");
                scanf("%d", &option);

                if (option == 1) { 
                    printf("your BALANCE is: Rs.%.2f\n", balance);
                }
                else if (option == 2) { 
                    printf("Enter amount to withdraw: ");
                    scanf("%f", &amount);

                    if (amount <= 0) {
                        printf("withdrawal amount is invalid.\n");
                    } else if (amount > balance) {
                        printf("insufficient balance.\n");
                    } else {
                        balance -= amount;
                        // balance = balance - amount;
                        printf("withdrawal successful!\n");
                        printf("Current balance: Rs.%.2f\n", balance);
                    }
                }
                else if (option == 3) { 
                    printf("enter amount for deposit: ");
                    scanf("%f", &amount);

                    if (amount <= 0) {
                        printf("Deposit amount is invalid.\n");
                    } else {
                        balance += amount;
                        printf("Deposited successfully.");
                        printf("New balance: Rs.%.2f\n", balance);
                    }
                }
                else if (option == 4) { 
                    file = fopen(data_file, "r");
                    FILE *temp_file = fopen("temp.txt", "w");

                    while (fscanf(file, "%s %s %d %f", stored_username, stored_password, &stored_account_number, &amount) != EOF) {
                        if (strcmp(stored_username, username) == 0) {
                            fprintf(temp_file, "%s %s %d %.2f\n", stored_username, stored_password, stored_account_number, balance);
                        } else {
                            fprintf(temp_file, "%s %s %d %.2f\n", stored_username, stored_password, stored_account_number, amount);
                        }
                    }

                    fclose(file);
                    fclose(temp_file);
                    remove(data_file);
                    rename("temp.txt", data_file);

                    printf("thank you  have a good day.\n ");
                    break;
                }
                else {
                    printf("please select a VALID choice\n");
                }
            }
        }
        else {
            printf("INVALID option. Please try again.\n");
        }
    }

    return 0;
} 

