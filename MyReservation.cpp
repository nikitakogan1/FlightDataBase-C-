#include <sstream>
#include <cstdlib>
#include "interface.h"


class MyReservation : public Reservation {
protected:
    Customer* customer;
    Flight* flight;
    Classes classType;
    int bag;
    string id;
public:
    // Create a reservation.
    MyReservation(Customer *buyer, Flight *fly, Classes seat, int bag) : customer(buyer), flight(fly), classType(seat), bag(bag) {
        this->id = generateID();
    }

    // Get the customer that made the reservation.
    Customer* getCustomer() {
        return this->customer;
    }

    // Get flight the reservation was made on.
    Flight* getFlight() {
        return this->flight;
    }
    // Return the class of the classType.
    Classes getClass() {
        return this->classType;
    }
    // Get max baggage.
    virtual int getMaxBaggage() {
        return this->bag;
    }
    // Get the ID.
    string getID() {
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
    // Default destructor.
    virtual ~MyReservation(){
    }
};