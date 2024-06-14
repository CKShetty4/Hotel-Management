#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_GUESTS 100
#define MAX_FOOD_ITEMS 100
#define MAX_ROOMS 30

typedef struct {
    char username[20];
    char password[20];
} Guest;

typedef struct {
    char name[50];
    int price;
    int quantity;
} FoodItem;

typedef struct {
    int roomNumber;
    char roomType[20];
    int price;
    bool isBooked;
} Room;

Guest guests[MAX_GUESTS];
FoodItem foodItems[MAX_FOOD_ITEMS];
Room rooms[MAX_ROOMS];

int numGuests = 0;
int numFoodItems = 0;
int numRooms = 10 + 8 + 6 + 4 + 2 + 1;

void initRooms() {
    int i;
    for (i = 0; i < 10; i++) {
        rooms[i].roomNumber = i + 1;
        strcpy(rooms[i].roomType, "Standard");
        rooms[i].price = 999;
        rooms[i].isBooked = false;
    }
    for (i = 10; i < 18; i++) {
        rooms[i].roomNumber = i + 1;
        strcpy(rooms[i].roomType, "Executive");
        rooms[i].price = 4999;
        rooms[i].isBooked = false;
    }
    for (i = 18; i < 24; i++) {
        rooms[i].roomNumber = i + 1;
        strcpy(rooms[i].roomType, "Presidential Suite");
        rooms[i].price = 7999;
        rooms[i].isBooked = false;
    }
    for (i = 24; i < 28; i++) {
        rooms[i].roomNumber = i + 1;
        strcpy(rooms[i].roomType, "Penthouse Suite");
        rooms[i].price = 17999;
        rooms[i].isBooked = false;
    }
    for (i = 28; i < 30; i++) {
        rooms[i].roomNumber = i + 1;
        strcpy(rooms[i].roomType, "Deluxe");
        rooms[i].price = 34999;
        rooms[i].isBooked = false;
    }
    rooms[30].roomNumber = 31;
    strcpy(rooms[30].roomType, "Superior");
    rooms[30].price = 59999;
    rooms[30].isBooked = false;
}

void initFoodItems() {
    FILE *fp = fopen("food_items.txt", "r");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    char line[100];
    int i = 0;
    while (fgets(line, sizeof(line), fp)) {
        char name[50];
        int price, quantity;
        sscanf(line, "%s %d %d", name, &price, &quantity);
        strcpy(foodItems[i].name, name);
        foodItems[i].price = price;
        foodItems[i].quantity = quantity;
        i++;
    }

    fclose(fp);
    numFoodItems = i;
}

void registerGuest() {
    Guest guest;
    printf("Enter username: ");
    scanf("%s", guest.username);
    printf("Enter password: ");
    scanf("%s", guest.password);
    guests[numGuests] = guest;
    numGuests++;
    FILE *fp = fopen("guest_credentials.txt", "a");
    fprintf(fp, "%s %s\n", guest.username, guest.password);
    fclose(fp);
}

void loginGuest() {
    char username[20], password[20];
    printf("Enter username: ");
    scanf("%19s", username);  // Use %19s to prevent buffer overflow
    printf("Enter password: ");
    scanf("%19s", password);  // Use %19s to prevent buffer overflow
    FILE *fp = fopen("guest_credentials.txt", "r");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    char line[40];
    while (fgets(line, sizeof(line), fp)) {
        char fileUsername[20], filePassword[20];
        sscanf(line, "%s %s", fileUsername, filePassword);
        if (strcmp(username, fileUsername) == 0 && strcmp(password, filePassword) == 0) {
            printf("Login successful!\n");
            guestMenu();
            return;
        }
    }
    printf("Invalid username or password!\n");
    fclose(fp);
}

void adminLogin() {
    char username[20], password[20];
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);
    if (strcmp(username, "admin") == 0 && strcmp(password, "1234") == 0) {
        printf("Login successful!\n");
        adminMenu();
    } else {
        printf("Invalid username or password!\n");
    }
}

void guestMenu() {
    int choice;
    printf("1. View rooms\n");
    printf("2. Book room\n");
    printf("3. Cancel booking\n");
    printf("4. View food items\n");
    printf("5. Order food\n");
    printf("6. Generate bill\n");
    printf("7. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            viewRooms();
            break;
        case 2:
            bookRoom();
            break;
        case 3:
            cancelBooking();
            break;
        case 4:
            viewFoodItems();
            break;
        case 5:
            orderFood();
            break;
        case 6:
            generateBill();
            break;
        case 7:
            exit(0);
            break;
        default:
            printf("Invalid choice!\n");
    }
}

