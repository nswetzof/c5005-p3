// TODO: DOCUMENT
// Created by Nathan on 11/2/2023.
//

#ifndef P3_PATIENT_H
#define P3_PATIENT_H

#include <sstream>
#include <string>

using namespace std;

class Patient {
public:
    Patient(const string &, const string &, int);
    // TODO: Change signature to make priorityCode an int.  Will handle finding priority code in PatientPriorityQueue
    // TODO: document

    bool operator<(const Patient &) const;
    // Less than operator for two Patients.  Return true if Patient passed into
    //      function has higher priority (based on priority code) than
    //      this Patient.  If Patient passed into function has higher priority
    //      than this Patient, return false.  If both Patients have same
    //      priority, return true if arrival order is lower for this Patient
    //      than the Patient passed into function.  Otherwise, return false.

    bool operator>(const Patient &) const;
    // Greater than operator for two Patients.  Return true if Patient passed
    //      into function has lower priority (based on priority code) than
    //      this Patient.  If Patient passed into function has lower priority
    //      than this Patient, return false.  If both Patients have same
    //      priority, return true if arrival order is higher for this Patient
    //      than the Patient passed into function.  Otherwise, return false.

    bool operator==(const Patient &) const;
    // Equals operator for two Patients.  Return true if both Patients have
    //      same priority codes and arrival orders, false otherwise.
    // TODO: Confirm this is desired behavior (not just priority code?)

    bool operator<=(const Patient &) const;
    // Less than or equals operator returns true if Patient object passed into
    //      function satisfies less than and equals operator conditions

    bool operator>=(const Patient &) const;
    // Greater than or equals operator returns true if Patient object passed
    //      into function satisfies greater than and equals operator conditions

    string to_string() const;
    // Return string representation of Patient, indicating arrival number,
    //      priority code, and patient name

private:
    string name;
    int priorityCode;
    int arrivalOrder;

    string getPriorityString() const;
    // Return string corresponding to priority code based on priority code
    //      integer field.
};

Patient::Patient(const string &priority, const string &name, int arrivalOrder) {
    if (priority == "immediate")
        priorityCode = 1;
    else if (priority == "emergency")
        priorityCode = 2;
    else if (priority == "urgent")
        priorityCode = 3;
    else
        priorityCode = 4;

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
