// Babbyy Girl apny jb bhi gpt wagaira ko code dena hai to unhein 1 poori class di jiay ga
// Dont give poora code (BECAUSE CODE LMBA HAI GPT PE PASTE NI HONA)

// Babes use system("clear") And system("pause") in your code 
// system("clear") pehle likha hoa sb clear kr de ga and system("pause") udhr rok de ga 

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class CarManager {
private:
    struct Car {
        string plate;
        string name;
        int price;
        int available;
        Car *next;
    };

    Car *head;
    int loaded;
public:
    CarManager() {
        head = NULL;
        loaded = 0;
    }
    void loadCars() {
        if (loaded) return;
        loaded = 1;
        ifstream fin("cars.txt");
        while (true) {
            Car *n = new Car;
            if (!(fin >> n->plate >> n->name >> n->price >> n->available)) {
                delete n;
                break;
            }
            n->next = head;
            head = n;
        }
        fin.close();
    }
    void saveCars() {
        ofstream fout("cars.txt");
        Car *t = head;
        while (t) {
            fout << t->plate << " " << t->name << " " << t->price << " " << t->available << endl;
            t = t->next;
        }
        fout.close();
    }
    void addCar(string plate, string name, int price) {
        loadCars();
        Car *n = new Car;
        n->plate = plate;
        n->name = name;
        n->price = price;
        n->available = 1;
        n->next = head;
        head = n;
        saveCars();
    }
    void viewCars() {
        loadCars();
        Car *t = head;
        int found = 0;
        while (t) {
            cout << "Plate: " << t->plate << endl;
            cout << "Name: " << t->name << endl;
            cout << "Price/hr: " << t->price << endl;
            cout << "Status: " << (t->available ? "Available" : "Rented") << endl << endl;
            t = t->next;
            found = 1;
        }
        if (!found) cout << "No cars available" << endl;
    }
    int deleteCar(string plate) {
        loadCars();
        Car *t = head, *p = NULL;
        while (t) {
            if (t->plate == plate) {
                if (!p) head = t->next;
                else p->next = t->next;
                delete t;
                saveCars();
                return 1;
            }
            p = t;
            t = t->next;
        }
        return 0;
    }
    int rentCar(string plate, int hours, int &bill) {
        loadCars();
        Car *t = head;
        while (t) {
            if (t->plate == plate && t->available) {
                t->available = 0;
                bill = t->price * hours;
                saveCars();
                return 1;
            }
            t = t->next;
        }
        return 0;
    }
};

class TransactionManager {
private:
    struct Transaction {
        string plate;
        int hours, bill;
        Transaction *next;
    };

    Transaction *top;
public:
    TransactionManager() {
        top = NULL;
    }
    void pushTransaction(string plate, int hours, int bill) {
        Transaction *n = new Transaction;
        n->plate = plate;
        n->hours = hours;
        n->bill = bill;
        n->next = top;
        top = n;
        ofstream fout("transactions.txt", ios::app);
        fout << plate << " " << hours << " " << bill << endl;
        fout.close();
    }
    void viewTransactions() {
        ifstream fin("transactions.txt");
        string p;
        int h, b;
        int found = 0;
        while (fin >> p >> h >> b) {
            cout << "Car: " << p << " Hours: " << h << " Bill: " << b << endl;
            found = 1;
        }
        if (!found) cout << "No transactions" << endl;
        fin.close();
    }
};

