#include "StudentManager.h"
#include "StudentInput.h"

#include <iostream>
#include <optional>
#include <sstream>
#include <string>

namespace {

template <typename Value>
bool parseValue(const std::string& text, Value& value) {
    std::istringstream input(text);
    if (!(input >> value)) {
        return false;
    }

    input >> std::ws;
    return input.eof();
}

void displayMenu() {
    std::cout << "\nStudent Management System\n"
              << "1. Add student\n"
              << "2. Display all students\n"
              << "3. Find student by ID\n"
              << "4. Calculate average marks\n"
              << "5. Find top student\n"
              << "0. Exit\n"
              << "Choice: ";
}

} // namespace

int main() {
    StudentManager manager;

    while (true) {
        displayMenu();
        std::string input;
        if (!std::getline(std::cin, input)) {
            break;
        }

        int choice = -1;
        if (!parseValue(input, choice)) {
            std::cout << "Enter a valid menu number.\n";
            continue;
        }

        if (choice == 0) {
            std::cout << "Goodbye.\n";
            break;
        }

        switch (choice) {
        case 1:
            if (!StudentInput::addStudentFromInput(manager, std::cin, std::cout)) {
                return 0;
            }
            break;
        case 2:
            manager.displayStudents();
            break;
        case 3: {
            const std::optional<int> id =
                StudentInput::readStudentId(std::cin, std::cout);
            if (!id) {
                return 0;
            }

            const std::optional<Student> student = manager.findStudentById(*id);
            if (student) {
                std::cout << "ID: " << student->getId()
                          << ", Name: " << student->getName()
                          << ", Marks: " << student->getMarks() << '\n';
            } else {
                std::cout << "No student found with that ID.\n";
            }
            break;
        }
        case 4: {
            const std::optional<double> average = manager.calculateAverageMarks();
            if (average) {
                std::cout << "Average marks: " << *average << '\n';
            } else {
                std::cout << "No students available to calculate an average.\n";
            }
            break;
        }
        case 5: {
            const std::optional<Student> topStudent = manager.findTopStudent();
            if (topStudent) {
                std::cout << "Top student: " << topStudent->getName()
                          << " (ID: " << topStudent->getId()
                          << ", Marks: " << topStudent->getMarks() << ")\n";
            } else {
                std::cout << "No students available.\n";
            }
            break;
        }
        default:
            std::cout << "Choose a number from 0 to 5.\n";
            break;
        }
    }

    return 0;
}