void adminMenu() {
    int choice;
    printf("1. Add food item\n");
    printf("2. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            addFoodItem();
            break;
        case 2:
            exit(0);
            break;
        default:
            printf("Invalid choice!\n");
    }
}

void viewRooms() {
    for (int i = 0; i < numRooms; i++) {
        if (!rooms[i].isBooked) {
            printf("Room Number: %d, Room Type: %s, Price: %d\n", rooms[i].roomNumber, rooms[i].roomType, rooms[i].price);
        }
    }
}

void bookRoom() {
    int roomNumber;
    printf("Enter room number: ");
    scanf("%d", &roomNumber);
    for (int i = 0; i < numRooms; i++) {
        if (rooms[i].roomNumber == roomNumber &&!rooms[i].isBooked) {
            rooms[i].isBooked = true;
            printf("Room booked successfully!\n");
            return;
        }
    }
    printf("Room not available!\n");
}

void cancelBooking() {
    int roomNumber;
    printf("Enter room number: ");
    scanf("%d", &roomNumber);
    for (int i = 0; i < numRooms; i++) {
        if (rooms[i].roomNumber == roomNumber && rooms[i].isBooked) {
            rooms[i].isBooked = false;
            printf("Booking cancelled successfully!\n");
            return;
        }
    }
    printf("Room not booked!\n");
}

void viewFoodItems() {
    printf("Item Name \t\t Price\t  Quantity\n");
    for (int i = 0; i < numFoodItems; i++) {
        printf("%s \t\t  %d\t  %d\n", foodItems[i].name, foodItems[i].price, foodItems[i].quantity);
    }
}

void orderFood() {
    char foodItem[50];
    int quantity;
    printf("Enter food item: ");
    scanf("%s", foodItem);
    printf("Enter quantity: ");
    scanf("%d", &quantity);
    for (int i = 0; i < numFoodItems; i++) {
        if (strcmp(foodItems[i].name, foodItem) == 0) {
            foodItems[i].quantity -= quantity;
            printf("Food ordered successfully!\n");
            return;
        }
    }
    printf("Food item not available!\n");
}

void generateBill() {
    int total = 0;
    for (int i = 0; i < numRooms; i++) {
        if (rooms[i].isBooked) {
            total += rooms[i].price;
        }
    }
    for (int i = 0; i < numFoodItems; i++) {
        total += foodItems[i].price * foodItems[i].quantity;
    }
    float gst;
    if (total < 1000) {
        gst = total * 0.12;
    } else if (total >= 1000 && total <= 7500) {
        gst = total * 0.12;
    } else {
        gst = total * 0.18;
    }
    total += gst;
    printf("Total bill: %d\n", total);
    FILE *fp = fopen("bill_guest_number.txt", "w");
    fprintf(fp, "Bill Number: %d\n", 1);
    fprintf(fp, "Total bill: %d\n", total);
    fclose(fp);
}

void addFoodItem() {
    char res = 'y';
    while (res == 'y') {
        FoodItem foodItem;
        printf("Enter food item name: ");
        scanf("%19s", foodItem.name);
        printf("Enter food item price: ");
        scanf("%d", &foodItem.price);
        printf("Enter food item quantity: ");
        scanf("%d", &foodItem.quantity);

        FILE *fp = fopen("food_items.txt", "a");
        if (fp == NULL) {
            printf("Error opening file!\n");
            return;
        }
        fprintf(fp, "%s %d %d\n", foodItem.name, foodItem.price, foodItem.quantity);
        fclose(fp);

        foodItems[numFoodItems] = foodItem;
        numFoodItems++;

        printf("Are there other items to be added? (y/n)\n");
        scanf(" %c", &res);
    }
    printf("Food items added successfully!\n");
}

int main() {
    initRooms();
    initFoodItems();
    int choice;
    printf("1. Register\n");
    printf("2. Login as guest\n");
    printf("3. Login as admin\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            registerGuest();
            break;
        case 2:
            loginGuest();
            break;
        case 3:
            adminLogin();
            break;
        case 4:
            exit(0);
            break;
        default:
            printf("Invalid choice!\n");
    }
    return 0;
}
