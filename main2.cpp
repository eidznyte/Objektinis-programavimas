#include <iostream>
#include <vector>
#include "students2.h" // Including the header for the Student structure and associated functions

int main() {
    std::vector<Student> students;
    while (true) {
        std::cout << "Choose an option:\n";
        std::cout << "1. Read data from file\n";
        std::cout << "2. Input data manually\n";
        std::cout << "3. Generate random student list files\n";
        std::cout << "4. Exit\n";
        std::cout << "Your choice: ";

        int choice;
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
        case 1:
            readFromFile(students);
            break;
        case 2:
            inputStudentsManually(students);
            break;
        case 3:
            std::cout << "Generating files...\n";
            generateFile("1000.txt", 1000);
            generateFile("10000.txt", 10000);
            generateFile("100000.txt", 100000);
            generateFile("1000000.txt", 1000000);
            generateFile("10000000.txt", 10000000);
            std::cout << "Files generated successfully!\n";
            break;
        case 4:
            return 0;
        default:
            std::cout << "Invalid choice. Please try again.\n";
        }

        // After processing, display results
        displayStudents(students);
        students.clear();  // Clearing the vector for next operations
    }

    return 0;
}

