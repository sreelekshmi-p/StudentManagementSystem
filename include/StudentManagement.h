#pragma once

#include "IStudentManager.h"
#include "Student.h"

#include <optional>
#include <vector>

class StudentManager : public IStudentManager {
public:
	bool addStudent(const Student& student) override;
	void displayStudents() const override;
	const Student* findStudentById(int studentId) const override;
	double calculateAverageMarks() const override;
	std::optional<Student> findTopStudent() const override;
	bool empty() const noexcept override;

private:
	std::vector<Student> students_;
};
