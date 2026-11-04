#include "StudentManager.h"

#include <gtest/gtest.h>

TEST(StudentManagerTests, AddStudentAcceptsNewStudent) {
    StudentManager manager;
    const Student student(1, "Ada Lovelace", 91.5);

    EXPECT_TRUE(manager.addStudent(student));
}

TEST(StudentManagerTests, FindStudentByIdReturnsMatchingStudent) {
    StudentManager manager;
    ASSERT_TRUE(manager.addStudent(Student(2, "Grace Hopper", 95.0)));

    const auto found = manager.findStudentById(2);

    ASSERT_TRUE(found.has_value());
    EXPECT_EQ(found->getId(), 2);
    EXPECT_EQ(found->getName(), "Grace Hopper");
    EXPECT_DOUBLE_EQ(found->getMarks(), 95.0);
}

TEST(StudentManagerTests, FindStudentByIdReturnsEmptyForUnknownId) {
    StudentManager manager;
    ASSERT_TRUE(manager.addStudent(Student(3, "Katherine Johnson", 88.0)));

    EXPECT_FALSE(manager.findStudentById(4).has_value());
}

TEST(StudentManagerTests, CalculateAverageMarksReturnsMeanOfAllStudents) {
    StudentManager manager;
    ASSERT_TRUE(manager.addStudent(Student(1, "Ada", 80.0)));
    ASSERT_TRUE(manager.addStudent(Student(2, "Grace", 100.0)));

    const auto average = manager.calculateAverageMarks();

    ASSERT_TRUE(average.has_value());
    EXPECT_DOUBLE_EQ(*average, 90.0);
}

TEST(StudentManagerTests, FindTopStudentReturnsStudentWithHighestMarks) {
    StudentManager manager;
    ASSERT_TRUE(manager.addStudent(Student(1, "Ada", 80.0)));
    ASSERT_TRUE(manager.addStudent(Student(2, "Grace", 95.0)));
    ASSERT_TRUE(manager.addStudent(Student(3, "Katherine", 90.0)));

    const auto topStudent = manager.findTopStudent();

    ASSERT_TRUE(topStudent.has_value());
    EXPECT_EQ(topStudent->getId(), 2);
    EXPECT_EQ(topStudent->getName(), "Grace");
    EXPECT_DOUBLE_EQ(topStudent->getMarks(), 95.0);
}

TEST(StudentManagerTests, EmptyCollectionReturnsNoSearchAverageOrTopResult) {
    StudentManager manager;

    EXPECT_FALSE(manager.findStudentById(1).has_value());
    EXPECT_FALSE(manager.calculateAverageMarks().has_value());
    EXPECT_FALSE(manager.findTopStudent().has_value());
}

TEST(StudentManagerTests, AddStudentRejectsDuplicateId) {
    StudentManager manager;
    ASSERT_TRUE(manager.addStudent(Student(7, "Original", 80.0)));

    EXPECT_FALSE(manager.addStudent(Student(7, "Duplicate", 100.0)));

    const auto found = manager.findStudentById(7);
    ASSERT_TRUE(found.has_value());
    EXPECT_EQ(found->getName(), "Original");
    EXPECT_DOUBLE_EQ(found->getMarks(), 80.0);
}
