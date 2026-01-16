#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Car
{
    string carName;
    string carPlateNo;
    string color;
    string brand;
    string model;
    string pricePerHour;
    bool availability;
    Car *next;
};

struct Transaction
{
    int transactionID;
    int customerID;
    string carPlateNo;
    int rentHours;
    string rentDate;
    int totalAmount;
    Transaction *next;
};

extern Car *carHead;
extern Transaction *transactionHead;

void displayCars();
void pushTransaction(int tID, int cID, string plateNo, int hours, string date, int amount);

bool isCarAvailable(string plateNo)
{
    Transaction *tempT = transactionHead;
    while (tempT != NULL)
    {
        if (tempT->carPlateNo == plateNo)
            return false;
        tempT = tempT->next;
    }
    Car *tempC = carHead;
    while (tempC != NULL)
    {
        if (tempC->carPlateNo == plateNo)
            return tempC->availability;
        tempC = tempC->next;
    }
    return false;
}

string getCarPrice(string plateNo)
{
    Car *temp = carHead;
    while (temp != NULL)
    {
        if (temp->carPlateNo == plateNo)
            return temp->pricePerHour;
        temp = temp->next;
    }
    return "0";
}

void customerMenu(int customerID)
{
    int choice;
    do
    {
        cout << "\n--- CUSTOMER MENU ---\n";
        cout << "1. View Cars\n2. Rent Car\n3. Logout\n";
        cin >> choice;
        switch (choice)
        {
        case 1:
            displayCars();
            break;
        case 2:
        {
            string plateNo, date;
            int hours;
            displayCars();
            cout << "Enter car plate number: ";
            cin >> plateNo;
            if (!isCarAvailable(plateNo))
            {
                cout << "Car already rented or not available\n";
                break;
            }
            cout << "Enter rent hours: ";
            cin >> hours;
            int price = stoi(getCarPrice(plateNo));
            int total = price * hours;
            cout << "Total amount: " << total << endl;
            cout << "Confirm payment? (1 = Yes): ";
            int confirm;
            cin >> confirm;
            if (confirm == 1)
            {
                cout << "Enter rent date: ";
                cin >> date;
                pushTransaction(1, customerID, plateNo, hours, date, total);
                cout << "Car rented successfully\n";
            }
            else
                cout << "Payment cancelled\n";
            break;
        }
        case 3:
            cout << "Logging out...\n";
            break;
        default:
            cout << "Invalid choice\n";
        }
    } while (choice != 3);
}

int loginCustomerFromFile(string username, string password)
{
    ifstream fin("customers.txt");
    int id;
    string u, p;
    while (fin >> id >> u >> p)
    {
        if (u == username && p == password)
        {
            fin.close();
            return id;
        }
    }
    fin.close();
    return -1;
}

void customerLogin()
{
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    int customerID = loginCustomerFromFile(username, password);
    if (customerID != -1)
        customerMenu(customerID);
    else
        cout << "Invalid customer credentials\n";
}

void saveCustomerCredentials()
{
    ofstream fout("customers.txt");
    fout << 1 << " user 123";
    fout.close();
}
