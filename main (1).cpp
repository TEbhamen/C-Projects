#include <iostream>
#include <queue>
#include <string>
using namespace std;

struct Car {
    string Owner_Name;
    string Licence_Plate;
    string Car_Model;
    int Ticket_Number;
    int Check_in;
    int Check_Out;
};

struct Node {
    Car car;
    Node *next;
};

class Parking {
    Node *front = nullptr;
    Node *rear = nullptr;
    int ticketCounter = 0;
    double dailyIncome = 0;
    
public:
    void readData() {
        Car car;
        cout << "Enter owner name: ";
        cin >> car.Owner_Name;
        cout << "Enter licence plate: ";
        cin >> car.Licence_Plate;
        cout << "Enter car model: ";
        cin >> car.Car_Model;
        car.Ticket_Number = ++ticketCounter;
        cout << "Enter check-in time (in minutes since 00:00): ";
        cin >> car.Check_in;
        push(car);
    }

    void push(Car car) {
        Node *temp = new Node{car, nullptr};
        if (front == nullptr) {
            front = rear = temp;
        } else {
            rear->next = temp;
            rear = temp;
        }
        cout << "Car added to the parking lot." << endl;
    }

    void pop() {
        if (front == nullptr) {
            cout << "Parking lot is empty." << endl;
            return;
        }
        Car car = front->car;
        cout << "Enter check-out time for " << car.Licence_Plate << " (in minutes since 00:00): ";
        cin >> car.Check_Out;
        double charge = calculateCharge(car.Check_Out - car.Check_in);
        charge += charge * 0.15;  // Adding 15% tip
        dailyIncome += charge;
        cout << "Charge for " << car.Licence_Plate << ": $" << charge << endl;
        Node *temp = front;
        front = front->next;
        delete temp;
        if (front == nullptr) rear = nullptr;
    }

    double calculateCharge(int duration) {
        if (duration <= 30) {
            return 3.00;
        } else if (duration <= 59) {
            return 5.00;
        } else if (duration <= 300) {
            return 10.00;
        } else if (duration <= 720) {
            return 15.00;
        } else {
            return 20.00;
        }
    }

    double getDailyIncome() {
        return dailyIncome;
    }

    void resetDailyIncome() {
        dailyIncome = 0;
    }
};

int main() {
    Parking parking;
    double weeklyIncome = 0;

    for (int i = 0; i < 7; i++) {
        cout << "Day " << (i + 1) << endl;
        while (true) {
            cout << "Options:\n1. Add a car\n2. Remove a car\n3. Move to next day\n4. Exit\nEnter choice: ";
            int choice;
            cin >> choice;
        if(cin.fail()){
            throw "Enter a valid choice";
        }
            switch (choice) {
                case 1:
                    parking.readData();
                    break;
                case 2:
                    parking.pop();
                    break;
                case 3:
                    weeklyIncome += parking.getDailyIncome();
                    parking.resetDailyIncome();
                    goto nextDay;
                case 4:
                    return 0;
                default:
                    cout << "Invalid choice. Try again." << endl;
            }
        }
    nextDay:;
    }

    double monthlyIncome = weeklyIncome * 4;
    double yearlyIncome = monthlyIncome * 12;
    double overhead = yearlyIncome * 0.55;
    double netYearlyIncome = yearlyIncome - overhead;

    cout << "Total money made by 10 cars in one week: $" << weeklyIncome << endl;
    cout << "Monthly net income: $" << monthlyIncome - (monthlyIncome * 0.55) << endl;
    cout << "Yearly net income: $" << netYearlyIncome << endl;
    cout << "Predicted annual income from parking garage: $" << netYearlyIncome << endl;

    return 0;
}
