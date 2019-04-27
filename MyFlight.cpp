#include <sstream>
#include <cstdlib>
#include "interface.h"
//Class  flights.
class MyFlight : public Flight {
protected:
    int planeModel;
    list<Reservation *> reservations;
    list<Employee*> employees;
    Date date;
    string source;
    string destination;
    string id;
public:
    //constructor.
    MyFlight(int model, list<Reservation *> reservations, list<Employee *> employees, Date date,
             string source, string destination) : planeModel(model), reservations(reservations), employees(employees),
             date(date), source(source), destination(destination) {
        this->id = generateID();
    }
    MyFlight(string id,int model, string source, string destination ,Date date,list<Employee *> employees) : id(id),date(date),planeModel(model),
    source(source), destination(destination),employees(employees) {
    }

    // Get flight plane planeModel.
    virtual int getModelNumber() {
        return this->planeModel;
    }

    // Get list of reservations for flight.
    virtual list<Reservation *> getReservations() {
        return this->reservations;
    }

    // Get list of employeesList of flight.
    virtual list<Employee *> getAssignedCrew() {
    	return employees;
    }


    // Return date of flight.
    virtual Date getDate() {
        return this->date;
    }

    // Return source of flight.
    virtual string getSource() {
        return this->source;
    }

    // Return destination of flight.
    virtual string getDestination() {
        return this->destination;
    }



    // Return id of flight.
    virtual string getID() {
        return this->id;
    }
    void bookReservation(Reservation* res) {
        this->reservations.push_back(res);
    }

    // Returns random ID.
    string generateID() {
        // Random using rand function.
        int randID = rand() % 10000000 + 1;
        // Convert to string.
        ostringstream str1;
        str1 << randID;
        string readyID = str1.str();
        return readyID;
    }
    string getEmployeeIds(){
        list<Employee*>::iterator iterator2;
        string s;
        for (iterator2= employees.begin();iterator2!=employees.end();iterator2++){
            s= s + " "+(*iterator2)->getID();
        }
        return s;
    }

};
