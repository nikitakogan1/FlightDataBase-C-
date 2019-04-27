////
//// Created by nikita on 11/26/18.
////

#include <iostream>
#include "interface.h"
#define YEAR_POS 0
#define FOUR 4
#define MONTH_POS 5
#define TWO 2
#define DAY_POS 8
#define YEAR stoi(this->date.substr(YEAR_POS,FOUR))
#define MONTH stoi(this->date.substr(MONTH_POS,TWO))
#define DAY stoi(this->date.substr(DAY_POS,TWO))


Date::Date(string date) : date("1111-11-11"){ // format: YYYY-MM-DD
    if((YEAR <= 0) || (YEAR > 9999)){
        throw "invalid year";
    }
    if((MONTH <= 0) || (MONTH > 12)){
        throw "invalid month";
    }
    if((DAY <= 0) || (DAY > 31)){
        throw "invalid day";
    }
    this->date = date;
}

bool Date::operator<(const Date& d) const {
    int thisYear = stoi(this->date.substr(YEAR_POS, FOUR));
    int otherYear = stoi(d.date.substr(YEAR_POS, FOUR));
    int thisMonth = stoi(this->date.substr(MONTH_POS, TWO));
    int otherMonth = stoi(d.date.substr(MONTH_POS, TWO));
    int thisDay = stoi(this->date.substr(DAY_POS, TWO));
    int otherDay = stoi(d.date.substr(DAY_POS, TWO));
    if (thisYear != otherYear)
        return thisYear > otherYear;
    if (thisMonth != otherMonth)
        return thisMonth > otherMonth;
    if (thisDay != otherDay)
        return thisDay > otherDay;
    // the dates are equals
    return false;
}

bool Date::operator>(const Date& d) const{
    int thisYear = stoi(this->date.substr(YEAR_POS,FOUR));
    int otherYear = stoi(d.date.substr(YEAR_POS,FOUR));
    int thisMonth = stoi(this->date.substr(MONTH_POS,TWO));
    int otherMonth = stoi(d.date.substr(MONTH_POS,TWO));
    int thisDay = stoi(this->date.substr(DAY_POS,TWO));
    int otherDay = stoi(d.date.substr(DAY_POS,TWO));
    if(thisYear != otherYear)
        return thisYear < otherYear;
    if(thisMonth != otherMonth)
        return thisMonth < otherMonth;
    if(thisDay != otherDay)
        return thisDay < otherDay;
    // the dates are equals
    return false;

}
bool Date::operator==(const Date& d) const {
    return date == d.date;
}
