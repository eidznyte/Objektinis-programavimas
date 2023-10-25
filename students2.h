#ifndef STUDENTS2_H
#define STUDENTS2_H
#pragma once
#include <string>
#include <vector>
#include <list>

struct Student {
    std::string name;
    std::string surname;
    std::vector<int> homeworks;
    int exam = 0;
    double finalScoreAvg = 0;
    double finalScoreMed = 0;
};

// Choose a container type. Uncomment one line based on what you want to test.
 using StudentsContainer = std::vector<Student>;
 //using StudentsContainer = std::list<Student>;

void inputStudentsManually(StudentsContainer& students);
void displayStudents(const StudentsContainer& students);
void generateFile(const std::string& filename, int numStudents);
void generateRandomScores(Student& student);
void categorizeStudents(const StudentsContainer& students, StudentsContainer& dummies, StudentsContainer& smart);
void writeToFile(const StudentsContainer& students, const std::string& filename);
void readFromFile(StudentsContainer& students, const std::string& filename);
double calculateAverage(const std::vector<int>& grades);
double calculateMedian(std::vector<int> grades);

#endif // STUDENTS2_H

