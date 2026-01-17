#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Transaction
{
    string plate;
    int hours, bill;
    Transaction *next;
};

static Transaction *top = NULL;

void pushTransaction(string plate, int hours, int bill)
{
    Transaction *n = new Transaction;
    n->plate = plate;
    n->hours = hours;
    n->bill = bill;
    n->next = top;
    top = n;

    ofstream fout("transactions.txt", ios::app);
    fout << plate << " " << hours << " " << bill << "\n";
    fout.close();
}

void viewTransactions()
{
    ifstream fin("transactions.txt");
    string p;
    int h, b;
    int found = 0;
    while (fin >> p >> h >> b)
    {
        cout << "Car: " << p << " Hours: " << h << " Bill: " << b << "\n";
        found = 1;
    }
    if (!found)
        cout << "No transactions\n";
    fin.close();
}

void loadTransactions()
{
    ifstream fin("transactions.txt");
    string p;
    int h, b;
    while (fin >> p >> h >> b)
        pushTransaction(p, h, b);
    fin.close();
}
