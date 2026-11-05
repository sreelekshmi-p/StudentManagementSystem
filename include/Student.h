#pragma once

#include <string>

class Student {
public:
	Student(int studentId, std::string studentName, double marks);

	int getStudentId() const noexcept;
	const std::string& getStudentName() const noexcept;
	double getMarks() const noexcept;

private:
	int studentId_;
	std::string studentName_;
	double marks_;
};
