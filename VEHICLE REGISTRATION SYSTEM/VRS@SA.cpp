#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Vehicle {
protected:
    string vehicleID;
    string manufacturer;
    string model;
    int year;
    static int totalVehicles;

public:
    Vehicle() : vehicleID(""), manufacturer(""), model(""), year(0) {
        totalVehicles++;
    }

    Vehicle(string vID, string mfr, string mdl, int yr) 
    
        : vehicleID(vID), manufacturer(mfr), model(mdl), year(yr) {
        totalVehicles++;
    }

    virtual ~Vehicle() {
        totalVehicles--;
    }

    
    string getVehicleID() const { return vehicleID; }
    void setVehicleID(const string& vID) { vehicleID = vID; }

    string getManufacturer() const { return manufacturer; }
    void setManufacturer(const string& mfr) { manufacturer = mfr; }

    string getModel() const { return model; }
    void setModel(const string& mdl) { model = mdl; }

    int getYear() const { return year; }
    void setYear(int yr) { year = yr; }

    static int getTotalVehicles() { return totalVehicles; }

    virtual void display() const {
        cout << "Vehicle ID: " << vehicleID << "\nManufacturer: " << manufacturer
             << "\nModel: " << model << "\nYear: " << year << endl;
    }
};

int Vehicle::totalVehicles = 0;

class Car : public Vehicle {
protected:
    string fuelType;

public:
    Car() : Vehicle(), fuelType("") {}

    Car(string vID, string mfr, string mdl, int yr, string fuel) 
        : Vehicle(vID, mfr, mdl, yr), fuelType(fuel) {}

    string getFuelType() const { return fuelType; }
    void setFuelType(const string& fuel) { fuelType = fuel; }

    void display() const override {
        Vehicle::display();
        cout << "Fuel Type: " << fuelType << endl;
    }
};

class ElectricCar : public Car {
protected:
    int batteryCapacity;

public:
    ElectricCar() : Car(), batteryCapacity(0) {}

    ElectricCar(string vID, string mfr, string mdl, int yr, string fuel, int battery)
        : Car(vID, mfr, mdl, yr, fuel), batteryCapacity(battery) {}

    int getBatteryCapacity() const { return batteryCapacity; }
    void setBatteryCapacity(int battery) { batteryCapacity = battery; }

    void display() const override {
        Car::display();
        cout << "Battery Capacity: " << batteryCapacity << " kWh" << endl;
    }
};

class Aircraft {
protected:
    int flightRange;

public:
    Aircraft() : flightRange(0) {}

    Aircraft(int range) : flightRange(range) {}

    int getFlightRange() const { return flightRange; }
    void setFlightRange(int range) { flightRange = range; }

    virtual void display() const {
        cout << "Flight Range: " << flightRange << " km" << endl;
    }
};

class FlyingCar : public Car, public Aircraft {
public:
    FlyingCar() : Car(), Aircraft() {}

    FlyingCar(string vID, string mfr, string mdl, int yr, string fuel, int range)
        : Car(vID, mfr, mdl, yr, fuel), Aircraft(range) {}

    void display() const override {
        Car::display();
        Aircraft::display();
    }
};

class SportsCar : public ElectricCar {
protected:
    int topSpeed;

public:
    SportsCar() : ElectricCar(), topSpeed(0) {}

    SportsCar(string vID, string mfr, string mdl, int yr, string fuel, int battery, int speed)
        : ElectricCar(vID, mfr, mdl, yr, fuel, battery), topSpeed(speed) {}

    int getTopSpeed() const { return topSpeed; }
    void setTopSpeed(int speed) { topSpeed = speed; }

    void display() const override {
        ElectricCar::display();
        cout << "Top Speed: " << topSpeed << " km/h" << endl;
    }
};

class Sedan : public Car {
public:
    Sedan() : Car() {}

    Sedan(string vID, string mfr, string mdl, int yr, string fuel)
        : Car(vID, mfr, mdl, yr, fuel) {}

