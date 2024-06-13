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
    string password;
    string usertype;
public:
    User(int id, string n, string e, string p, string ut) : userID(id), name(n), email(e), password(p), usertype(ut) {}

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
    string getUserEmail(){
        return email;
    }
    string getUserName(){
        return name;
    }
    string getUserPassword(){
        return password;
    }
    string getUserType(){
        return usertype;
    }
};

class Participant: public User{
private:
    vector<int>registeredEvents;
public:
    Participant(int id, string n, string e, string p, string ut) : User(id,n,e,p,ut) {}

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
    Admin(int id, string n, string e, string p, string ut) : User(id,n,e,p,ut) {}


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
    vector<Participant*> participants;
    vector<Admin*> admins;
public:
    void addUser(User* user) {
        if(user->getUserType() == "Participant"){
            Participant* p = new Participant(user->getUserID(), user->getUserName(), user->getUserEmail(), user->getUserPassword(), user->getUserType());

            participants.push_back(p); 
        }
        if(user->getUserType() == "Admin"){
            Admin* a = new Admin(user->getUserID(), user->getUserName(), user->getUserEmail(), user->getUserPassword(), user->getUserType());

            admins.push_back(a); 
        }

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



    User* findUser(string userEmail) {
        for (User* user : users) {
            if (user->getUserEmail() == userEmail) {
                return user;
            }
        }
        return nullptr;
    }
    User* findUserId(int userID) {
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


int uniqueIdGenerator(){
    int suffix = rand()%10000;
    return suffix;
}

void participantDashboard(User* user){
// --------------------------------------------------------------------------------------------------------------
// dynamic_cast is used to typecast one class to another. Here I've casted User* user to Participant* as I'm sure that user is a Participant and can be sucessfully casted.
// --------------------------------------------------------------------------------------------------------------
    Participant* puser = dynamic_cast<Participant*>(user);
    decor();
    cout<<"Welcome Participant! Here is your profile: "<<endl;
    puser->viewProfile();
    decor();

    int choice;
    while(1){
        cout<<"1. Log Out"<<endl;
        cin>>choice;
        switch (choice){
            case 1 :{
                cout<<"Successfully Logged Out"<<endl;
                return;
            }
            default:
                break;
        }
    }

}

void adminDashboard(User* user){
    decor();
    Admin* auser = dynamic_cast<Admin*>(user);
    auser->viewProfile();
}

int main(){
    EventManager ems;

    int flag = 1;
    while(flag){
        decor();
        int choice;
        cout<<"1. Log In"<<endl;        
        cout<<"2. Sign Up"<<endl;
        cout<<"3. Exit"<<endl;
        cout<<"Enter Your Choice: "; cin>>choice;

        switch (choice)
        {
            case 1: {
                decor();
                string email; string password;
                cout<<"Enter email: "; cin>>email;
                cout<<"Enter password: "; cin>>password;
                User* user = ems.findUser(email);

                if(!user){
                    cout<<"No such user exists!"<<endl;
                    break;
                }
                if(user->getUserPassword() != password){
                    cout<<"Wrong Password!"<<endl;
                    break;
                }

                cout<<"You're logged in as "<<user->getUserName()<<"!"<<endl;
                if(user->getUserType() == "Participant"){
                    participantDashboard(user);
                }
                else if(user->getUserType() == "Admin"){
                    adminDashboard(user);
                }

                break;
            }
            
            case 2: {
                decor();
                string name, email, password;
                cout<<"Enter Name: "; cin>>name;
                cout<<"Enter email: "; cin>>email;
                cout<<"Enter password: "; cin>>password;
                string ut = "Participant";
                int uid;
                while(1){
                    uid = uniqueIdGenerator();
                    if(!ems.findUserId(uid)) break;
                }
                Participant* p = new Participant(uid, name, email, password, ut);
                ems.addUser(p);
                cout<<"Account successfully created!"<<endl;
                
                participantDashboard(p);

                break;
            }

            case 3: {
                decor();
                cout<<endl;
                cout<<"Adieu!"<<endl;
                decor();
                flag = 0;
                break;
            }

            default:
                break;

        }

    }
    

    return 0;
}