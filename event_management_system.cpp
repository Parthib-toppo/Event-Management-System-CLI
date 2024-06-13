//Toppo
#include <bits/stdc++.h>
using namespace std;

void decor(){
    cout<<endl;
    cout<<"-----------------------------------------------------------------------------------------------"<<endl;
}


class User {
protected:
    int userID;
    string name;
    string email;
public:
    User(int id, string n, string e) : userID(id), name(n), email(e) {}

    virtual void viewProfile(){
        cout<<"UserID: "<<userID<<endl;
        cout<<"Name: "<<name<<endl;
        cout<<"Email: "<<email<<endl;
    }
    virtual void editProfile(string newName, string newEmail){
        name = newName;
        email = newEmail;
    }

    int getUserID() const{
        return userID;
    }
};

class Participant: public User{
private:
    vector<int>registeredEvents;
public:
    Participant(int id, string n, string e) : User(id,n,e) {}

    void registerEvent(int eventID){
        registeredEvents.push_back(eventID);
    }

    void viewRegisteredEvents(){
        cout<<"Registered events for "<<name<<": ";
        for(auto it: registeredEvents){
            cout<<it<<" ";
        }
        cout<<endl;
    }

};

class Admin: public User{
public:
    Admin(int id, string n, string e) : User(id,n,e) {}


};



class Event{
protected:
    int eventID;
    string eventName;
    string eventDate;
    int budget;
    vector<string>guests;
public:
    Event(int eid, string ename, string edate, int b) : eventID(eid), eventName(ename), eventDate(edate), budget(b) {}

    int getEventID(){
        return eventID;
    }
    string getEventName(){
        return eventName;
    }
    string getEventDate(){
        return eventDate;
    }

    virtual void viewEventDetails(){
        cout<<"Event ID: "<<eventID<<endl;
        cout<<"Event Name: "<<eventName<<endl;
        cout<<"Event Date: "<<eventDate<<endl;
        cout<<"Event Budget: "<<budget<<endl;
        cout<<"Guests: ";
        if(guests.empty()){
            cout<<"No Guests!";
        }
        else{
            for(auto it: guests){
                cout<<it<<" ";
            }
        }
        cout<<endl;
    }

    virtual void editEventDetails(string newname, string date, double bud){
        eventName = newname;
        eventDate = date;
        budget = bud;
    }

    void addGuest(string guest){
        guests.push_back(guest);
    }
};

class Competition : public Event {
private:
    double prize;
public:
    Competition(int id, string name, string date, double bud, double p) : Event(id, name, date, bud), prize(p) {}

    void viewCompetitionDetails() {
        viewEventDetails();
        cout << "Prize: " << prize << endl;
    }
};

class Program : public Event {
private:
    string programType;
public:
    Program(int id, string name, string date, double bud, string type) : Event(id, name, date, bud), programType(type) {}

    void viewProgramDetails() {
        viewEventDetails();
        cout << "Program Type: " << programType << endl;
    }
};

class Session : public Event {
private:
    string speaker;
public:
    Session(int id, string name, string date, double bud, string spk) : Event(id, name, date, bud), speaker(spk) {}

    void viewSessionDetails() {
        viewEventDetails();
        cout << "Speaker: " << speaker << endl;
    }
};



class EventManager {
private:
    vector<Event*> events;
    vector<User*> users;
public:
    void addUser(User* user) {
        users.push_back(user);
    }
    void displayAllUsers(){
        for(auto it: users){
            decor();
            it->viewProfile();
        }
        decor();
    }

    void addEvent(Event* event) {
        events.push_back(event);
    }

    void displayAllEvents(){
        for(auto it: events){
            decor();
            it->viewEventDetails();
        }
        decor();
    }



    User* findUser(int userID) {
        for (User* user : users) {
            if (user->getUserID() == userID) {
                return user;
            }
        }
        return nullptr;
    }

    Event* findEvent(int eventID) {
        for (Event* event : events) {
            if (event->getEventID() == eventID) {
                return event;
            }
        }
        return nullptr;
    }
};



int main(){
    EventManager ems;
    
    Participant* p1 = new Participant(1, "John Doe", "john@example.com");
    Admin* a1 = new Admin(2, "Admin User", "admin@example.com");

    ems.addUser(p1);
    ems.addUser(a1);

    Competition* c1 = new Competition(1, "Coding Competition", "2024-06-20", 1000.0, 500.0);
    Program* pr1 = new Program(2, "AI Workshop", "2024-06-21", 1500.0, "Workshop");
    Session* s1 = new Session(3, "Tech Talk", "2024-06-22", 500.0, "Dr. Smith");

    ems.addEvent(c1);
    ems.addEvent(pr1);
    ems.addEvent(s1);

    p1->registerEvent(1);
    p1->registerEvent(2);

    // p1->viewRegisteredEvents();

    // ems.displayAllEvents();
    ems.displayAllUsers();

    delete p1;
    delete a1;
    delete c1;
    delete pr1;
    delete s1;

    return 0;
}