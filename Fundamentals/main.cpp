#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Vehicle
{
protected:
    string ID;
    double length;
    string type;

public:
    Vehicle(string ID, double length, string type)
        : ID(ID), length(length), type(type) {}

    virtual double calcMoney(int hours) = 0;

    string getID()
    {
        return ID;
    }

    double getLength()
    {
        return length;
    }

    string getType()
    {
        return type;
    }
};

class Car : public Vehicle
{
public:
    Car(string ID)
        : Vehicle(ID, 5.0, "Car") {}

    double calcMoney(int hours) override
    {
        return hours * 10.0;
    }
};

class Motorcycle : public Vehicle
{
public:
    Motorcycle(string ID)
        : Vehicle(ID, 2.0, "Motorcycle") {}

    double calcMoney(int hours) override
    {
        return hours * 5.0;
    }
};

class Bus : public Vehicle
{
public:
    Bus(string ID)
        : Vehicle(ID, 10.0, "Bus") {}

    double calcMoney(int hours) override
    {
        return hours * 15.0;
    }
};

class Truck : public Vehicle
{
public:
    Truck(string ID)
        : Vehicle(ID, 7.0, "Truck") {}

    double calcMoney(int hours) override
    {
        return hours * 15.0;
    }
};

class Customer
{
private:
    string name;
    string customerID;
    string vehicleID;

public:
    Customer(string name, string customerID)
        : name(name), customerID(customerID), vehicleID("") {}

    string getName()
    {
        return name;
    }

    string getCustomerID()
    {
        return customerID;
    }

    string getVehicleID()
    {
        return vehicleID;
    }

    void setVehicleID(string ID)
    {
        vehicleID = ID;
    }
};

class Parking
{
private:
    vector<Vehicle *> parkedVehicles;
    vector<Customer *> customers;
    double parkingSpace;

public:
    Parking(double space)
        : parkingSpace(space) {}

    double getAvailableSpace()
    {
        double occupiedSpace = 0.0;
        for (vector<Vehicle *>::iterator it = parkedVehicles.begin(); it != parkedVehicles.end(); ++it)
        {
            occupiedSpace += (*it)->getLength();
        }
        return parkingSpace - occupiedSpace;
    }

    bool addVehicle(Vehicle *vehicle)
    {
        if (getAvailableSpace() >= vehicle->getLength())
        {
            parkedVehicles.push_back(vehicle);
            return 1;
        }
    }

    void leaveVehicle(string ID, int hours)
    {
        vector<Vehicle *>::iterator it = parkedVehicles.begin();
        while (it != parkedVehicles.end())
        {
            if ((*it)->getID() == ID)
            {
                double fee = (*it)->calcMoney(hours);
                cout << "Vehicle ID: " << (*it)->getID() << ", Type: " << (*it)->getType() << ", Parking Fee: $" << fee << endl;
                delete *it;
                it = parkedVehicles.erase(it);
                return;
            }
            else
            {
                ++it;
            }
        }
        cout << "Vehicle plate " << ID;
    }

    void leaveCustomer(string ID)
    {
        vector<Customer *>::iterator i = customers.begin();
        while (i != customers.end())
        {
            if ((*i)->getCustomerID() == ID)
            {
                cout << "customer ID: " << (*i)->getCustomerID();
                delete *i;
                i = customers.erase(i);
                return;
            }
            else
            {
                ++i;
            }
        }
        cout << ", customer ID " << ID << " is not found in the parking." << endl;
    }

    void addCustomer(Customer *customer)
    {
        customers.push_back(customer);
    }

    void showParkingStatus()
    {
        cout << "Parking Status:" << endl;
        for (vector<Vehicle *>::iterator it = parkedVehicles.begin(); it != parkedVehicles.end(); ++it)
        {
            cout << "Vehicle ID: " << (*it)->getID() << ", Type: " << (*it)->getType() << endl;
        }
        cout << "Total parked vehicles: " << parkedVehicles.size() << endl;
        cout << "Available space in the parking: " << getAvailableSpace() << " meters" << endl;
    }

    void showCustomerList()
    {
        cout << "Customer List:" << endl;
        for (vector<Customer *>::iterator it = customers.begin(); it != customers.end(); ++it)
        {
            cout << "Customer Name: " << (*it)->getName() << ", ID: " << (*it)->getCustomerID() << endl;
        }
        cout << "Total customers: " << customers.size() << endl;
    }

    void assignVehicleToCustomer(string customerID, string vehicleID)
    {
        vector<Customer *>::iterator customerIt = customers.begin();
        int hours;
        while (customerIt != customers.end())
        {
            if ((*customerIt)->getCustomerID() == customerID)
            {
                vector<Vehicle *>::iterator vehicleIt = parkedVehicles.begin();
                while (vehicleIt != parkedVehicles.end())
                {
                    if ((*vehicleIt)->getID() == vehicleID)
                    {
                        (*customerIt)->setVehicleID(vehicleID);
                        return;
                    }
                    else
                    {
                        ++vehicleIt;
                    }
                }
                cout << "Vehicle with ID " << vehicleID << " is not found in the parking. " << endl;
                return;
            }
            else
            {
                ++customerIt;
            }
        }
        cout << "Customer with ID " << customerID << " is not found." << endl;
    }
};
int main()
{
    Parking parking(100.0);
    int choice;
    while (true)
    {
        cout << "Parking System Menu:" << endl;
        cout << "1. Assign Vehicle to Customer" << endl;
        cout << "2. Show Parking Status" << endl;
        cout << "3. Show Customer List" << endl;
        cout << "4. Leave vehicle" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            string vehicleID;
            int vehicleType;

            cout << "Enter your vehicle plate number : ";
            cin >> vehicleID;
            string name, customerID;

            cout << "Enter customer name: ";
            cin.ignore();
            getline(cin, name);

            cout << "Enter customer ID: ";
            cin >> customerID;

            cout << "Select vehicle type:" << endl;
            cout << "1. Car" << endl;
            cout << "2. Motorcycle" << endl;
            cout << "3. Bus" << endl;
            cout << "4. Truck" << endl;
            cout << "Enter vehicle type: ";
            cin >> vehicleType;

            Vehicle *vehicle;
            switch (vehicleType)
            {
            case 1:
                vehicle = new Car(vehicleID);
                break;

            case 2:
                vehicle = new Motorcycle(vehicleID);
                break;

            case 3:
                vehicle = new Bus(vehicleID);
                break;

            case 4:
                vehicle = new Truck(vehicleID);
                break;

            default:
                cout << "Invalid vehicle type. Please try again." << endl;
                continue;
            }

            if (parking.addVehicle(vehicle))
            {
                Customer *customer = new Customer(name, customerID);
                parking.addCustomer(customer);
                cout << "Vehicle's Customer added successfully." << endl;
            }
            else
            {
                cout << "Parking space is full. Cannot park." << endl;
            }

            break;
        }

        case 2:
            parking.showParkingStatus();
            break;
        case 3:
            parking.showCustomerList();
            break;

        case 4:
        {
            cout << "Enter your vehicle plate number: ";
            string vehicleID;
            cin >> vehicleID;
            cout << "Enter your ID: ";
            string ID;
            cin >> ID;
            cout << "Enter number of hours parked: ";
            int hours;
            cin >> hours;
            parking.leaveVehicle(vehicleID, hours);
            parking.leaveCustomer(ID);
            break;
        }

        case 5:
            cout << "Exiting the program." << endl;
            return 0;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }

        cout << endl;
    }
}
