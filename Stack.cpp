#include <iostream>
#include <string>
using namespace std;


    //  BASE CLASS


class Entity {
protected:
    int ID;
public:
    Entity() : ID(0) {}
    Entity(int id) : ID(id) {}
    int  getID() const { return ID; }
    void setID(int id) { ID = id; }
    virtual void display() = 0;
    virtual ~Entity() {}
};

//        CLASSES

class Passenger : public Entity {
private:
    string Name;
    string PassportNo;
public:
    Passenger() : Entity(0), Name(""), PassportNo("") {}
    Passenger(int id, string name, string passport)
        : Entity(id), Name(name), PassportNo(passport) {}

    string getName()       const { return Name; }
    string getPassportNo() const { return PassportNo; }
    void setName(string name)           { Name = name; }
    void setPassportNo(string passport) { PassportNo = passport; }

    void display() override {
        cout << "  Passenger ID   : " << ID        << endl;
        cout << "  Name           : " << Name       << endl;
        cout << "  Passport No    : " << PassportNo << endl;
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

    int    getOfficeID()   const { return ID; }
    string getOfficeName() const { return OfficeName; }
    string getLocation()   const { return Location; }
    void setOfficeID(int id)        { ID = id; }
    void setOfficeName(string name) { OfficeName = name; }
    void setLocation(string loc)    { Location = loc; }

    void display() override {
        cout << "  Office ID      : " << ID        << endl;
        cout << "  Office Name    : " << OfficeName << endl;
        cout << "  Location       : " << Location   << endl;
    }
};

class Ticket : public Entity {
private:
    string PassengerList;
    int    FlightNo;
    string OfficeName;
public:
    Ticket() : Entity(0), PassengerList(""), FlightNo(0), OfficeName("") {}
    Ticket(int tno, string plist, int fno, string oname)
        : Entity(tno), PassengerList(plist), FlightNo(fno), OfficeName(oname) {}

    int    getTicketNo()      const { return ID; }
    string getPassengerList() const { return PassengerList; }
    int    getFlightNo()      const { return FlightNo; }
    string getOfficeName()    const { return OfficeName; }
    void setTicketNo(int tno)           { ID = tno; }
    void setPassengerList(string plist) { PassengerList = plist; }
    void setFlightNo(int fno)           { FlightNo = fno; }
    void setOfficeName(string oname)    { OfficeName = oname; }

    void display() override {
        cout << "  Ticket No      : " << ID           << endl;
        cout << "  Passenger      : " << PassengerList << endl;
        cout << "  Flight No      : " << FlightNo      << endl;
        cout << "  Office Name    : " << OfficeName    << endl;
    }
};

// ── Internal ticket list inside Flight (stays as LL) ──
struct TicketNode {
    Ticket      data;
    TicketNode* next;
    TicketNode(Ticket t) : data(t), next(NULL) {}
};

class Flight : public Entity {
private:
    string      Destination;
    string      Gate;
    string      DepartureTime;
    TicketNode* TicketList;
public:
    Flight() : Entity(0), Destination(""), Gate(""),
               DepartureTime(""), TicketList(NULL) {}
    Flight(int id, string dest, string gate, string depTime)
        : Entity(id), Destination(dest), Gate(gate),
          DepartureTime(depTime), TicketList(NULL) {}

    // Copy constructor (needed because FlightNode copies Flight)
    Flight(const Flight& f) : Entity(f.ID) {
        Destination   = f.Destination;
        Gate          = f.Gate;
        DepartureTime = f.DepartureTime;
        TicketList    = NULL;
        TicketNode* curr = f.TicketList;
        TicketNode* tail = NULL;
        while (curr != NULL) {
            TicketNode* n = new TicketNode(curr->data);
            if (!TicketList) { TicketList = n; tail = n; }
            else             { tail->next = n; tail = n; }
            curr = curr->next;
        }
    }

