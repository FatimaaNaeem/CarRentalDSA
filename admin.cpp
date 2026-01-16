#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Functions from car.cpp
void insertCar(string name, string plateNo, string color, string brand, string model, string pricePerHour, bool availability);
void displayCars();
bool deleteCar(string plateNo);
void saveCarData();
void displayTransactions(); // optional if you have transactions
void ViewCarData();

void adminMenu()
{
    int choice;
    string name, plate, color, brand, model, price;
    bool availability = true;

    do
    {
        cout << "\n--- ADMIN MENU ---\n";
        cout << "1. Add Car\n2. View Cars\n3. Delete Car\n4. View Transactions\n5. Logout\n";
        cin >> choice;
        cin.ignore(); // clear newline

        switch (choice)
        {
        case 1:
            cout << "Car Name: ";
            getline(cin, name);
            cout << "Plate No: ";
            getline(cin, plate);
            cout << "Color: ";
            getline(cin, color);
            cout << "Brand: ";
            getline(cin, brand);
            cout << "Model: ";
            getline(cin, model);
            cout << "Price Per Hour: ";
            getline(cin, price);
            insertCar(name, plate, color, brand, model, price, availability);
            saveCarData();
            cout << "Car added successfully\n";
            break;

        case 2:
            displayCars();
            break;

        case 3:
            cout << "Enter plate to delete: ";
            getline(cin, plate);
            if (deleteCar(plate))
            {
                saveCarData();
                cout << "Car deleted successfully\n";
            }
            else
                cout << "Car not found\n";
            break;

        case 4:
            displayTransactions();
            break;

        case 5:
            cout << "Logging out...\n";
            break;

        default:
            cout << "Invalid choice\n";
        }
    } while (choice != 5);
}

bool loginAdminFromFile(string username, string password)
{
    ifstream fin("admins.txt");
    int id;
    string u, p;
    while (fin >> id >> u >> p)
        if (u == username && p == password)
        {
            fin.close();
            return true;
        }
    fin.close();
    return false;
}

void adminLogin()
{
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    if (loginAdminFromFile(username, password))
        adminMenu();
    else
        cout << "Invalid admin credentials\n";
}

void saveAdminCredentials()
{
    ofstream fout("admins.txt");
    fout << 1 << " fatima 66660";
    fout.close();
}
