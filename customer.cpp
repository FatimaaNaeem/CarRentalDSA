#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void viewCars();
int rentCar(string, int, int &);
void pushTransaction(string, int, int);

bool loginCustomer(string u, string p)
{
    ifstream fin("customers.txt");
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

void customerMenu()
{
    int ch, hours, bill;
    string plate;

    do
    {
        cout << "\nCUSTOMER MENU\n1. View Cars\n2. Rent Car\n3. Logout\nChoice: ";
        cin >> ch;
        cin.ignore();

        if (ch == 1)
            viewCars();
        else if (ch == 2)
        {
            cout << "Plate: ";
            getline(cin, plate);
            cout << "Hours: ";
            cin >> hours;
            cin.ignore();
            if (rentCar(plate, hours, bill))
            {
                cout << "Bill: " << bill << "\nConfirm payment (1=yes): ";
                int c;
                cin >> c;
                cin.ignore();
                if (c == 1)
                {
                    pushTransaction(plate, hours, bill);
                    cout << "Rental successful\n";
                }
            }
            else
                cout << "Car not available\n";
        }
        else if (ch == 3)
            return;
        else
            cout << "Invalid choice\n";
    } while (true);
}

void customerLogin()
{
    string u, p;
    cout << "Enter username: ";
    cin >> u;
    cout << "Enter password: ";
    cin >> p;
    if (loginCustomer(u, p))
        customerMenu();
    else
        cout << "Invalid customer credentials\n";
}

void saveCustomerCredentials()
{
    ofstream fout("customers.txt");
    fout << "user 123\n";
    fout.close();
}
