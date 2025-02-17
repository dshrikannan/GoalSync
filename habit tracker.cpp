#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

struct Habit {
    string name;
    int completedDays;
};

// Global vector to store habits
vector<Habit> habits;

// Function to load habits from a file
void loadHabits() {
    ifstream file("habits.txt");
    if (file.is_open()) {
        Habit h;
        while (file >> h.name >> h.completedDays) {
            habits.push_back(h);
        }
        file.close();
    }
}

// Function to save habits to a file
void saveHabits() {
    ofstream file("habits.txt");
    for (const auto &h : habits) {
        file << h.name << " " << h.completedDays << endl;
    }
    file.close();
}

// Function to add a new habit
void addHabit() {
    Habit h;
    cout << "Enter habit name (single word only): ";
    cin >> h.name;
    h.completedDays = 0;
    habits.push_back(h);
    saveHabits();
    cout << "Habit added successfully!\n";
}

// Function to mark a habit as completed
void markCompleted() {
    if (habits.empty()) {
        cout << "No habits to mark as completed!\n";
        return;
    }

    cout << "Your Habits:\n";
    for (size_t i = 0; i < habits.size(); i++) {
        cout << i + 1 << ". " << habits[i].name << " (Completed: " << habits[i].completedDays << " days)\n";
    }

    int choice;
    cout << "Enter habit number to mark as completed: ";
    cin >> choice;

    if (choice > 0 && choice <= static_cast<int>(habits.size())) {
        habits[choice - 1].completedDays++;
        saveHabits();
        cout << "Marked as completed!\n";
    } else {
        cout << "Invalid choice!\n";
    }
}

// Function to view progress
void viewProgress() {
    if (habits.empty()) {
        cout << "No habits to display!\n";
        return;
    }

    cout << "\nHabit Progress:\n";
    cout << setw(20) << left << "Habit" << "Completed Days\n";
    cout << "--------------------------------\n";

    for (const auto &h : habits) {
        cout << setw(20) << left << h.name << h.completedDays << endl;
    }
}

// Main function
int main() {
    loadHabits();
    int choice;
    
    do {
        cout << "\nHabit Tracker Menu\n";
        cout << "1. Add Habit\n";
        cout << "2. Mark Habit as Completed\n";
        cout << "3. View Progress\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addHabit(); break;
            case 2: markCompleted(); break;
            case 3: viewProgress(); break;
            case 4: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 4);

    return 0;
}
