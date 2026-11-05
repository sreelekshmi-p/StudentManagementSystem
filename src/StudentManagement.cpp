#include "StudentManagement.h"

#include <cmath>
#include <iomanip>
#include <iostream>
#include <numeric>

bool StudentManager::addStudent(const Student& student) {
	const auto& name = student.getStudentName();
	const bool hasName = name.find_first_not_of(" \t\n\r") != std::string::npos;

	if (student.getStudentId() <= 0 || !hasName || !std::isfinite(student.getMarks()) ||
		student.getMarks() < 0.0 || student.getMarks() > 100.0 ||
		findStudentById(student.getStudentId()) != nullptr) {
		return false;
	}

	students_.push_back(student);
	return true;
}

void StudentManager::displayStudents() const {
	if (empty()) {
		std::cout << "No students available.\n";
		return;
	}

	std::cout << std::left << std::setw(12) << "Student ID"
			  << std::setw(30) << "Student Name" << "Marks\n";
	std::cout << std::string(50, '-') << '\n';
	for (const auto& student : students_) {
		std::cout << std::left << std::setw(12) << student.getStudentId()
				  << std::setw(30) << student.getStudentName()
				  << std::fixed << std::setprecision(2) << student.getMarks() << '\n';
	}
}

const Student* StudentManager::findStudentById(int studentId) const {
	for (const auto& student : students_) {
		if (student.getStudentId() == studentId) {
			return &student;
		}
	}
	return nullptr;
}

double StudentManager::calculateAverageMarks() const {
	if (empty()) {
		return 0.0;
	}

	const double total = std::accumulate(
		students_.begin(), students_.end(), 0.0,
		[](double sum, const Student& student) { return sum + student.getMarks(); });
	return total / static_cast<double>(students_.size());
}

std::optional<Student> StudentManager::findTopStudent() const {
	if (empty()) {
		return std::nullopt;
	}

	const Student* topStudent = &students_.front();
	for (const auto& student : students_) {
		if (student.getMarks() > topStudent->getMarks()) {
			topStudent = &student;
		}
	}
	return *topStudent;
}

bool StudentManager::empty() const noexcept {
	return students_.empty();
}
