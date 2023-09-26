#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream> 

using namespace std;

struct Student {
    string name;
    string surname;
    vector<int> homeworks;
    int exam;
};

int main() {
    ifstream file("students.txt");

    if (!file.is_open()) {
        cerr << "Unable to open file." << endl;
        return 1;
    }

    vector<Student> students;
    string line;

    
    getline(file, line); 

    
    while (getline(file, line)) {
        if (line.empty()) continue; 

        Student student;
        istringstream iss(line); 

        
        iss >> student.name >> student.surname;

        
        int score;
        while (iss >> score) {
            student.homeworks.push_back(score);
        }

        if (!student.homeworks.empty()) {
            student.exam = student.homeworks.back(); 
            student.homeworks.pop_back(); 
        }
        else {
            cerr << "Error: couldn't read any scores for " << student.name << " " << student.surname << ". Aborting." << endl;
            return 1;
        }

        students.push_back(student);
    }

    cout << setw(20) << "Name" << setw(20) << "Surname" << setw(20) << "Final Score" << '\n';
    cout << fixed << setprecision(2); 
    for (const Student& student : students) {
        double average = 0;
        for (int score : student.homeworks) average += score;
        if (!student.homeworks.empty()) average /= student.homeworks.size();

        double finalScore = 0.4 * average + 0.6 * student.exam;
        cout << setw(20) << student.name << setw(20) << student.surname << setw(20) << finalScore << '\n';
    }

    return 0;
}


