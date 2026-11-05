#include "Student.h"

#include <utility>

Student::Student(int studentId, std::string studentName, double marks)
	: studentId_(studentId), studentName_(std::move(studentName)), marks_(marks) {}

int Student::getStudentId() const noexcept {
	return studentId_;
}

const std::string& Student::getStudentName() const noexcept {
	return studentName_;
}

double Student::getMarks() const noexcept {
	return marks_;
}
