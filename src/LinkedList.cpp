#include <iostream>
#include <string>
using namespace std;

class Entity {
protected:
    int ID;

public:
    Entity() : ID(0) {}
    Entity(int id) : ID(id) {}

    int getID() const {
        return ID;
    }

    void setID(int id) {
        ID = id;
    }

    virtual void display() = 0;

    virtual ~Entity() {}
};

class Passenger : public Entity {
private:
    string Name;
    string PassportNo;

public:
    Passenger() : Entity(0), Name(""), PassportNo("") {}

    Passenger(int id, string name, string passport)
        : Entity(id), Name(name), PassportNo(passport) {}

    string getName() const {
        return Name;
    }

    string getPassportNo() const {
        return PassportNo;
    }

    void setName(string name) {
        Name = name;
    }

    void setPassportNo(string passport) {
        PassportNo = passport;
    }

    void display() override {
        cout << "Passenger ID : " << ID << endl;
        cout << "Name         : " << Name << endl;
        cout << "Passport No  : " << PassportNo << endl;
    }
};

class BookingOffice : public Entity {
private:
    string OfficeName;
    string Location;

public:
    BookingOffice() : Entity(0), OfficeName(""), Location("") {}

    BookingOffice(int id, string name, string loc)
        : Entity(id), OfficeName(name), Location(loc) {}

    int getOfficeID() const {
        return ID;
    }

    string getOfficeName() const {
        return OfficeName;
    }

    string getLocation() const {
        return Location;
    }

    void setOfficeID(int id) {
        ID = id;
    }

    void setOfficeName(string name) {
        OfficeName = name;
    }

    void setLocation(string loc) {
        Location = loc;
    }

    void display() override {
        cout << "Office ID    : " << ID << endl;
        cout << "Office Name  : " << OfficeName << endl;
        cout << "Location     : " << Location << endl;
    }
};

class Ticket : public Entity {
private:
    string PassengerList;
    int FlightNo;
    string OfficeName;

public:
    Ticket() : Entity(0), PassengerList(""), FlightNo(0), OfficeName("") {}

    Ticket(int tno, string plist, int fno, string oname)
        : Entity(tno), PassengerList(plist), FlightNo(fno), OfficeName(oname) {}

    int getTicketNo() const {
        return ID;
    }

    string getPassengerList() const {
        return PassengerList;
    }

    int getFlightNo() const {
        return FlightNo;
    }

    string getOfficeName() const {
        return OfficeName;
    }

    void setTicketNo(int tno) {
        ID = tno;
    }

    void setPassengerList(string plist) {
        PassengerList = plist;
    }

    void setFlightNo(int fno) {
        FlightNo = fno;
    }

    void setOfficeName(string oname) {
        OfficeName = oname;
    }

    void display() override {
        cout << "Ticket No    : " << ID << endl;
        cout << "Passenger    : " << PassengerList << endl;
        cout << "Flight No    : " << FlightNo << endl;
        cout << "Office Name  : " << OfficeName << endl;
    }
};

struct TicketNode {
    Ticket data;
    TicketNode* next;

    TicketNode(Ticket t) : data(t), next(NULL) {}
};

class Flight : public Entity {
private:
    string Destination;
    string Gate;
    string DepartureTime;
    TicketNode* TicketList;

public:
    Flight()
        : Entity(0),
          Destination(""),
          Gate(""),
          DepartureTime(""),
          TicketList(NULL) {}

    Flight(int id, string dest, string gate, string depTime)
        : Entity(id),
          Destination(dest),
          Gate(gate),
          DepartureTime(depTime),
          TicketList(NULL) {}

    Flight(const Flight& f) : Entity(f.ID) {
        Destination = f.Destination;
        Gate = f.Gate;
        DepartureTime = f.DepartureTime;
        TicketList = NULL;

        TicketNode* curr = f.TicketList;
        TicketNode* tail = NULL;

        while (curr != NULL) {
            TicketNode* n = new TicketNode(curr->data);

            if (!TicketList) {
                TicketList = n;
                tail = n;
            } else {
                tail->next = n;
                tail = n;
            }

            curr = curr->next;
        }
    }

    ~Flight() {
        TicketNode* curr = TicketList;

        while (curr) {
            TicketNode* t = curr;
            curr = curr->next;
            delete t;
        }
    }

    int getFlightID() const {
        return ID;
    }

    string getDestination() const {
        return Destination;
    }

    string getGate() const {
        return Gate;
    }

    string getDepartureTime() const {
        return DepartureTime;
    }

