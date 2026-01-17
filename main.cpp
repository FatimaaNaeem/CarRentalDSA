#include <iostream>
using namespace std;

void adminLogin();
void customerLogin();
void saveAdminCredentials();
void saveCustomerCredentials();
void loadCars();
void loadTransactions();

int main()
{
    saveAdminCredentials();
    saveCustomerCredentials();
    loadCars();
    loadTransactions();

    int choice;
    do
    {
        cout << "\nPlease login to proceed\n1. Admin\n2. Customer\n3. Exit\nChoice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) adminLogin();
        else if (choice == 2) customerLogin();
        else if (choice == 3) break;
        else cout << "Invalid choice\n";
    } while (true);
}
