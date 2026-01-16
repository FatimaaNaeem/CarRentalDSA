#include <iostream>
#include <string>
using namespace std;

class Car
{
public:
    int carID;
    string carName;
    string carPlateNo;
    string color;
    string brand;
    string model;
    string pricePerHour;
    bool availability;

    Car *next;

    Car(int id, string name, string plateNo, string c, string b,
        string m, string price, bool avail)
    {
        carID=id;
        carName=name;
        carPlateNo=plateNo;
        color=c;
        brand=b;
        model=m;
        pricePerHour=price;
        availability=avail;
        next=NULL;
    }
};
Car *head=NULL;

void insertCar(int id, string name, string plateNo, string color,
               string brand, string model, string pricePerHour, bool availability)
{
    Car *newNode=new Car(id, name, plateNo, color, brand, model, pricePerHour, availability);

    if(head==NULL)
    {
        head=newNode;
    }else{
        Car *temp=head;
        while(temp->next!=NULL)
        {
            temp=temp->next;
        }
        temp->next=newNode;
    }
}
void displayCars()
{
    Car *temp=head;

    while(temp!=NULL)
    {
        cout<<"Car ID: "<<temp->carID<<endl;
        cout<<"Car Name: "<<temp->carName<<endl;
        cout<<"Car Plate No: "<<temp->carPlateNo<<endl;
        cout<<"Color: "<<temp->color<<endl;
        cout<<"Brand: "<<temp->brand<<endl;
        cout<<"Model: "<<temp->model<<endl;
        cout<<"Price Per Hour: "<<temp->pricePerHour<<endl;
        cout<<"Availability: "<<(temp->availability ? "Available" : "Not Available")<<endl;

        temp=temp->next;
    }
}
