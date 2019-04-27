//
// Created by nikita on 11/26/18.
//

#include <sstream>
#include <cstdlib>
#include "interface.h"
class MyCustomer : public Customer {
    string name;
    int rank;
    list<Reservation*> reservations;
    string id;
public:
    MyCustomer(int pr,string name, list<Reservation*> reservations) : rank(pr), name(name), reservations(reservations){
        this->id = generateID();
    }
    MyCustomer(string id,string name, int pr) : rank(pr), name(name), id(id){
    }
    MyCustomer(Customer* p) {
        this->rank = p->getPriority();
        this->name = p->getFullName();
        this->reservations = p->getReservations();
        this->id = p->getID();
    }
    // Get name of customer.
    virtual string getFullName(){
        return this->name;
    }
    // Get priority of passanger.
    virtual int getPriority() {
        return rank;
    }
    // Get all the customers reservations.
    virtual list<Reservation*> getReservations() {
        return reservations;
    }
    // Get the ID.
    virtual string getID() {
        return this->id;
    }
    // Create the the ID as a random integer string.
    string generateID() {
        // Random using rand function.
        int randID = rand() % 10000000 + 1;
        // Convert to string.
        ostringstream str1;
        str1 << randID;
        string readyID = str1.str();
        return readyID;
    }
    // Adds a reservation to this customer.
    void bookReservation(Reservation* res) {
        this->reservations.push_back(res);
    }
    // Default destructor.
    virtual ~MyCustomer() {
    }
};