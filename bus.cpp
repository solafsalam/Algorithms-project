#include <iostream>
#include "Passenger.cpp"

using namespace std;

// تعريف كلاس السائق 
class Driver {
private:
    int id;
    string name;
    bool isAssigned;

    // رخصة القيادة
    struct DrivingLicense {
        string licensenumber;    // رقم الرخصة
        string expiryDate;       // تاريخ الانتهاء
        string driverName;       // اسم السائق
        int driverId;            // رقم السائق

        void LicenseDetails() {
            cout << "License details:\n"
                << "* License number: " << licensenumber << "\n"
                << "* Expiration date: " << expiryDate << "\n"
                << "* Driver name: " << driverName << "\n"
                << "* Driver's identification number: " << driverId << "\n";
        }

        bool isValid(string currentDate) {
            return expiryDate > currentDate;
        }
    } license;

public:
    Driver(int driverId, string driverName, string licNum, string licExpiry) {
        id = driverId;
        name = driverName;
        isAssigned = false;
        license.licensenumber = licNum;
        license.expiryDate = licExpiry;
        license.driverName = name;
        license.driverId = id;
    }

    void printInfo() {
        cout << " *Driver Name: " << name
            << "\n *Driver's identification number: " << id
            << "\n *Driving license: \n";
        license.LicenseDetails();
    }

    int getId() {
        return id;
    }

    string getName() {
        return name;
    }

    bool isLicenseValid(string date) {
        return license.isValid(date);
    }

    bool getIsAssigned() {
        return isAssigned;
    }

    void setAssigned(bool assigned) {
        isAssigned = assigned;
    }

    DrivingLicense getLicense() {
        return license;
    }
    struct PassengerNode {
        Passenger* passenger;
        PassengerNode* next;

        PassengerNode(Passenger* p) {
            passenger = p;
            next = nullptr;
        }

    };

    class Bus {
    private:
        // نوع المقعد
        enum SeatType {
            REGULAR,
            DISABLED_ACCESSIBLE
        };

        // نوع الباص
        enum BusType {
            MINI,
            MEDIUM,
            LARGE
        };

        // المستودع 
        struct Baggage {
            int passengerId;
            string description;
            float StorageCost;
            Baggage* next;
            float size;

            Baggage(int pid, string desc, float sc, float sz, Baggage* n = nullptr)
            {
                passengerId = pid;
                description = desc;
                StorageCost = sc;
                next = n;
                size = sz;
            }
        };

        int id;
        int capacity;
        int currentLineId;
        int currentStopId;
        float speed;
        Driver* driver;
        BusType type;
        SeatType* seatTypes;
        Baggage* baggageHead;
        float maxBaggageVolume;
        float usedVolume;
        float totalFees;
        int baggageCount;
        PassengerNode* firstPassenger;
        PassengerNode* lastPassenger;
        int passengerCount;


    public:
        Bus(int busId, BusType busType, int line, int stop)
        {
            id = id;
            type = type;
            currentLineId = line;
            currentStopId = stop;
            baggageCount = 0;
            driver = 0;
            baggageHead = nullptr;
            usedVolume = 0;
            totalFees = 0;
            passengerCount = 0;
            firstPassenger = 0;
            lastPassenger = 0;
            switch (type) {
            case MINI:
                capacity = 20;
                speed = 80.0f;
                maxBaggageVolume = 5.0f;
                break;
            case MEDIUM:
                capacity = 40;
                speed = 90.0f;
                maxBaggageVolume = 10.0f;
                break;
            case LARGE:
                capacity = 80;
                speed = 70.0f;
                maxBaggageVolume = 15.0f;
                break;
            }
            // توزيع أنواع المقاعد حسب نوع الباص
            seatTypes = new SeatType[capacity];
            for (int i = 0; i < capacity; i++) {
                if (i < 5) { // أول 5 مقاعد مخصصة
                    seatTypes[i] = SeatType(DISABLED_ACCESSIBLE);
                }

                else {
                    seatTypes[i] = SeatType(REGULAR);
                }
            }
        }

        bool assignDriver(Driver* newDriver, string currentDate) {
            if (newDriver == nullptr) {
                cout << "Error: Driver is null\n";
                return false;
            }

            // التحقق من صلاحية الرخصة
            if (!newDriver->isLicenseValid(currentDate)) {
                cout << "Driver cannot be assigned! Expired license\n";
                return false;
            }

            driver = newDriver;
            driver->setAssigned(true);
            cout << "Driver " << driver->getName() << " assigned to Bus: " << id << endl;
            return true;
        }

        void removeDriver() {
            if (driver != nullptr) {
                driver->setAssigned(false);
                cout << "Driver " << driver->getName() << " removed from Bus: " << id << endl;
                driver = nullptr;
            }
        }

