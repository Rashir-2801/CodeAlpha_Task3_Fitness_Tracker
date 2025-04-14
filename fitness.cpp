#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct Workout {
    string date;
    string type;
    int duration; // in minutes
    int calories;
};

void addWorkout(vector<Workout>& workouts) {
    Workout w;
    cout << "Enter date (YYYY-MM-DD): ";
    cin >> ws; getline(cin, w.date);

    cout << "Enter workout type (e.g., Running, Cycling): ";
    getline(cin, w.type);

    cout << "Enter duration (minutes): ";
    cin >> w.duration;

    cout << "Enter calories burned: ";
    cin >> w.calories;

    workouts.push_back(w);
    cout << "\n Workout added successfully!\n";
}

void viewWorkouts(const vector<Workout>& workouts) {
    if (workouts.empty()) {
        cout << "\n No workouts recorded yet.\n";
        return;
    }

    cout << "\n Workout History:\n";
    cout << "----------------------------\n";
    for (const auto& w : workouts) {
        cout << " Date: " << w.date << "\n";
        cout << " Type: " << w.type << "\n";
        cout << " Duration: " << w.duration << " minutes\n";
        cout << " Calories: " << w.calories << " kcal\n";
        cout << "----------------------------\n";
    }
}

void saveToFile(const vector<Workout>& workouts, const string& filename) {
    ofstream file(filename);
    for (const auto& w : workouts) {
        file << w.date << "|" << w.type << "|" << w.duration << "|" << w.calories << "\n";
    }
    file.close();
}

void loadFromFile(vector<Workout>& workouts, const string& filename) {
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        Workout w;
        size_t pos1 = line.find('|');
        size_t pos2 = line.find('|', pos1 + 1);
        size_t pos3 = line.find('|', pos2 + 1);

        w.date = line.substr(0, pos1);
        w.type = line.substr(pos1 + 1, pos2 - pos1 - 1);
        w.duration = stoi(line.substr(pos2 + 1, pos3 - pos2 - 1));
        w.calories = stoi(line.substr(pos3 + 1));

        workouts.push_back(w);
    }
    file.close();
}

int main() {
    vector<Workout> workouts;
    const string filename = "workouts.txt";
    loadFromFile(workouts, filename);

    int choice;
    do {
        cout << "\n FITNESS TRACKER MENU\n";
        cout << "1. Add Workout\n";
        cout << "2. View Workout History\n";
        cout << "3. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
            case 1: addWorkout(workouts); break;
            case 2: viewWorkouts(workouts); break;
            case 3: saveToFile(workouts, filename);
                    cout << "\n Data saved. Stay healthy! \n";
                    break;
            default: cout << " Invalid option. Try again.\n"; break;
        }
    } while (choice != 3);

    return 0;
}
