#ifndef STUDENTS2_H
#define STUDENTS2_H
#pragma once
#include <string>
#include <vector>

struct Student {
    std::string name;
    std::string surname;
    std::vector<int> homeworks;
    int exam = 0;
    double finalScoreAvg = 0;
    double finalScoreMed = 0;
};

void inputStudentsManually(std::vector<Student>& students);
void displayStudents(const std::vector<Student>& students);
void generateFile(const std::string& filename, int numStudents);
void generateRandomScores(Student& student);
void categorizeStudents(const std::vector<Student>& students, std::vector<Student>& dummies, std::vector<Student>& smart);
void writeToFile(const std::vector<Student>& students, const std::string& filename);
void readFromFile(std::vector<Student>& students, const std::string& filename);
double calculateAverage(const std::vector<int>& grades);
double calculateMedian(std::vector<int> grades);



#endif // STUDENTS2_H