        // دالة نقل السائق مع جميع الشروط
        bool transferDriver(Driver* driver, Bus* targetBus, float payment, string currentDate) {
            // الشرط 1: السائق غير معين حالياً
            if (driver->getIsAssigned()) {
                cout << "The driver is currently assigned and cannot be transferred.\n";
                return false;
            }

            // الشرط 2: الباص الهدف لا يملك سائق حالياً
            if (targetBus->driver != nullptr) {
                cout << "The target bus already has a driver.\n";
                return false;
            }

            // الشرط 3: التحقق من صلاحية الرخصة
            if (!driver->isLicenseValid(currentDate)) {
                cout << "Expired driving license.\n";
                return false;
            }

            // الشرط 4: وجود بدل نقل
            if (payment <= 0) {
                cout << "An amount must be specified for the transfer.\n";
                return false;
            }

            // إذا تحققت جميع الشروط
            targetBus->assignDriver(driver, currentDate);
            cout << "The driver was successfully transferred for a fee: " << payment << "\n";
            return true;
        }
        // إضافة راكب
        bool addPassenger(Passenger* p) {
            if (passengerCount >= capacity) {
                cout << "Bus is full!" << endl;
                return false;
            }

            PassengerNode* newNode = new PassengerNode(p);

            if (firstPassenger == nullptr) {
                firstPassenger = lastPassenger = newNode;
            }
            else if (p->hasBoardingPriority()) {
                newNode->next = firstPassenger;
                firstPassenger = newNode;
            }
            else {
                lastPassenger->next = newNode;
                lastPassenger = newNode;
            }

            passengerCount++;
            cout << "Passenger " << p->getId() << " boarded the bus";
            if (p->hasBoardingPriority()) cout << " (with priority)";
            cout << endl;

            return true;
        }


        // إزالة راكب
        bool removePassenger(int passengerId) {
            PassengerNode* current = firstPassenger;
            PassengerNode* prev = nullptr;
            bool found = false;

            while (current != nullptr) {
                if (current->passenger->getId() == passengerId) {
                    if (prev == nullptr) {
                        firstPassenger = current->next;
                    }
                    else {
                        prev->next = current->next;
                    }

                    if (current == lastPassenger) {
                        lastPassenger = prev;
                    }

                    delete current;
                    passengerCount--;
                    found = true;
                    cout << "Passenger " << passengerId << " removed from bus" << endl;
                    break;
                }

                prev = current;
                current = current->next;
            }

            if (!found) {
                cout << "Passenger " << passengerId << " not found on bus" << endl;
            }

            return found;
        }
        // عرض الركاب
        void listPassengers() {
            cout << "Passengers on bus " << id
                << " (" << passengerCount << "/" << capacity << "):" << endl;

            PassengerNode* current = firstPassenger;
            while (current != nullptr) {
                current->passenger->printInfo();
                cout << "-----------------" << endl;
                current = current->next;
            }
        }


        void addBaggage(int passengerId, string description, float fee, float size) {
            // التحقق من عدم تجاوز السعة
            if ((usedVolume + size) > maxBaggageVolume) {
                cout << "No more luggage can be added, the baggage storage is full!\n";
                return;
            }

            // إنشاء حقيبة جديدة
            Baggage* newBaggage = new Baggage(passengerId, description, fee, size, baggageHead);
            baggageHead = newBaggage;
            totalFees += fee;
            usedVolume += size;
            baggageCount++;

            cout << "Passenger bag added " << passengerId
                << " (" << description << ") with size " << size
                << " m3 for fee " << fee << endl;
        }

        // دالة حذف الحقيبة حسب passengerId
        bool removeBaggage(int passengerId) {
            Baggage* current = baggageHead;
            Baggage* prev = nullptr;
            bool found = false;

            while (current != nullptr) {
                if (current->passengerId == passengerId) {
                    // إزالة الحقيبة
                    if (prev == nullptr) {
                        baggageHead = current->next;
                    }
                    else {
                        prev->next = current->next;
                    }

                    totalFees -= current->StorageCost;
                    usedVolume -= current->size;
                    baggageCount--;

                    Baggage* temp = current;
                    current = current->next;
                    delete temp;

                    found = true;
                    cout << "Passenger bag removed " << passengerId << endl;
                }
                else {
                    prev = current;
                    current = current->next;
                }
            }

            if (!found) {
                cout << "No luggage found for passenger " << passengerId << endl;
            }

            return found;
        }

        // دالة طباعة معلومات الباص والمستودع
        void printBusInfo() {
            cout << "\n Bus Information \n";
            cout << "Bus ID: " << id << endl;
            cout << "Type: ";
            switch (type) {
            case MINI:
                cout << "Mini";
                break;
            case MEDIUM:
                cout << "Medium";
                break;
            case LARGE:
                cout << "Large";
                break;
            }
            cout << "\nCapacity: " << capacity << " passengers\n";
            cout << "Current line: " << currentLineId << endl;
            cout << "Current stop: " << currentStopId << endl;
            cout << "Passengers: " << passengerCount << endl;
            cout << "Baggage Count: " << baggageCount << endl;
            if (driver != nullptr) {
                cout << "Current driver: " << driver->getName() << endl;
            }
            else {
                cout << "No driver assigned\n";
            }

            cout << "\n Baggage Storage \n";
            cout << "Max volume: " << maxBaggageVolume << " \n";
            cout << "Used volume: " << usedVolume << " \n";
            cout << "Available volume: " << (maxBaggageVolume - usedVolume) << " \n";
            cout << "Total fees collected: " << totalFees << endl;
            cout << "\nBaggage items (" << baggageCount << "):\n";
            if (baggageCount == 0) {
                cout << "No baggage stored\n";
            }
            else {
                Baggage* current = baggageHead;
                while (current != nullptr) {
                    cout << "Passenger " << current->passengerId
                        << ": " << current->description
                        << " (Size: " << current->size << " m3, Fee: "
                        << current->StorageCost << ")\n";
                    current = current->next;
                }
            }
        }

    };

};