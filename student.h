#ifndef STUDENT_H
#define STUDENT_H

#include <vector>
#include <string>

struct Student {
    std::string name;
    std::string surname;
    std::vector<int> homeworks;
    int exam;
};

double calculateAverage(const std::vector<int>& scores);
double calculateMedian(const std::vector<int>& scores);
void displayStudents(const std::vector<Student>& students);
void readStudentsFromFile(std::vector<Student>& students, const std::string& filename);
void inputStudentsManually(std::vector<Student>& students);
void generateRandomScores(Student& student);
#endif //STUDENT_H
