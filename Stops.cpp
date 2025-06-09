#include <iostream>
using namespace std;
// تعريف كلاس بطاقة الراكب (PassengerCard)
class PassengerCard {
private:
    int id;
    string name;
    int priority; // أولوية الصعود (الأصغر أولوية أعلى)
    int destinationStopId; // رقم موقف الوجهة

public:
    PassengerCard(int pId, string pName, int destId, int prio = 10)
    {
        id = pId;
        name = pName;
        destinationStopId = destId;
        priority = prio;
    }

    int getId() { 
        return id;
    }
   string getName() { 
       return name; 
   }
    int getPriority()  { 
        return priority;
    }
    int getDestination()  {
        return destinationStopId;
    }

    void setPriority(int newPrio) {
        priority = newPrio;
    }
};
class BusParking {
private:
    int lineId;        // الخط الذي يخدمه هذا المصف

    // كيو الباصات في المصفة
    struct BusNode {
        int busId; // رقم الباص
        BusNode* next;
        BusNode(int id, BusNode* n = nullptr)  {
            busId = id; 
                next = n;
        }
    };
    BusNode* front; // بداية المصف
    BusNode* rear;  // نهاية المصف

public:
    BusParking(int lId) {
        lineId = lId;
        front = nullptr;
        rear = nullptr;
   
    }

   

    // إضافة باص لنهاية الكيو
    void addBus(int busId) {
        BusNode* newNode = new BusNode(busId);
        if (rear == nullptr) {
            front = rear = newNode;
        }
        else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    // إخراج باص من بداية الكيو
    int removeBus() {
        if (front == nullptr) 
            return -1; // -1 يعني لا يوجد باصات

        BusNode* temp = front;
        int busId = temp->busId;
        front = front->next;

        if (front == nullptr) {
            rear = nullptr;
        }

        delete temp;
        return busId;
    }

    // طباعة باصات المصفة
    void printBuses()  {
        BusNode* current = front;
         cout << "Buses in parking for line " << lineId << ": ";
        while (current != nullptr) {
            cout << current->busId << " ";
            current = current->next;
        }
       cout << endl;
    }

    int getLineId()  {
        return lineId; 
    }
};

 class Stop {
 private:
     int id;
     string name;

     // طابور الركاب حسب الأولوية
     struct PassengerNode {
         PassengerCard* passenger;
         PassengerNode* next;

         PassengerNode(PassengerCard* p, PassengerNode* n = nullptr)  {
             passenger = p;
             next = n;
         }
     };

    PassengerNode* passengerHead;          // مؤشر لأول راكب في الطابور
    int passengerCount;           // عدد الركاب في الانتظار
    // نظام المصفات(5 مصفات)
    static const int PARKING_SLOTS = 5;
    BusParking* parkings[PARKING_SLOTS];

    // دالة Hash لتوزيع المصفات
    int parkingHash(int parkingId) {
        return parkingId % PARKING_SLOTS;
    }
 public:
    
    Stop(int stopId, string stopName) {
        id = stopId;
        name = stopName;
        passengerHead = nullptr;
        passengerCount = 0;
        for (int i = 0; i < PARKING_SLOTS; i++) {
            parkings[i] = new BusParking (-1);
        }
    }

    int getId()  { 
        return id;
    }
   string getName() { 
       return name; 
   }
    int getPassengerCount() { 
        return passengerCount;
    }
    void addPassenger(PassengerCard* passenger) {
        PassengerNode* newNode = new PassengerNode(passenger);

        // الحالة 1: الطابور فارغ أو الأولوية الجديدة أعلى من أول راكب
        if (passengerHead == nullptr ||
            passenger->getPriority() < passengerHead->passenger->getPriority()) {
            newNode->next = passengerHead;
            passengerHead = newNode;
        } 
        // الحالة 2: نضيف الراكب في منتصف أو نهاية الطابور
        else {
            // نبدأ من أول راكب
            PassengerNode* current = passengerHead;
            // نبحث عن الموضع المناسب حسب الأولوية
            // نتوقف عندما نصل لنهاية الطابور أو نجد راكب بأولوية أقل
            while (current->next != nullptr &&
                current->next->passenger->getPriority() <= passenger->getPriority()) {
                current = current->next;
            }
            // نضع العقدة الجديدة بعد العقدة الحالية
            newNode->next = current->next;
            current->next = newNode;
        }
        // نزيد عدد الركاب في الموقف
 
        passengerCount++;
    }
         
        
  

};