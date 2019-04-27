//
// Created by Nikita on 26/11/2018.
//ID 320767643 Advanced Programing.
//

#ifndef EX2_MYIMPLEMENTATION_H
#define EX2_MYIMPLEMENTATION_H

#include "interface.h"
#include <iostream>
#include <fstream>
#include "MyEmployee.cpp"
#include "MyPlane.cpp"
#include "MyCostumer.cpp"
#include "MyFlight.cpp"
#include "MyReservation.cpp"
#include "vector"
//#include "MyDate.cpp"
using namespace std;

struct Booking
{
	string emp;
	string d;
};

class MyImplementation : public Ex2 {
    list<MyEmployee*> employeesList;
    list<MyCustomer*> customers;
    list<MyPlane*> planes;
    list<MyFlight*> flights;
    list<MyReservation*> reservations;
    list<Booking*> bookings;
public:
    MyImplementation(){
        loadEmployees();
        loadPlanes();
        loadCustomers();
        loadFlights();
        loadReservations();
    }
    // i add the employee with boss or without boss.
    virtual Employee* addEmployee(int seniority, int birth_year, string employer_id, Jobs title){
        list<MyEmployee*> :: iterator it; //extract iterator.
        for (it = employeesList.begin(); it != employeesList.end(); ++it) { //check if there is a boss.
            if ((*it)->getID() == employer_id) {
                MyEmployee *e = new MyEmployee(seniority, birth_year, *it, title);
                employeesList.push_back(e);
                updateEmployeesTable();
                return e;
            }
        }
        // if there is no boss.
        MyEmployee* e = new MyEmployee(seniority, birth_year, NULL, title);
        employeesList.push_back(e);
        updateEmployeesTable();
        return e;
    }
//get employee by ID.
    Employee *getEmployee(string id) {
        //look for the employee using the iterator.
        list<MyEmployee*> :: iterator it;
        for (it = employeesList.begin(); it != employeesList.end(); ++it) {
            if ((*it)->getID() == id) {
                return (*it);
            }
        }
        //if employee does not exist we threw an error.

            throw("No employee with given id!");

        //run time error.
    }
    //--------------------------------------------------------------------------------------------//
    //add plane and get plane
    Plane *getPlane(string id){
        list<MyPlane*> :: iterator it;
        for (it = planes.begin(); it != planes.end(); ++it) {
            if ((*it)->getID() == id) {
                return (*it);
            }
        }
//        try {
            throw ("No such plane found !");
//        }
//        catch(runtime_error& e) {
//            cout << e.what() << endl;
//            exit();
//            ::exit(0);
//        }
    }
    Plane *addPlane(int model_number, map<Jobs, int> crew_needed,map<Classes, int> max_passangers) {
        MyPlane* p = new MyPlane(model_number, crew_needed,
                max_passangers.at(FIRST_CLASS), max_passangers.at(SECOND_CLASS));
        planes.push_back(p);
        updatePlanesTable();
        return p;
    }
    //--------------------------------------------------------------------------------------------------------------//
//add and get custumer.
    Customer *addCustomer(string full_name,int priority) {
        if (priority < 1 || priority > 5){
            throw "priority not valid";
        }
        // Create new list for a new customer.
        list<Reservation*> newList;
        // Add the customer to the customer list.
        MyCustomer* a = new MyCustomer(priority,full_name, newList);
        customers.push_back(a);
        updateCustomersTable();
        return a;
    }
    Customer *getCustomer(string id) {
        list<MyCustomer*> :: iterator it;
        for (it = customers.begin(); it != customers.end(); ++it) {
            if ((*it)->getID() == id) {
                return (*it);
            }
        }
        // Throw a runtime error and exit when trying to get a customer that doesn't exist.

            throw("No such customer");
    }
    //---------------------------------------------------------------------------------------------//
    //create flights and get flights.
    virtual Flight *addFlight(int model_number, Date date, string source, string destination){
        MyPlane* plane; //out future plane.
        int flag = 0; //to dicide if we have all the crew.
        //if there are no employess or no planes.
        if (employeesList.empty()) {
//            try {
                throw ("Exception: No employeesList exist, flight cannot be isBooked.");
//            }
//            catch(runtime_error& e) {
//                cout << e.what() << endl;
//                exit();
//                ::exit(0);
//            }
        }
        if (planes.empty()) {
//            try {
                throw ("Exception: No planes exist, flight cannot be isBooked.");
//            }
//            catch(runtime_error& e) {
//                cout << e.what() << endl;
//                exit();
//                ::exit(0);
//            }
        }
        list<MyPlane*> :: iterator it; //extract the list of planes iterator.
        for (it = planes.begin(); it != planes.end();++it){
            MyPlane* a = (*it);
            if (a->getModelNumber() == model_number && !(a->isBooked(date))) {
                flag = 1;
                plane = *it;
                plane->bookMe(date);
                break;
            }
        }

        if (flag == 0){
//            try {
                throw ("No plane model available, flight cannot be booked.");
//         }
//            catch(runtime_error& e) {
//                cout << e.what() << endl;
//                exit();
//                ::exit(0);
//            }
        }
        list<Reservation*> reservations; //list of reservations for the new flight.
        list<Employee*> employees; //list of employeesList for the new flight.
        map<Jobs, int>::iterator iterator1; //iterator for counting the crew members needed.
        map<Jobs, int> temp = plane->getCrewNeeded();
        int crewCounter[5] = {0}; //in each cell count the number of each job.
        for ( iterator1 = temp.begin(); iterator1 != temp.end(); iterator1++ ) {
            //loop threw the crew needed and count.
            // if we find we continue.
            if((*iterator1).first == MANAGER) {
                crewCounter[0] = (*iterator1).second ;
                continue;
            }
            if((*iterator1).first == NAVIGATOR) {
                crewCounter[1] = (*iterator1).second ;
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
                crewCounter[4] = (*iterator1).second ;
                continue;
            }
        }
        list<MyEmployee*>::iterator iterator2;
        // 0- manager 1- navigator 2-fly attendant 3-pilot 4-other.
        for ( iterator2 = employeesList.begin(); iterator2 != employeesList.end(); iterator2++){
            // if we need a manager, we book him if he is available.
            if ((*iterator2)->getTitle() == MANAGER && crewCounter[0] > 0 && !(*iterator2)->isBooked(date)) {
                (*iterator2)->bookMe(date);
                Booking* b = new Booking();
                b->emp = (*iterator2)->getID();
                b->d = date.getDate();
                bookings.push_back(b);
                crewCounter[0] --;
                employees.push_back((*iterator2));
            }
            // if we need a navigator, we book him if he is available.
            if ((*iterator2)->getTitle() == NAVIGATOR && crewCounter[1] > 0 && !(*iterator2)->isBooked(date)) {
                (*iterator2)->bookMe(date);
                Booking* b = new Booking();
                b->emp = (*iterator2)->getID();
                b->d = date.getDate();
                bookings.push_back(b);
                crewCounter[1] --;
                employees.push_back((*iterator2));
            }
            // if we need a fly attendant, we book him if he is available.
            if ((*iterator2)->getTitle() == FLY_ATTENDANT && crewCounter[2] > 0 && !(*iterator2)->isBooked(date)) {
                (*iterator2)->bookMe(date);
                Booking* b = new Booking();
                b->emp = (*iterator2)->getID();
                b->d = date.getDate();
                bookings.push_back(b);
                crewCounter[2] --;
                employees.push_back((*iterator2));
            }
            // if we need a pilot, we book him if he is available.
            if ((*iterator2)->getTitle() == PILOT && crewCounter[3] > 0 && !(*iterator2)->isBooked(date)) {
                (*iterator2)->bookMe(date);
                Booking* b = new Booking();
                b->emp = (*iterator2)->getID();
                b->d = date.getDate();
                bookings.push_back(b);
                crewCounter[3] --;
                employees.push_back((*iterator2));
            }
            //if we need "other".
            if ((*iterator2)->getTitle() == OTHER && crewCounter[4] > 0 && !(*iterator2)->isBooked(date)) {
                (*iterator2)->bookMe(date);
                Booking* b = new Booking();
                b->emp = (*iterator2)->getID();
                b->d = date.getDate();
                bookings.push_back(b);
                crewCounter[4] --;
                employees.push_back((*iterator2));
            }
        }
            //if we dont have enought crew members, we threw an exception.
        if (crewCounter[0] > 0 || crewCounter[1] > 0 ||
        crewCounter [2] > 0 || crewCounter [3] > 0 || crewCounter[4] > 0) {
//            try {
                throw ("Not enough employeesList for the flight");
//            }
//            catch(runtime_error& e) {
//                cout << e.what() << endl;
//                exit();
//                ::exit(0);
//            }
        }
        //if all right we return the flight
        MyFlight* f = new MyFlight(model_number, reservations, employees, date, source, destination);
        flights.push_back(f);
        updateFlightsTable();
        return f;
    }
    virtual Flight *getFlight(string id) {
        //serach in the flight list.
        list<MyFlight*> :: iterator iterator;
        for (iterator = flights.begin(); iterator != flights.end(); ++iterator) {
            if ((*iterator)->getID() == id) {
                return (*iterator);
            }
        }
        //error if not found.

            throw runtime_error("No such flight found !");


    }

