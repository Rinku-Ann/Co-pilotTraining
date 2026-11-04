#pragma once

#include <string>

class Student {
public:
    Student(int id, std::string name, double marks);

    int getId() const noexcept;
    const std::string& getName() const noexcept;
    double getMarks() const noexcept;

private:
    int id_;
    std::string name_;
    double marks_;
};
