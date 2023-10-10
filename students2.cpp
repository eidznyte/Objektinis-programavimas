#include "students2.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cstdlib>
#include <iomanip>
#include <stdexcept>

// Read from file
void readFromFile(std::vector<Student>& students) {
    std::ifstream file("students.txt");
    if (!file.is_open()) {
        std::cerr << "Failed to open the file 'students.txt'\n";
        return;
    }

    std::string line;
    std::getline(file, line);  // Discard the header line

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        Student student;

        if (!(iss >> student.name >> student.surname)) { break; }  // Error or end of file

        int score;
        while (iss >> score && student.homeworks.size() < line.size() - 2) {
            student.homeworks.push_back(score);
        }
        student.exam = score;  // The last score read will be the exam score

        student.finalScoreAvg = 0.4 * calculateAverage(student.homeworks) + 0.6 * student.exam;
        student.finalScoreMed = 0.4 * calculateMedian(student.homeworks) + 0.6 * student.exam;

        students.push_back(student);
    }

    file.close();
}

// Input students manually
void inputStudentsManually(std::vector<Student>& students) {
    std::cout << "Enter the number of students: ";
    int numStudents;
    while (!(std::cin >> numStudents) || numStudents <= 0) {
        std::cin.clear(); // Clear the error flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
        std::cout << "Invalid input! Please enter a positive integer for the number of students: ";
    }
    std::cin.ignore(); // To remove the newline character from the buffer

    for (int i = 0; i < numStudents; ++i) {
        Student student;
        std::cout << "Enter name and surname of student " << i + 1 << ": ";
        std::cin >> student.name >> student.surname;
        std::cin.ignore(); // To remove the newline character from the buffer

        std::cout << "Do you want to generate random scores? (y/n): ";
        char choice;
        std::cin >> choice;
        std::cin.ignore(); // To remove the newline character from the buffer

        if (choice == 'y' || choice == 'Y') {
            generateRandomScores(student);
        }
        else {
            std::string line;
            std::cout << "Enter homework scores followed by exam score (end the homework scores with an empty line):\n";
            while (true) {
                std::getline(std::cin, line);
                if (line.empty()) break; // Stop when an empty line is encountered

                std::istringstream iss(line);
                int score;
                while (iss >> score) {
                    if (score < 0 || score > 10) {
                        std::cerr << "Invalid score " << score << ", please enter scores between 0 and 10.\n";
                        return; // We exit if there's an invalid score. If you want to continue and ask again, you'd need a loop here.
                    }
                    student.homeworks.push_back(score);
                }

                // Check for any leftover characters in the stream (which would indicate non-numeric input)
                if (!iss.eof()) {
                    std::cerr << "Invalid input detected. Please only enter numbers for scores.\n";
                    return;
                }
            }
            std::cout << "Enter exam score: ";
            while (!(std::cin >> student.exam) || student.exam < 0 || student.exam > 10) {
                std::cin.clear(); // Clear the error flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
                std::cout << "Invalid input! Please enter a number between 0 and 10 for the exam score: ";
            }
            std::cin.ignore(); // To remove the newline character from the buffer
        }
        students.push_back(student);
    }
}


// Display students
void displayStudents(const std::vector<Student>& students) {
    std::cout << std::setw(15) << "Name"
        << std::setw(15) << "Surname"
        << std::setw(20) << "Final Score(Avg)"
        << std::setw(20) << "Final Score(Med)" << std::endl;
    std::cout << std::string(70, '-') << std::endl;

    for (const Student& student : students) {
        std::cout << std::setw(15) << student.name
            << std::setw(15) << student.surname
            << std::setw(20) << std::fixed << std::setprecision(2) << student.finalScoreAvg
            << std::setw(20) << std::fixed << std::setprecision(2) << student.finalScoreMed << std::endl;
    }
}

void generateFile(const std::string& filename, int numStudents) {
    std::ofstream outFile(filename);
    if (!outFile) {
        std::cerr << "Failed to create file: " << filename << std::endl;
        return;
    }

    // Header line
    outFile << std::setw(15) << "Vardas"
        << std::setw(15) << "Pavarde"
        << std::setw(100) << "ND scores"  // Adjust width as necessary
        << std::setw(10) << "Egz." << std::endl;

    for (int i = 1; i <= numStudents; i++) {
        outFile << std::setw(15) << ("Vardas" + std::to_string(i))
            << std::setw(15) << ("Pavarde" + std::to_string(i));

        for (int j = 0; j < 14; j++) {
            outFile << std::setw(3) << (rand() % 10 + 1);  // Random scores between 1 and 10
        }

        outFile << std::setw(10) << (rand() % 10 + 1) << std::endl;  // Random exam score between 1 and 10
    }

    outFile.close();
}

double calculateAverage(const std::vector<int>& grades) {
    double sum = 0;
    for (int grade : grades) {
        sum += grade;
    }
    return grades.empty() ? 0 : sum / grades.size();
}

double calculateMedian(std::vector<int> grades) {
    size_t size = grades.size();
    if (size == 0) return 0;

    sort(grades.begin(), grades.end());
    size_t mid = size / 2;

    return size % 2 == 0 ? (grades[mid - 1] + grades[mid]) / 2.0 : grades[mid];
}

void generateRandomScores(Student& student) {
    const int numHomeworks = rand() % 20 + 1;  // Random number of homeworks between 1 and 20
    for (int i = 0; i < numHomeworks; ++i) {
        student.homeworks.push_back(rand() % 10 + 1);  // Scores between 1 and 10
    }
    student.exam = rand() % 10 + 1;  // Exam score between 1 and 10
}