    ~Flight() {
        TicketNode* curr = TicketList;
        while (curr) { TicketNode* t = curr; curr = curr->next; delete t; }
    }

    int    getFlightID()      const { return ID; }
    string getDestination()   const { return Destination; }
    string getGate()          const { return Gate; }
    string getDepartureTime() const { return DepartureTime; }
    void setFlightID(int id)         { ID = id; }
    void setDestination(string dest) { Destination = dest; }
    void setGate(string gate)        { Gate = gate; }
    void setDepartureTime(string d)  { DepartureTime = d; }

    void addTicketToFlight(Ticket t) {
        TicketNode* newNode = new TicketNode(t);
        if (!TicketList) { TicketList = newNode; return; }
        TicketNode* curr = TicketList;
        while (curr->next) curr = curr->next;
        curr->next = newNode;
    }

    void display() override {
        cout << "  Flight ID      : " << ID           << endl;
        cout << "  Destination    : " << Destination  << endl;
        cout << "  Gate           : " << Gate          << endl;
        cout << "  Departure Time : " << DepartureTime << endl;
        cout << "  --- Tickets Issued for this Flight ---" << endl;
        TicketNode* curr = TicketList;
        if (!curr) { cout << "  (No tickets issued yet)" << endl; return; }
        int count = 1;
        while (curr) { cout << "  [Ticket " << count++ << "]" << endl;
                       curr->data.display(); curr = curr->next; }
    }
};

 

struct PassengerNode {
    Passenger      data;
    PassengerNode* next;
    PassengerNode(Passenger p) : data(p), next(NULL) {}
};

struct FlightNode {
    Flight      data;
    FlightNode* next;
    FlightNode(Flight f) : data(f), next(NULL) {}
};

struct OfficeNode {
    BookingOffice data;
    OfficeNode*   next;
    OfficeNode(BookingOffice o) : data(o), next(NULL) {}
};

struct GlobalTicketNode {
    Ticket            data;
    GlobalTicketNode* next;
    GlobalTicketNode(Ticket t) : data(t), next(NULL) {}
};



PassengerNode*    passengerStack = NULL;   // TOP of passenger stack
FlightNode*       flightStack    = NULL;   // TOP of flight stack
OfficeNode*       officeStack    = NULL;   // TOP of office stack
GlobalTicketNode* ticketStack    = NULL;   // TOP of ticket stack



void printLine() {
    cout << "------------------------------------------" << endl;
}

void cleanupMemory() {
    PassengerNode* pc = passengerStack;
    while (pc) { PassengerNode* t = pc; pc = pc->next; delete t; }

    FlightNode* fc = flightStack;
    while (fc) { FlightNode* t = fc; fc = fc->next; delete t; }

    OfficeNode* oc = officeStack;
    while (oc) { OfficeNode* t = oc; oc = oc->next; delete t; }

    GlobalTicketNode* tc = ticketStack;
    while (tc) { GlobalTicketNode* t = tc; tc = tc->next; delete t; }
}

