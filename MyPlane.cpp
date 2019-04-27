//
// Created by nikita on 11/26/18.
//

#include <sstream>
#include <cstdlib>
#include "interface.h"

// My plane class used to create planes.
class MyPlane: public Plane {
protected:
    int modelNumer; //plane planeModel number.
    map<Jobs,int>  crew;
    int firstClass;
    int economyCLass;
    string id;
    map<Date, int> booking;
    int firstClassCounter = 0;
    int secondClassCounter = 0;

public:
    // Constructor.
    MyPlane(int modelNumer, map<Jobs, int> crew, int firstClass, int economyCLass) : modelNumer(modelNumer),
    crew(crew), firstClass(firstClass), economyCLass(economyCLass) {
        this->id = generateID();
    }
    //extra constructor. carefull with the crew.
    MyPlane(string id,int modelNumer, int firstClass, int economyCLass) :
    id(id),modelNumer(modelNumer), firstClass(firstClass), economyCLass(economyCLass) {}

    void bookMe(Date date) {
        booking.insert (pair<Date ,int>(date,1));
    }
    // Return true if employee as isBooked at that date, false otherwise.
    bool isBooked(Date date) {
        map<Date, int>::iterator it;
        for (it = booking.begin(); it != booking.end(); it++ ) {
            if (it->first == date && it->second == 1) {
                return true;
            }
        }
        return false;
    }
    // Get the plane planeModel number;
    virtual int getModelNumber() {
        return this->modelNumer;
    }
    // Get all neseccary crew.
    virtual map<Jobs, int> getCrewNeeded() {
        return this->crew;
    }
    // Get max first class seats.
    virtual int getMaxFirstClass() {
        return this->firstClass;
    }
    // Get max economy class seats.
    virtual int getMaxEconomyClass() {
        return this->economyCLass;
    }
    // Get plane ID.
    string getID() {
        return this->id;
    }
    virtual bool firstClassCheck(){
        return firstClassCounter<firstClass;
    }
    virtual bool economyClassCheck(){
        return secondClassCounter<economyCLass;
    }
    virtual void raiseFirstClass(){
        firstClassCounter++;
    }
    virtual void raiseEconomyClass(){
        secondClassCounter++;
    }
    virtual map<Date, int> getBookingMap(){
        return booking;
    }
    string getCrewString(){
        map<Jobs, int>::iterator iterator1; //iterator for counting the crew members needed.
        int crewCounter[5] = {0};
        for (iterator1 = crew.begin();iterator1 != crew.end();iterator1++){
            if((*iterator1).first == MANAGER) {
                crewCounter[0] = (*iterator1).second ;
                continue;
            }
            if((*iterator1).first == NAVIGATOR) {
                crewCounter[1] = (*iterator1).second;
                continue;
            }
            if((*iterator1).first == FLY_ATTENDANT) {
                crewCounter[2] = (*iterator1).second ;
                continue;
            }
            if((*iterator1).first == PILOT) {
                crewCounter[3] = (*iterator1).second ;
                continue;
            }
            if((*iterator1).first == OTHER) {
                crewCounter[4]  = (*iterator1).second ;
                continue;
            }
        }

        string str = "Manager:"+to_string(crewCounter[0]) + " " "Navigator:"+to_string(crewCounter[1]) + " "
        "FLYATTENDANT:"+to_string(crewCounter[2]) + " "+
         " "+"PILOT:"+to_string(crewCounter[3]) + " " "OTHER:"+to_string(crewCounter[4]);
        return str;
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
    // empty destructor.
    virtual ~MyPlane(){
    }
    //new methods

};