    Reservation *getReservation(string id) {
        list<MyReservation*> :: iterator iterator;
        //look for reservation id.
        for (iterator = reservations.begin(); iterator != reservations.end(); ++iterator) {
            if ((*iterator)->getID() == id) {
                return (*iterator);
            }
        }
        // Throw a runtime error and exit when trying to get a reservation that doesn't exist.
            throw runtime_error("No such reservation found");


    }
    Reservation *addResevation(string customerId, string flightId, Classes cls, int max_baggage){
        int flightFlag = 0;
        int cosFlag =0;
        if (customers.empty()) {
                throw runtime_error("No customers for reservation!");

        }
        // Can't make a reservation without any flights.
        if (flights.empty()) {
                throw runtime_error("Exception: No flights exist !");

        }
        MyCustomer* buyer;
        list<MyCustomer*> :: iterator iterator;
        for (iterator = customers.begin(); iterator != customers.end(); ++iterator) {
            if ((*iterator)->getID() == customerId) {
                cosFlag = 1;
                buyer = (*iterator);
                break; //quit loop if found.
            }
        }
        if (cosFlag == 0) {

                throw ("No such customer found");

        }
        MyFlight* flight;
        list<MyFlight*> :: iterator iterator2;
        for (iterator2 = flights.begin(); iterator2 != flights.end(); ++iterator2) {
            if ((*iterator2)->getID() == flightId ) {
                flightFlag = 1;
                flight = (*iterator2);
                break;
            }
        }
        //if flight not found
        if (flightFlag == 0) {

                throw ("No such flight found !");
        }
        MyReservation* reservation = new MyReservation(buyer, flight, cls, max_baggage);
        reservations.push_back(reservation);
        buyer->bookReservation(reservation);
        flight->bookReservation(reservation);
        updateReservationsTable();
        return reservation;
    }
    ~MyImplementation(){
        list<MyEmployee*> :: iterator it1;
        list<MyCustomer*> :: iterator it2;
        list<MyPlane*> :: iterator it3;
        list<MyFlight*> :: iterator it4;
        list<MyReservation*> :: iterator it5;
        list<Booking*> :: iterator it6;
        for (it1= employeesList.begin();it1!=employeesList.end();it1++){
            delete(*it1);
        }
        for (it3= planes.begin();it3!=planes.end();it3++){
            delete(*it3);
        }
        for (it2= customers.begin();it2!=customers.end();it2++){
            delete(*it2);
        }
        for (it4= flights.begin();it4!=flights.end();it4++){
            delete(*it4);
        }
        for (it5= reservations.begin();it5!=reservations.end();it5++){
            delete(*it5);
        }
        for (it6= bookings.begin();it6!=bookings.end();it6++){
            delete(*it6);
        }
    }
    void exit() {
    }
    void updateEmployeesTable() {
        ofstream file ("EmployeesTable.txt");
        list<MyEmployee*> :: iterator it;
        if (file.is_open()) {
            file << "*****Employees****" << endl;
            file <<"ID     Seniority     Birth Year    Jobs    Boss ID" << endl;
            file << "--------------------------------------------------------" << endl;
            for (it = employeesList.begin(); it != employeesList.end(); ++it){
                file << (*it) -> getID() << "    ";
                file << (*it) -> getSeniority() << "            ";
                file << (*it) -> getBirthYear() << "            ";
                file << (*it) -> getTitle() << "          ";
                if ((*it)->getEmployer() != NULL) {
                    file << (*it)->getEmployer()->getID() << endl;
                }
                else {
                    file << "none" << endl;
                }
                file << "-------------------------------------------------------------" << endl;
            }
            file << "*************************************************************" << endl;
        }
        file.close();
        this->createEmployeeBooking();
    }
    void updateCustomersTable() {
        list<MyCustomer*> :: iterator it;
        ofstream file ("CustomersTable.txt");
        if (file.is_open()) {
            file << "***Customers***" << endl;
            file <<"   ID                    Name               Priority    " << endl;
            for (it = customers.begin(); it != customers.end(); ++it){
                file << "" << (*it) -> getID() << "                ";
                file << (*it) -> getFullName() << "               ";
                file << (*it) -> getPriority() << endl;
                file << "----------------------------------------------------------" << endl;
            }
            file << "**************************************************************" << endl;
        }
        file.close();
    }
    void updatePlanesTable() {
        list<MyPlane*> :: iterator it;
        ofstream file ("PlanesTable.txt");
        if (file.is_open()) {
            file << "****Planes***" << endl;
            file <<"  ID     Model Number     First Class     Economy Class   Crew  " << endl;
            for (it = planes.begin(); it != planes.end(); ++it){
                file << (*it) -> getID() << "       ";
                file << (*it) -> getModelNumber() << "               ";
                file << (*it) -> getMaxFirstClass() << "                 ";
                file << (*it) -> getMaxEconomyClass() << "              ";
                file<<(*it)->getCrewString()<<endl;
                file << "-------------------------------------------------------------------------" << endl;
            }
            file << "*************************************************************************" << endl;
        }
        file.close();
    }
    void updateFlightsTable() {
        list<MyFlight*> :: iterator it;
        ofstream file ("FlightsTable.txt");
        if (file.is_open()) {
            file << "***Flights****" << endl;
            file <<"ID           Model           Source          Destination      Date     Employees IDs" << endl;
            for (it = flights.begin(); it != flights.end(); ++it){
                file << (*it) -> getID() << "        ";
                file << (*it) -> getModelNumber() << "             ";
                file << (*it) -> getSource() << "              ";
                file << (*it) -> getDestination() << "            ";
                file << (*it) -> getDate().getDate() <<"       ";
                file<<(*it)->getEmployeeIds()<<endl;
                file << "-------------------------------------------------------------------------" << endl;
            }
            file << "*************************************************************************" << endl;
        }
        file.close();
    }
    void updateReservationsTable() {
        list<MyReservation*> :: iterator it;
        ofstream file ("ReservationsTable.txt");
        if (file.is_open()) {
            file << "****Reservations***" << endl;
            file <<"ID       Class      Customer name       Baggage       Flight ID   " << endl;
            for (it = reservations.begin(); it != reservations.end(); ++it){
                file << (*it) -> getID() << "        ";
                file << (*it) -> getClass() << "              ";
                file << (*it) -> getCustomer()->getFullName() << "    ";
                file << (*it) -> getMaxBaggage() << "            ";
                file << (*it) -> getFlight()->getID() << endl;
                file << "-------------------------------------------------------------------------------" << endl;
            }
            file << "*******************************************************************************" << endl;
        }
        file.close();
    }

