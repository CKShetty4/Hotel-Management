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
    bool isBooked;
    char guestName[20];
} Room;

Guest guests[MAX_GUESTS];
FoodItem foodItems[MAX_FOOD_ITEMS];
Room rooms[MAX_ROOMS];

int numGuests = 0;
int numFoodItems = 0;
int numRooms = 30;

void initRooms() {
    FILE *fp = fopen("room.txt", "r");
    if (fp == NULL) {
        fp = fopen("room.txt", "w");
        for (int i = 0; i < numRooms; i++) {
            fprintf(fp, "%d %s %d %s\n", i + 1, "Standard", 0, "");
            i++;
            fprintf(fp, "%d %s %d %s\n", i + 1, "Executive", 0, "");
            i++;
            fprintf(fp, "%d %s %d %s\n", i + 1, "Presidential_Suite", 0, "");
            i++;
            fprintf(fp, "%d %s %d %s\n", i + 1, "Penthouse_Suite", 0, "");
            i++;
            fprintf(fp, "%d %s %d %s\n", i + 1, "Deluxe", 0, "");
            i++;
            fprintf(fp, "%d %s %d %s\n", i + 1, "Superior", 0, "");
        }
        fclose(fp);
    } else {
        for (int i = 0; i < numRooms; i++) {
            fscanf(fp, "%d %s %d %s\n", &rooms[i].roomNumber, rooms[i].roomType, &rooms[i].isBooked, rooms[i].guestName);
        }
        fclose(fp);
    }
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
    scanf("%19s", username);
    printf("Enter password: ");
    scanf("%19s", password);
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
    system("cls");
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
    FILE *fp = fopen("room.txt", "r");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    int countStandard = 0, countExecutive = 0, countPresidential = 0, countPenthouse = 0, countDeluxe = 0, countSuperior = 0;
    Room room;
    while (fscanf(fp, "%d %s %d %19s\n", &room.roomNumber, room.roomType, &room.isBooked, room.guestName) == 4) {
        if (!room.isBooked) {
            if (strcmp(room.roomType, "Standard") == 0) {
                countStandard++;
            } else if (strcmp(room.roomType, "Executive") == 0) {
                countExecutive++;
            } else if (strcmp(room.roomType, "Presidential_Suite") == 0) {
                countPresidential++;
            } else if (strcmp(room.roomType, "Penthouse_Suite") == 0) {
                countPenthouse++;
            } else if (strcmp(room.roomType, "Deluxe") == 0) {
                countDeluxe++;
            } else if (strcmp(room.roomType, "Superior") == 0) {
                countSuperior++;
            }
        }
    }

    fclose(fp);

    printf("Room Types and Availability:\n");
    printf("Room Type \t\t\t Available \t Price\n");
    if (countStandard > 0) {
        printf("Standard Room \t\t\t %d   \t\t 999\n", countStandard);
    }
    if (countExecutive > 0) {
        printf("Executive Room \t\t\t %d   \t\t 4999\n", countExecutive);
    }
    if (countPresidential > 0) {
        printf("Presidential Suite \t\t %d   \t\t 7999\n", countPresidential);
    }
    if (countPenthouse > 0) {
        printf("Penthouse Suite \t\t %d   \t\t 17999\n", countPenthouse);
    }
    if (countDeluxe > 0) {
        printf("Deluxe Room \t\t\t %d   \t\t 34999\n", countDeluxe);
    }
    if (countSuperior > 0) {
        printf("Superior Room \t\t\t %d  \t\t 59999\n", countSuperior);
    }
}

