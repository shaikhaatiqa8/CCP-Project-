#include <stdio.h>
#include <string.h>
int main() {
    // --------------------------- DATA STORAGE ---------------------------
    // Arrays to store account information
    char names[100][50];          // Names of up to 100 users
    int accNo[100];               // Account numbers
    char passwords[100][20];      // Account passwords
    float balance[100];           // Account balances
    char transactions[100][10][100]; // Stores last 10 transactions per account
    int transCount[100] = {0};    // Keeps count of transactions per account

    int totalAccounts = 0;        // Total number of accounts in the system
    char adminPass[20] = "admin123"; // Hardcoded admin password
    int choice, i, j;             // General loop and menu variables
    char tempPass[20];            // Temporary variable to take admin password input
    int accIndex = -1;            // Used to store index of logged-in account

    // --------------------------- MAIN LOOP ---------------------------
    while (1) {
        // Main menu
        printf("\n==============================\n");
        printf("     BANK MANAGEMENT SYSTEM\n");
        printf("==============================\n");
        printf("1. Admin Login\n");
        printf("2. ATM Services\n");
        printf("3. Help Desk\n");
        printf("4. Additional Features\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {

            // --------------------------- ADMIN LOGIN ---------------------------
            case 1: {
                printf("\nEnter Admin Password: ");
                scanf("%s", tempPass);

                // Verify admin password
                if (strcmp(tempPass, adminPass) == 0) {
                    int adminChoice;
                    while (1) {
                        // Admin panel options
                        printf("\n--- ADMIN PANEL ---\n");
                        printf("1. Add New Account\n");
                        printf("2. Delete Account\n");
                        printf("3. View All Accounts\n");
                        printf("4. Reset Account Password\n");
                        printf("5. Back to Main Menu\n");
                        printf("Enter choice: ");
                        scanf("%d", &adminChoice);

                        switch (adminChoice) {
                            case 1:  // Add new account
								printf("\nEnter Name: ");
                                scanf("%s", names[totalAccounts]);
                                fflush(stdin);
							    printf("Enter Account Number: ");
                                scanf("%d", &accNo[totalAccounts]);
                                printf("Set Password: ");
                                scanf("%s", passwords[totalAccounts]);
                                printf("Enter Initial Balance: ");
                                scanf("%f", &balance[totalAccounts]);
                                printf("Account Created Successfully!\n");
                                totalAccounts++;
                                break;

                            case 2:  // Delete existing account
                                printf("\nEnter Account Number to Delete: ");
                                int delAcc;
                                scanf("%d", &delAcc);
                                int found = 0;

                                // Search account to delete
                                for (i = 0; i < totalAccounts; i++) {
                                    if (accNo[i] == delAcc) {
                                        // Shift elements to remove account
                                        for (j = i; j < totalAccounts - 1; j++) {
                                            strcpy(names[j], names[j + 1]);
                                            accNo[j] = accNo[j + 1];
                                            strcpy(passwords[j], passwords[j + 1]);
                                            balance[j] = balance[j + 1];
                                        }
                                        totalAccounts--;
                                        printf("Account Deleted!\n");
                                        found = 1;
                                        break;
                                    }
                                }
                                if (!found) printf("Account Not Found!\n");
                                break;

                            case 3:  // View list of all accounts
                                printf("\n--- ALL ACCOUNTS ---\n");
                                for (i = 0; i < totalAccounts; i++) {
                                    printf("Name: %s | AccNo: %d | Balance: %.2f\n",
                                           names[i], accNo[i], balance[i]);
                                }
                                break;

                            
                               case 4:  // Reset password to new password entered by admin
                                 printf("Enter Account Number to Reset Password: ");
                                 int resAcc;
                                 scanf("%d", &resAcc);
                                 found = 0;

                                // Search and reset
                               for (i = 0; i < totalAccounts; i++) {
                                if (accNo[i] == resAcc) {
                                char newPass[20];
                               printf("Enter new password for account %d: ", resAcc);
                              scanf("%s", newPass);        // Take new password input
                            strcpy(passwords[i], newPass);  // Set the new password
                                 printf("Password reset successfully!\n");
                             found = 1;
                            break;
                               }
                          }
                              if (!found) printf("Account Not Found!\n");
                             break;

                            case 5:
                                // Exit admin panel
                                goto endAdmin;
                        }
                    }
                endAdmin:
                    ;
                } else {
                    printf("Incorrect Admin Password!\n");
                }
                break;
            }

            // --------------------------- ATM SERVICES ---------------------------
            case 2: {
                int userAcc;
                char userPass[20];

                // Login section
                printf("\nEnter Account Number: ");
                scanf("%d", &userAcc);
                printf("Enter Password: ");
                scanf("%s", userPass);

                int loggedIn = 0;

                // Validate user credentials
                for (i = 0; i < totalAccounts; i++) {
                    if (accNo[i] == userAcc && strcmp(passwords[i], userPass) == 0) {
                        accIndex = i;
                        loggedIn = 1;
                        break;
                    }
                }

                // If login is successful
                if (loggedIn) {
                    int atmChoice;
                    while (1) {
                        printf("\n--- ATM SERVICES ---\n");
                        printf("1. Withdraw Money\n");
                        printf("2. Deposit Money\n");
                        printf("3. Check Balance\n");
                        printf("4. Transfer Money\n");
                        printf("5. Mini Statement\n");
                        printf("6. Back to Main Menu\n");
                        printf("Enter choice: ");
                        scanf("%d", &atmChoice);

                        // Withdraw money
                        if (atmChoice == 1) {
                            float amt;
                            printf("Enter amount to withdraw: ");
                            scanf("%f", &amt);
                            if (balance[accIndex] >= amt) {
                                balance[accIndex] -= amt;
                                printf("Withdraw successful! New balance: %.2f\n", balance[accIndex]);
                                sprintf(transactions[accIndex][transCount[accIndex]++],
                                        "Withdraw: -%.2f", amt);
                            } else {
                                printf("Insufficient Balance!\n");
                            }
                        }

                        // Deposit money
                        else if (atmChoice == 2) {
                            float amt;
                            printf("Enter amount to deposit: ");
                            scanf("%f", &amt);
                            balance[accIndex] += amt;
                            printf("Deposit successful! New balance: %.2f\n", balance[accIndex]);
                            sprintf(transactions[accIndex][transCount[accIndex]++],
                                    "Deposit: +%.2f", amt);
                        }

                        // Check balance
                        else if (atmChoice == 3) {
                            printf("Current Balance: %.2f\n", balance[accIndex]);
                        }

                        // Transfer money to another account
                        else if (atmChoice == 4) {
                            int recvAcc;
                            float amt;
                            printf("Enter receiver account number: ");
                            scanf("%d", &recvAcc);
                            printf("Enter amount to transfer: ");
                            scanf("%f", &amt);

                            int recvIndex = -1;
                            for (i = 0; i < totalAccounts; i++) {
                                if (accNo[i] == recvAcc) {
                                    recvIndex = i;
                                    break;
                                }
                            }

                            if (recvIndex != -1 && balance[accIndex] >= amt) {
                                balance[accIndex] -= amt;
                                balance[recvIndex] += amt;
                                printf("Transfer successful!\n");
                                sprintf(transactions[accIndex][transCount[accIndex]++],
                                        "Transfer Out: -%.2f", amt);
                                sprintf(transactions[recvIndex][transCount[recvIndex]++],
                                        "Transfer In: +%.2f", amt);
                            } else {
                                printf("Transfer Failed!\n");
                            }
                        }

                        // View mini statement (recent transactions)
                        else if (atmChoice == 5) {
                            printf("\n--- MINI STATEMENT ---\n");
                            for (j = 0; j < transCount[accIndex]; j++) {
                                printf("%s\n", transactions[accIndex][j]);
                            }
                        }

                        // Exit ATM menu
                        else if (atmChoice == 6)
                            goto endATM;
                    }
                endATM:
                    ;
                } else {
                    printf("Invalid Login!\n");
                }
                break;
            }

            // --------------------------- HELP DESK ---------------------------
            case 3: {
                int helpChoice;
                while (1) {
                    // Help menu options
                    printf("\n--- HELP DESK ---\n");
                    printf("1. How to open account?\n");
                    printf("2. How to deposit money?\n");
                    printf("3. How to withdraw money?\n");
                    printf("4. How to transfer money?\n");
                    printf("5. How to check balance?\n");
                    printf("6. Back to Main Menu\n");
                    printf("Enter choice: ");
                    scanf("%d", &helpChoice);

                    // Simple informational responses
                    if (helpChoice == 1)
                        printf("Visit bank or admin section to create a new account.\n");
                    else if (helpChoice == 2)
                        printf("Login to ATM Services and select Deposit.\n");
                    else if (helpChoice == 3)
                        printf("Login to ATM Services and select Withdraw.\n");
                    else if (helpChoice == 4)
                        printf("Login to ATM Services and select Transfer.\n");
                    else if (helpChoice == 5)
                        printf("Login to ATM Services and select Check Balance.\n");
                    else if (helpChoice == 6)
                        break;
                }
                break;
            }

            // --------------------------- ADDITIONAL FEATURES ---------------------------
            case 4: {
                int addChoice;
                while (1) {
                    printf("\n--- ADDITIONAL FEATURES ---\n");
                    printf("1. Interest Calculation\n");
                    printf("2. View Highest Balance Account\n");
                    printf("3. View Accounts Below Balance Threshold\n");
                    printf("4. Total Accounts Summary\n");
                    printf("5. Back to Main Menu\n");
                    printf("Enter choice: ");
                    scanf("%d", &addChoice);

                    // Add interest to all accounts
                    if (addChoice == 1) {
                        float rate;
                        printf("Enter interest rate (%%): ");
                        scanf("%f", &rate);
                        for (i = 0; i < totalAccounts; i++) {
                            float interest = balance[i] * rate / 100.0;
                            balance[i] += interest;
                        }
                        printf("Interest added successfully to all accounts!\n");
                    }

                    // Display account with highest balance
                    else if (addChoice == 2) {
                        if(totalAccounts == 0){ 
                            printf("No accounts yet!\n"); 
                            continue;
                        }
                        int maxIndex = 0;
                        for(i = 1; i < totalAccounts; i++)
                            if(balance[i] > balance[maxIndex])
                                maxIndex = i;
                        printf("Highest Balance Account: %s | AccNo: %d | Balance: %.2f\n",
                               names[maxIndex], accNo[maxIndex], balance[maxIndex]);
                    }

                    // Display accounts with balance below a limit
                    else if (addChoice == 3) {
                        float limit;
                        printf("Enter balance threshold: ");
                        scanf("%f", &limit);
                        printf("Accounts below %.2f:\n", limit);
                        for(i = 0; i < totalAccounts; i++)
                            if(balance[i] < limit)
                                printf("Name: %s | AccNo: %d | Balance: %.2f\n",
                                       names[i], accNo[i], balance[i]);
                    }

                    // Display total number of accounts
                    else if (addChoice == 4) {
                        printf("Total Accounts: %d\n", totalAccounts);
                    }

                    // Exit additional features
                    else if (addChoice == 5)
                        break;
                }
                break;
            }

            // --------------------------- EXIT ---------------------------
            case 5: {
                char ch;
                printf("Are you sure you want to exit? (y/n): ");
                scanf(" %c", &ch);
                if (ch == 'y' || ch == 'Y') {
                    printf("Thank you for using our Bank!\n");
                    return 0;
                }
                break;
            }

            // Invalid menu input
            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}
