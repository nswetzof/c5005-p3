// Nathan Swetzof
// p3.cpp
// 11/12/23
// Interface for a hospital triage system allows user to add patients to the
//      emergency room and uses priority queue to determine which patients will
//      be seen next and removed from the queue.
// Input: Accepts user commands to the console for individual patients or to
//      add patients listed in a separate file.
// Process: Add or remove patients from the priority queue
// Output: Displays patient information for all patients or for the highest
//      priority patient.

#include "PatientPriorityQueuex.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;


void welcome();
// Prints welcome message.

void goodbye();
// Prints goodbye message.

void help();
// Prints help menu.

bool processLine(string, PatientPriorityQueue &);
// Process the line entered from the user or read from the file.

void addPatientCmd(string, PatientPriorityQueue &);
// Adds the patient to the waiting room.

void peekNextCmd(PatientPriorityQueue &);
// Displays the next patient in the waiting room that will be called.

void removePatientCmd(PatientPriorityQueue &);
// Removes a patient from the waiting room and displays the name on the screen.

void showPatientListCmd(PatientPriorityQueue &);
// Displays the list of patients in the waiting room.

void execCommandsFromFileCmd(string, PatientPriorityQueue &); 
// Reads a text file with each command on a separate line and executes the
// lines as if they were typed into the command prompt.

void changeCmd(string &, PatientPriorityQueue &);
// Changes the priority code of a patient in the waiting room based on arrival
//  order and priority code typed into the command prompt

string delimitBySpace(string &);
// Delimits (by space) the string from user or file input.

string removeWhitespace(const string &);
// Returns a string that matches the string passed into function with leading
//      and trailing whitespace removed.


int main() {

	// declare variables
	string line;

	// welcome message
	welcome();

	// process commands
	PatientPriorityQueue priQueue;
	do {
		cout << "\ntriage> ";
		getline(cin, line);
	} while (processLine(line, priQueue));

	// goodbye message
	goodbye();
}

bool processLine(string line, PatientPriorityQueue &priQueue) {
	// get command
	string cmd = delimitBySpace(line);
	if (cmd.length() == 0) {
		cout << "Error: no command given.";
		return false;
	}
	
	// process user input
	if (cmd == "help")
		help();
	else if (cmd == "add")
		addPatientCmd(line, priQueue);
	else if (cmd == "peek")
		peekNextCmd(priQueue);
	else if (cmd == "next")
		removePatientCmd(priQueue);
	else if (cmd == "list")
		showPatientListCmd(priQueue);
	else if (cmd == "load")
		execCommandsFromFileCmd(line, priQueue);
    else if (cmd == "change")
        changeCmd(line, priQueue);
	else if (cmd == "quit")
		return false;
	else
		cout << "Error: unrecognized command: " << cmd << endl;

	return true;
}

void addPatientCmd(string line, PatientPriorityQueue &priQueue) { 
	string priority, name; 

	// get priority and name
	priority = delimitBySpace(line);
	if (priority.length() == 0) {
		cout << "Error: no priority code given.\n";
		return;
	}
	name = line;
	if (name.length() == 0) {
		cout << "Error: no patient name given.\n";
		return;
	}

    // remove leading and trailing whitespace
	priority = removeWhitespace(priority);
    name = removeWhitespace(name);

	// validate priority is between 1 and 4 and add patient
    if (priority == "immediate" || priority == "emergency"
        || priority == "urgent" || priority == "minimal") {
        priQueue.add(priority, name);
        cout << "\nAdded patient \"" << name << "\" to the priority system"
            << endl;
    }
    else
        cout << "Error: invalid priority code (must be 'immediate', 'emergency'"
            << ", 'urgent' or 'minimal'." << endl;
}

void peekNextCmd(PatientPriorityQueue &priQueue) {
    string name = priQueue.peek().to_string();
	cout << "Highest priority patient to be called next: "
        << name.substr(0, name.find_first_of('{') - 1) << endl;
}

void removePatientCmd(PatientPriorityQueue &priQueue) {
	string name = priQueue.remove().to_string();
    cout << "This patient will now be seen: "
        << name.substr(0, name.find_first_of('{') - 1) << endl;
}

void showPatientListCmd(PatientPriorityQueue &priQueue) {
	cout << "# patients waiting: " << priQueue.size() << endl;
	cout << "  Arrival #   Priority Code   Patient Name\n"
		  << "+-----------+---------------+--------------+\n";

    // shows patient detail in heap order
    cout << priQueue.to_string();
}

void execCommandsFromFileCmd(string filename, PatientPriorityQueue &priQueue) {
	ifstream infile;
	string line;

	// open and read from file
	infile.open(filename);
	if (infile) {
		while (getline(infile, line)) {
			cout << "\ntriage> " << line;
			// process file input 
			processLine(line, priQueue);
		} 
	} else {
		cout << "Error: could not open file.\n";
	}
	// close file
	infile.close();
}

void changeCmd(string &line, PatientPriorityQueue &priQueue) {
    string arrivalOrder, priority;
    string changedString;

    arrivalOrder = delimitBySpace(line);
    priority = delimitBySpace(line);

    if (arrivalOrder.empty())
        cout << "Error: No patient id provided" << endl;
    else if (priority.empty())
        cout << "Error: No priority code given" << endl;
    else if (priority != "immediate" || priority != "emergency"
        || priority != "urgent" || priority != "minimal")
        cout << "Error: invalid priority level code" << endl;
    else {
        changedString = priQueue.change(stoi(arrivalOrder), priority);
        cout << changedString << endl;
    }
}

string delimitBySpace(string &s) {
    const char SPACE = ' ';
    size_t pos = 0;
    string result = "";

    pos = s.find(SPACE);
    if (pos == string::npos)
        return s;

    result = s.substr(0, pos);
    s.erase(0, pos + 1);
    return result;
}

void welcome() {
	cout << "Welcome to the hospital triage system." << endl;
}

void goodbye() {
	cout << "Exiting hospital triage system." << endl;
}	

void help() {
	cout << "add <priority-code> <patient-name>\n"
<< "            Adds the patient to the triage system.\n"
<< "            <priority-code> must be one of the 4 accepted priority codes:\n"
<< "                1. immediate 2. emergency 3. urgent 4. minimal\n"
<< "            <patient-name>: patient's full legal name (may contain spaces)\n"
<< "next        Announces the patient to be seen next. Takes into account the\n"
<< "            type of emergency and the patient's arrival order.\n"
<< "peek        Displays the patient that is next in line, but keeps in queue\n"
<< "list        Displays the list of all patients that are still waiting\n"
<< "            in the order that they have arrived.\n"
<< "load <file> Reads the file and executes the command on each line\n"
<< "help        Displays this menu\n"
<< "quit        Exits the program\n";
}

string removeWhitespace(const string &text) {
    stringstream ss;

    size_t begin, end;
    begin = text.find_first_not_of(" \t");
    end = text.find_last_not_of(" \t");

    return text.substr(begin, end - begin + 1);
}