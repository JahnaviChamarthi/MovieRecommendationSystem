#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<windows.h>
#include<string.h>

void gotoxy(int ,int );
void displayMenu();
void bookTicket();
void viewBookings();
void searchBooking();
void modifyBooking();
void cancelBooking();

struct movieBooking {
    char movieName[50];
    char customerName[50];
    int numTickets;
    float totalPrice;
};

int main()
{
    gotoxy(15,8);
    printf("<--:MOVIE TICKET BOOKING SYSTEM:-->");
    gotoxy(19,15);
    printf("Press any key to continue.");
    getch();
    displayMenu();
    return 0;
}

void displayMenu()
{
    int choice;
    system("cls"); //clrscr()
    gotoxy(10,3);
    printf("<--:MENU:-->");
    gotoxy(10,5);
    printf("Enter appropriate number to perform following task.");
    gotoxy(10,7);
    printf("1 : Book Ticket.");
    gotoxy(10,8);
    printf("2 : View Bookings.");
    gotoxy(10,9);
    printf("3 : Search Bookings.");
    gotoxy(10,10);
    printf("4 : Modify Bookings.");
    gotoxy(10,11);
    printf("5 : Cancel Booking.");
    gotoxy(10,12);
    printf("6 : Exit.");
    gotoxy(10,15);
    printf("Enter your choice.");
    scanf("%d",&choice);
    switch(choice)
    {
    case 1:
        bookTicket();
        break;

    case 2:
        viewBookings();
        break;

    case 3:
        searchBooking();
        break;

    case 4:
        modifyBooking();
        break;

    case 5:
        cancelBooking();
        break;

    case 6:
        exit(1);
        break;

    default:
        gotoxy(10,17);
        printf("Invalid Choice.");
    }
}

void bookTicket() {
    FILE *fp;
    struct movieBooking booking;
    char another ='y';
    system("cls");

    fp = fopen("bookings.txt","ab+");
    if(fp == NULL){
        gotoxy(10,5);
        printf("Error opening file");
        exit(1);
    }
    fflush(stdin);
    while(another=='y'){
        gotoxy(10,3);
        printf("\n---- Book Ticket ----\n");
        gotoxy(10,5);
        printf("Enter Movie Name: ");
        scanf("%s", booking.movieName);
        gotoxy(10,6);
        printf("Enter Customer Name: ");
        scanf("%s", booking.customerName);
        gotoxy(10,7);
        printf("Enter Number of Tickets: ");
        scanf("%d", &booking.numTickets);
        gotoxy(10,8);
        printf("Enter Total Price: ");
        scanf("%f", &booking.totalPrice);
        fwrite(&booking, sizeof(struct movieBooking), 1, fp);
        printf("Booking successful!\n");
        gotoxy(10,10);
        printf("Want to add of another record? Then press 'y' else 'n'.");
        fflush(stdin);
        another = getch();
        system("cls");
        fflush(stdin);
    }
    fclose(fp);
    gotoxy(10,15);
    printf("Press any key to continue.");
    getch();
    displayMenu();
}

void viewBookings() {
    struct movieBooking booking;
    system("cls");
    gotoxy(10,3);
    printf("\n---- View Bookings ----\n");
    gotoxy(10,5);
    FILE *fp = fopen("bookings.txt", "rb");
    if (fp == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }
    printf("Movie Name\tCustomer Name\tTickets\tTotal Price\n");
    gotoxy(10,6);
    printf("--------------------------------------------------\n");
    int j=7;
    while (fread(&booking, sizeof(struct movieBooking), 1, fp) == 1) {
        gotoxy(10,j);
        printf("%s\t\t%s\t\t%d\t%.2f\n", booking.movieName, booking.customerName,
        booking.numTickets, booking.totalPrice);
        j++;
    }
    fclose(fp);
    gotoxy(10,j+3);
    printf("Press any key to continue.");
    getch();
    displayMenu();
}

