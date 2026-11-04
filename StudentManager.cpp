#include "StudentManager.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <numeric>

bool StudentManager::addStudent(const Student& student) {
    if (findStudentById(student.getId())) {
        return false;
    }

    students_.push_back(student);
    return true;
}

void StudentManager::displayStudents() const {
    if (students_.empty()) {
        std::cout << "No students available.\n";
        return;
    }

    std::cout << std::left << std::setw(12) << "Student ID"
              << std::setw(24) << "Name" << "Marks\n";
    std::cout << std::string(46, '-') << '\n';

    for (const Student& student : students_) {
        std::cout << std::left << std::setw(12) << student.getId()
                  << std::setw(24) << student.getName()
                  << std::fixed << std::setprecision(2) << student.getMarks()
                  << '\n';
    }
}

std::optional<Student> StudentManager::findStudentById(int id) const {
    const auto student = std::find_if(
        students_.begin(), students_.end(),
        [id](const Student& candidate) { return candidate.getId() == id; });

    if (student == students_.end()) {
        return std::nullopt;
    }

    return *student;
}

std::optional<double> StudentManager::calculateAverageMarks() const {
    if (students_.empty()) {
        return std::nullopt;
    }

    const double total = std::accumulate(
        students_.begin(), students_.end(), 0.0,
        [](double sum, const Student& student) {
            return sum + student.getMarks();
        });

    return total / static_cast<double>(students_.size());
}

std::optional<Student> StudentManager::findTopStudent() const {
    if (students_.empty()) {
        return std::nullopt;
    }

    const auto topStudent = std::max_element(
        students_.begin(), students_.end(),
        [](const Student& left, const Student& right) {
            return left.getMarks() < right.getMarks();
        });

    return *topStudent;
}
