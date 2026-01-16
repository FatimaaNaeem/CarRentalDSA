#include <iostream>
#include <string>
#include <fstream>
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

Car *carHead = NULL;

void insertCar(string name, string plateNo, string color, string brand, string model, string pricePerHour, bool availability)
{
    Car *newNode = new Car{name, plateNo, color, brand, model, pricePerHour, availability, NULL};

    if (carHead == NULL)
        carHead = newNode;
    else
    {
        Car *temp = carHead;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newNode;
    }
}

bool deleteCar(string plateNo)
{
    if (carHead == NULL)
        return false;

    if (carHead->carPlateNo == plateNo)
    {
        Car *temp = carHead;
        carHead = carHead->next;
        delete temp;
        return true;
    }

    Car *current = carHead;
    Car *prev = NULL;

    while (current != NULL && current->carPlateNo != plateNo)
    {
        prev = current;
        current = current->next;
    }

    if (current == NULL)
        return false;

    prev->next = current->next;
    delete current;
    return true;
}

void displayCars()
{
    Car *temp = carHead;
    if (temp == NULL)
    {
        cout << "No cars available.\n";
        return;
    }
    while (temp != NULL)
    {
        cout << "Car Name: " << temp->carName << endl;
        cout << "Car Plate No: " << temp->carPlateNo << endl;
        cout << "Color: " << temp->color << endl;
        cout << "Brand: " << temp->brand << endl;
        cout << "Model: " << temp->model << endl;
        cout << "Price Per Hour: " << temp->pricePerHour << endl;
        cout << "Availability: " << (temp->availability ? "Available" : "Not Available") << endl;
        cout << "-----------------------\n";
        temp = temp->next;
    }
}

void saveCarData()
{
    ofstream fout("cars.txt");
    Car *temp = carHead;
    while (temp != NULL)
    {
        fout << temp->carName << " " << temp->carPlateNo << " " << temp->color << " "
             << temp->brand << " " << temp->model << " " << temp->pricePerHour << " "
             << temp->availability << endl;
        temp = temp->next;
    }
    fout.close();
}

void ViewCarData()
{
    ifstream fin("cars.txt");
    string name, plate, color, brand, model, price;
    bool avail;

    while (fin >> name >> plate >> color >> brand >> model >> price >> avail)
        insertCar(name, plate, color, brand, model, price, avail);

    fin.close();
}
