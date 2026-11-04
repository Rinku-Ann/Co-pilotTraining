#include "Student.h"

#include <gtest/gtest.h>

#include <string>

TEST(StudentTests, CanBeCreatedWithConstructorValues) {
    const Student student(42, "Ada Lovelace", 91.5);

    EXPECT_EQ(student.getId(), 42);
}

TEST(StudentTests, GetIdReturnsConstructorId) {
    const Student student(73, "Katherine Johnson", 88.0);

    EXPECT_EQ(student.getId(), 73);
}

TEST(StudentTests, GetNameReturnsConstructorName) {
    const Student student(18, "Grace Hopper", 94.0);

    EXPECT_EQ(student.getName(), "Grace Hopper");
}

TEST(StudentTests, GetMarksReturnsConstructorMarks) {
    const Student student(29, "Alan Turing", 76.25);

    EXPECT_DOUBLE_EQ(student.getMarks(), 76.25);
}
