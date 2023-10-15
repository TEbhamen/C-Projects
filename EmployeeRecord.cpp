//Anthony Ebhamen - Employee Record Stack Storage

#include<iostream>
#include<string>
using namespace std;

struct SalaryRecord {
    float weekly_hours;
    float rate_per_hour;
    float gross_salary;
    float tax;
    float net_salary;
};

struct Employee {
    string name;
    int ID;
    SalaryRecord salary;
    Employee* next;  // pointer to next employee in stack
};

class EmployeeStack {
    private:
        Employee* top;
    
    public:
        EmployeeStack() {
            top = nullptr;
        }

        bool isEmpty() {
            return top == nullptr;
        }

        void push(Employee* emp) {
            emp->next = top;
            top = emp;
        }

        Employee* pop() {
            if(isEmpty()) {
                cout << "Stack is empty!" << endl;
                return nullptr;
            }

            Employee* temp = top;
            top = top->next;
            return temp; // Remember to delete the memory after using this popped employee
        }
        
         void displayRecords() {
            Employee* temp = top;
            if (!temp) {
                cout << "No records available." << endl;
                return;
            }
            cout << "Current Employee Records:" << endl;
            while (temp) {
                cout << "-------------------------" << endl;
                cout << "Name: " << temp->name << endl;
                cout << "ID: " << temp->ID << endl;
                cout << "Gross Salary: " << temp->salary.gross_salary << endl;
                cout << "Tax: " << temp->salary.tax << endl;
                cout << "Net Salary: " << temp->salary.net_salary << endl;
                temp = temp->next;
            }
            cout << "-------------------------" << endl;
        }
};
        
        


int main() {
    EmployeeStack stack;
    int choice;
    int count = 0;

    do {
        cout << "1. Add Employee Details" << endl;
        cout << "2. Remove Employee Details" << endl;
        cout << "3. Display Current Records" << endl;  // New Option
        cout << "4. Exit" << endl;  // Note that the exit option is now 4
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1: {
                if(count >= 20) {
                    cout << "Max Employee Limit Reached!" << endl;
                    break;
                }
                Employee* emp = new Employee;
                cout << "Enter Employee Name: ";
                cin.ignore();
                getline(cin, emp->name);
                cout << "Enter Employee ID: ";
                cin >> emp->ID;
                cout << "Enter Weekly Hours: ";
                cin >> emp->salary.weekly_hours;
                cout << "Enter Rate per Hour: ";
                cin >> emp->salary.rate_per_hour;

                emp->salary.gross_salary = emp->salary.weekly_hours * emp->salary.rate_per_hour;
                emp->salary.tax = 0.1 * emp->salary.gross_salary; //10% tax rate
                emp->salary.net_salary = emp->salary.gross_salary - emp->salary.tax;

                stack.push(emp);
                count++;
                break;
            }
            case 2: {
                Employee* emp = stack.pop();
                if(emp) {
                    cout << "Added Employee Details:" << endl;
                    cout << "Name: " << emp->name << endl;
                    cout << "ID: " << emp->ID << endl;
                    cout << "Gross Salary: " << emp->salary.gross_salary << endl;
                    cout << "Tax: " << emp->salary.tax << endl;
                    cout << "Net Salary: " << emp->salary.net_salary << endl;
                    delete emp;
                    count--;
                }
                break;
            }
            case 3:
                stack.displayRecords();
                break;
            case 4:
                cout << "Exiting program!" << endl;
                break;
            default:
                cout << "Invalid choice!" << endl;
        }
    } while(choice != 4);

    return 0;
}




