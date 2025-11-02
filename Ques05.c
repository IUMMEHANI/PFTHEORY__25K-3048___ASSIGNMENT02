#include <stdio.h>
#include <string.h>
void encoding(char message[]);
void decoding(char message[]);
void encoding(char message[]) {
    int length = strlen(message);
    int i;
    for ( i = 0; i < length / 2; i++) {
        char temp = message[i];
        message[i] = message[length - i - 1];
        message[length - i - 1] = temp;
    }
    printf("\nReversed string: %s\n", message);
    for ( i = 0; i < length; i++) {
        message[i] = message[i] ^ (1 << 1); 
        message[i] = message[i] ^ (1 << 4);  
    }
    printf("Encoded Message: %s\n", message);
}
void decoding(char message[]) {
    int length = strlen(message);
    int i;
    for ( i = 0; i < length; i++) {
        message[i] = message[i] ^ (1 << 1);
        message[i] = message[i] ^ (1 << 4);
    }
    for ( i = 0; i < length / 2; i++) {
        char temp = message[i];
        message[i] = message[length - i - 1];
        message[length - i - 1] = temp;
    }
    printf("Decoded Message: %s\n", message);
}

int main() {
    int choice;
    char message[100];
    do {
        printf("\nWELCOME TO TCS\n");
        printf("1. ENCODE MESSAGE\n");
        printf("2. DECODE MESSAGE\n");
        printf("3. EXIT\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); 
        switch (choice) {
            case 1:
                printf("Enter a message: ");
                fgets(message, sizeof(message), stdin);
                message[strcspn(message, "\n")] = '\0'; 
                encoding(message);
                break;
            case 2:
                printf("Enter a message: ");
                fgets(message, sizeof(message), stdin);
                message[strcspn(message, "\n")] = '\0';
                decoding(message);
                break;
            case 3:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 3);
    return 0;
}

