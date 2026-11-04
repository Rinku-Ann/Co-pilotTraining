#include "StudentInput.h"

#include <cmath>
#include <istream>
#include <ostream>
#include <sstream>
#include <string>
#include <utility>

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

std::optional<std::string> readStudentName(std::istream& input,
                                           std::ostream& output) {
    while (true) {
        output << "Student name: ";
        std::string name;
        if (!std::getline(input, name)) {
            return std::nullopt;
        }

        if (name.find_first_not_of(" \t\r\n") != std::string::npos) {
            return name;
        }

        output << "Name cannot be empty.\n";
    }
}

std::optional<double> readMarks(std::istream& input, std::ostream& output) {
    while (true) {
        output << "Marks (0-100): ";
        std::string text;
        if (!std::getline(input, text)) {
            return std::nullopt;
        }

        double marks = 0.0;
        if (parseValue(text, marks) && std::isfinite(marks) &&
            marks >= 0.0 && marks <= 100.0) {
            return marks;
        }

        output << "Enter a number from 0 to 100.\n";
    }
}

} // namespace

std::optional<int> StudentInput::readStudentId(std::istream& input,
                                               std::ostream& output) {
    while (true) {
        output << "Student ID (positive integer): ";
        std::string text;
        if (!std::getline(input, text)) {
            return std::nullopt;
        }

        int id = 0;
        if (parseValue(text, id) && id > 0) {
            return id;
        }

        output << "Enter a valid positive integer ID.\n";
    }
}

bool StudentInput::addStudentFromInput(IStudentAdder& manager,
                                       std::istream& input,
                                       std::ostream& output) {
    const std::optional<int> id = readStudentId(input, output);
    if (!id) {
        return false;
    }

    std::optional<std::string> name = readStudentName(input, output);
    if (!name) {
        return false;
    }

    const std::optional<double> marks = readMarks(input, output);
    if (!marks) {
        return false;
    }

    if (!manager.addStudent(Student(*id, std::move(*name), *marks))) {
        output << "A student with that ID already exists.\n";
    } else {
        output << "Student added.\n";
    }

    return true;
}