  // PASSENGER STACK OPERATIONS


void pushPassenger() {
    int id; string name, passport;
    cout << "\n  Enter Passenger ID     : "; cin >> id;
    cin.ignore();
    cout << "  Enter Passenger Name   : "; getline(cin, name);
    cout << "  Enter Passport No      : "; getline(cin, passport);

    PassengerNode* newNode = new PassengerNode(Passenger(id, name, passport));
    newNode->next  = passengerStack;   
    passengerStack = newNode;          
    cout << "\n  >> Passenger pushed to stack!" << endl;
}

void popPassenger() {
    if (passengerStack == NULL) { cout << "\n  >> Stack is EMPTY! Nothing to pop." << endl; return; }
    PassengerNode* temp = passengerStack;
    cout << "\n  >> Popped Passenger (TOP):" << endl;
    temp->data.display();
    passengerStack = passengerStack->next;
    delete temp;
}

void peekPassenger() {
    if (passengerStack == NULL) { cout << "\n  >> Stack is EMPTY!" << endl; return; }
    cout << "\n  >> TOP of Passenger Stack:" << endl;
    passengerStack->data.display();
}

void displayPassengers() {
    if (passengerStack == NULL) { cout << "\n  (Stack is empty)" << endl; return; }
    PassengerNode* curr = passengerStack;
    int count = 1;
    cout << "\n  [Stack — Top to Bottom]" << endl;
    while (curr) {
        cout << "\n  [Position " << count++ << " | ";
        if (count == 2) cout << "TOP]" << endl;
        else            cout << "]"    << endl;
        curr->data.display();
        curr = curr->next;
    }
}

void modifyPassenger() {
    int id; cout << "\n  Enter Passenger ID to modify: "; cin >> id; cin.ignore();
    PassengerNode* curr = passengerStack;
    while (curr) {
        if (curr->data.getID() == id) {
            string name, passport;
            cout << "  Enter new Name        : "; getline(cin, name);
            cout << "  Enter new Passport No : "; getline(cin, passport);
            curr->data.setName(name);
            curr->data.setPassportNo(passport);
            cout << "  >> Passenger modified!" << endl; return;
        }
        curr = curr->next;
    }
    cout << "  >> Passenger not found." << endl;
}

void findPassenger() {
    int id; cout << "\n  Enter Passenger ID to find: "; cin >> id;
    PassengerNode* curr = passengerStack;
    while (curr) {
        if (curr->data.getID() == id) {
            cout << "\n  >> Passenger Found:" << endl;
            curr->data.display(); return;
        }
        curr = curr->next;
    }
    cout << "  >> Passenger not found." << endl;
}

//   FLIGHT STACK OPERATIONS


void pushFlight() {
    int id; string dest, gate, depTime;
    cout << "\n  Enter Flight ID        : "; cin >> id; cin.ignore();
    cout << "  Enter Destination      : "; getline(cin, dest);
    cout << "  Enter Gate             : "; getline(cin, gate);
    cout << "  Enter Departure Time   : "; getline(cin, depTime);

    FlightNode* newNode = new FlightNode(Flight(id, dest, gate, depTime));
    newNode->next = flightStack;
    flightStack   = newNode;
    cout << "\n  >> Flight pushed to stack!" << endl;
}

void popFlight() {
    if (!flightStack) { cout << "\n  >> Stack is EMPTY!" << endl; return; }
    FlightNode* temp = flightStack;
    cout << "\n  >> Popped Flight (TOP):" << endl;
    temp->data.display();
    flightStack = flightStack->next;
    delete temp;
}

void peekFlight() {
    if (!flightStack) { cout << "\n  >> Stack is EMPTY!" << endl; return; }
    cout << "\n  >> TOP of Flight Stack:" << endl;
    flightStack->data.display();
}

void displayFlights() {
    if (!flightStack) { cout << "\n  (Stack is empty)" << endl; return; }
    FlightNode* curr = flightStack;
    int count = 1;
    cout << "\n  [Stack — Top to Bottom]" << endl;
    while (curr) {
        cout << "\n  [Position " << count;
        if (count == 1) cout << " | TOP]" << endl;
        else            cout << "]"        << endl;
        curr->data.display();
        curr = curr->next; count++;
    }
}

void modifyFlight() {
    int id; cout << "\n  Enter Flight ID to modify: "; cin >> id; cin.ignore();
    FlightNode* curr = flightStack;
    while (curr) {
        if (curr->data.getFlightID() == id) {
            string dest, gate, depTime;
            cout << "  Enter new Destination    : "; getline(cin, dest);
            cout << "  Enter new Gate           : "; getline(cin, gate);
            cout << "  Enter new Departure Time : "; getline(cin, depTime);
            curr->data.setDestination(dest);
            curr->data.setGate(gate);
            curr->data.setDepartureTime(depTime);
            cout << "  >> Flight modified!" << endl; return;
        }
        curr = curr->next;
    }
    cout << "  >> Flight not found." << endl;
}

void findFlight() {
    int id; cout << "\n  Enter Flight ID to find: "; cin >> id;
    FlightNode* curr = flightStack;
    while (curr) {
        if (curr->data.getFlightID() == id) {
            cout << "\n  >> Flight Found:" << endl;
            curr->data.display(); return;
        }
        curr = curr->next;
    }
    cout << "  >> Flight not found." << endl;
}

//   OFFICE STACK OPERATIONS

void pushOffice() {
    int id; string name, loc;
    cout << "\n  Enter Office ID        : "; cin >> id; cin.ignore();
    cout << "  Enter Office Name      : "; getline(cin, name);
    cout << "  Enter Location         : "; getline(cin, loc);

    OfficeNode* newNode = new OfficeNode(BookingOffice(id, name, loc));
    newNode->next = officeStack;
    officeStack   = newNode;
    cout << "\n  >> Office pushed to stack!" << endl;
}

void popOffice() {
    if (!officeStack) { cout << "\n  >> Stack is EMPTY!" << endl; return; }
    OfficeNode* temp = officeStack;
    cout << "\n  >> Popped Office (TOP):" << endl;
    temp->data.display();
    officeStack = officeStack->next;
    delete temp;
}

void peekOffice() {
    if (!officeStack) { cout << "\n  >> Stack is EMPTY!" << endl; return; }
    cout << "\n  >> TOP of Office Stack:" << endl;
    officeStack->data.display();
}

void displayOffices() {
    if (!officeStack) { cout << "\n  (Stack is empty)" << endl; return; }
    OfficeNode* curr = officeStack;
    int count = 1;
    cout << "\n  [Stack — Top to Bottom]" << endl;
    while (curr) {
        cout << "\n  [Position " << count;
        if (count == 1) cout << " | TOP]" << endl;
        else            cout << "]"        << endl;
        curr->data.display();
        curr = curr->next; count++;
    }
}

void modifyOffice() {
    int id; cout << "\n  Enter Office ID to modify: "; cin >> id; cin.ignore();
    OfficeNode* curr = officeStack;
    while (curr) {
        if (curr->data.getOfficeID() == id) {
            string name, loc;
            cout << "  Enter new Office Name : "; getline(cin, name);
            cout << "  Enter new Location    : "; getline(cin, loc);
            curr->data.setOfficeName(name);
            curr->data.setLocation(loc);
            cout << "  >> Office modified!" << endl; return;
        }
        curr = curr->next;
    }
    cout << "  >> Office not found." << endl;
}

void findOffice() {
    int id; cout << "\n  Enter Office ID to find: "; cin >> id;
    OfficeNode* curr = officeStack;
    while (curr) {
        if (curr->data.getOfficeID() == id) {
            cout << "\n  >> Office Found:" << endl;
            curr->data.display(); return;
        }
        curr = curr->next;
    }
    cout << "  >> Office not found." << endl;
}

//   TICKET STACK OPERATIONS

void pushTicket() {
    int tno, fno; string pname, oname;
    cout << "\n  Enter Ticket No        : "; cin >> tno; cin.ignore();
    cout << "  Enter Passenger Name   : "; getline(cin, pname);
    cout << "  Enter Flight No        : "; cin >> fno; cin.ignore();
    cout << "  Enter Office Name      : "; getline(cin, oname);

    bool pFound = false;
    PassengerNode* pc = passengerStack;
    while (pc) { if (pc->data.getName() == pname) { pFound = true; break; } pc = pc->next; }
    if (!pFound) cout << "  >> Warning: Passenger '" << pname << "' not found." << endl;

    bool fFound = false;
    FlightNode* fc = flightStack;
    while (fc) { if (fc->data.getFlightID() == fno) { fFound = true; break; } fc = fc->next; }
    if (!fFound) cout << "  >> Warning: Flight ID " << fno << " not found." << endl;

    Ticket t(tno, pname, fno, oname);

    GlobalTicketNode* newNode = new GlobalTicketNode(t);
    newNode->next = ticketStack;
    ticketStack   = newNode;

    FlightNode* curr = flightStack;
    while (curr) {
        if (curr->data.getFlightID() == fno) { curr->data.addTicketToFlight(t); break; }
        curr = curr->next;
    }
    cout << "\n  >> Ticket pushed to stack!" << endl;
}

void popTicket() {
    if (!ticketStack) { cout << "\n  >> Stack is EMPTY!" << endl; return; }
    GlobalTicketNode* temp = ticketStack;
    cout << "\n  >> Popped Ticket (TOP):" << endl;
    temp->data.display();
    ticketStack = ticketStack->next;
    delete temp;
}

void peekTicket() {
    if (!ticketStack) { cout << "\n  >> Stack is EMPTY!" << endl; return; }
    cout << "\n  >> TOP of Ticket Stack:" << endl;
    ticketStack->data.display();
}

void displayTickets() {
    if (!ticketStack) { cout << "\n  (Stack is empty)" << endl; return; }
    GlobalTicketNode* curr = ticketStack;
    int count = 1;
    cout << "\n  [Stack — Top to Bottom]" << endl;
    while (curr) {
        cout << "\n  [Position " << count;
        if (count == 1) cout << " | TOP]" << endl;
        else            cout << "]"        << endl;
        curr->data.display();
        curr = curr->next; count++;
    }
}

void modifyTicket() {
    int tno; cout << "\n  Enter Ticket No to modify: "; cin >> tno; cin.ignore();
    GlobalTicketNode* curr = ticketStack;
    while (curr) {
        if (curr->data.getTicketNo() == tno) {
            string pname, oname; int fno;
            cout << "  Enter new Passenger Name : "; getline(cin, pname);
            cout << "  Enter new Flight No      : "; cin >> fno; cin.ignore();
            cout << "  Enter new Office Name    : "; getline(cin, oname);
            curr->data.setPassengerList(pname);
            curr->data.setFlightNo(fno);
            curr->data.setOfficeName(oname);
            cout << "  >> Ticket modified!" << endl; return;
        }
        curr = curr->next;
    }
    cout << "  >> Ticket not found." << endl;
}

void findTicket() {
    int tno; cout << "\n  Enter Ticket No to find: "; cin >> tno;
    GlobalTicketNode* curr = ticketStack;
    while (curr) {
        if (curr->data.getTicketNo() == tno) {
            cout << "\n  >> Ticket Found:" << endl;
            curr->data.display(); return;
        }
        curr = curr->next;
    }
    cout << "  >> Ticket not found." << endl;
}

//   MENUS

void passengerMenu() {
    int choice;
    do {
        printLine();
        cout << "    PASSENGER STACK MENU" << endl;
        printLine();
        cout << "  1. Display All  (Top→Bottom)" << endl;
        cout << "  2. Push         (Insert)"      << endl;
        cout << "  3. Pop          (Delete Top)"  << endl;
        cout << "  4. Peek         (View Top)"    << endl;
        cout << "  5. Modify"                     << endl;
        cout << "  6. Find"                       << endl;
        cout << "  0. Back"                       << endl;
        printLine();
        cout << "  Enter choice: "; cin >> choice;
        switch (choice) {
            case 1: displayPassengers(); break;
            case 2: pushPassenger();     break;
            case 3: popPassenger();      break;
            case 4: peekPassenger();     break;
            case 5: modifyPassenger();   break;
            case 6: findPassenger();     break;
            case 0: break;
            default: cout << "  >> Invalid option." << endl;
        }
    } while (choice != 0);
}

void flightMenu() {
    int choice;
    do {
        printLine();
        cout << "      FLIGHT STACK MENU" << endl;
        printLine();
        cout << "  1. Display All  (Top→Bottom)" << endl;
        cout << "  2. Push         (Insert)"      << endl;
        cout << "  3. Pop          (Delete Top)"  << endl;
        cout << "  4. Peek         (View Top)"    << endl;
        cout << "  5. Modify"                     << endl;
        cout << "  6. Find"                       << endl;
        cout << "  0. Back"                       << endl;
        printLine();
        cout << "  Enter choice: "; cin >> choice;
        switch (choice) {
            case 1: displayFlights(); break;
            case 2: pushFlight();     break;
            case 3: popFlight();      break;
            case 4: peekFlight();     break;
            case 5: modifyFlight();   break;
            case 6: findFlight();     break;
            case 0: break;
            default: cout << "  >> Invalid option." << endl;
        }
    } while (choice != 0);
}

void officeMenu() {
    int choice;
    do {
        printLine();
        cout << "   BOOKING OFFICE STACK MENU" << endl;
        printLine();
        cout << "  1. Display All  (Top→Bottom)" << endl;
        cout << "  2. Push         (Insert)"      << endl;
        cout << "  3. Pop          (Delete Top)"  << endl;
        cout << "  4. Peek         (View Top)"    << endl;
        cout << "  5. Modify"                     << endl;
        cout << "  6. Find"                       << endl;
        cout << "  0. Back"                       << endl;
        printLine();
        cout << "  Enter choice: "; cin >> choice;
        switch (choice) {
            case 1: displayOffices(); break;
            case 2: pushOffice();     break;
            case 3: popOffice();      break;
            case 4: peekOffice();     break;
            case 5: modifyOffice();   break;
            case 6: findOffice();     break;
            case 0: break;
            default: cout << "  >> Invalid option." << endl;
        }
    } while (choice != 0);
}

void ticketMenu() {
    int choice;
    do {
        printLine();
        cout << "      TICKET STACK MENU" << endl;
        printLine();
        cout << "  1. Display All  (Top→Bottom)" << endl;
        cout << "  2. Push         (Issue Ticket)" << endl;
        cout << "  3. Pop          (Delete Top)"   << endl;
        cout << "  4. Peek         (View Top)"     << endl;
        cout << "  5. Modify"                      << endl;
        cout << "  6. Find"                        << endl;
        cout << "  0. Back"                        << endl;
        printLine();
        cout << "  Enter choice: "; cin >> choice;
        switch (choice) {
            case 1: displayTickets(); break;
            case 2: pushTicket();     break;
            case 3: popTicket();      break;
            case 4: peekTicket();     break;
            case 5: modifyTicket();   break;
            case 6: findTicket();     break;
            case 0: break;
            default: cout << "  >> Invalid option." << endl;
        }
    } while (choice != 0);
}

//   MAIN

int main() {
    int choice;
    cout << endl;
    printLine();
    cout << "  AIRLINE MANAGEMENT SYSTEM  [STACK MODE]" << endl;
    printLine();

    do {
        cout << "\n        MAIN MENU" << endl;
        printLine();
        cout << "  1. Flights"         << endl;
        cout << "  2. Booking Offices" << endl;
        cout << "  3. Passengers"      << endl;
        cout << "  4. Tickets"         << endl;
        cout << "  0. Exit"            << endl;
        printLine();
        cout << "  Enter choice: "; cin >> choice;
        switch (choice) {
            case 1: flightMenu();    break;
            case 2: officeMenu();    break;
            case 3: passengerMenu(); break;
            case 4: ticketMenu();    break;
            case 0:
                cleanupMemory();
                cout << "\n  Goodbye!" << endl;
                printLine();
                break;
            default: cout << "  >> Invalid option." << endl;
        }
    } while (choice != 0);

    return 0;
}