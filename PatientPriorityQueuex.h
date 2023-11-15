// Nathan Swetzof
// PatientPriorityQueue.h
// November 12, 2023
// Specification and implementation file for PatientPriorityQueue class used
//      to create a priority queue for patients entered into an emergency room.

#ifndef P3_PATIENTPRIORITYQUEUEX_H
#define P3_PATIENTPRIORITYQUEUEX_H


#include <algorithm>
#include <cassert>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include "Patient.h"

class PatientPriorityQueue {
public:
    PatientPriorityQueue();
    // Default constructor
    // precondition: none
    // postcondition: initializes patients vector as empty vector and assigns
    //      nextPatient value to 1

    void add(const string &, const string &);
    // Add Patient, with name and priority code passed into function, to
    //      priority queue.
    // preconditions: priority code must be "immediate", "emergency", "urgent",
    //      or "minimal"
    // postcondition: Patient is added to patients vector.  Maintains min-heap
    //      ordering after addition.

    Patient peek() const;
    // Return highest priority Patient in the priority queue without removing
    // precondition: patients vector is not empty
    // postcondition: returns highest priority Patient

    Patient remove();
    // Remove the highest priority patient from the priority queue
    // precondition: patients vector is not empty
    // postcondition: highest priority Patient is removed from the patients
    //      vector and returned.  Maintains min-heap ordering in vector after
    //      removal.

    int size() const;
    // Return number of patients still waiting
    // preconditon: none
    // postcondition: returns size of patients vector

    string to_string() const;
    // Return string representation of all Patients in the waiting list
    // precondition: none
    // postcondition: returns multiline string with each line consisting of
    //      arrival order, priority, and name of each patient in min-heap
    //      order.

    string change(int, const string &);
    // Change priority code of a patient given an arrival order
    // preconditions: new priority code must be "immediate", "emergency",
    //      "urgent", or "minimal";
    //      Patient arrival order must match an arrival order in the patients
    //      vector
    // postcondition: The priority code of the Patient associated with the
    //      arrival order integer passed into the function will be updated to
    //      the priority code corresponding with the string passed into the
    //      function.  Function returns string indicating patient name and new
    //      priority if the change was successful.  Otherwise, returns error
    //      message indicating arrival order was not found.

    void save(ostream &) const;
    // Save patient names and priorities to a file
    // preconditions: none
    // postcondition: add patient statements are added to the ostream object
    //      reference passed into function with one patient per line including
    //      patient priority and patient name. File is written by order of
    //      arrival of patients.

private:
    vector<Patient> patients;
    int nextPatientNumber;

    void siftUp(int);
    // Moves the element at given index up the heap such that the min-heap
    //      condition is maintained
    // precondition: value passed into function represents a valid index
    //    in the patients vector
    // postcondition: moves the element in patients vector, at index passed into
    //      function, to its parent in the priority queue recursively until it
    //      satisfies the min-heap condition

    void siftDown(int);
    // Moves the element at given index down the heap such that the min-heap
    //      condition is maintained
    // precondition: value passed into function represents a valid index
    //      in the patients vector
    // postcondition: Moves the element at index passed into function to its
    //      left or right child in the priority queue recursively until it
    //      satisfies the min-heap condition

    int getParent(int);
    // Return parent index of index passed into function
    // precondition: value passed into function represents a valid index
    //      in the patients vector
    // postcondition: returns index of parent in the priority queue

    int getLeftChild(int);
    // Return left child index of index passed into function
    // precondition: value passed into function represents a valid index
    //      in the patients vector
    // postcondition: returns index of left child in the priority queue

    int getRightChild(int);
    // Return right child index of index passed into function
    // precondition: value passed into function represents a valid index
    //      in the patients vector
    // postcondition: returns index of right child in the priority queue

    static int getPriorityCode(const string &);
    // Return integer associated with priority code string passed into function
    // precondition: none
    // postcondition: returns priority code of string passed into function
};

PatientPriorityQueue::PatientPriorityQueue() {
    nextPatientNumber = 1;
}

