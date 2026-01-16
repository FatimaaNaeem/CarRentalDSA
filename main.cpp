#include <iostream>
using namespace std;

// Admin functions
void adminLogin();
void saveAdminCredentials();

// Customer functions
void customerLogin();
void saveCustomerCredentials();

// Car function to load cars from file
void ViewCarData();

int main()
{
    // Load cars at program start
    ViewCarData();

    // Ensure admin and customer credentials exist
    saveAdminCredentials();
    saveCustomerCredentials();

    int option;
    do
    {
        cout << "Please login to proceed\n";
        cout << "1. Admin\n2. Customer\n3. Exit\n";
        cin >> option;

        switch (option)
        {
        case 1:
            adminLogin();
            break;
        case 2:
            customerLogin();
            break;
        case 3:
            cout << "Exiting system\n";
            break;
        default:
            cout << "Invalid option\n";
        }

    } while (option != 3);

    return 0;
}
