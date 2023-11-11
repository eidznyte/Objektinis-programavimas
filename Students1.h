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

void inputStudentsManually(std::vector<Student>& students);
void displayStudents(const std::vector<Student>& students);
void generateFile(const std::string& filename, int numStudents);
void generateRandomScores(Student& student);
void writeToFile(const std::vector<Student>& students, const std::string& filename);
void readFromFile(std::vector<Student>& students, const std::string& filename);
void inputStudentsManually(std::list<Student>& students);
void displayStudents(const std::list<Student>& students);
void categorizeStudents(std::vector<Student>& students, std::vector<Student>& dummies);
void categorizeStudents(std::list<Student>& students, std::list<Student>& dummies);
void categorizeStudentsremove(std::vector<Student>& students, std::vector<Student>& dummies);
void writeToFile(const std::list<Student>& students, const std::string& filename);
void readFromFile(std::list<Student>& students, const std::string& filename);
double calculateAverage(const std::vector<int>& grades);
double calculateMedian(std::vector<int> grades);

#endif // STUDENTS2_H
