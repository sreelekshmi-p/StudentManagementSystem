#include "Student.h"

#include <gtest/gtest.h>

TEST(StudentTests, CanCreateStudentWithProvidedValues) {
    EXPECT_NO_THROW({
        const Student student(42, "Nora Patel", 86.5);
        static_cast<void>(student);
    });
}

TEST(StudentTests, GetStudentIdReturnsProvidedId) {
    const Student student(42, "Nora Patel", 86.5);

    EXPECT_EQ(student.getStudentId(), 42);
}

TEST(StudentTests, GetStudentNameReturnsProvidedName) {
    const Student student(42, "Nora Patel", 86.5);

    EXPECT_EQ(student.getStudentName(), "Nora Patel");
}

TEST(StudentTests, GetMarksReturnsProvidedMarks) {
    const Student student(42, "Nora Patel", 86.5);

    EXPECT_DOUBLE_EQ(student.getMarks(), 86.5);
}