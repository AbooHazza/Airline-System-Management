#include <iostream>
#include <string>
using namespace std;
 
class Person {
protected:
	int ID;
	string Name;
 
public:
	Person() {
		ID = 0;
		Name = "";
	}
 
	int getID() { return ID; }
	string getName() { return Name; }
	void setID(int id) { ID = id; }
	void setName(string n) { Name = n; }
};
 
class Passenger : public Person {
 
private:
	string PassportNo;
 
public:
	Passenger* next;
 
	Passenger() {
		PassportNo = "";
		next = NULL;
	}
 
	Passenger(int id, string name, string passport) {
		ID = id;
		Name = name;
		PassportNo = passport;
		next = NULL;
	}
 
	string getPassportNo() { return PassportNo; }
	void setPassportNo(string p) { PassportNo = p; }
 
	void display() {
		cout << "ID: " << ID << endl;
		cout << "Name: " << Name << endl;
		cout << "Passport: " << PassportNo << endl;
	}
};
 
class BookingOffice {
 
public:
	int OfficeID;
	string OfficeName;
	string Location;
	BookingOffice* next;
 
	BookingOffice() {
		OfficeID = 0;
		OfficeName = "";
		Location = "";
		next = NULL;
	}
 
	BookingOffice(int id, string name, string loc) {
		OfficeID = id;
		OfficeName = name;
		Location = loc;
		next = NULL;
	}
 
	void display() {
		cout << "Office ID: " << OfficeID << endl;
		cout << "Office Name: " << OfficeName << endl;
		cout << "Location: " << Location << endl;
	}
};
 
class Flight {
 
public:
	int FlightID;
	string Destination;
	string Gate;
	string DepartureTime;
	Flight* next;
 
	Flight() {
		FlightID = 0;
		next = NULL;
	}
 
	Flight(int id, string des, string g, string dep) {
		FlightID = id;
		Destination = des;
		Gate = g;
		DepartureTime = dep;
		next = NULL;
	}
 
	void display() {
		cout << "Flight ID: " << FlightID << endl;
		cout << "Destination: " << Destination << endl;
		cout << "Gate: " << Gate << endl;
		cout << "Departure Time: " << DepartureTime << endl;
	}
};
 
class Ticket {
 
public:
	int TicketNo;
	string PassengerName;
	int FlightNo;
	string OfficeName;
	Ticket* next;
 
	Ticket() {
		TicketNo = 0;
		FlightNo = 0;
		next = NULL;
	}
 
	Ticket(int t, string p, int f, string o) {
		TicketNo = t;
		PassengerName = p;
		FlightNo = f;
		OfficeName = o;
		next = NULL;
	}
 
	void display() {
		cout << "Ticket No: " << TicketNo << endl;
		cout << "Passenger: " << PassengerName << endl;
		cout << "Flight No: " << FlightNo << endl;
		cout << "Office: " << OfficeName << endl;
	}
};
 
 
Passenger* pFront = NULL;
Passenger* pRear = NULL;
 
void addPassenger() {
	int id;
	string name, passport;
	cout << "Enter ID: ";
	cin >> id;
	cin.ignore();
	cout << "Enter Name: ";
	getline(cin, name);
	cout << "Enter Passport: ";
	getline(cin, passport);
	Passenger* newNode = new Passenger(id, name, passport);
	if (pFront == NULL) {
		pFront = pRear = newNode;
	} else {
		pRear->next = newNode;
		pRear = newNode;
	}
	cout << "Passenger Added\n";
}
 
void deletePassenger() {
	int id;
	cout << "Enter ID to delete: ";
	cin >> id;
	Passenger* curr = pFront;
	Passenger* prev = NULL;
	while (curr != NULL) {
		if (curr->getID() == id) {
			if (prev == NULL) pFront = curr->next;
			else prev->next = curr->next;
			if (curr == pRear) pRear = prev;
			delete curr;
			cout << "Passenger Deleted\n";
			return;
		}
		prev = curr;
		curr = curr->next;
	}
	cout << "Not Found\n";
}
 
void findPassenger() {
	int id;
	cout << "Enter ID to find: ";
	cin >> id;
	Passenger* curr = pFront;
	while (curr != NULL) {
		if (curr->getID() == id) {
			curr->display();
			return;
		}
		curr = curr->next;
	}
	cout << "Not Found\n";
}
 
void modifyPassenger() {
	int id;
	cout << "Enter ID to modify: ";
	cin >> id;
	cin.ignore();
	Passenger* curr = pFront;
	while (curr != NULL) {
		if (curr->getID() == id) {
			string name, passport;
			cout << "New Name: ";
			getline(cin, name);
			cout << "New Passport: ";
			getline(cin, passport);
			curr->setName(name);
			curr->setPassportNo(passport);
			cout << "Passenger Modified\n";
			return;
		}
		curr = curr->next;
	}
	cout << "Not Found\n";
}
 
