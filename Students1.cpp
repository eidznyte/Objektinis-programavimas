#include "students1.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cstdlib>
#include <iomanip>
#include <stdexcept>
#include <limits>
#include <chrono>
#include <list>
std::chrono::high_resolution_clock::time_point start;
std::chrono::high_resolution_clock::time_point end;


void displayDuration(const std::chrono::high_resolution_clock::time_point& start,
    const std::chrono::high_resolution_clock::time_point& end,
    const std::string& operationName)
{
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << operationName << " took " << duration << " milliseconds." << std::endl;
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

void readFromFile(std::vector<Student>& students, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open the file '" << filename << "'\n";
        return;
    }

    std::string line;
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        Student student;

        if (!(iss >> student.name >> student.surname)) { break; }

        for (int i = 0; i < 14; i++) {
            int score;
            if (iss >> score) {
                student.homeworks.push_back(score);
            }
        }
        if (iss >> student.exam) {
            student.finalScoreAvg = 0.4 * calculateAverage(student.homeworks) + 0.6 * student.exam;
            student.finalScoreMed = 0.4 * calculateMedian(student.homeworks) + 0.6 * student.exam;
            students.push_back(student);
        }
    }
    file.close();
}

void readFromFile(std::list<Student>& students, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open the file '" << filename << "'\n";
        return;
    }

    std::string line;
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        Student student;

        if (!(iss >> student.name >> student.surname)) { break; }

        for (int i = 0; i < 14; i++) {
            int score;
            if (iss >> score) {
                student.homeworks.push_back(score);
            }
        }
        if (iss >> student.exam) {
            student.finalScoreAvg = 0.4 * calculateAverage(student.homeworks) + 0.6 * student.exam;
            student.finalScoreMed = 0.4 * calculateMedian(student.homeworks) + 0.6 * student.exam;
            students.push_back(student);
        }
    }
    file.close();
}

void inputStudentsManually(std::vector<Student>& students) {
    std::cout << "Enter the number of students: ";
    int numStudents;
    while (!(std::cin >> numStudents) || numStudents <= 0) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input! Please enter a positive integer for the number of students: ";
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
            std::string line;
            std::cout << "Enter homework scores (end the homework scores with an empty line):\n";
            while (true) {
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


                if (!iss.eof()) {
                    std::cerr << "Invalid input detected. Please only enter numbers for scores.\n";
                    return;
                }
            }
            std::cout << "Enter exam score: ";
            while (!(std::cin >> student.exam) || student.exam < 0 || student.exam > 10) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input! Please enter a number between 0 and 10 for the exam score: ";
            }
            std::cin.ignore();
        }

        student.finalScoreAvg = 0.4 * calculateAverage(student.homeworks) + 0.6 * student.exam;
        student.finalScoreMed = 0.4 * calculateMedian(student.homeworks) + 0.6 * student.exam;

        students.push_back(student);
    }
}

void inputStudentsManually(std::list<Student>& students) {
    std::cout << "Enter the number of students: ";
    int numStudents;
    while (!(std::cin >> numStudents) || numStudents <= 0) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input! Please enter a positive integer for the number of students: ";
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
            std::string line;
            std::cout << "Enter homework scores (end the homework scores with an empty line):\n";
            while (true) {
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


                if (!iss.eof()) {
                    std::cerr << "Invalid input detected. Please only enter numbers for scores.\n";
                    return;
                }
            }
            std::cout << "Enter exam score: ";
            while (!(std::cin >> student.exam) || student.exam < 0 || student.exam > 10) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input! Please enter a number between 0 and 10 for the exam score: ";
            }
            std::cin.ignore();
        }

        student.finalScoreAvg = 0.4 * calculateAverage(student.homeworks) + 0.6 * student.exam;
        student.finalScoreMed = 0.4 * calculateMedian(student.homeworks) + 0.6 * student.exam;

        students.push_back(student);

    }
}

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

void displayStudents(const std::list<Student>& students) {
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


    outFile << std::setw(15) << "Vardas"
        << std::setw(15) << "Pavarde"
        << std::setw(25) << "ND scores"
        << std::setw(30) << "Egz." << std::endl;

    for (int i = 1; i <= numStudents; i++) {
        outFile << std::setw(15) << ("Vardas" + std::to_string(i))
            << std::setw(15) << ("Pavarde" + std::to_string(i));

        for (int j = 0; j < 14; j++) {
            outFile << std::setw(3) << (rand() % 10 + 1);
        }

        outFile << std::setw(10) << (rand() % 10 + 1) << std::endl;
    }

    outFile.close();
}

void generateRandomScores(Student& student) {
    const int numHomeworks = rand() % 20 + 1;
    for (int i = 0; i < numHomeworks; ++i) {
        student.homeworks.push_back(rand() % 10 + 1);
    }
    student.exam = rand() % 10 + 1;
}

void categorizeStudents(std::vector<Student>& students, std::vector<Student>& dummies) {
    auto start = std::chrono::high_resolution_clock::now();

    for (auto it = students.begin(); it != students.end();) {
        if (it->finalScoreAvg < 5.0) {
            dummies.push_back(*it);
            it = students.erase(it); 
        }
        else {
            ++it; 
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    displayDuration(start, end, "Categorizing students with vectors");
}

void categorizeStudents(std::list<Student>& students, std::list<Student>& dummies) {
    auto start = std::chrono::high_resolution_clock::now();

    for (auto it = students.begin(); it != students.end();) {
        if (it->finalScoreAvg < 5.0) {
            dummies.push_back(*it);
            it = students.erase(it);
        }
        else {
            ++it;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    displayDuration(start, end, "Categorizing students with lists");
}

void writeToFile(const std::vector<Student>& students, const std::string& filename) {
    start = std::chrono::high_resolution_clock::now();
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open the file '" << filename << "'\n";
        return;
    }

    file << std::setw(15) << "Name"
        << std::setw(15) << "Surname"
        << std::setw(20) << "Final Score(Avg)"
        << std::setw(20) << "Final Score(Med)" << std::endl;
    file << std::string(70, '-') << std::endl;

    for (const Student& student : students) {
        file << std::setw(15) << student.name
            << std::setw(15) << student.surname
            << std::setw(20) << std::fixed << std::setprecision(2) << student.finalScoreAvg
            << std::setw(20) << std::fixed << std::setprecision(2) << student.finalScoreMed << std::endl;
    }
    end = std::chrono::high_resolution_clock::now();
    displayDuration(start, end, "Writing to file");
    file.close();
}

void writeToFile(const std::list<Student>& students, const std::string& filename) {
    auto start = std::chrono::high_resolution_clock::now();
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Failed to open the file '" << filename << "'\n";
        return;
    }

    file << std::setw(15) << "Name"
        << std::setw(15) << "Surname"
        << std::setw(20) << "Final Score(Avg)"
        << std::setw(20) << "Final Score(Med)" << std::endl;
    file << std::string(70, '-') << std::endl;

    if (students.empty()) {
        std::cerr << "No students data to write.\n";
        file.close();
        return;
    }

    for (const Student& student : students) {
        if (file.fail()) {
            std::cerr << "Failed to write data to the file.\n";
            break;
        }
        file << std::setw(15) << student.name
            << std::setw(15) << student.surname
            << std::setw(20) << std::fixed << std::setprecision(2) << student.finalScoreAvg
            << std::setw(20) << std::fixed << std::setprecision(2) << student.finalScoreMed << std::endl;
    }

    auto end = std::chrono::high_resolution_clock::now();
    displayDuration(start, end, "Writing to file");
    file.close();
}
