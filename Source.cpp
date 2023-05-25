#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Subscriber {
    string name;
    string phoneNumber;
};

struct CallRecord {
    string phoneNumber;
    int duration;
};

struct TelephoneDirectory {
    Subscriber* subscribers;
    int count;
};

void createTelephoneDirectory(TelephoneDirectory& directory) {
    cout << "Enter the number of subscribers: ";
    cin >> directory.count;
    cin.ignore(); // Ignore the newline character

    directory.subscribers = new Subscriber[directory.count];

    for (int i = 0; i < directory.count; i++) {
        cout << "Subscriber " << i + 1 << " name: ";
        getline(cin, directory.subscribers[i].name);

        cout << "Subscriber " << i + 1 << " phone number: ";
        getline(cin, directory.subscribers[i].phoneNumber);
    }
}

void printTelephoneDirectory(const TelephoneDirectory& directory) {
    cout << "Telephone Directory:" << endl;
    for (int i = 0; i < directory.count; i++) {
        cout << "Subscriber " << i + 1 << ":" << endl;
        cout << "Name: " << directory.subscribers[i].name << endl;
        cout << "Phone Number: " << directory.subscribers[i].phoneNumber << endl;
    }
}

void saveTelephoneDirectory(const TelephoneDirectory& directory, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        file << directory.count << endl;
        for (int i = 0; i < directory.count; i++) {
            file << directory.subscribers[i].name << endl;
            file << directory.subscribers[i].phoneNumber << endl;
        }
        file.close();
        cout << "Telephone directory saved to " << filename << endl;
    }
    else {
        cout << "Error opening file " << filename << " for writing." << endl;
    }
}

void loadTelephoneDirectory(TelephoneDirectory& directory, const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        file >> directory.count;
        file.ignore(); // Ignore the newline character

        directory.subscribers = new Subscriber[directory.count];

        for (int i = 0; i < directory.count; i++) {
            getline(file, directory.subscribers[i].name);
            getline(file, directory.subscribers[i].phoneNumber);
        }
        file.close();
        cout << "Telephone directory loaded from " << filename << endl;
    }
    else {
        cout << "Error opening file " << filename << " for reading." << endl;
    }
}

void makePhoneCall(const TelephoneDirectory& directory) {
    string phoneNumber;
    int duration;

    cout << "Enter phone number: ";
    getline(cin, phoneNumber);

    cout << "Enter call duration (in minutes): ";
    cin >> duration;

    // Check if the phone number exists in the directory
    bool found = false;
    for (int i = 0; i < directory.count; i++) {
        if (directory.subscribers[i].phoneNumber == phoneNumber) {
            found = true;
            break;
        }
    }

    if (found) {
        if (duration > 100) {
            cout << "Payment required for phone call with duration > 100 minutes." << endl;
        }
        else {
            cout << "there is no payment required for this phone call." << endl;
        }
    }
    else {
        cout << "Phone number not found in the directory." << endl;
    }
}

int main() {
    TelephoneDirectory directory;
    string filename;

    int choice;
    do {
        cout << "Telephone Directory Menu:" << endl;
        cout << "1. Create Telephone Directory" << endl;
        cout << "2. Print Telephone Directory" << endl;
        cout << "3. Save Telephone Directory to File" << endl;
        cout << "4. Load Telephone Directory from File" << endl;
        cout << "5. Make Phone Call" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice (1-6): ";
        cin >> choice;
        cin.ignore(); // Ignore the newline character

        switch (choice) {
        case 1:
            createTelephoneDirectory(directory);
            break;
        case 2:
            printTelephoneDirectory(directory);
            break;
        case 3:
            cout << "Enter filename to save: ";
            getline(cin, filename);
            saveTelephoneDirectory(directory, filename);
            break;
        case 4:
            cout << "Enter filename to load: ";
            getline(cin, filename);
            loadTelephoneDirectory(directory, filename);
            break;
        case 5:
            makePhoneCall(directory);
            break;
        case 6:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice. Please enter a number between 1 and 6." << endl;
            break;
        }

        cout << endl;
    } while (choice != 6);

    delete[] directory.subscribers; // Free allocated memory

    return 0;
}