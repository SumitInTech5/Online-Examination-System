/* =============================================================
   ONLINE EXAMINATION MANAGEMENT SYSTEM
   =============================================================
   PROJECT OVERVIEW:
   -----------------
   This program simulates a basic online examination system.
   It allows students to register, log in, take exams, and view their scores.
   The admin can log in separately to add questions and view user results.
   Data is stored in text and binary files.
   FEATURES:
   ---------
   ✅ User Registration and Login
   ✅ Secure Admin Login
   ✅ Add Questions (MCQs)
   ✅ Take Exams
   ✅ Auto Scoring System
   ✅ View Individual Results
   ✅ View All Results (Admin)
   ✅ File-based Data Storage
   ✅ User-Friendly Interface
   Developed by: Sumit Kumar Sah
   Date : December 2025
   Language : C Programming
   Admin Credentials : Username: admin, Password: admin123
   ============================================================= */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>      // For getch()
#include <ctype.h>      // For toupper()
#include <time.h>       // For date/time

#define MAX_QUESTIONS 100
#define MAX_NAME 50
#define MAX_PASS 20

// ===================== STRUCTURES ==========================
typedef struct {
    char question[200];
    char options[4][100];
    char correctOption;
} Question;

typedef struct {
    char username[MAX_NAME];
    int score;
    int total;
    char date[30];
} Result;

// ===================== FUNCTION DECLARATIONS ===============
void mainMenu();
void registerUser();
int loginUser(char username[]);
void userDashboard(char username[]);
void takeExam(char username[]);
void viewUserResults(char username[]);
void adminLogin();
void adminDashboard();
void addQuestions();
void viewAllResults();
void clearScreen();
void pause();
void getDate(char *buffer);

// ===================== UTILITY FUNCTIONS ===================
void clearScreen() {
    system("cls"); // For Windows; use "clear" on Linux/Mac
}

void pause() {
    printf("\nPress any key to continue...");
    getch();
}

// Function to get current date and time
void getDate(char *buffer) {
    time_t t;
    time(&t);
    strftime(buffer, 30, "%d-%m-%Y %H:%M:%S", localtime(&t));
}

// ===================== MAIN FUNCTION =======================
int main() {
    mainMenu();
    return 0;
}

// ===================== MAIN MENU ===========================
void mainMenu() {
    int choice;
    char username[MAX_NAME];

    while (1) {
        clearScreen();
        printf("\n========================================================\n");
        printf(" WELCOME TO ONLINE EXAMINATION SYSTEM \n");
        printf("========================================================\n");
        printf("1. Register New User\n");
        printf("2. Login as User\n");
        printf("3. Login as Admin\n");
        printf("4. Exit\n");
        printf("--------------------------------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                if (loginUser(username))
                    userDashboard(username);
                break;
            case 3:
                adminLogin();
                break;
            case 4:
                clearScreen();
                printf("\nThank you for using the Online Examination System.\n");
                exit(0);
            default:
                printf("\nInvalid choice! Please try again.\n");
                pause();
        }
    }
}

// ===================== USER REGISTRATION ===================
void registerUser() {
    FILE *fp;
    char username[MAX_NAME], password[MAX_PASS], u[MAX_NAME], p[MAX_PASS];
    int exists = 0;

    clearScreen();
    printf("\n----------------- USER REGISTRATION -----------------\n");
    printf("Enter new username: ");
    scanf("%s", username);
    printf("Enter new password: ");
    scanf("%s", password);

    // Check if username already exists
    fp = fopen("users.txt", "r");
    if (fp != NULL) {
        while (fscanf(fp, "%s %s", u, p) != EOF) {
            if (strcmp(username, u) == 0) {
                exists = 1;
                break;
            }
        }
        fclose(fp);
    }

    if (exists) {
        printf("\n Username already exists. Please choose another.\n");
        pause();
        return;
    }

    fp = fopen("users.txt", "a");
    if (fp == NULL) {
        printf("Error: Unable to open file!\n");
        pause();
        return;
    }

    fprintf(fp, "%s %s\n", username, password);
    fclose(fp);

    printf("\n Registration successful! You can now log in.\n");
    pause();
}

// ===================== USER LOGIN ==========================
int loginUser(char username[]) {
    FILE *fp;
    char password[MAX_PASS];
    char u[MAX_NAME], p[MAX_PASS];
    int found = 0;

    clearScreen();
    printf("\n------------------- USER LOGIN --------------------\n");
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    fp = fopen("users.txt", "r");
    if (fp == NULL) {
        printf("\nNo registered users found. Please register first.\n");
        pause();
        return 0;
    }

    while (fscanf(fp, "%s %s", u, p) != EOF) {
        if (strcmp(username, u) == 0 && strcmp(password, p) == 0) {
            found = 1;
            break;
        }
    }
    fclose(fp);

    if (found) {
        printf("\n Login successful! Welcome, %s.\n", username);
        pause();
        return 1;
    } else {
        printf("\n Invalid credentials! Try again.\n");
        pause();
        return 0;
    }
}