void bookRoom() {
    int roomType, numRoomsAvailable;
    printf("Enter room type (1: Standard, 2: Executive, 3: Presidential_Suite, 4: Penthouse_Suite, 5: Deluxe, 6: Superior): ");
    scanf("%d", &roomType);

    switch (roomType) {
       case 1:
            numRoomsAvailable = getNumRoomsAvailable("Standard");
            if (numRoomsAvailable == 0) {
                printf("No Standard rooms available!\n");
                return;
            }
            assignRoom("Standard", numRoomsAvailable);
            break;
        case 2:
            numRoomsAvailable = getNumRoomsAvailable("Executive");
            if (numRoomsAvailable == 0) {
                printf("No Executive rooms available!\n");
                return;
            }
            assignRoom("Executive", numRoomsAvailable);
            break;
        case 3:
            numRoomsAvailable = getNumRoomsAvailable("Presidential_Suite");
            if (numRoomsAvailable == 0) {
                printf("No Presidential_Suites available!\n");
                return;
            }
            assignRoom("Presidential_Suite", numRoomsAvailable);
            break;
        case 4:
            numRoomsAvailable = getNumRoomsAvailable("Penthouse_Suite");
            if (numRoomsAvailable == 0) {
                printf("No Penthouse_Suites available!\n");
                return;
            }
            assignRoom("Penthouse_Suite", numRoomsAvailable);
            break;
        case 5:
            numRoomsAvailable = getNumRoomsAvailable("Deluxe");
            if (numRoomsAvailable == 0) {
                printf("No Deluxe rooms available!\n");
                return;
            }
            assignRoom("Deluxe", numRoomsAvailable);
            break;
        case 6:
            numRoomsAvailable = getNumRoomsAvailable("Superior");
            if (numRoomsAvailable == 0) {
                printf("No Superior rooms available!\n");
                return;
            }
            assignRoom("Superior", numRoomsAvailable);
            break;
        default:
            printf("Invalid room type!\n");
            return;
    }

    printf("Room booked successfully!\n");
}

int getNumRoomsAvailable(const char* roomType) {
    int count = 0;
    for (int i = 0; i < numRooms; i++) {
        if (strcmp(rooms[i].guestName, "") == 0 && strcmp(rooms[i].roomType, roomType) == 0) {
            count++;
        }
    }
    return count;
}

void assignRoom(const char* roomType, int numRoomsAvailable) {
    for (int i = 0; i < numRooms; i++) {
        if (strcmp(rooms[i].guestName, "") == 0 && strcmp(rooms[i].roomType, roomType) == 0) {
            printf("Enter guest name: ");
            scanf("%19s", rooms[i].guestName);
            rooms[i].isBooked = true;
            FILE *fp = fopen("room.txt", "w");
            for (int j = 0; j < numRooms; j++) {
                fprintf(fp, "%d %s %d %s\n", rooms[j].roomNumber, rooms[j].roomType, rooms[j].isBooked, rooms[j].guestName);
            }
            fclose(fp);
            return;
        }
    }
}

void cancelBooking() {
    int roomNumber;
    printf("Enter room number: ");
    scanf("%d", &roomNumber);
    for (int i = 0; i < numRooms; i++) {
        if (rooms[i].roomNumber == roomNumber && strcmp(rooms[i].guestName, "")!= 0) {
            strcpy(rooms[i].guestName, "");
            rooms[i].isBooked = false;
            FILE *fp = fopen("room.txt", "w");
            for (int j = 0; j < numRooms; j++) {
                fprintf(fp, "%d %s %d %s\n", rooms[j].roomNumber, rooms[j].roomType, rooms[j].isBooked, rooms[j].guestName);
            }
            fclose(fp);
            printf("Booking canceled successfully!\n");
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
            FILE *fp = fopen("food_items.txt", "w");
            for (int j = 0;j < numFoodItems; j++) {
                fprintf(fp, "%s %d %d\n", foodItems[j].name, foodItems[j].price, foodItems[j].quantity);
            }
            fclose(fp);
            return;
        }
    }
    printf("Food item not available!\n");
}

void generateBill() {
    int total = 0;
    for (int i = 0; i < numRooms; i++) {
        if (strcmp(rooms[i].guestName, "") != 0) {
            if (strcmp(rooms[i].roomType, "Standard") == 0) {
                total += 999;
            } else if (strcmp(rooms[i].roomType, "Executive") == 0) {
                total += 4999;
            } else if (strcmp(rooms[i].roomType, "Presidential_Suite") == 0) {
                total += 7999;
            } else if (strcmp(rooms[i].roomType, "Penthouse_Suite") == 0) {
                total += 17999;
            } else if (strcmp(rooms[i].roomType, "Deluxe") == 0) {
                total += 34999;
            } else if (strcmp(rooms[i].roomType, "Superior") == 0) {
                total += 59999;
            }
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
