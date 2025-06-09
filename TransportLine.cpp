#include <iostream>
using namespace std;

// تعريف عقدة الموقف ضمن الخط
struct StopNode {
    string stopName;
   float costToNext;
    StopNode* next;

    StopNode(string name, int cost = 0) {
        stopName = name;
        costToNext = cost;
        next = nullptr;
    }
}; 

class  TransportLine {
private:
     int* maxLinesPtr;             // مؤشر لعدد الخطوط، قابل للتعديل ديناميكياً
    int currentLineCount;         // عدد الخطوط المنشأة حاليًا
    TransportLine** transportLines;        // مصفوفة ديناميكية لاحتواء الخطوط
    string lineName;
    StopNode* head;
public:
    TransportLine(string name) {
        lineName = name;
        head = nullptr;
        transportLines[currentLineCount++] = this;
    }

     int getMaxLines() {
        return *maxLinesPtr;
    }

    int getCurrentLineCount() {
        return currentLineCount;
    }

     void displayAllLines() {
        for (int i = 0; i < currentLineCount; ++i) {
            if (transportLines[i]) {
                transportLines[i]->displayLine();
            }
        }
    }

    string getLineName() const {
        return lineName;
    }

    void addStop(string stopName, int cost = 0) {
        StopNode* newStop = new StopNode(stopName);
        if (head == 0) {
            head = newStop;
            head->next = head;
            newStop->costToNext = cost;
        }
        else {
            StopNode* temp = head;
            while (temp->next != head) {
                temp = temp->next;
            }
            temp->next = newStop;
            newStop->next = head;
            temp->costToNext = cost;
            newStop->costToNext = 0;
        }
    }

    void removeStop(string stopName) {
        if (head == 0 )
             return;
        StopNode* curr = head;
        StopNode* prev = nullptr;

        do {
            if (curr->stopName == stopName) {
                if (curr == head) {
                    StopNode* tail = head;
                    while (tail->next != head)  
                        tail = tail->next;
                    if (head->next == head) {
                        delete head;
                        head = nullptr;
                        return;
                    }
                    tail->next = head->next;
                    StopNode* temp = head;
                    head = head->next;
                    delete temp;
                }
                else {
                    prev->next = curr->next;
                    delete curr;
                }
                return;
            }
            prev = curr;
            curr = curr->next;
        } while (curr != head);
    }

    void setCostBetween(string from, string to, int cost) {
        if (head == 0) 
            return;
        StopNode* temp = head;
        do {
            if (temp->stopName == from && temp->next->stopName == to) {
                temp->costToNext = cost;
                return;
            }
            temp = temp->next;
        } while (temp != head);
        cout << " The specified consecutive positions were not found.\n";
    }

    void printStops()  {
        if (head == 0) {
            cout << "There are no stops spaces yet..\n";
            return;
        }
        StopNode* temp = head;
        do {
            cout << "*" << temp->stopName << " (Cost to next: " << temp->costToNext << ")" << endl;
            temp = temp->next;
        } while (temp != head);
    }

    void displayLine()  {
        cout << "\n the line is: " << lineName << endl;
        printStops();
        cout << "----------------------------------\n";
    }

    bool hasStop(string name) const {
        if (head == 0) 
            return false;
        StopNode* temp = head;
        do {
            if (temp->stopName == name) return true;
            temp = temp->next;
        } while (temp != head);
        return false;
    }

   
};
