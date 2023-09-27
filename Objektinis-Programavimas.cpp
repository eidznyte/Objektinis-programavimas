#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
#include <algorithm> 
#include <random> 
#include <ctime> 

using namespace std;

struct Student {
    string name;
    string surname;
    vector<int> homeworks;
    int exam;
};

double calculateMedian(const vector<int>& scores) {
    if (scores.empty()) return 0.0;

    vector<int> sortedScores = scores;
    sort(sortedScores.begin(), sortedScores.end());

    size_t size = sortedScores.size();
    if (size % 2 == 0) {
        return (sortedScores[size / 2 - 1] + sortedScores[size / 2]) / 2.0;
    }
    else {
        return sortedScores[size / 2];
    }
}

int main() {
    vector<Student> students;

    cout << "Press 1 to input your own data, 2 to read data from the file or 3 to randomly generate data: ";
    int choice;
    cin >> choice;
    cin.ignore(); 

    if (choice == 1) {
        
        cout << "Enter student's name, surname, homework scores, and finally the exam score.\n";
        cout << "Enter scores (0-10) (end with a non-numeric character like 'e' or just press enter): \n";

        Student student;
        cout << "Name: ";
        getline(cin, student.name);

        cout << "Surname: ";
        getline(cin, student.surname);

        cout << "Enter homework scores separated by space (0-10), and press Enter when done: ";
        string line;
        getline(cin, line);

        istringstream iss(line);
        string token;
        while (iss >> token) {
            try {
                size_t pos; 
                int score = stoi(token, &pos); 

                if (pos < token.length()) 
                    throw invalid_argument("non-numeric character found");

                if (score < 0 || score > 10) 
                    throw out_of_range("score out of range");

                student.homeworks.push_back(score);
            }
            catch (const exception& e) {
                cerr << "Invalid input detected: " << token << ". Please enter only numeric scores between 0 and 10.\n";
                return 1;
            }
        }

        if (student.homeworks.empty()) {
            cerr << "No valid scores were entered. Exiting.\n";
            return 1;
        }

        cout << "Enter exam score (0-10): ";
        cin >> line;
        try {
            size_t pos;
            student.exam = stoi(line, &pos);
            if (pos < line.length() || student.exam < 0 || student.exam > 10)
                throw invalid_argument("invalid input");
        }
        catch (const exception& e) {
            cerr << "Invalid input detected for exam score. Please enter a numeric score between 0 and 10.\n";
            return 1;
        }

        students.push_back(student);
    }
    else if (choice == 2) {
        
        ifstream file("students.txt");

        if (!file.is_open()) {
            cerr << "Unable to open file." << endl;
            return 1;
        }

        string line;
        getline(file, line);

        while (getline(file, line)) {
            if (line.empty()) continue;

            Student student;
            istringstream iss(line);
            iss >> student.name >> student.surname;

            int score;
            while (iss >> score) student.homeworks.push_back(score);

            if (!student.homeworks.empty()) {
                student.exam = student.homeworks.back();
                student.homeworks.pop_back();
            }
            else {
                cerr << "No scores were read from file. Exiting." << endl;
                return 1;
            }

            students.push_back(student);
        }
    }

 else if (choice == 3) {
   
    default_random_engine generator(time(0)); 
    uniform_int_distribution<int> distribution(1, 10); 

    cout << "Enter the number of students to generate data for: ";
    int numStudents;
    cin >> numStudents;

    for (int i = 0; i < numStudents; ++i) {
        Student student;
        student.name = "Name" + to_string(i + 1);
        student.surname = "Surname" + to_string(i + 1);

        cout << "Enter the number of homeworks for " << student.name << " " << student.surname << ": ";
        int numHomeworks;
        cin >> numHomeworks;

        for (int j = 0; j < numHomeworks; ++j)
            student.homeworks.push_back(distribution(generator));

        student.exam = distribution(generator); 

        students.push_back(student);
    }

    }
 else {
        cerr << "Invalid choice. Exiting." << endl;
        return 1;
        }

    cout << "Press 1 to calculate the final score with the average of homework scores or 2 to use the median: ";
    int calcChoice;
    cin >> calcChoice;

    cout << setw(20) << "Name" << setw(20) << "Surname" << setw(20) << "Final Score" << '\n';
    cout << fixed << setprecision(2);
    for (const Student& student : students) {
        double finalScore;
        if (calcChoice == 1) {
            double average = 0;
            for (int score : student.homeworks) average += score;
            if (!student.homeworks.empty()) average /= student.homeworks.size();
            finalScore = 0.4 * average + 0.6 * student.exam;
        }
        else if (calcChoice == 2) {
            double median = calculateMedian(student.homeworks);
            finalScore = 0.4 * median + 0.6 * student.exam;
        }
        else {
            cerr << "Invalid calculation choice. Exiting." << endl;
            return 1;
        }

        cout << setw(20) << student.name << setw(20) << student.surname << setw(20) << finalScore << '\n';
    }

    return 0;
}