    void createEmployeeBooking ()
    {
    	list<Booking*>::iterator it;
    	ofstream f;
    	f.open("bookings.txt");
    	for (it = bookings.begin(); it != bookings.end(); it++)
    	{
    		f << (*it)->emp << " " << (*it)->d << endl;

    	}
    	f.close();
    }
    void loadEmployees(){
        string line = "";
        string id = "";
        string date = "";
        list<MyEmployee*>::iterator it;
        unsigned int i = 0;
        int boss = 0;
        ifstream file ("EmployeesTable.txt");
        MyEmployee * e = NULL;
        if (file)
        {
            while ( getline (file,line) )
            {
                char* ptr;
                ptr = &line.at(0);
                if (*ptr == '-' || *ptr == '*' || *ptr == 'I') {
                    continue;
                }
                vector <string> vec = split (line,' ');
                vec = eraseBackSpace(vec);
                if (vec[4] == "none"){
                    MyEmployee * b = NULL; //no need?
                }
                else{
                     boss = stoi(vec[4]);
                }
                if (stoi(vec[3]) == 0) {
                    e = new MyEmployee(vec[0], stoi(vec[1]), stoi(vec[2]), MANAGER, boss);
                }
                else if (stoi(vec[3]) == 1) {
                    e = new MyEmployee(vec[0], stoi(vec[1]), stoi(vec[2]), NAVIGATOR, boss);
                }
                else if (stoi(vec[3]) == 2) {
                    e = new MyEmployee(vec[0], stoi(vec[1]), stoi(vec[2]), FLY_ATTENDANT, boss);
                }
                else if (stoi(vec[3]) == 3) {
                    e = new MyEmployee(vec[0], stoi(vec[1]), stoi(vec[2]), PILOT, boss);
                }
                else if (stoi(vec[3]) == 4) {
                    e = new MyEmployee(vec[0], stoi(vec[1]), stoi(vec[2]), OTHER, boss);
                }
                else
                        throw ("fuck");
                employeesList.push_back(e);
            }
            file.close();
            file.open("bookings.txt");
            if (file)
            {
            	while (getline(file, line))
            	{
            		while (line.at(i) != ' ')
            		{
            			id.push_back(line.at(i));
            			i++;
            		}
            		i++;
            		while (i < line.size() && line.at(i) != ' ')
            		{
            			date.push_back(line.at(i));
            			i++;
            		}
            		for (it = employeesList.begin(); it != employeesList.end(); it++)
            		{
            			e = *it;
            			if (e->getID() == id)
            			{
            				e->bookMe(Date(date));
            				Booking* b = new Booking();
            				b->emp = id;
            				b->d = date;
            				bookings.push_back(b);
            			}
            		}
            		id = "";
            		date = "";
            		i = 0;
            	}
            }
        }

     }

