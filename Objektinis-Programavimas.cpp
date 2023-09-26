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
        for (int i = 0; i < 15 && iss >> score; ++i) {
            student.homeworks.push_back(score);
        }

       
        string egz;
        iss >> egz >> student.exam;

        students.push_back(student);
    }

    cout << setw(20) << "Name" << setw(20) << "Surname" << setw(20) << "Final Score" << '\n';
    for (const Student& student : students) {
        double average = 0;
        for (int score : student.homeworks) average += score;
        if (!student.homeworks.empty()) average /= student.homeworks.size();

        
        cout << "Average for " << student.name << ": " << average << endl;

        double finalScore = 0.4 * average + 0.6 * student.exam;

        
        cout << "Final Score before formatting for " << student.name << ": " << finalScore << endl;

        cout << setw(20) << student.name << setw(20) << student.surname << setw(20) << finalScore << '\n';
    }

    return 0;
}