class Customer {
private:
    string username;
    string password;
public:
    void signup() {
        string u, p;
        cout << "Enter new username: ";
        cin >> u;
        cout << "Enter new password: ";
        cin >> p;
        ofstream fout("customers.txt", ios::app);
        fout << u << " " << p << endl;
        fout.close();
        cout << "Signup successful!" << endl;
    }
    bool login() {
        string u, p, fileU, fileP;
        cout << "Enter username: ";
        cin >> u;
        cout << "Enter password: ";
        cin >> p;
        ifstream fin("customers.txt");
        while (fin >> fileU >> fileP) {
            if (fileU == u && fileP == p) {
                username = u;
                password = p;
                fin.close();
                return true;
            }
        }
        fin.close();
        return false;
    }
    void showMenu(CarManager &cm, TransactionManager &tm) {
        int choice;
        do {
            cout << endl << "--- CUSTOMER MENU ---" << endl;
            cout << "1. View Available Cars" << endl;
            cout << "2. Rent a Car" << endl;
            cout << "3. Logout" << endl;
            cout << "Choice: ";
            cin >> choice;
            if (choice == 1) {
                cm.viewCars();
            } else if (choice == 2) {
                string plate;
                int hours, bill;
                cout << "Enter Car Plate: ";
                cin.ignore();
                getline(cin, plate);
                cout << "Enter Hours: ";
                cin >> hours;
                if (cm.rentCar(plate, hours, bill)) {
                    cout << "Total Bill: " << bill << endl;
                    cout << "Confirm payment (1=yes): ";
                    int confirm;
                    cin >> confirm;
                    if (confirm == 1) {
                        tm.pushTransaction(plate, hours, bill);
                        cout << "Rental successful!" << endl;
                    } else cout << "Transaction cancelled." << endl;
                } else cout << "Car not available." << endl;
            } else if (choice == 3) break;
        } while (true);
    }
    void customerAccess(CarManager &cm, TransactionManager &tm) {
        int choice;
        do {
            cout << endl << "--- CUSTOMER PORTAL ---" << endl;
            cout << "1. Login" << endl;
            cout << "2. Signup" << endl;
            cout << "3. Exit" << endl;
            cout << "Choice: ";
            cin >> choice;
            if (choice == 1) {
                if (login()) showMenu(cm, tm);
                else cout << "Invalid credentials." << endl;
            } else if (choice == 2) signup();
            else if (choice == 3) break;
        } while (choice != 3);
    }
};
class Admin {
public:
    bool login() {
        string u, p, fileU, fileP;
        cout << "Enter admin username: ";
        cin >> u;
        cout << "Enter admin password: ";
        cin >> p;
        ifstream fin("admins.txt");
        if (!fin) return false;
        while (fin >> fileU >> fileP) {
            if (fileU == u && fileP == p) {
                fin.close();
                return true;
            }
        }
        fin.close();
        return false;
    }
    void showMenu(CarManager &cm, TransactionManager &tm) {
        int ch;
        do {
            cout << endl << "--- ADMIN MENU ---" << endl;
            cout << "1. Add Car" << endl;
            cout << "2. View Cars" << endl;
            cout << "3. Delete Car" << endl;
            cout << "4. View Transactions" << endl;
            cout << "5. Logout" << endl;
            cout << "Choice: ";
            cin >> ch;
            cin.ignore();
            if (ch == 1) {
                string plate, name;
                int price;
                cout << "Plate: ";
                getline(cin, plate);
                cout << "Name: ";
                getline(cin, name);
                cout << "Price/hr: ";
                cin >> price;
                cin.ignore();
                cm.addCar(plate, name, price);
                cout << "Car added" << endl;
            } else if (ch == 2) {
                cm.viewCars();
            } else if (ch == 3) {
                string plate;
                cout << "Plate: ";
                getline(cin, plate);
                if (cm.deleteCar(plate)) cout << "Deleted" << endl;
                else cout << "Not found" << endl;
            } else if (ch == 4) {
                tm.viewTransactions();
            } else if (ch == 5) break;
        } while (true);
    }
    void adminAccess(CarManager &cm, TransactionManager &tm) {
        if (login()) showMenu(cm, tm);
        else cout << "Invalid admin credentials" << endl;
    }
};

void saveAdminCredentials() {
    ofstream fout("admins.txt");
    fout << "fatima 66660" << endl;
    fout.close();
}

int main() {
    saveAdminCredentials();
    CarManager cm;
    TransactionManager tm;
    Customer cust;
    Admin adm;
    int choice;
    do {
        cout <<endl<< "1. Admin Portal" << endl;
        cout << "2. Customer Portal" << endl;
        cout << "3. Exit" << endl;
        cout << "Choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1){
            adm.adminAccess(cm, tm);
        }else if (choice == 2){
            cust.customerAccess(cm, tm);
        }else if (choice == 3){
            break;
        }

    } while (true);
}