    void loadPlanes(){
        string line;
        int i = 0;
        ifstream file ("PlanesTable.txt");
        MyPlane * e = NULL;
        if (file.is_open())
        {
            while ( getline (file,line) )
            {
                char* ptr;
                ptr = &line.at(0);
                if (*ptr == '-' || *ptr == '*' || *ptr == 'I' || *ptr == ' ') {
                    continue;
                }
                vector <string> vec = split (line,' ');
                vec = eraseBackSpace(vec);
                string crew1 = vec[4];
                vector<int> a = extractInts(crew1);
                string crew2 = vec[5];
                vector<int> b = extractInts(crew2);
                string crew3 = vec[6];
                vector<int> c = extractInts(crew3);
                string crew4 = vec[7];
                vector<int> d = extractInts(crew4);
                string crew5 = vec[8];
                vector<int> e = extractInts(crew5);
                map<Jobs , int> finalCrew;
                finalCrew.insert (pair<Jobs ,int>(MANAGER,a[0]));
                finalCrew.insert (pair<Jobs ,int>(NAVIGATOR,b[0]));
                finalCrew.insert (pair<Jobs ,int>(FLY_ATTENDANT,c[0]));
                finalCrew.insert (pair<Jobs ,int>(PILOT,d[0]));
                finalCrew.insert (pair<Jobs ,int>(OTHER,e[0]));

                MyPlane *pl = new MyPlane(stoi(vec[1]),finalCrew,stoi(vec[2]),stoi(vec[3]));
                planes.push_back(pl);
            }
            file.close();
        }
    }
    void loadReservations(){
        string line;
        int i = 0;
        ifstream file ("ReservationsTable.txt");
        MyReservation * e = NULL;
        if (file.is_open())
        {
            while ( getline (file,line) )
            {
                char* ptr;
                ptr = &line.at(0);
                if (*ptr == '-' || *ptr == '*' || *ptr == 'I' || *ptr == ' ') {
                    continue;
                }
                vector <string> vec = split (line,' ');
                vec = eraseBackSpace(vec);
//                MyCustomer *k = new MyCustomer(vec[0],vec[2],1);
//                MyFlight * f = new MyFlight(vec[4],stoi(vec[5]),vec[6],vec[7],Date(vec[8]));
                Customer * k = getCustomer(vec[0]);
                Flight * f = getFlight(vec[4]);
                if (stoi(vec[1]) == 0) {
                    e = new MyReservation(k, f, FIRST_CLASS, stoi(vec[3]));
                }
                else if (stoi(vec[1]) == 1) {
                    e = new MyReservation(k,f,SECOND_CLASS,stoi(vec[3]));
                }
                reservations.push_back(e);

            }
            file.close();
        }
    }
    // Load customers from file.
    void loadCustomers() {
        string line;
        int i = 0;
        ifstream file ("CustomersTable.txt");
        MyCustomer* customer = NULL;
        if (file.is_open()) {
            while ( getline (file,line) ) {
                char* ptr;
                ptr = &line.at(0);
              if (*ptr == '-' || *ptr == '*' || *ptr == 'I' || *ptr == ' ') {
                   continue;
               }
                vector <string> vec = split (line,' ');
                vec = eraseBackSpace(vec);
                if (vec.size() == 3) {
                    MyCustomer* customer = new MyCustomer(vec[0], vec[1], stoi(vec[2]));
                    customers.push_back(customer);
                }
                if (vec.size() == 4) {
                    string name = vec[1];
                    string lastName = vec[2];
                    string fullName = name + " " + lastName;
                    vec[2] = vec[3];
                    MyCustomer* customer = new MyCustomer(vec[0], fullName, stoi(vec[2]));
                    customers.push_back(customer);
                }
            }
            file.close();
        }
    }

