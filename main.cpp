#include <iostream>
using namespace std;

const int maxContacts = 100;
const int maxNameLen = 50;
const int maxPhoneLen = 15;
const int maxAddressLen = 100;
const int maxEmailLen = 50;

struct Contact {
    char name[maxNameLen];
    char phone[maxPhoneLen];
    char address[maxAddressLen];
    char email[maxEmailLen];
};

bool isValidPhone(const char phone[]) {
    int len = 0;
    if (phone[0] != '0') {
        return false;
    }
    while (phone[len] != '\0') {
        if (phone[len] < '0' || phone[len] > '9') {
            return false;
        }
        len++;
    }
    return len == 11;
}

bool isValidEmail(const char email[]) {
    int atPos = -1, dotPos = -1, len = 0;
    for (int i = 0; email[i] != '\0'; ++i) {
        if (email[i] == '@') {
            atPos = i;
        } else if (email[i] == '.' && atPos != -1) {
            dotPos = i;
        }
        len++;
    }
    return atPos != -1 && dotPos > atPos && dotPos < len - 1;
}

void addContact(Contact contacts[], int &cnt) {
    if (cnt >= maxContacts) {
        cout << "Contact list is full. Cannot add more contacts.\n";
        return;
    }

    cout << "\n--- Add New Contact ---\n";
    cout << "Enter name: ";
    cin.ignore();
    cin.getline(contacts[cnt].name, maxNameLen);

    do {
        cout << "Enter phone number (11 digits, starting with 0): ";
        cin.getline(contacts[cnt].phone, maxPhoneLen);
        if (!isValidPhone(contacts[cnt].phone)) {
            cout << "Invalid phone number. Please try again.\n";
        }
    } while (!isValidPhone(contacts[cnt].phone));

    cout << "Enter address: ";
    cin.getline(contacts[cnt].address, maxAddressLen);

    do {
        cout << "Enter email (must contain '@' and end with '.com'): ";
        cin.getline(contacts[cnt].email, maxEmailLen);
        if (!isValidEmail(contacts[cnt].email)) {
            cout << "Invalid email. Please try again.\n";
        }
    } while (!isValidEmail(contacts[cnt].email));

    cnt++;
    cout << "Contact added successfully!\n";
}

void listContacts(const Contact contacts[], int cnt) {
    if (cnt == 0) {
        cout << "No contacts to display.\n";
        return;
    }

    cout << "\n--- Contact List ---\n";
    for (int i = 0; i < cnt; ++i) {
        cout << "Contact " << i + 1 << ":\n";
        cout << "Name: " << contacts[i].name << "\n";
        cout << "Phone: " << contacts[i].phone << "\n";
        cout << "Address: " << contacts[i].address << "\n";
        cout << "Email: " << contacts[i].email << "\n";
        cout << "--------------------------\n";
    }
}

void searchContact(const Contact contacts[], int cnt) {
    char phone[maxPhoneLen];
    cout << "\n--- Search Contact ---\n";
    cout << "Enter phone number to search: ";
    cin.ignore();
    cin.getline(phone, maxPhoneLen);

    for (int i = 0; i < cnt; ++i) {
        bool match = true;
        for (int j = 0; phone[j] != '\0' || contacts[i].phone[j] != '\0'; ++j) {
            if (phone[j] != contacts[i].phone[j]) {
                match = false;
                break;
            }
        }
        if (match) {
            cout << "Contact found:\n";
            cout << "Name: " << contacts[i].name << "\n";
            cout << "Phone: " << contacts[i].phone << "\n";
            cout << "Address: " << contacts[i].address << "\n";
            cout << "Email: " << contacts[i].email << "\n";
            return;
        }
    }
    cout << "Contact not found.\n";
}

void deleteContact(Contact contacts[], int &cnt) {
    char phone[maxPhoneLen];
    cout << "\n--- Delete Contact ---\n";
    cout << "Enter phone number to delete: ";
    cin.ignore();
    cin.getline(phone, maxPhoneLen);

    for (int i = 0; i < cnt; ++i) {
        bool match = true;
        for (int j = 0; phone[j] != '\0' || contacts[i].phone[j] != '\0'; ++j) {
            if (phone[j] != contacts[i].phone[j]) {
                match = false;
                break;
            }
        }
        if (match) {
            for (int k = i; k < cnt - 1; ++k) {
                contacts[k] = contacts[k + 1];
            }
            cnt--;
            cout << "Contact deleted successfully.\n";
            return;
        }
    }
    cout << "Contact not found.\n";
}

void editContact(Contact contacts[], int cnt) {
    char phone[maxPhoneLen];
    cout << "\n--- Edit Contact ---\n";
    cout << "Enter phone number to edit: ";
    cin.ignore();
    cin.getline(phone, maxPhoneLen);

    for (int i = 0; i < cnt; ++i) {
        bool match = true;
        for (int j = 0; phone[j] != '\0' || contacts[i].phone[j] != '\0'; ++j) {
            if (phone[j] != contacts[i].phone[j]) {
                match = false;
                break;
            }
        }
        if (match) {
            cout << "Editing contact:\n";

            cout << "Enter new name: ";
            cin.getline(contacts[i].name, maxNameLen);

            do {
                cout << "Enter new phone number (11 digits, starting with 0): ";
                cin.getline(contacts[i].phone, maxPhoneLen);
                if (!isValidPhone(contacts[i].phone)) {
                    cout << "Invalid phone number. Please try again.\n";
                }
            } while (!isValidPhone(contacts[i].phone));

            cout << "Enter new address: ";
            cin.getline(contacts[i].address, maxAddressLen);

            do {
                cout << "Enter new email (must contain '@' and end with '.com'): ";
                cin.getline(contacts[i].email, maxEmailLen);
                if (!isValidEmail(contacts[i].email)) {
                    cout << "Invalid email. Please try again.\n";
                }
            } while (!isValidEmail(contacts[i].email));

            cout << "Contact updated successfully.\n";
            return;
        }
    }
    cout << "Contact not found.\n";
}

int main() {
    Contact contacts[maxContacts];
    int contactCount = 0;
    int choice;

    cout << "\n*** Welcome to the Contact Management System ***\n";

    do {
        cout << "\n--- Main Menu ---\n";
        cout << "1. Add New Contact\n";
        cout << "2. List All Contacts\n";
        cout << "3. Search for a Contact\n";
        cout << "4. Delete a Contact\n";
        cout << "5. Edit a Contact\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addContact(contacts, contactCount);
                break;
            case 2:
                listContacts(contacts, contactCount);
                break;
            case 3:
                searchContact(contacts, contactCount);
                break;
            case 4:
                deleteContact(contacts, contactCount);
                break;
            case 5:
                editContact(contacts, contactCount);
                break;
            case 6:
                cout << "Exiting the program. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}