    void display() const override {
        Car::display();
    }
};

class SUV : public Car {
public:
    SUV() : Car() {}

    SUV(string vID, string mfr, string mdl, int yr, string fuel)
        : Car(vID, mfr, mdl, yr, fuel) {}

    void display() const override {
        Car::display();
    }
};

class VehicleRegistry {
private:
    vector<Vehicle*> vehicles;

public:
    ~VehicleRegistry() {
        for (Vehicle* v : vehicles) {
            delete v;
        }
    }

    void addVehicle(Vehicle* v) {
        vehicles.push_back(v);
    }

    void displayAllVehicles() const {
        for (const Vehicle* v : vehicles) {
            v->display();
            cout << "---------------------" << endl;
        }
    }

    Vehicle* searchById(const string& id) const {
        for (Vehicle* v : vehicles) {
            if (v->getVehicleID() == id) {
                return v;
            }
        }
        return nullptr;
    }
};

void menu() {
    VehicleRegistry registry;
    int choice;

    do {
        cout << "\nVehicle Registry Menu:\n";
        cout << "1. Add a vehicle\n";
        cout << "2. View all vehicles\n";
        cout << "3. Search by ID\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int type;
                cout << "\nSelect Vehicle Type:\n";
                cout << "1. Car\n";
                cout << "2. Electric Car\n";
                cout << "3. Flying Car\n";
                cout << "4. Sports Car\n";
                cout << "5. Sedan\n";
                cout << "6. SUV\n";
                cout << "Enter your choice: ";
                cin >> type;

                string vID, mfr, mdl, fuel;
                int yr, battery, range, speed;

                cout << "Enter Vehicle ID: ";
                cin >> vID;
                cout << "Enter Manufacturer: ";
                cin >> mfr;
                cout << "Enter Model: ";
                cin >> mdl;
                cout << "Enter Year: ";
                cin >> yr;

                if (type == 1) {
                    cout << "Enter Fuel Type: ";
                    cin >> fuel;
                    registry.addVehicle(new Car(vID, mfr, mdl, yr, fuel));
                } else if (type == 2) {
                    cout << "Enter Fuel Type: ";
                    cin >> fuel;
                    cout << "Enter Battery Capacity: ";
                    cin >> battery;
                    registry.addVehicle(new ElectricCar(vID, mfr, mdl, yr, fuel, battery));
                } else if (type == 3) {
                    cout << "Enter Fuel Type: ";
                    cin >> fuel;
                    cout << "Enter Flight Range: ";
                    cin >> range;
                    registry.addVehicle(new FlyingCar(vID, mfr, mdl, yr, fuel, range));
                } else if (type == 4) {
                    cout << "Enter Fuel Type: ";
                    cin >> fuel;
                    cout << "Enter Battery Capacity: ";
                    cin >> battery;
                    cout << "Enter Top Speed: ";
                    cin >> speed;
                    registry.addVehicle(new SportsCar(vID, mfr, mdl, yr, fuel, battery, speed));
                } else if (type == 5) {
                    cout << "Enter Fuel Type: ";
                    cin >> fuel;
                    registry.addVehicle(new Sedan(vID, mfr, mdl, yr, fuel));
                } else if (type == 6) {
                    cout << "Enter Fuel Type: ";
                    cin >> fuel;
                    registry.addVehicle(new SUV(vID, mfr, mdl, yr, fuel));
                } else {
                    cout << "Invalid choice!" << endl;
                }
                break;
            }
            case 2: {
                registry.displayAllVehicles();
                break;
            }
            case 3: {
                string id;
                cout << "Enter Vehicle ID to search: ";
                cin >> id;
                Vehicle* v = registry.searchById(id);
                if (v) {
                    v->display();
                } else {
                    cout << "Vehicle not found!" << endl;
                }
                break;
            }
            case 4:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 4);
}

int main() {
    menu();
    return 0;
}