void PatientPriorityQueue::add(const string &priority, const string &name) {
    int priorityCode = getPriorityCode(priority);

    patients.emplace_back(priorityCode, name, nextPatientNumber++);
    siftUp(patients.size() - 1);
}

Patient PatientPriorityQueue::peek() const {
    assert(!patients.empty());

    return patients.at(0);
}

Patient PatientPriorityQueue::remove() {
    assert(!patients.empty());

    Patient result = patients.at(0);

    patients.at(0) = patients.at(patients.size() - 1);
    patients.pop_back();

    if (patients.size() > 1)
        siftDown(0);

    return result;
}

int PatientPriorityQueue::size() const {
    return patients.size();
}

string PatientPriorityQueue::to_string() const {
    stringstream ss;
    string name, priorityCode;
    int arrivalOrder;
    vector<Patient>::const_iterator it = patients.begin();

    while(it != patients.end()) {
        name = it->getName();
        priorityCode = it->getPriorityCode();
        arrivalOrder = it->getArrivalOrder();

        ss << right << setw(7) << arrivalOrder << "\t\t"
            << left << setw(15) << priorityCode << name << '\n';

        it++;
    }

    return ss.str();
}

string PatientPriorityQueue::change(int arrivalOrder,
                                    const string &priority) {
    int newPriority = getPriorityCode(priority);

    for (int i = 0; i < patients.size(); i++) {
        Patient patient = patients.at(i);

        if (patient.getArrivalOrder() == arrivalOrder) {
            Patient newPatient(getPriorityCode(priority),
                               patient.getName(),
                               patient.getArrivalOrder());
            patients.at(i) = newPatient;

            if (newPriority < getPriorityCode(patient.getPriorityCode()))
                siftUp(i);
            else
                siftDown(i);

            return "Changed patient " + patient.getName() + "'s priority to "
                + priority;
        }
    }

    return "Error: no patient with the given id was found.";
}

void PatientPriorityQueue::save(ostream &file) const {
    vector<Patient> copy; // hold a copy of the patients vector

    for(int i = 0; i < patients.size(); i++)
        copy.push_back(patients.at(i));

    // sort by patient arrival time
    sort(copy.begin(), copy.end(), [](Patient &x, Patient &y){
        return x.getArrivalOrder() < y.getArrivalOrder();
        }
    );

    for (int i = 0; i < patients.size(); i++)
        file << "add " << copy.at(i).getPriorityCode() << " "
            << copy.at(i).getName() << '\n';
}

void PatientPriorityQueue::siftUp(int index) {
    int parentIdx;
    if (index != 0) {
        parentIdx = getParent(index);
        if (patients.at(parentIdx) > patients.at(index)) {
            Patient temp = patients.at(parentIdx);
            patients.at(parentIdx) = patients.at(index);
            patients.at(index) = temp;
            siftUp(parentIdx);
        }
    }
}

void PatientPriorityQueue::siftDown(int index) {
    size_t leftIdx, rightIdx, minIdx;
    leftIdx = getLeftChild(index);
    rightIdx = getRightChild(index);

    // find minIdx
    if (rightIdx >= patients.size()) {
        if (leftIdx >= patients.size())
            return;
        else
            minIdx = leftIdx;
    } else {
        if (patients.at(leftIdx) <= patients.at(rightIdx))
            minIdx = leftIdx;
        else
            minIdx = rightIdx;
    }

    // swap?
    if (patients.at(minIdx) < patients.at(index)) {
        Patient temp = patients.at(minIdx);
        patients.at(minIdx) = patients.at(index);
        patients.at(index) = temp;
        siftDown(minIdx);
    }

}

int PatientPriorityQueue::getParent(int index) {
    return (index - 1) / 2;
}

int PatientPriorityQueue::getLeftChild(int index) {
    return 2 * index + 1;
}

int PatientPriorityQueue::getRightChild(int index) {
    return 2 * index + 2;
}

int PatientPriorityQueue::getPriorityCode(const string &priorityString) {
    if (priorityString == "immediate")
        return 1;
    else if (priorityString == "emergency")
        return 2;
    else if (priorityString == "urgent")
        return 3;
    else
        return 4;
}

#endif //P3_PATIENTPRIORITYQUEUEX_H
