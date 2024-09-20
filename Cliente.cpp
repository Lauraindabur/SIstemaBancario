#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

class Cliente
{

private:
    string name;
    string lastName;
    string id;
    string active;
    string turn;
    string timeStart;
    string timeEnd;

public:
    Cliente(string n, string ln, string id, string active, string t, string ts, string te) : name(name), lastName(ln), id(id), turn(t), timeStart(ts), timeEnd(te) {};

    Cliente() : name(""), lastName(""), id(""), active(""), turn(""), timeStart(""), timeEnd("") {};

    // Getters and setters
    string getName() const { return name; }
    void setName(const string &name) { this->name = name; }

    string getLastName() const { return lastName; }
    void setLastName(const string &lastName) { this->lastName = lastName; }

    string getId() const { return id; }
    void setId(const string &id) { this->id = id; }

    string getActive() const { return active; }
    void setActive(const string &active) { this->active = active; }

    string getTurn() const { return turn; }
    void setTurn(const string &turn) { this->turn = turn; }

    string getTimeStart() const { return timeStart; }
    void setTimeStart(const string &timeStar) { this->timeStart = timeStar; }

    string getTimeEnd() const { return timeEnd; }
    void setTimeEnd(const string &timeEnd) { this->timeEnd = timeEnd; }

    string printInformation()
    {
        return name + "," + lastName + "," + id + "," + active + "," + turn + "," + timeStart + "," + timeEnd;
    }
};