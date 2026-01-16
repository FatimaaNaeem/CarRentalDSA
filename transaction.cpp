#include <iostream>
#include <string>
#include <fstream>
using namespace std;

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

Transaction *transactionHead = NULL;

void pushTransaction(int tID, int cID, string plateNo, int hours, string date, int amount)
{
    Transaction *newNode = new Transaction{tID, cID, plateNo, hours, date, amount, NULL};
    newNode->next = transactionHead;
    transactionHead = newNode;
}

void displayTransactions()
{
    Transaction *temp = transactionHead;
    while (temp != NULL)
    {
        cout << "Transaction ID: " << temp->transactionID << endl;
        cout << "Customer ID: " << temp->customerID << endl;
        cout << "Car Plate: " << temp->carPlateNo << endl;
        cout << "Hours: " << temp->rentHours << endl;
        cout << "Date: " << temp->rentDate << endl;
        cout << "Total: " << temp->totalAmount << endl;
        cout << "-----------------------\n";
        temp = temp->next;
    }
}

void SaveTransactionsToFile()
{
    ofstream fout("transactions.txt");
    Transaction *temp = transactionHead;
    while (temp != NULL)
    {
        fout << temp->transactionID << " " << temp->customerID << " "
             << temp->carPlateNo << " " << temp->rentHours << " "
             << temp->rentDate << " " << temp->totalAmount << endl;
        temp = temp->next;
    }
    fout.close();
}

void LoadTransactionsFromFile()
{
    ifstream fin("transactions.txt");
    int tid, cid, rhours, total;
    string plateNo, rdate;
    while (fin >> tid >> cid >> plateNo >> rhours >> rdate >> total)
        pushTransaction(tid, cid, plateNo, rhours, rdate, total);
    fin.close();
}