// ===================== USER DASHBOARD ======================
void userDashboard(char username[]) {
    int choice;

    while (1) {
        clearScreen();
        printf("\n================== USER DASHBOARD ==================\n");
        printf("Welcome, %s!\n", username);
        printf("1. Take Exam\n");
        printf("2. View Your Results\n");
        printf("3. Logout\n");
        printf("----------------------------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                takeExam(username);
                break;
            case 2:
                viewUserResults(username);
                break;
            case 3:
                return;
            default:
                printf("\nInvalid choice! Try again.\n");
                pause();
        }
    }
}

// ===================== ADMIN LOGIN =========================
void adminLogin() {
    char user[20], pass[20];
    clearScreen();
    printf("\n-------------------- ADMIN LOGIN --------------------\n");
    printf("Enter admin username: ");
    scanf("%s", user);
    printf("Enter admin password: ");
    scanf("%s", pass);
//admin username: admin
//admin password: admin123
    if (strcmp(user, "admin") == 0 && strcmp(pass, "admin123") == 0) {
        printf("\n Admin Login Successful!\n");
        pause();
        adminDashboard();
    } else {
        printf("\n Invalid admin credentials!\n");
        pause();
    }
}

// ===================== ADMIN DASHBOARD =====================
void adminDashboard() {
    int choice;

    while (1) {
        clearScreen();
        printf("\n================== ADMIN DASHBOARD ==================\n");
        printf("1. Add Questions\n");
        printf("2. View All Results\n");
        printf("3. Logout\n");
        printf("----------------------------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addQuestions();
                break;
            case 2:
                viewAllResults();
                break;
            case 3:
                return;
            default:
                printf("\nInvalid choice! Try again.\n");
                pause();
        }
    }
}

// ===================== ADD QUESTIONS =======================
void addQuestions() {
    FILE *fp;
    Question q;
    int n, i, j;

    clearScreen();
    printf("\nEnter number of questions to add: ");
    scanf("%d", &n);
    getchar();

    fp = fopen("questions.dat", "ab");
    if (fp == NULL) {
        printf("\nError: Unable to open file!\n");
        pause();
        return;
    }

    for (i = 0; i < n; i++) {
        printf("\nQuestion %d: ", i + 1);
        fgets(q.question, sizeof(q.question), stdin);
        q.question[strcspn(q.question, "\n")] = 0;

        for (j = 0; j < 4; j++) {
            printf("Option %c: ", 'A' + j);
            fgets(q.options[j], sizeof(q.options[j]), stdin);
            q.options[j][strcspn(q.options[j], "\n")] = 0;
        }

        printf("Correct option (A/B/C/D): ");
        scanf(" %c", &q.correctOption);
        getchar();

        fwrite(&q, sizeof(Question), 1, fp);
    }

    fclose(fp);
    printf("\n Questions added successfully!\n");
    pause();
}

// ===================== TAKE EXAM ===========================
void takeExam(char username[]) {
    FILE *fp, *rfp;
    Question q;
    Result r;
    int score = 0, total = 0;
    char ans;

    fp = fopen("questions.dat", "rb");
    if (fp == NULL) {
        printf("\n No questions available. Contact admin.\n");
        pause();
        return;
    }

    clearScreen();
    printf("\n================== EXAM START ==================\n");

    while (fread(&q, sizeof(Question), 1, fp)) {
        total++;
        printf("\nQ%d: %s\n", total, q.question);
        printf("A) %s\nB) %s\nC) %s\nD) %s\n", q.options[0], q.options[1], q.options[2], q.options[3]);
        printf("Your answer: ");
        scanf(" %c", &ans);

        if (toupper(ans) == toupper(q.correctOption))
            score++;
    }

    fclose(fp);

    strcpy(r.username, username);
    r.score = score;
    r.total = total;
    getDate(r.date);

    rfp = fopen("results.txt", "a");
    fprintf(rfp, "%s %d/%d %s\n", r.username, r.score, r.total, r.date);
    fclose(rfp);

    printf("\n Exam Completed Successfully!");
    printf("\nYour Score: %d/%d\n", score, total);
    pause();
}

// ===================== VIEW USER RESULTS ===================
void viewUserResults(char username[]) {
    FILE *fp;
    char u[MAX_NAME], date[30];
    int score, total;
    int found = 0;

    fp = fopen("results.txt", "r");
    if (fp == NULL) {
        printf("\nNo results available.\n");
        pause();
        return;
    }

    clearScreen();
    printf("\n=============== YOUR EXAM HISTORY ===============\n");

    while (fscanf(fp, "%s %d/%d %s", u, &score, date) != EOF) {
        if (strcmp(username, u) == 0) {
            printf("Date: %-20s | Score: %d/%d\n", date, score);
            found = 1;
        }
    }
    fclose(fp);

    if (!found)
        printf("\nNo results found for this user.\n");

    pause();
}

// ===================== VIEW ALL RESULTS ====================
void viewAllResults() {
    FILE *fp;
    char u[MAX_NAME], date[30];
    int score, total;

    fp = fopen("results.txt", "r");
    if (fp == NULL) {
        printf("\nNo results found!\n");
        pause();
        return;
    }

    clearScreen();
    printf("\n=============== ALL USER RESULTS ===============\n");

    while (fscanf(fp, "%s %d/%d %s", u, &score, &total, date) != EOF) {
        printf("User: %s | Score: %d/%d | Date: %s\n", u, score, total, date);
    }

    fclose(fp);
    pause();
}