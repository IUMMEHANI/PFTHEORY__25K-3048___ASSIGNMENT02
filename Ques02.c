#include <stdio.h>
#include <string.h>
#define MAX_PRODUCTS 4
#define MAX_CART 100
typedef struct {
    char code[4];
    int stock;
    int price;
} Product;
typedef struct {
    char name[50];
    char cnic[20];
} Customer;
typedef struct {
    int productIndex;
    int quantity;
} CartItem;
void inputCustomer(Customer *c);
void displayInventory(Product products[], int n);
void addToCart(Product products[], CartItem cart[], int *cartCount);
int updateInventory(Product products[], CartItem cart[], int cartCount);
int calculateTotal(Product products[], CartItem cart[], int cartCount);
void showInvoice(Customer c, Product products[], CartItem cart[], int cartCount, int total, int discountedTotal);

int main() {
    Product products[MAX_PRODUCTS] = {
        {"001", 50, 100},
        {"002", 10, 200},
        {"003", 20, 300},
        {"004", 8, 150}
    };
    Customer customer;
    CartItem cart[MAX_CART];
    int cartCount = 0;
    int choice;
    int total = 0;
    int discountedTotal = 0;
    char promo[20];
    do {
        printf("\n=== Supermarket System Menu ===\n");
        printf("1. Enter Customer Information\n");
        printf("2. Display Inventory\n");
        printf("3. Add Item to Cart\n");
        printf("4. Update Inventory & Display Total Bill\n");
        printf("5. Apply Promocode\n");
        printf("6. Show Invoice\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                inputCustomer(&customer);
                break;
            case 2:
                displayInventory(products, MAX_PRODUCTS);
                break;
            case 3:
                addToCart(products, cart, &cartCount);
                break;
            case 4:
                total = calculateTotal(products, cart, cartCount);
                updateInventory(products, cart, cartCount);
                printf("Total Bill: %d\n", total);
                break;
            case 5:
                printf("Enter promocode (if any): ");
                scanf("%s", promo);
                if(strcmp(promo, "Eid2025") == 0) {
                    discountedTotal = total - (total * 25 / 100);
                    printf("Promocode applied! Discounted Total: %d\n", discountedTotal);
                } else {
                    discountedTotal = total;
                    printf("Invalid promocode or no discount applied.\n");
                }
                break;
            case 6:
                if(discountedTotal == 0) discountedTotal = total;
                showInvoice(customer, products, cart, cartCount, total, discountedTotal);
                break;
            case 7:
                printf("Exiting system...\n");
                break;
            default:
                printf("Invalid choice! Try again.\n");
        }

    } while(choice != 7);
    return 0;
}
void inputCustomer(Customer *c) {
    printf("Enter customer name: ");
    scanf(" %[^\n]s", c->name);
    printf("Enter CNIC number: ");
    scanf(" %[^\n]s", c->cnic);
}
void displayInventory(Product products[], int n) {
	int i;
    printf("\nProduct Code  Quantity  Price\n");
    for(i = 0; i < n; i++) {
        printf("%s\t\t%d\t%d\n", products[i].code, products[i].stock, products[i].price);
    }
}
void addToCart(Product products[], CartItem cart[], int *cartCount) {
    char code[4];
    int qty, found = 0;
    int i;
    printf("Enter product code to add to cart: ");
    scanf("%s", code);
    for( i = 0; i < MAX_PRODUCTS; i++) {
        if(strcmp(products[i].code, code) == 0) {
            found = 1;
            printf("Enter quantity: ");
            scanf("%d", &qty);
            if(qty <= 0) {
                printf("Invalid quantity.\n");
                return;
            }
            if(qty > products[i].stock) {
                printf("Not enough stock! Available: %d\n", products[i].stock);
                return;
            }
            cart[*cartCount].productIndex = i;
            cart[*cartCount].quantity = qty;
            (*cartCount)++;
            printf("Added %d of %s to cart.\n", qty, code);
            return;
        }
    }
    if(!found) printf("Product code not found.\n");
}
int updateInventory(Product products[], CartItem cart[], int cartCount) {
	int i ;
    for( i = 0; i < cartCount; i++) {
        int idx = cart[i].productIndex;
        products[idx].stock -= cart[i].quantity;
    }
    return 1;
}
int calculateTotal(Product products[], CartItem cart[], int cartCount) {
    int total = 0;
    int i;
    for( i = 0; i < cartCount; i++) {
        int idx = cart[i].productIndex;
        total += products[idx].price * cart[i].quantity;
    }
     return total;
}
void showInvoice(Customer c, Product products[], CartItem cart[], int cartCount, int total, int discountedTotal) {
    printf("\n=== Invoice ===\n");
    printf("Customer Name: %s\n", c.name);
    printf("Customer CNIC: %s\n", c.cnic);
    printf("\nItems Purchased:\n");
    printf("Code\tQty\tPrice\tSubtotal\n");
    int i;
    for( i = 0; i < cartCount; i++) {
        int idx = cart[i].productIndex;
        int subtotal = products[idx].price * cart[i].quantity;
        printf("%s\t%d\t%d\t%d\n", products[idx].code, cart[i].quantity, products[idx].price, subtotal);
    }
    printf("\nTotal Bill: %d\n", total);
    if(discountedTotal < total) {
        printf("Discount Applied! Final Bill: %d\n", discountedTotal);
    }
}
    
