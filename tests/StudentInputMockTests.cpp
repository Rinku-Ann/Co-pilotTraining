#include "StudentInput.h"
#include "StudentManager.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>
#include <string>

namespace {

class MockStudentAdder : public IStudentAdder {
public:
    MOCK_METHOD(bool, addStudent, (const Student& student), (override));
};

TEST(StudentInputMockTests, AddsStudentAndCallsDependencyExactlyOnce) {
    ::testing::StrictMock<MockStudentAdder> adder;
    std::istringstream input("42\nAda Lovelace\n91.5\n");
    std::ostringstream output;

    EXPECT_CALL(adder, addStudent(::testing::Truly([](const Student& student) {
        return student.getId() == 42 && student.getName() == "Ada Lovelace" &&
               student.getMarks() == 91.5;
    })))
        .Times(1)
        .WillOnce(::testing::Return(true));

    EXPECT_TRUE(StudentInput::addStudentFromInput(adder, input, output));
    EXPECT_NE(output.str().find("Student added.\n"), std::string::npos);
}

TEST(StudentInputMockTests, ReportsDependencyRejectionAndCallsItOnce) {
    ::testing::StrictMock<MockStudentAdder> adder;
    std::istringstream input("42\nAda Lovelace\n91.5\n");
    std::ostringstream output;

    EXPECT_CALL(adder, addStudent(::testing::_))
        .Times(1)
        .WillOnce(::testing::Return(false));

    EXPECT_TRUE(StudentInput::addStudentFromInput(adder, input, output));
    EXPECT_NE(output.str().find("A student with that ID already exists.\n"),
              std::string::npos);
    EXPECT_EQ(output.str().find("Student added.\n"), std::string::npos);
}

TEST(StudentInputMockTests, DuplicateRecordIsRejectedByStudentManager) {
    StudentManager actualManager;
    ASSERT_TRUE(actualManager.addStudent(Student(42, "Existing Student", 80.0)));
    ::testing::StrictMock<MockStudentAdder> adder;
    std::istringstream input("42\nReplacement Student\n95.0\n");
    std::ostringstream output;

    EXPECT_CALL(adder, addStudent(::testing::Truly([](const Student& student) {
        return student.getId() == 42;
    })))
        .Times(1)
        .WillOnce([&actualManager](const Student& student) {
            return actualManager.addStudent(student);
        });

    EXPECT_TRUE(StudentInput::addStudentFromInput(adder, input, output));
    EXPECT_NE(output.str().find("A student with that ID already exists.\n"),
              std::string::npos);

    const auto storedStudent = actualManager.findStudentById(42);
    ASSERT_TRUE(storedStudent.has_value());
    EXPECT_EQ(storedStudent->getName(), "Existing Student");
    EXPECT_DOUBLE_EQ(storedStudent->getMarks(), 80.0);
}

TEST(StudentInputMockTests, DoesNotCallDependencyWhenInputEndsBeforeMarks)
{
    ::testing::StrictMock<MockStudentAdder> adder;
    std::istringstream input("42\nAda Lovelace\n");
    std::ostringstream output;

    EXPECT_CALL(adder, addStudent(::testing::_)).Times(0);

    EXPECT_FALSE(StudentInput::addStudentFromInput(adder, input, output));
}

} // namespace