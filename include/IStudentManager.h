#pragma once

#include "Student.h"

#include <optional>

class IStudentManager {
public:
	virtual ~IStudentManager() = default;

	virtual bool addStudent(const Student& student) = 0;
	virtual void displayStudents() const = 0;
	virtual const Student* findStudentById(int studentId) const = 0;
	virtual double calculateAverageMarks() const = 0;
	virtual std::optional<Student> findTopStudent() const = 0;
	virtual bool empty() const noexcept = 0;
};