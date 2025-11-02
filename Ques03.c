#include <stdio.h>
#define ROWS 3
#define COLS 3
void updateSector(int grid[][COLS], int row, int col, int flag, int value);
void querySector(int grid[][COLS], int row, int col);
void runDiagnostic(int grid[][COLS], int rows, int cols);
void updateSector(int grid[][COLS], int row, int col, int flag, int value) {
    if(value == 1) {
        grid[row][col] |= (1 << flag); 
    } else {
        grid[row][col] &= ~(1 << flag);
    }
    printf("Sector [%d][%d] updated successfully.\n", row, col);
}
void querySector(int grid[][COLS], int row, int col) {
    int status = grid[row][col];
    printf("Sector [%d][%d] Status:\n", row, col);
    printf("Power: %s\n", (status & (1 << 0)) ? "ON" : "OFF");
    printf("Overload: %s\n", (status & (1 << 1)) ? "YES" : "NO");
    printf("Maintenance: %s\n", (status & (1 << 2)) ? "REQUIRED" : "NOT REQUIRED");
}
void runDiagnostic(int grid[][COLS], int rows, int cols) {
    int overloaded = 0, maintenance = 0;
    int i,j;
    for( i = 0; i < rows; i++) {
        for( j = 0; j < cols; j++) {
            if(grid[i][j] & (1 << 1)) overloaded++;
            if(grid[i][j] & (1 << 2)) maintenance++;
        }
    }
    printf("\nSystem Diagnostic Report:\n");
    printf("Total sectors overloaded: %d\n", overloaded);
    printf("Total sectors requiring maintenance: %d\n", maintenance);
}
int main() {
    int grid[ROWS][COLS] = {0};  
    int choice, row, col, flag, value;
    do {
        printf("\n IESCO Power Grid Monitoring \n");
        printf("1. Update Sector Status\n");
        printf("2. Query Sector Status\n");
        printf("3. Run System Diagnostic\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                printf("Enter sector coordinates (row col): ");
                scanf("%d %d", &row, &col);
                printf("Select flag to update:\n");
                printf("0 = Power Status, 1 = Overload Warning, 2 = Maintenance Required\n");
                scanf("%d", &flag);
                printf("Set or Clear? (1 = Set, 0 = Clear): ");
                scanf("%d", &value);
                updateSector(grid, row, col, flag, value);
                break;

            case 2:
                printf("Enter sector coordinates (row col): ");
                scanf("%d %d", &row, &col);
                querySector(grid, row, col);
                break;

            case 3:
                runDiagnostic(grid, ROWS, COLS);
                break;

            case 4:
                printf("Exiting program...\n");
                break;

            default:
                printf("Invalid choice! Try again.\n");
        }

    } while(choice != 4);

    return 0;
}

