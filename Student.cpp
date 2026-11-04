#include "Student.h"

#include <utility>

Student::Student(int id, std::string name, double marks)
    : id_(id), name_(std::move(name)), marks_(marks) {}

int Student::getId() const noexcept {
    return id_;
}

const std::string& Student::getName() const noexcept {
    return name_;
}

double Student::getMarks() const noexcept {
    return marks_;
}
