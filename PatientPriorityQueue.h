//
// Created by Nathan on 11/2/2023.
//

#ifndef P3_PATIENTPRIORITYQUEUE_H
#define P3_PATIENTPRIORITYQUEUE_H


#include <cassert>
#include <sstream>
#include <string>
#include <vector>
#include "Patient.h"

class PatientPriorityQueue {
public:
    PatientPriorityQueue();
    // Default constructor creates empty vector of patients and initializes
    //      nextPatient number to 1

    void add(const string &, const string &);
    // Add patient, with name and priority code passed into function, to
    //      priority queue.  Maintains min-heap ordering after addition.

    Patient peek() const;
    // Return highest priority patient in the priority queue without removing

    Patient remove();
    // Remove the highest priority patient from the priority queue and returns
    //      patient.  Maintains min-heap ordering in priority queue after
    //      removal.

    int size() const;
    // Return number of patients still waiting

    string to_string() const;
    // Return string representation of object in min-heap order

private:
    vector<Patient> patients;
    int nextPatientNumber;

    void siftUp(int);
    // Moves the element at index passed into function to its parent
    //      in the priority queue recursively until it satisfies the min-heap
    //      condition

    void siftDown(int);
    // Moves the element at index passed into function to its left or right
    //      child in the priority queue recursively until it satisfies the
    //      min-heap condition

    int getParent(int);
    // Return parent index of index passed into function

    int getLeftChild(int);
    // Return left child index of index passed into function

    int getRightChild(int);
    // Return right child index of index passed into function
};

PatientPriorityQueue::PatientPriorityQueue() {
    nextPatientNumber = 1;
}

void PatientPriorityQueue::add(const string &priority, const string &name) {
    patients.emplace_back(priority, name, nextPatientNumber++);
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
    vector<Patient>::const_iterator it = patients.begin();

    while(it != patients.end()) {
        ss << it++->to_string() << '\n';
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
    int leftIdx, rightIdx, minIdx;
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