    void setFlightID(int id) {
        ID = id;
    }

    void setDestination(string dest) {
        Destination = dest;
    }

    void setGate(string gate) {
        Gate = gate;
    }

    void setDepartureTime(string d) {
        DepartureTime = d;
    }

    void addTicketToFlight(Ticket t) {
        TicketNode* newNode = new TicketNode(t);

        if (!TicketList) {
            TicketList = newNode;
            return;
        }

        TicketNode* curr = TicketList;

        while (curr->next)
            curr = curr->next;

        curr->next = newNode;
    }

    void display() override {
        cout << "Flight ID      : " << ID << endl;
        cout << "Destination    : " << Destination << endl;
        cout << "Gate           : " << Gate << endl;
        cout << "Departure Time : " << DepartureTime << endl;

        TicketNode* curr = TicketList;

        if (!curr) {
            cout << "No Tickets" << endl;
            return;
        }

        int count = 1;

        while (curr) {
            cout << "Ticket " << count++ << endl;
            curr->data.display();
            curr = curr->next;
        }
    }
};

struct PassengerNode {
    Passenger data;
    PassengerNode* next;

    PassengerNode(Passenger p) : data(p), next(NULL) {}
};

struct FlightNode {
    Flight data;
    FlightNode* next;

    FlightNode(Flight f) : data(f), next(NULL) {}
};

struct OfficeNode {
    BookingOffice data;
    OfficeNode* next;

    OfficeNode(BookingOffice o) : data(o), next(NULL) {}
};

struct GlobalTicketNode {
    Ticket data;
    GlobalTicketNode* next;

    GlobalTicketNode(Ticket t) : data(t), next(NULL) {}
};

PassengerNode* passengerHead = NULL;
FlightNode* flightHead = NULL;
OfficeNode* officeHead = NULL;
GlobalTicketNode* ticketHead = NULL;

void printLine() {
    cout << "----------------------------------" << endl;
}

void addPassenger() {
    int id;
    string name;
    string passport;

    cout << "Enter Passenger ID : ";
    cin >> id;
    cin.ignore();

    cout << "Enter Name : ";
    getline(cin, name);

    cout << "Enter Passport No : ";
    getline(cin, passport);

    PassengerNode* newNode =
        new PassengerNode(Passenger(id, name, passport));

    if (!passengerHead) {
        passengerHead = newNode;
    } else {
        PassengerNode* curr = passengerHead;

        while (curr->next)
            curr = curr->next;

        curr->next = newNode;
    }

    cout << "Passenger Added" << endl;
}

void displayPassengers() {
    if (!passengerHead) {
        cout << "Empty List" << endl;
        return;
    }

    PassengerNode* curr = passengerHead;

    while (curr) {
        curr->data.display();
        printLine();
        curr = curr->next;
    }
}

void addFlight() {
    int id;
    string dest;
    string gate;
    string dep;

    cout << "Enter Flight ID : ";
    cin >> id;
    cin.ignore();

    cout << "Enter Destination : ";
    getline(cin, dest);

    cout << "Enter Gate : ";
    getline(cin, gate);

    cout << "Enter Departure Time : ";
    getline(cin, dep);

    FlightNode* newNode =
        new FlightNode(Flight(id, dest, gate, dep));

    if (!flightHead) {
        flightHead = newNode;
    } else {
        FlightNode* curr = flightHead;

        while (curr->next)
            curr = curr->next;

        curr->next = newNode;
    }

    cout << "Flight Added" << endl;
}

void displayFlights() {
    if (!flightHead) {
        cout << "Empty List" << endl;
        return;
    }

    FlightNode* curr = flightHead;

    while (curr) {
        curr->data.display();
        printLine();
        curr = curr->next;
    }
}

int main() {
    int choice;

    do {
        printLine();

        cout << "AIRLINE MANAGEMENT SYSTEM" << endl;

        printLine();

        cout << "1. Add Passenger" << endl;
        cout << "2. Display Passengers" << endl;
        cout << "3. Add Flight" << endl;
        cout << "4. Display Flights" << endl;
        cout << "0. Exit" << endl;

        printLine();

        cout << "Enter Choice : ";
        cin >> choice;

        switch (choice) {
        case 1:
            addPassenger();
            break;

        case 2:
            displayPassengers();
            break;

        case 3:
            addFlight();
            break;

        case 4:
            displayFlights();
            break;

        case 0:
            cout << "Goodbye" << endl;
            break;

        default:
            cout << "Invalid Choice" << endl;
        }

    } while (choice != 0);

    return 0;
}
