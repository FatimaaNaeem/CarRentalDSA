#include <iostream>
#include <string>
#include <fstream>
using namespace std;

void addCar(string, string, int);
void viewCars();
int deleteCar(string);
void viewTransactions();

bool loginAdmin(string u, string p)
{
    ifstream fin("admins.txt");
    string U, P;
    while (fin >> U >> P)
        if (U == u && P == p)
        {
            fin.close();
            return true;
        }
    fin.close();
    return false;
}

void adminMenu()
{
    int ch, price;
    string plate, name;

    do
    {
        cout << "\nADMIN MENU\n1. Add Car\n2. View Cars\n3. Delete Car\n4. View Transactions\n5. Logout\nChoice: ";
        cin >> ch;
        cin.ignore();

        if (ch == 1)
        {
            cout << "Plate: ";
            getline(cin, plate);
            cout << "Name: ";
            getline(cin, name);
            cout << "Price/hr: ";
            cin >> price;
            cin.ignore();
            addCar(plate, name, price);
            cout << "Car added\n";
        }
        else if (ch == 2)
            viewCars();
        else if (ch == 3)
        {
            cout << "Plate: ";
            getline(cin, plate);
            if (deleteCar(plate))
                cout << "Deleted\n";
            else
                cout << "Not found\n";
        }
        else if (ch == 4)
            viewTransactions();
        else if (ch == 5)
            return;
        else
            cout << "Invalid choice\n";
    } while (true);
}

void adminLogin()
{
    string u, p;
    cout << "Enter username: ";
    cin >> u;
    cout << "Enter password: ";
    cin >> p;
    if (loginAdmin(u, p))
        adminMenu();
    else
        cout << "Invalid admin credentials\n";
}

void saveAdminCredentials()
{
    ofstream fout("admins.txt");
    fout << "fatima 66660\n";
    fout.close();
}
