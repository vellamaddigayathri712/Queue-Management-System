#include<stdio.h>
#include<stdlib.h>
#include<string.h>  // Added for strcmp
// Removed <conio.h> and clrscr(), as they aren't standard and won't work in VS Code

struct student {
    char rollno[20];
    char name[20];
    char time[20];
};

struct student user[20];
int count = 0, num = 0, i = 0;

void jointoqueue() {
    char ch;
    FILE *fp = fopen("Queue_Logger.txt", "a"); // Changed to "a" to append
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    if (count >= 20) {
        printf("\nQUEUE IS FULL\n");
        return;
    }

    printf("Enter your Roll Number:\n");
    scanf("%s", user[count].rollno); // Removed & (not needed for arrays)
    printf("Enter your Name:\n");
    scanf("%s", user[count].name);
    printf("Enter the Arrival Time:\n");
    scanf("%s", user[count].time);

    printf("\n**YOU ADDED TO QUEUE SUCCESSFULLY\n");

    fprintf(fp, "Action:Entered to Queue\n");
    fprintf(fp, "Current Queue(Total :%d students):\n\n", count + 1);
    for (i = 0; i <= count; i++) {
        fprintf(fp, "Position:%d\n", i + 1);
        fprintf(fp, "Roll Number:%s\n", user[i].rollno);
        fprintf(fp, "Name:%s\n", user[i].name);
        fprintf(fp, "Arrival Time:%s\n\n", user[i].time);
    }

    count++;
    fclose(fp);
    return;
}

void serve() {
    char ch;
    FILE *fp = fopen("Queue_Logger.txt", "a");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    if (count == 0) {
        printf("QUEUE IS EMPTY\n");
        return;
    }

    if (num >= 5) {
        printf("LAB IS FULL\n");
        printf("PLEASE WAIT IN QUEUE\n");
    } else {
        printf("Roll Number:%s\n", user[0].rollno);
        printf("Name:%s\n", user[0].name);
        printf("Arrival Time:%s\n", user[0].time);
        fprintf(fp, "Action:Allowed to Lab\n");
        fprintf(fp, "Served to You:\n");
        fprintf(fp, "Roll Number:%s\n", user[0].rollno);
        fprintf(fp, "Name:%s\n", user[0].name);
        fprintf(fp, "Arrival Time:%s\n\n", user[0].time);

        for (i = 0; i < count - 1; i++) {
            user[i] = user[i + 1];
        }
        count--;
        num++;
    }
    fclose(fp);
}

void check() {
    char ch;
    char roll[20];
    FILE *fp = fopen("Queue_Logger.txt", "a");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter the RollNumber:");
    scanf("%s", roll);
    fprintf(fp, "Action:Checking the current position in the queue\n");
    for (i = 0; i < count; i++) {
        if (strcmp(user[i].rollno, roll) == 0) {
            printf("Your current position in the queue is :%d\n", i + 1);
            fprintf(fp, "Your current position in the queue is :%d\n", i + 1);
            fclose(fp);
            return;
        }
    }
    printf("Roll Number %s is not found in the queue.\n", roll);
    fprintf(fp, "Roll Number %s is not found in the queue.\n", roll);
    fclose(fp);
}

void leave() {
    char ch;
    FILE *fp = fopen("Queue_Logger.txt", "a");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    fprintf(fp, "Action:Leave\n");
    if (num == 0) {
        printf("LAB IS EMPTY\n");
        fclose(fp);
        return;
    }
    num--;
    fclose(fp);
}

void display(struct student arr[20]) {
    if (count == 0) {
        printf("QUEUE IS EMPTY\n");
        return;
    }

    for (i = 0; i < count; i++) {
        printf("Roll Number:%s\n", arr[i].rollno);
        printf("Name:%s\n", arr[i].name);
        printf("Arrival Time:%s\n", arr[i].time);
    }
    printf("\n**END\n");
}

void labstatus() {
    char ch;
    FILE *fp = fopen("Queue_Logger.txt", "a");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    if (num == 0) {
        printf("LAB IS EMPTY\n");
    } else {
        printf("Seats Available:%d/5\n", (5 - num));
        fprintf(fp, "Seats Available:%d/5\n", (5 - num));
    }
    fclose(fp);
}

void logqueue() {
    char pass[20];
    char ch;
    FILE *f = fopen("Queue_Logger.txt", "a");
    if (f == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter password: ");
    scanf("%s", pass);

    if (strcmp("RGMCET", pass) == 0) {
        fprintf(f, "Queue successfully logged to 'Queue_Logger.txt'\n");
        printf("Queue successfully logged to 'Queue_Logger.txt'\n");
    } else {
        printf("Wrong Password!\nTry Again!\n");
        fprintf(f, "Wrong Password!\nTry Again!\n");
    }

    fclose(f);
}

void menu() {
    int num, size;
    printf("Menu:1.Join To Queue\n2.Display the Queue\n3.LabStatus\n4.Check the position\n5.Leave\n6.Queue_Logger\n7.Exit\n");
    printf("Enter your choice\n");
    scanf("%d", &num);

    switch (num) {
        case 1:
            jointoqueue();
            break;
        case 2:
            display(user);
            break;
        case 3:
            serve();
            labstatus();
            break;
        case 4:
            check();
            break;
        case 5:
            leave();
            break;
        case 6:
            logqueue();
            break;
        case 7:
            printf("\n&&& THANK YOU! &&&\n");
            break;// Exit cleanly
        default:
            printf("TRY AGAIN\n");
    }
    return;
}

int main() {
    // Removed clrscr(); // Not standard
    for (i = 0; i < 10; i++) {
        menu();
    }
    return 0;
}