    void loadFlights(){
        string line;
        int i;
        list<MyEmployee*> :: iterator it1;
        ifstream file ("FlightsTable.txt");
        MyFlight * e = NULL;
        if (file)
        {
            while ( getline (file,line) )
            {
                char* ptr;
                ptr = &line.at(0);
                if (*ptr == '-' || *ptr == '*' || *ptr == 'I' || *ptr == ' ') {
                    continue;
                }
                vector <string> vec = split (line,' ');
                vec = eraseBackSpace(vec);
                list <Employee*> list;
                for (i=5;i<vec.size();++i){
//                    Employee* a = getEmployee(vec[i]);
//                    list.push_back(a);

                    for(it1 = employeesList.begin();it1!=employeesList.end();it1++){
                    	if ((*it1)->getID() == vec[i]){
                    		list.push_back(*it1);
                    		(*it1)->bookMe(Date(vec[4])); //?
                    	}
                    }
                }
                MyFlight *e = new MyFlight(vec[0],stoi(vec[1]),vec[2],vec[3],Date(vec[4]),list);
                flights.push_back(e);
            }
            file.close();
        }
    }

    std::vector<std::string> split(const std::string &text, char sep) {
        std::vector<std::string> tokens;
        std::size_t start = 0, end = 0;
        while ((end = text.find(sep, start)) != std::string::npos) {
            tokens.push_back(text.substr(start, end - start));
            start = end + 1;
        }
        tokens.push_back(text.substr(start));
        return tokens;
    }

    std::vector<std::string> eraseBackSpace(vector<string> v){
        int i = 0;
        vector <string> ve;
        for (i;i<v.size();i++){
            if (v[i] == ""){
                continue;
            }
            else{
                ve.push_back(v[i]);
            }
        }
        return ve;

    }
    vector<int> extractInts(string str){
        std::vector<int> numbers;
        for ( std::string::iterator it=str.begin(); it!=str.end(); ++it){
            if (isdigit(*it)){
                numbers.push_back(*it - '0');
            }
        }

        return numbers;
    }

};

#endif //EX2_MYIMPLEMENTATION_H
