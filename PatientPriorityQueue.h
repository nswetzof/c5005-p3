// Nathan Swetzof
// PatientPriorityQueue.h
// November 12, 2023
// Specification and implementation file for PatientPriorityQueue class used
//      to create a priority queue for patients entered into an emergency room.

#ifndef P3_PATIENTPRIORITYQUEUE_H
#define P3_PATIENTPRIORITYQUEUE_H


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
};

PatientPriorityQueue::PatientPriorityQueue() {
    nextPatientNumber = 1;
}

void PatientPriorityQueue::add(const string &priority, const string &name) {
    int priorityCode;

    if (priority == "immediate")
        priorityCode = 1;
    else if (priority == "emergency")
        priorityCode = 2;
    else if (priority == "urgent")
        priorityCode = 3;
    else
        priorityCode = 4;

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
    string patientInfo, name, priorityCode, arrivalOrder;
    size_t spaceAfterName, priorityIndex, arrivalIndex;
    vector<Patient>::const_iterator it = patients.begin();

    while(it != patients.end()) {
        patientInfo = it++->to_string();

        spaceAfterName = patientInfo.find_first_of('{') - 1;
        priorityIndex = patientInfo.find_first_of('=') + 1;
        arrivalIndex = patientInfo.find_first_of('=', priorityIndex + 1) + 1;

        name = patientInfo.substr(0, spaceAfterName);
        priorityCode = patientInfo.substr(priorityIndex,
                          patientInfo.find_first_of(',') - priorityIndex);
        arrivalOrder = patientInfo.substr(arrivalIndex,
                          patientInfo.find_first_of(' ', arrivalIndex)
                          - arrivalIndex);

        ss << right << setw(7) << arrivalOrder << "\t\t"
            << left << setw(15) << priorityCode << name << '\n';
    }

    return ss.str();
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


#endif //P3_PATIENTPRIORITYQUEUE_H
