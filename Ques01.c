#include <stdio.h>
#include <string.h>
#define MAX_BOOKS 100
void addNewBook(int isbns[], char titles[][50], float prices[], int quantities[], int *bookCount);
void processSale(int isbns[], char titles[][50], float prices[], int quantities[], int bookCount);
void lowStockReport(int isbns[], char titles[][50], float prices[], int quantities[], int bookCount);

int main() {
    int isbns[MAX_BOOKS];
    char titles[MAX_BOOKS][50];
    float prices[MAX_BOOKS];
    int quantities[MAX_BOOKS];
    int bookCount = 0;
    int choice;
    do {
        printf("\n=== Liberty Books Inventory System ===\n");
        printf("1. Add New Book\n");
        printf("2. Process a Sale\n");
        printf("3. Generate Low-Stock Report\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                addNewBook(isbns, titles, prices, quantities, &bookCount);
                break;
            case 2:
                processSale(isbns, titles, prices, quantities, bookCount);
                break;
            case 3:
                lowStockReport(isbns, titles, prices, quantities, bookCount);
                break;
            case 4:
                printf("Exiting system...\n");
                break;
            default:
                printf("Invalid choice! Try again.\n");
        }
    } while(choice != 4);

    return 0;
}
void addNewBook(int isbns[], char titles[][50], float prices[], int quantities[], int *bookCount) {
    if(*bookCount >= MAX_BOOKS) {
        printf("Inventory full! Cannot add more books.\n");
        return;
    }

    int newISBN;
    char newTitle[50];
    float newPrice;
    int newQuantity;
    printf("Enter ISBN: ");
    scanf("%d", &newISBN);
    int i;
    for( i = 0; i < *bookCount; i++) {
        if(isbns[i] == newISBN) {
            printf("This ISBN already exists!\n");
            return;
        }
    }
    printf("Enter Book Title: ");
    scanf(" %[^\n]s", newTitle);
    printf("Enter Price: ");
    scanf("%f", &newPrice);
    printf("Enter Quantity: ");
    scanf("%d", &newQuantity);
    isbns[*bookCount] = newISBN;
    strcpy(titles[*bookCount], newTitle);
    prices[*bookCount] = newPrice;
    quantities[*bookCount] = newQuantity;

    (*bookCount)++;
    printf("Book added successfully!\n");
}
void processSale(int isbns[], char titles[][50], float prices[], int quantities[], int bookCount) {
    if(bookCount == 0) {
        printf("No books in inventory.\n");
        return;
    }

    int saleISBN, saleQty, found = 0;
    printf("Enter ISBN of book to sell: ");
    scanf("%d", &saleISBN);
    int i;
    for( i = 0; i < bookCount; i++) {
        if(isbns[i] == saleISBN) {
            found = 1;
            printf("Enter quantity to sell: ");
            scanf("%d", &saleQty);

            if(saleQty <= quantities[i]) {
                quantities[i] -= saleQty;
                printf("Sale processed! Remaining quantity: %d\n", quantities[i]);
            } else {
                printf("Not enough stock! Available: %d\n", quantities[i]);
            }
            break;
        }
    }

    if(!found) {
        printf("Book with ISBN %d not found.\n", saleISBN);
    }
}
void lowStockReport(int isbns[], char titles[][50], float prices[], int quantities[], int bookCount) {
    int found = 0;
    int i;
    printf("\n=== Low Stock Report (Quantity < 5) ===\n");
    for( i = 0; i < bookCount; i++) {
        if(quantities[i] < 5) {
            printf("ISBN: %d | Title: %s | Price: %.2f | Quantity: %d\n", isbns[i], titles[i], prices[i], quantities[i]);
            found = 1;
        }
    }
    if(!found) {
        printf("No books with low stock.\n");
    }
}