void displayPassengers() {
	if (pFront == NULL) {
		cout << "No Passengers\n";
		return;
	}
	Passenger* curr = pFront;
	while (curr != NULL) {
		curr->display();
		cout << "---\n";
		curr = curr->next;
	}
}
 
 
BookingOffice* oFront = NULL;
BookingOffice* oRear = NULL;
 
void addOffice() {
	int id;
	string name, loc;
	cout << "Enter Office ID: ";
	cin >> id;
	cin.ignore();
	cout << "Enter Office Name: ";
	getline(cin, name);
	cout << "Enter Location: ";
	getline(cin, loc);
	BookingOffice* newNode = new BookingOffice(id, name, loc);
	if (oFront == NULL) {
		oFront = oRear = newNode;
	} else {
		oRear->next = newNode;
		oRear = newNode;
	}
	cout << "Office Added\n";
}
 
void deleteOffice() {
	int id;
	cout << "Enter Office ID to delete: ";
	cin >> id;
	BookingOffice* curr = oFront;
	BookingOffice* prev = NULL;
	while (curr != NULL) {
		if (curr->OfficeID == id) {
			if (prev == NULL) oFront = curr->next;
			else prev->next = curr->next;
			if (curr == oRear) oRear = prev;
			delete curr;
			cout << "Office Deleted\n";
			return;
		}
		prev = curr;
		curr = curr->next;
	}
	cout << "Not Found\n";
}
 
void findOffice() {
	int id;
	cout << "Enter Office ID to find: ";
	cin >> id;
	BookingOffice* curr = oFront;
	while (curr != NULL) {
		if (curr->OfficeID == id) {
			curr->display();
			return;
		}
		curr = curr->next;
	}
	cout << "Not Found\n";
}
 
void modifyOffice() {
	int id;
	cout << "Enter Office ID to modify: ";
	cin >> id;
	cin.ignore();
	BookingOffice* curr = oFront;
	while (curr != NULL) {
		if (curr->OfficeID == id) {
			cout << "New Name: ";
			getline(cin, curr->OfficeName);
			cout << "New Location: ";
			getline(cin, curr->Location);
			cout << "Office Modified\n";
			return;
		}
		curr = curr->next;
	}
	cout << "Not Found\n";
}
 
void displayOffices() {
	if (oFront == NULL) {
		cout << "No Offices\n";
		return;
	}
	BookingOffice* curr = oFront;
	while (curr != NULL) {
		curr->display();
		cout << "---\n";
		curr = curr->next;
	}
}
 
 
Flight* fFront = NULL;
Flight* fRear = NULL;
 
void addFlight() {
	int id;
	string des, gate, dep;
	cout << "Enter Flight ID: ";
	cin >> id;
	cin.ignore();
	cout << "Enter Destination: ";
	getline(cin, des);
	cout << "Enter Gate: ";
	getline(cin, gate);
	cout << "Enter Departure Time: ";
	getline(cin, dep);
	Flight* newNode = new Flight(id, des, gate, dep);
	if (fFront == NULL) {
		fFront = fRear = newNode;
	} else {
		fRear->next = newNode;
		fRear = newNode;
	}
	cout << "Flight Added\n";
}
 
void deleteFlight() {
	int id;
	cout << "Enter Flight ID to delete: ";
	cin >> id;
	Flight* curr = fFront;
	Flight* prev = NULL;
	while (curr != NULL) {
		if (curr->FlightID == id) {
			if (prev == NULL) fFront = curr->next;
			else prev->next = curr->next;
			if (curr == fRear) fRear = prev;
			delete curr;
			cout << "Flight Deleted\n";
			return;
		}
		prev = curr;
		curr = curr->next;
	}
	cout << "Not Found\n";
}
 
void findFlight() {
	int id;
	cout << "Enter Flight ID to find: ";
	cin >> id;
	Flight* curr = fFront;
	while (curr != NULL) {
		if (curr->FlightID == id) {
			curr->display();
			return;
		}
		curr = curr->next;
	}
	cout << "Not Found\n";
}
 
void modifyFlight() {
	int id;
	cout << "Enter Flight ID to modify: ";
	cin >> id;
	cin.ignore();
	Flight* curr = fFront;
	while (curr != NULL) {
		if (curr->FlightID == id) {
			cout << "New Destination: ";
			getline(cin, curr->Destination);
			cout << "New Gate: ";
			getline(cin, curr->Gate);
			cout << "New Departure Time: ";
			getline(cin, curr->DepartureTime);
			cout << "Flight Modified\n";
			return;
		}
		curr = curr->next;
	}
	cout << "Not Found\n";
}
 
void displayFlights() {
	if (fFront == NULL) {
		cout << "No Flights\n";
		return;
	}
	Flight* curr = fFront;
	while (curr != NULL) {
		curr->display();
		cout << "---\n";
		curr = curr->next;
	}
}
 
 
Ticket* tFront = NULL;
Ticket* tRear = NULL;
 
