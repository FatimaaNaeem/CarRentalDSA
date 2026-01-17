#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Car
{
    string plate;
    string name;
    int price;
    int available;
    Car *next;
};

static Car *head = NULL;
static int loaded = 0;

void loadCars()
{
    if (loaded)
        return;
    loaded = 1;

    ifstream fin("cars.txt");
    while (true)
    {
        Car *n = new Car;
        fin >> n->plate >> n->name >> n->price >> n->available;
        if (!fin)
        {
            delete n;
            break;
        }
        n->next = head;
        head = n;
    }
    fin.close();
}

void saveCars()
{
    ofstream fout("cars.txt");
    Car *t = head;
    while (t)
    {
        fout << t->plate << " " << t->name << " " << t->price << " " << t->available << "\n";
        t = t->next;
    }
    fout.close();
}

void addCar(string plate, string name, int price)
{
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

void viewCars()
{
    loadCars();
    Car *t = head;
    int found = 0;
    while (t)
    {
        cout << "Plate: " << t->plate << "\nName: " << t->name
             << "\nPrice/hr: " << t->price
             << "\nStatus: " << (t->available ? "Available" : "Rented") << "\n\n";
        t = t->next;
        found = 1;
    }
    if (!found)
        cout << "No cars available\n";
}

int deleteCar(string plate)
{
    loadCars();
    Car *t = head, *p = NULL;
    while (t)
    {
        if (t->plate == plate)
        {
            if (!p)
                head = t->next;
            else
                p->next = t->next;
            delete t;
            saveCars();
            return 1;
        }
        p = t;
        t = t->next;
    }
    return 0;
}

int rentCar(string plate, int hours, int &bill)
{
    loadCars();
    Car *t = head;
    while (t)
    {
        if (t->plate == plate && t->available)
        {
            t->available = 0;
            bill = t->price * hours;
            saveCars();
            return 1;
        }
        t = t->next;
    }
    return 0;
}
