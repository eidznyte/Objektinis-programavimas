#include "students2.h"
#include <iostream>
#include <chrono>
#include <iomanip>

int main() {
    std::vector<Student> students;
    std::chrono::duration<double> readingDuration(0.0), sortingDuration(0.0), writingDuration(0.0);

    std::cout << "Would you like to: \n"
        "1. Input data manually \n"
        "2. Read data from a file \n"
        "3. Generate a random student list file\n"
        "Choose an option (1/2/3): ";
    int choice;
    std::cin >> choice;

    auto start = std::chrono::high_resolution_clock::now();
    switch (choice) {
    case 1:
        inputStudentsManually(students);
        break;
    case 2:
    {
        std::cout << "Enter the filename to read from (including extension, e.g., 'data.txt'): ";
        std::string filename;
        std::cin >> filename;
        readFromFile(students, filename);
        break;
    }
    case 3:
    {
        std::cout << "How many records would you like to generate? \n"
            "1. 1,000 \n"
            "2. 10,000 \n"
            "3. 100,000 \n"
            "4. 1,000,000 \n"
            "5. 10,000,000 \n"
            "Choose an option (1/2/3/4/5): ";
        int subChoice;
        std::cin >> subChoice;
        size_t records;
        switch (subChoice) {
        case 1: records = 1'000; break;
        case 2: records = 10'000; break;
        case 3: records = 100'000; break;
        case 4: records = 1'000'000; break;
        case 5: records = 10'000'000; break;
        default:
            std::cerr << "Invalid option!" << std::endl;
            return 1;
        }
        std::string filename = "random_students_" + std::to_string(records) + ".txt";
        generateFile(filename, records);
        break;
    }
    default:
        std::cerr << "Invalid choice!" << std::endl;
        return 1;
    }
    auto end = std::chrono::high_resolution_clock::now();
    readingDuration = end - start;

    displayStudents(students);

    start = std::chrono::high_resolution_clock::now();
    std::vector<Student> dummies, smart;
    categorizeStudents(students, dummies, smart);
    end = std::chrono::high_resolution_clock::now();
    sortingDuration = end - start;

    std::cout << "\nDummies:\n";
    displayStudents(dummies);
    std::cout << "\nSmart:\n";
    displayStudents(smart);

    start = std::chrono::high_resolution_clock::now();
    writeToFile(dummies, "dummies.txt");
    writeToFile(smart, "smart.txt");
    end = std::chrono::high_resolution_clock::now();
    writingDuration = end - start;

    std::cout << "Students have been categorized and written to 'dummies.txt' and 'smart.txt' respectively." << std::endl;

    std::cout << std::fixed << std::setprecision(6); 
    std::cout << "\nTime taken for reading data: " << readingDuration.count() << " seconds." << std::endl;
    std::cout << "Time taken for sorting students: " << sortingDuration.count() << " seconds." << std::endl;
    std::cout << "Time taken for writing to files: " << writingDuration.count() << " seconds." << std::endl;

    return 0;
}

