#include "students2.h"
#include <iostream>
#include <chrono>


int main() {
    std::vector<Student> students;

    std::cout << "Would you like to: \n"
        "1. Input data manually \n"
        "2. Read data from a file \n"
        "3. Generate a random student list file\n"
        "Choose an option (1/2/3): ";

    int choice;
    std::cin >> choice;

   
    std::chrono::high_resolution_clock::time_point startReading, endReading, startSorting, endSorting, startWriting, endWriting;

    switch (choice) {
    case 1:
        inputStudentsManually(students);
        break;
    case 2:
    {
        std::cout << "Enter the filename to read from (or type 'default' for generated files): ";
        std::string filename;
        std::cin >> filename;

        if (filename == "default") {
            std::cout << "How many records in the file? \n"
                << "1. 1,000 \n"
                << "2. 10,000 \n"
                << "3. 100,000 \n"
                << "4. 1,000,000 \n"
                << "5. 10,000,000 \n"
                << "Choose an option (1/2/3/4/5): ";
            int subChoice;
            std::cin >> subChoice;

            switch (subChoice) {
            case 1: filename = "random_students_1000.txt"; break;
            case 2: filename = "random_students_10000.txt"; break;
            case 3: filename = "random_students_100000.txt"; break;
            case 4: filename = "random_students_1000000.txt"; break;
            case 5: filename = "random_students_10000000.txt"; break;
            default:
                std::cerr << "Invalid option!" << std::endl;
                return 1;
            }
        }

        startReading = std::chrono::high_resolution_clock::now();
        readFromFile(students, filename);
        endReading = std::chrono::high_resolution_clock::now();
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
            case 1:
                records = 1'000;
                break;
            case 2:
                records = 10'000;
                break;
            case 3:
                records = 100'000;
                break;
            case 4:
                records = 1'000'000;
                break;
            case 5:
                records = 10'000'000;
                break;
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

    if (choice != 3) {
        displayStudents(students);
    }

    std::vector<Student> dummies;
    std::vector<Student> smart;

    startSorting = std::chrono::high_resolution_clock::now();
    categorizeStudents(students, dummies, smart);
    endSorting = std::chrono::high_resolution_clock::now();

    
    std::cout << "\nDummies:\n";
    displayStudents(dummies);

    std::cout << "\nSmart:\n";
    displayStudents(smart);

    
    startWriting = std::chrono::high_resolution_clock::now();
    writeToFile(dummies, "dummies.txt");
    writeToFile(smart, "smart.txt");
    endWriting = std::chrono::high_resolution_clock::now();

    std::cout << "Students have been categorized and written to 'dummies.txt' and 'smart.txt' respectively." << std::endl;

    
    std::chrono::duration<double> readingDuration = endReading - startReading;
    std::chrono::duration<double> sortingDuration = endSorting - startSorting;
    std::chrono::duration<double> writingDuration = endWriting - startWriting;

    std::cout << "\nTime taken for reading data: " << readingDuration.count() << " seconds." << std::endl;
    std::cout << "Time taken for sorting students: " << sortingDuration.count() << " seconds." << std::endl;
    std::cout << "Time taken for writing to files: " << writingDuration.count() << " seconds." << std::endl;

    return 0;
}