void searchBooking() {
    struct movieBooking booking;
    char searchName[50];
    system("cls");
    gotoxy(10,3);
    printf("\n---- Search Booking ----\n");
    gotoxy(10,5);
    printf("Enter Customer Name to search: ");
    scanf("%s", searchName);
    FILE *fp = fopen("bookings.txt", "rb");
    if (fp == NULL) {
        gotoxy(10,7);
        printf("Error opening file for reading.\n");
        return;
    }
    while (fread(&booking, sizeof(struct movieBooking), 1, fp) == 1) {
        if (strcmp(searchName, booking.customerName) == 0) {
            gotoxy(10,8);
            printf("Movie Name\tCustomer Name\tTickets\tTotal Price\n");
            gotoxy(10,9);
            printf("--------------------------------------------------\n");
            printf("%s\t\t%s\t\t%d\t%.2f\n", booking.movieName, booking.customerName,
            booking.numTickets, booking.totalPrice);
            fclose(fp);
            return;
        }
    }
    printf("Booking not found for customer: %s\n", searchName);
    fclose(fp);
    printf("Press any key to continue.");
    getch();
    displayMenu();
}

void modifyBooking() {
    struct movieBooking booking;
    char modifyName[50];
    system("cls");
    gotoxy(10,3);
    printf("\n---- Modify Booking ----\n");
    gotoxy(10,5);
    printf("Enter Customer Name to modify: ");
    scanf("%s", modifyName);
    gotoxy(10,7);
    FILE *fp = fopen("bookings.txt", "r+b");
    if (fp == NULL) {
        gotoxy(10,8);
        printf("Error opening file for reading and writing.\n");
        return;
    }
    while (fread(&booking, sizeof(struct movieBooking), 1, fp) == 1) {
        if (strcmp(modifyName, booking.customerName) == 0) {
            gotoxy(10,9);
            printf("Enter new Number of Tickets: ");
            scanf("%d", &booking.numTickets);
            gotoxy(10,11);
            printf("Enter new Total Price: ");
            scanf("%f", &booking.totalPrice);
            fseek(fp, -sizeof(struct movieBooking), SEEK_CUR);
            fwrite(&booking, sizeof(struct movieBooking), 1, fp);
            fclose(fp);
            gotoxy(10,13);
            printf("Booking modified successfully!\n");
            return;
        }
    }
    gotoxy(10,15);
    printf("Booking not found for customer: %s\n", modifyName);
    fclose(fp);
    printf("Press any key to continue.");
    getch();
    displayMenu();
}

void cancelBooking() {
    struct movieBooking booking;
    char cancelName[50];
    system("cls");
    gotoxy(10,3);
    printf("\n---- Cancel Booking ----\n");
    gotoxy(10,5);
    printf("Enter Customer Name to cancel booking: ");
    scanf("%s", cancelName);
    gotoxy(10,6);
    FILE *fp = fopen("bookings.txt", "rb");
    if (fp == NULL) {
        gotoxy(10,7);
        printf("Error opening file for reading.\n");
        return;
    }
    FILE *tempFile = fopen("temp.txt", "wb");
    if (tempFile == NULL) {
        gotoxy(10,8);
        printf("Error opening temporary file for writing.\n");
        fclose(fp);
        return;
    }
    int bookingFound = 0;
    while (fread(&booking, sizeof(struct movieBooking), 1, fp) == 1) {
        if (strcmp(cancelName, booking.customerName) == 0) {
            gotoxy(10,10);
            printf("Booking for customer %s canceled.\n", cancelName);
            bookingFound = 1;
        }
        else {
            fwrite(&booking, sizeof(struct movieBooking), 1, tempFile);
        }
    }
    fclose(fp);
    fclose(tempFile);
    remove("bookings.txt");
    rename("temp.txt", "bookings.txt");
    if (!bookingFound) {
        gotoxy(10,12);
        printf("Booking not found for customer: %s\n", cancelName);
    }
    printf("Press any key to continue.");
    getch();
    displayMenu();
}

void gotoxy(int x,int y)
{
        COORD c;
        c.X=x;
        c.Y=y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}
