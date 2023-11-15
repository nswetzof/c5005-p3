// Nathan Swetzof
// Patient.h
// November 14, 2023
// Specification and implementation file for Patient class used to represent
//      a single patient in a priority queue.  Implements comparison operators
//      to determine relative priority between patients.

#ifndef P3_PATIENT_H
#define P3_PATIENT_H

#include <sstream>
#include <string>

using namespace std;

class Patient {
public:
    Patient(int, const string &, int);
    // Default constructor creates patient with priority code corresponding
    //      with first parameter, name corresponding with second parameter, and
    //      arrival order corresponding with third parameter
    // preconditions: priority code must be in range 1 to 4,
    //      arrival order must be greater than 0
    // postcondition: name, priorityCode, and arrivalOrder are assigned to
    //      the values passed into the constructor

    bool operator<(const Patient &) const;
    // Less than operator to compare two Patients.
    // precondition: none
    // postcondition: Return true if Patient passed into
    //      function has higher priority (based on priority code) than
    //      this Patient.  If Patient passed into function has higher priority
    //      than this Patient, return false.  If both Patients have same
    //      priority, return true if arrival order is lower for this Patient
    //      than the Patient passed into function.  Otherwise, return false.

    bool operator>(const Patient &) const;
    // Greater than operator for two Patients.
    // precondition: none
    // postcondition: Return true if Patient passed
    //      into function has lower priority (based on priority code) than
    //      this Patient.  If Patient passed into function has lower priority
    //      than this Patient, return false.  If both Patients have same
    //      priority, return true if arrival order is higher for this Patient
    //      than the Patient passed into function.  Otherwise, return false.

    bool operator==(const Patient &) const;
    // Equals operator for two Patients.
    // precondition: none
    // postcondition: Return true if both Patients have
    //      same priority codes and arrival orders, false otherwise.

    bool operator<=(const Patient &) const;
    // Less than or equals operator
    // precondition: none
    // postcondition: Returns true if Patient object passed into
    //      function satisfies less than and equals operator conditions

    bool operator>=(const Patient &) const;
    // Greater than or equals operator
    // precondition: none
    // postcondition: returns true if Patient object passed
    //      into function satisfies greater than and equals operator conditions

    string getName() const;
    // Returns the name of the Patient
    // preconditions: none
    // postcondition: returns name

    string getPriorityCode() const;
    // Returns the priority code of the Patient
    // preconditions: none
    // postcondition: returns the priority code string corresponding to the
    //      value of priorityCode

    int getArrivalOrder() const;
    // Returns the order in which the patient arrived
    // preconditions: none
    // postcondition: returns arrivalOrder

    string to_string() const;
    // String representation of the Patient
    // precondition: none
    // postcondition: Return string indicating arrival number,
    //      priority code, and patient name

private:
    string name; // patient name
    int priorityCode; // patient priority code (1 to 4)
    int arrivalOrder; // order of patient arrival in emergency room

    string getPriorityString() const;
    // Return string representation of Patient priority
    // precondition: none
    // postcondition: Return string corresponding to priorityCode field
};

Patient::Patient(int priority, const string &name, int arrivalOrder) {
    this->priorityCode = priority;
    this->name = name;
    this->arrivalOrder = arrivalOrder;
}

bool Patient::operator<(const Patient &obj) const {
    if (priorityCode < obj.priorityCode)
        return true;
    else if (priorityCode == obj.priorityCode)
        return arrivalOrder < obj.arrivalOrder;

    return false;
}

bool Patient::operator>(const Patient &obj) const {
    if (priorityCode > obj.priorityCode)
        return true;
    else if (priorityCode == obj.priorityCode)
        return arrivalOrder > obj.arrivalOrder;

    return false;
}

bool Patient::operator==(const Patient &right) const {
    return (priorityCode == right.priorityCode &&
            arrivalOrder == right.arrivalOrder);
}

bool Patient::operator<=(const Patient &right) const {
    return ((*this) < right || (*this) == right);
}

bool Patient::operator>=(const Patient &right) const {
    return ((*this) > right || (*this) == right);
}

string Patient::getName() const {
    return name;
}

string Patient::getPriorityCode() const {
    return getPriorityString();
}

int Patient::getArrivalOrder() const {
    return arrivalOrder;
}

string Patient::to_string() const {
    stringstream ss;
    ss << name << " { pri=" << getPriorityString()
        << ", arrive=" << arrivalOrder << " }";

    return ss.str();
}

string Patient::getPriorityString() const {
    if (priorityCode == 1)
        return "immediate";
    else if (priorityCode == 2)
        return "emergency";
    else if (priorityCode == 3)
        return "urgent";

    return "minimal";
}

#endif //P3_PATIENT_H
