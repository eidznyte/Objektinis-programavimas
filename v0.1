#include "student.h"
#include <algorithm>
#include <iostream>

int main() {
    std::vector<Student> students;

    try {
        std::cout << "How would you like to enter data? (1: Read from file, 2: Manual input): ";
        int choice;
        std::cin >> choice;
        std::cin.ignore(); 

        if (choice == 1) {
            readStudentsFromFile(students, "students.txt"); 
        }
        else if (choice == 2) {
            inputStudentsManually(students);
        }
        else {
            std::cerr << "Invalid choice! Please enter 1 to read from file or 2 for manual input.\n";
            return 1;
        }

        if (students.empty()) {
            std::cerr << "No students' data available to display.\n";
            return 1;
        }

        std::sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
            return a.name < b.name; 
            });

        displayStudents(students);

    }
    catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << '\n';
        return 1;
    }
    return 0;
}
