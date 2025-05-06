//Hospital priority queue

#include <iostream>
#include <queue>
#include <string>

using namespace std;

// Define the structure of a patient
struct Patient {
    string name;
    string type;   // Serious, Non-serious, General Checkup
    int priority;  // Priority (higher value means higher priority)

    // Constructor to initialize the patient details
    Patient(string n, string t, int p) : name(n), type(t), priority(p) {}

    // Overload the comparison operator to prioritize by the highest priority
    bool operator<(const Patient &other) const {
        return priority < other.priority; // In max-heap, higher priority will come first
    }
};

int main() {
    // Create a priority queue to manage patients with the highest priority patient first
    priority_queue<Patient> pq;

    int numPatients;
    cout << "Enter the number of patients: ";
    cin >> numPatients;

    // Clear the input buffer after reading numPatients to handle getline properly
    cin.ignore();

    // Input patient details
    for (int i = 0; i < numPatients; ++i) {
        string name, type;
        int priority;

        cout << "\nEnter details for patient " << (i + 1) << endl;
        cout << "Enter patient's name: ";
        getline(cin, name);  // Read the entire line for patient's name

        cout << "Enter patient's type (Serious, Non-serious, General Checkup): ";
        getline(cin, type);  // Read the entire line for patient's type

        // Assign priority based on type
        if (type == "Serious") {
            priority = 3;
        } else if (type == "Non-serious") {
            priority = 2;
        } else if (type == "General Checkup") {
            priority = 1;
        } else {
            cout << "Invalid type! Defaulting to General Checkup (Priority 1).\n";
            priority = 1;
        }

        // Add patient to the priority queue
        pq.push(Patient(name, type, priority));
    }

    // Serving the patients based on priority
    cout << "\nServing patients based on priority (Highest to Lowest):\n";
    while (!pq.empty()) {
        Patient current = pq.top();
        pq.pop();

        cout << "Serving " << current.name << " - Type: " << current.type 
             << " (Priority: " << current.priority << ")\n";
    }

    return 0;
}
