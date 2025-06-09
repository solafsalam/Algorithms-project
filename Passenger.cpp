#include <iostream>
using namespace std;
class Passenger {

    // أنواع بطاقات الركاب
    enum CardType {
        REGULAR,
        VIP,
        DISABLED
    };
private:
    struct Baggage {
        string description;
        float cost;
        float size;
        Baggage* next;
        Baggage(string desc, float c, float s, Baggage* n = nullptr)
            {
            description = desc;
            cost = c;
            size = s;
            next = n;
        }
    };
        int id;
        string name;
        CardType cardType;
        float balance;
        int freeRides; // الرحلات المجانية لـVIP
        Baggage* baggage;
        

public:
    Passenger(int pid, string pname, CardType pcard, float pbalance = 0.0f, int pfreeRides = 0)
         {
        id = pid;
        name = pname;
        cardType = pcard;
        balance = pbalance;
        freeRides = pfreeRides;
        baggage = nullptr;
    }

    bool isVIP() {
        return cardType == VIP;
    }
    int getId() {
        return id;
    }
    string getName() {
        return name;
    }
    float getBalance() {
        return balance;
    }
    void recharge(float amount) {
        balance += amount; 
    }

    // دالة الصعود إلى الباص مع تطبق أولوية VIP
    bool hasBoardingPriority()  {
        return isVIP(); // 
    }
    // دفع تكلفة مع خصم VIP
    bool pay(float amount) {
        if (cardType == CardType::VIP) {
            amount *= 0.5f; // خصم 50%
        }
        if (balance >= amount) {
            balance -= amount;
            return true;
        }
        return false;
    }// إضافة أمتعة مع تطبيق خصم VIP إذا كان مؤهلاً
    bool addBaggage(string item, float cost, float size) {
        if (isVIP()) {
            cost *= 0.7; // خصم 30% على الأمتعة
        }
        if (balance >= cost) {
            baggage = new Baggage(item, cost, size, baggage);
            balance -= cost;
            return true;
        }
        return false;
    }
    // إزالة الأمتعة
    bool removeBaggage() {
        if (!baggage)
            return false;
        Baggage* temp = baggage;
        baggage = baggage->next;
        delete temp;
        return true;
    }

    // دفع ثمن الرحلة و مجانية لـ VIP
    bool payForRide(float cost) {
        if (!isVIP()) {
            if (balance >= cost) {
                balance -= cost;
                return true;
            }
            return false;
        }
        // VIP لا يدفع ثمن الرحلة
        return true;
    }
  
    // دالة عرض معلومات الراكب
    void printInfo()  {
        cout << "\n passenger information:\n";
        cout << "the passdenger name: " << name << "\n";
        cout << "card id: " << id << "\n";
        cout << "card type: ";
        switch (cardType) {
        case REGULAR:
            cout << "regular card."; break;
        case VIP: 
            cout << "VIP card."; break;
        case DISABLED: 
            cout << "DISABLED card."; break;
        }
        cout << "\n";

        cout << "\n" << "the balance is: " << balance << "\n";

        
    }

};
