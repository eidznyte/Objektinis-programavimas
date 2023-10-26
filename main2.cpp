#include "students2.h"
#include <iostream>
#include <chrono>
#include <iomanip>
#include <vector>
#include <list>

int main() {
    std::vector<Student> studentsVector;
    std::list<Student> studentsList;
    std::vector<Student> dummiesVector, smartVector;
    std::list<Student> dummiesList, smartList;
    std::chrono::time_point<std::chrono::high_resolution_clock> startVector, endVector, startList, endList;
    std::chrono::duration<double> vectorDuration, listDuration;
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
        inputStudentsManually(studentsVector);
        break;
    case 2:
    {
        std::cout << "Enter the filename to read from (including extension, e.g., 'data.txt'): ";
        std::string filename;
        std::cin >> filename;
        readFromFile(studentsVector, filename);
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
        readFromFile(studentsVector, filename);
        break;
    }
    default:
        std::cerr << "Invalid choice!" << std::endl;
        return 1;
    }
    auto end = std::chrono::high_resolution_clock::now();
    readingDuration = end - start;

    displayStudents(studentsVector);

    startVector = std::chrono::high_resolution_clock::now();
    categorizeStudents(studentsVector, dummiesVector, smartVector);
    writeToFile(dummiesVector, "dummies_vector.txt");
    writeToFile(smartVector, "smart_vector.txt");
    endVector = std::chrono::high_resolution_clock::now();
    vectorDuration = endVector - startVector;

    
    studentsList.assign(studentsVector.begin(), studentsVector.end());

  
    startList = std::chrono::high_resolution_clock::now();
    categorizeStudents(studentsList, dummiesList, smartList);
    writeToFile(dummiesList, "dummies_list.txt");
    writeToFile(smartList, "smart_list.txt");
    endList = std::chrono::high_resolution_clock::now();
    listDuration = endList - startList;

    std::cout << "\nTime taken using std::vector: " << vectorDuration.count() << " seconds." << std::endl;
    std::cout << "Time taken using std::list: " << listDuration.count() << " seconds." << std::endl;

    std::cout << "\nStudents have been categorized and written to 'dummies_vector.txt' and 'smart_vector.txt' respectively." << std::endl;

    std::cout << std::fixed << std::setprecision(6);
    std::cout << "\nTime taken for reading data: " << readingDuration.count() << " seconds." << std::endl;

    return 0;
}

