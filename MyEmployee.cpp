//
// Created by nikita on 11/26/18.
//


#include <sstream>
#include "interface.h"

class MyEmployee : public Employee {
protected:
    int seniority;
    int birth_year;
    Employee * boss;
    Jobs job;
    string id;
    map<Date, int> booking;

public:
    MyEmployee(int seniority, int birth_year, Employee *boss, Jobs job) : seniority(seniority),
    birth_year(birth_year), boss(boss),job(job) {
        //use function to generate id.
        this->id = generateID();
    }
    MyEmployee(string eID,int seniority, int birth_year,Jobs job, int bossID) : id(eID),seniority(seniority)
    ,birth_year(birth_year),job(job), boss(boss) {
        if (boss == 0){
            this->boss = NULL;
        }
    }
    string generateID() {
        // Random using rand function.
        int randID = rand() % 10000000 + 1;
        // Convert to string.
        ostringstream str1;
        str1 << randID;
        string readyID = str1.str();
        return readyID;
    }
    //virtual for horasha.
    // Get seniority.
    virtual int getSeniority() {
        return this->seniority;
    };
    // Get birth year.
    virtual int getBirthYear() {
        return this->birth_year;
    }
    // Get employer.
    virtual Employee* getEmployer() {
        return this->boss;
    }
    // Gets job.(from enum types).
    virtual Jobs getTitle() {
        return this->job;
    }
    // Get the ID.
    virtual string getID() {
        return this->id;
    }
    //empty distractor.
    virtual ~MyEmployee(){
    }
    // Book employee at certain date.
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

    virtual map<Date, int> getCrewMap()
	{
    	return booking;
	}
};


