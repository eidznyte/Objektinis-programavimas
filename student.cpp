#include "student.h"
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cstdlib> 
#include <ctime>

double calculateAverage(const std::vector<int>& scores) {
    double sum = 0;
    for (const int& score : scores) sum += score;
    return scores.empty() ? 0 : sum / scores.size();
}

double calculateMedian(const std::vector<int>& scores) {
    if (scores.empty()) return 0.0;
    std::vector<int> sortedScores = scores;
    std::sort(sortedScores.begin(), sortedScores.end());
    size_t size = sortedScores.size();
    return size % 2 == 0 ? (sortedScores[size / 2 - 1] + sortedScores[size / 2]) / 2.0 : sortedScores[size / 2];
}

void displayStudents(const std::vector<Student>& students) {
    std::cout << std::setw(20) << "Name" << std::setw(20) << "Surname"
        << std::setw(20) << "Final Score(Avg)" << std::setw(20) << "Final Score(Med)" << '\n';
    std::cout << std::fixed << std::setprecision(2);

    for (const Student& student : students) {
        double finalScoreAvg = 0.4 * calculateAverage(student.homeworks) + 0.6 * student.exam;
        double finalScoreMed = 0.4 * calculateMedian(student.homeworks) + 0.6 * student.exam;
        std::cout << std::setw(20) << student.name << std::setw(20) << student.surname
            << std::setw(20) << finalScoreAvg << std::setw(20) << finalScoreMed << '\n';
    }
}
void inputStudentsManually(std::vector<Student>& students) {
    std::cout << "Enter the number of students: ";
    int numStudents;
    while (!(std::cin >> numStudents) || numStudents <= 0) {
        std::cerr << "Invalid input! Please enter a positive number for the number of students.\n";
        std::cin.clear(); 
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
    }
    std::cin.ignore(); 

    for (int i = 0; i < numStudents; ++i) {
        Student student;
        std::cout << "Enter name and surname of student " << i + 1 << ": ";
        std::cin >> student.name >> student.surname;
        std::cin.ignore(); 

        std::cout << "Do you want to generate random scores? (y/n): ";
        char choice;
        std::cin >> choice;
        std::cin.ignore(); 

        if (choice == 'y' || choice == 'Y') {
            generateRandomScores(student);
        }
        else {
            std::cout << "Enter homework scores (end the homework scores with an empty line):\n";
            while (true) {
                std::string line;
                std::getline(std::cin, line);
                if (line.empty()) break; 

                std::istringstream iss(line);
                int score;
                while (iss >> score) {
                    if (score < 0 || score > 10) {
                        std::cerr << "Invalid score " << score << ", please enter scores between 0 and 10.\n";
                        return;
                    }
                    student.homeworks.push_back(score);
                }
                if (iss.fail() && !iss.eof()) {
                    std::cerr << "Invalid input detected! Please enter only numeric values for scores.\n";
                    return;
                }
            }
            std::cout << "Enter exam score: ";
            while (!(std::cin >> student.exam) || student.exam < 0 || student.exam > 10) {
                std::cerr << "Invalid input! Please enter a numeric value between 0 and 10 for the exam score.\n";
                std::cin.clear(); 
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            }
            std::cin.ignore(); 
        }
        students.push_back(student);
    }
}


void generateRandomScores(Student& student) {
    srand(static_cast<unsigned>(time(nullptr))); 

    int numHomeworks = rand() % 10 + 1; 
    for (int i = 0; i < numHomeworks; ++i) {
        student.homeworks.push_back(rand() % 11); 
    }
    student.exam = rand() % 11; 
}
void readStudentsFromFile(std::vector<Student>& students, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file " + filename);
    }

    std::string line;
    std::getline(file, line); 

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        Student student;

        if (!(iss >> student.name >> student.surname)) {
            throw std::runtime_error("Error reading name or surname from the file");
        }

        std::string score;
        while (iss >> score) {
            try {
                size_t pos;
                int num = std::stoi(score, &pos);
                if (pos < score.size() || num < 0 || num > 10)
                    throw std::invalid_argument("Invalid character in score or score out of range");

                if (iss.eof()) student.exam = num;
                else student.homeworks.push_back(num);

            }
            catch (const std::exception& e) {
                throw std::runtime_error("Error reading scores from the file: " + std::string(e.what()));
            }
        }

        students.push_back(student);
    }

    file.close();
}
