#ifndef STUDENTS2_H
#define STUDENTS2_H

#include <vector>
#include <string>

struct Student {
    std::string name;
    std::string surname;
    std::vector<int> homeworks;
    int exam;
    double finalScoreAvg;
    double finalScoreMed;
};

void readFromFile(std::vector<Student>& students);
void inputStudentsManually(std::vector<Student>& students);
void displayStudents(const std::vector<Student>& students);
void generateFile(const std::string& filename, int numStudents);
double calculateAverage(const std::vector<int>& grades);
double calculateMedian(std::vector<int> grades);
void generateRandomScores(Student& student);

#endif // STUDENTS2_H

