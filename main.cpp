//Anthony Ebhamen - Vending Machine

#include<iostream>
#include<iomanip>
using namespace std;

struct Item {
    string name;
    float price; // Selling price
    int quantity;
};
const int MAX_ITEMS = 5;
Item items[MAX_ITEMS] = {
    {"Soda", 1.25, 5},
    {"Chips", 0.75, 5},
    {"Candy", 0.5, 5},
    {"Cookies", 1.0, 5},
    {"Juice", 1.5, 5}
};
const float COIN_VALUES[5] = {0.25, 0.05, 0.10, 1.0, 5.0}; // Quarters, nickels, dimes, dollars, and five dollars respectively
float totalRevenue = 0.0;

void displayItems() {
    cout << "Items available:\n";
    for (int i = 0; i < MAX_ITEMS; i++) {
        cout << i + 1 << ". " << items[i].name << " - $" << fixed << setprecision(2) << items[i].price 
             << " (" << items[i].quantity << " left)" << endl;
    }
}
float acceptMoney(float itemPrice) {
    float moneyInserted = 0.0;
    int coinChoice;
    cout << "Please insert money:\n";
    cout << "1. Quarter ($0.25)\n2. Nickel ($0.05)\n3. Dime ($0.10)\n4. Dollar ($1.00)\n5. Five Dollars ($5.00)\n"; // Added option for $5
    while (moneyInserted < itemPrice) {
        cin >> coinChoice;
        if (coinChoice >= 1 && coinChoice <= 5) {  // Updated the limit check to 5
            moneyInserted += COIN_VALUES[coinChoice - 1];
            cout << "Money inserted so far: $" << fixed << setprecision(2) << moneyInserted << endl;
        } else {
            cout << "Invalid choice. Please insert a valid coin.\n";
        }
    }
    return moneyInserted;
}
void vendItem() {
    displayItems();
    int itemChoice;
    cout << "Choose an item by its number: ";
    cin >> itemChoice;
    if (itemChoice >= 1 && itemChoice <= MAX_ITEMS && items[itemChoice - 1].quantity > 0) {
        float moneyInserted = acceptMoney(items[itemChoice - 1].price);
        float change = moneyInserted - items[itemChoice - 1].price;
        items[itemChoice - 1].quantity--;
        totalRevenue += items[itemChoice - 1].price;
        cout << "Vending " << items[itemChoice - 1].name << ".\n";
        cout << "Change returned: $" << fixed << setprecision(2) << change << endl;
    } else {
        cout << "Invalid choice or item out of stock.\n";
    }
}
void endOfDayReport() {
    float cost = 0.35 * totalRevenue;
    float labor = 0.25 * totalRevenue;
    float overhead = 0.05 * totalRevenue;
    float profit = totalRevenue - (cost + labor + overhead);

    cout << "End of Day Report:\n";
    cout << "Total Revenue: $" << fixed << setprecision(2) << totalRevenue << endl;
    cout << "Cost: $" << fixed << setprecision(2) << cost << endl;
    cout << "Labor: $" << fixed << setprecision(2) << labor << endl;
    cout << "Overhead: $" << fixed << setprecision(2) << overhead << endl;
    cout << "Profit: $" << fixed << setprecision(2) << profit << endl;
}
int main() {
    char choice;
    int hoursOperated = 0;
    cout << "Do you want to turn on the vending machine? (Y/N): ";
    cin >> choice;
    while (toupper(choice) == 'Y' && hoursOperated < 6) {
        vendItem();
        cout << "Do you want to continue vending? (Y/N): ";
        cin >> choice;
        hoursOperated++;
    }
    endOfDayReport();
    return 0;
}