void addTicket() {
	int tno, fno;
	string pname, oname;
	cout << "Enter Ticket No: ";
	cin >> tno;
	cin.ignore();
	cout << "Enter Passenger Name: ";
	getline(cin, pname);
	cout << "Enter Flight No: ";
	cin >> fno;
	cin.ignore();
	cout << "Enter Office Name: ";
	getline(cin, oname);
	Ticket* newNode = new Ticket(tno, pname, fno, oname);
	if (tFront == NULL) {
		tFront = tRear = newNode;
	} else {
		tRear->next = newNode;
		tRear = newNode;
	}
	cout << "Ticket Added\n";
}
 
void deleteTicket() {
	int tno;
	cout << "Enter Ticket No to delete: ";
	cin >> tno;
	Ticket* curr = tFront;
	Ticket* prev = NULL;
	while (curr != NULL) {
		if (curr->TicketNo == tno) {
			if (prev == NULL) tFront = curr->next;
			else prev->next = curr->next;
			if (curr == tRear) tRear = prev;
			delete curr;
			cout << "Ticket Deleted\n";
			return;
		}
		prev = curr;
		curr = curr->next;
	}
	cout << "Not Found\n";
}
 
void findTicket() {
	int tno;
	cout << "Enter Ticket No to find: ";
	cin >> tno;
	Ticket* curr = tFront;
	while (curr != NULL) {
		if (curr->TicketNo == tno) {
			curr->display();
			return;
		}
		curr = curr->next;
	}
	cout << "Not Found\n";
}
 
void modifyTicket() {
	int tno;
	cout << "Enter Ticket No to modify: ";
	cin >> tno;
	cin.ignore();
	Ticket* curr = tFront;
	while (curr != NULL) {
		if (curr->TicketNo == tno) {
			cout << "New Passenger Name: ";
			getline(cin, curr->PassengerName);
			     cout << "New Flight No: ";
			  cin >> curr->FlightNo;
			  cin.ignore();
			     cout << "New Office Name: ";
			getline(cin, curr->OfficeName);
			     cout << "Ticket Modified\n";
			return;
		}
		curr = curr->next;
	}
	cout << "Not Found\n";
}
 
void displayTickets() {
	if (tFront == NULL) {
		cout << "No Tickets\n";
		return;
	}
	Ticket* curr = tFront;
	while (curr != NULL) {
		curr->display();
		cout << "---\n";
		curr = curr->next;
	}
}
 
 
int main() {
 
	int choice;
 
	do {
		        cout << "\n...| Airline Management System |...\n";
		        cout << "1. Passengers\n";
		        cout << "2. Booking Offices\n";
		        cout << "3. Flights\n";
		        cout << "4. Tickets\n";
		        cout << "0. Exit\n";
		        cout << "Enter choice: ";
		       cin >> choice;
 
		if (choice == 1) {
			int ch;
			do {
				     cout << "\n-- Passenger Menu --\n";
				    cout << "1. Display\n2. Insert\n3. Delete\n4. Modify\n5. Find\n0. Back\n";
				    cout << "Enter choice: ";
				cin >> ch;
				         if (ch == 1) displayPassengers();
				          else if (ch == 2) addPassenger();
				            else if (ch == 3) deletePassenger();
				         else if (ch == 4) modifyPassenger();
				              else if (ch == 5) findPassenger();
			} while (ch != 0);
		}
 
		else if (choice == 2) {
			int ch;
			do {
				cout << "\n-- Office Menu --\n";
				cout << "1. Display\n2. Insert\n3. Delete\n4. Modify\n5. Find\n0. Back\n";
				cout << "Enter choice: ";
				cin >> ch;
				if (ch == 1) displayOffices();
				else if (ch == 2) addOffice();
				else if (ch == 3) deleteOffice();
				else if (ch == 4) modifyOffice();
				else if (ch == 5) findOffice();
			} while (ch != 0);
		}
 
		else if (choice == 3) {
			int ch;
			do {
				cout << "\n-- Flight Menu --\n";
				cout << "1. Display\n2. Insert\n3. Delete\n4. Modify\n5. Find\n0. Back\n";
				cout << "Enter choice: ";
				cin >> ch;
				if (ch == 1) displayFlights();
				else if (ch == 2) addFlight();
				else if (ch == 3) deleteFlight();
				else if (ch == 4) modifyFlight();
				else if (ch == 5) findFlight();
			} while (ch != 0);
		}
 
		else if (choice == 4) {
			int ch;
			do {
				cout << "\n-- Ticket Menu --\n";
				cout << "1. Display\n2. Insert\n3. Delete\n4. Modify\n5. Find\n0. Back\n";
				cout << "Enter choice: ";
				cin >> ch;
				if (ch == 1) displayTickets();
				else if (ch == 2) addTicket();
				else if (ch == 3) deleteTicket();
				else if (ch == 4) modifyTicket();
				else if (ch == 5) findTicket();
			} while (ch != 0);
		}
 
	} while (choice != 0);
 
	return 0;
}