#include "StudentManagement.h"

#include <gtest/gtest.h>

#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

TEST(StudentManagerTests, NewManagerIsEmpty) {
    const StudentManager manager;

    EXPECT_TRUE(manager.empty());
    EXPECT_DOUBLE_EQ(manager.calculateAverageMarks(), 0.0);
    EXPECT_FALSE(manager.findTopStudent().has_value());
}

TEST(StudentManagerTests, AddsValidStudent) {
    StudentManager manager;
    const Student student(42, "Nora Patel", 86.5);

    EXPECT_TRUE(manager.addStudent(student));
    EXPECT_FALSE(manager.empty());
}

TEST(StudentManagerTests, FindsExistingStudentById) {
    StudentManager manager;
    ASSERT_TRUE(manager.addStudent(Student(42, "Nora Patel", 86.5)));

    const Student* found = manager.findStudentById(42);
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->getStudentName(), "Nora Patel");
    EXPECT_DOUBLE_EQ(found->getMarks(), 86.5);
}

TEST(StudentManagerTests, RejectsInvalidStudentData) {
    StudentManager manager;
    const std::vector<Student> invalidStudents = {
        Student(0, "Zero ID", 50.0),
        Student(-1, "Negative ID", 50.0),
        Student(1, "", 50.0),
        Student(2, " \t\n", 50.0),
        Student(3, "Negative marks", -0.01),
        Student(4, "Excess marks", 100.01),
        Student(5, "NaN marks", std::numeric_limits<double>::quiet_NaN()),
        Student(6, "Infinite marks", std::numeric_limits<double>::infinity())
    };

    for (const Student& student : invalidStudents) {
        EXPECT_FALSE(manager.addStudent(student));
    }
    EXPECT_TRUE(manager.empty());
}

TEST(StudentManagerTests, AcceptsInclusiveIdAndMarksBoundaries) {
    StudentManager manager;

    EXPECT_TRUE(manager.addStudent(Student(1, "Minimum", 0.0)));
    EXPECT_TRUE(manager.addStudent(
        Student(std::numeric_limits<int>::max(), "Maximum", 100.0)));
}

TEST(StudentManagerTests, RejectsDuplicateIdAndKeepsOriginalRecord) {
    StudentManager manager;
    ASSERT_TRUE(manager.addStudent(Student(42, "Original", 80.0)));

    EXPECT_FALSE(manager.addStudent(Student(42, "Duplicate", 90.0)));

    const Student* found = manager.findStudentById(42);
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->getStudentName(), "Original");
    EXPECT_DOUBLE_EQ(found->getMarks(), 80.0);
}

TEST(StudentManagerTests, ReturnsNullForMissingId) {
    StudentManager manager;
    ASSERT_TRUE(manager.addStudent(Student(42, "Nora Patel", 86.5)));

    EXPECT_EQ(manager.findStudentById(99), nullptr);
}

TEST(StudentManagerTests, CalculatesAverageMarks) {
    StudentManager manager;
    ASSERT_TRUE(manager.addStudent(Student(1, "First", 0.0)));
    ASSERT_TRUE(manager.addStudent(Student(2, "Second", 100.0)));
    ASSERT_TRUE(manager.addStudent(Student(3, "Third", 72.5)));

    EXPECT_DOUBLE_EQ(manager.calculateAverageMarks(), 57.5);
}

TEST(StudentManagerTests, FindsHighestMarkAndKeepsFirstOnTie) {
    StudentManager manager;
    ASSERT_TRUE(manager.addStudent(Student(1, "First", 95.0)));
    ASSERT_TRUE(manager.addStudent(Student(2, "Second", 100.0)));
    ASSERT_TRUE(manager.addStudent(Student(3, "Third", 100.0)));

    const std::optional<Student> topStudent = manager.findTopStudent();
    ASSERT_TRUE(topStudent.has_value());
    EXPECT_EQ(topStudent->getStudentId(), 2);
}

TEST(StudentManagerTests, DisplaysMessageWhenEmpty) {
    const StudentManager manager;
    std::ostringstream output;
    std::streambuf* previousBuffer = std::cout.rdbuf(output.rdbuf());

    manager.displayStudents();

    std::cout.rdbuf(previousBuffer);
    EXPECT_NE(output.str().find("No students available."), std::string::npos);
}

TEST(StudentManagerTests, DisplaysStoredStudent) {
    StudentManager manager;
    ASSERT_TRUE(manager.addStudent(Student(42, "Nora Patel", 86.5)));
    std::ostringstream output;
    std::streambuf* previousBuffer = std::cout.rdbuf(output.rdbuf());
    const std::ios::fmtflags previousFlags = std::cout.flags();
    const std::streamsize previousPrecision = std::cout.precision();

    manager.displayStudents();

    std::cout.rdbuf(previousBuffer);
    std::cout.flags(previousFlags);
    std::cout.precision(previousPrecision);
    EXPECT_NE(output.str().find("Nora Patel"), std::string::npos);
    EXPECT_NE(output.str().find("86.50"), std::string::npos);
}