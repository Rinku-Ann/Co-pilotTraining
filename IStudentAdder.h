#pragma once

#include "Student.h"

class IStudentAdder {
public:
    virtual ~IStudentAdder() = default;
    virtual bool addStudent(const Student& student) = 0;
};