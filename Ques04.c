#include <stdio.h>
void push(int stack[], int *top, int b);
void pop(int stack[], int *top);
void peek(int stack[], int top);
void display(int stack[], int top);
void push(int stack[], int *top, int b) {
    if (*top == b - 1) {
        printf("Stack Overflow! Cannot push more elements.\n");
    } else {
        int val;
        printf("Enter an element to push: ");
        scanf("%d", &val);
        (*top)++;              
        stack[*top] = val;    
        printf("%d pushed onto the stack.\n", val);
    }
}
void pop(int stack[], int *top) {
    if (*top == -1) {
        printf("Stack Underflow! Cannot pop elements.\n");
    } else {
        printf("Popped element is: %d\n", stack[*top]);
        (*top)--;
    }   
}
void peek(int stack[], int top) {
    if (top == -1) {
        printf("Stack is empty!\n");
    } else {
        printf("Top element is: %d\n", stack[top]);
    }             
}
void display(int stack[], int top) {
    if (top == -1) {
        printf("Stack is empty!\n");
    } else {
        printf("Stack elements are:\n");
        int i;
        for ( i = top; i >= 0; i--) {
            printf("%d\n", stack[i]);
        }
    }
}
int main() {
    int b;
    printf("Enter the size of the stack: ");
    scanf("%d", &b);
    int stack[b];
    int top = -1;
    int choice;
    do {
        printf("\nSTACK OPERATIONS:\n");
        printf("1. PUSH\n");
        printf("2. POP\n");
        printf("3. PEEK\n");
        printf("4. DISPLAY\n");
        printf("5. EXIT\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                push(stack, &top, b);
                break;
            case 2:
                pop(stack, &top);
                break;
            case 3:
                peek(stack, top);
                break;
            case 4:
                display(stack, top);
                break;
            case 5:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }

    } while (choice != 5);

    return 0;
}

