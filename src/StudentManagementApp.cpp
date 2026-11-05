#include "StudentManagementApp.h"

#include <cmath>
#include <iostream>
#include <sstream>
#include <string>

namespace {

bool readInteger(std::istream& input, std::ostream& output, const std::string& prompt, int& value) {
	output << prompt;
	std::string line;
	if (!std::getline(input, line)) {
		return false;
	}

	std::istringstream parser(line);
	if (!(parser >> value)) {
		return false;
	}
	parser >> std::ws;
	return parser.eof();
}

bool readMarks(std::istream& input, std::ostream& output, const std::string& prompt, double& marks) {
	output << prompt;
	std::string line;
	if (!std::getline(input, line)) {
		return false;
	}

	std::istringstream parser(line);
	if (!(parser >> marks)) {
		return false;
	}
	parser >> std::ws;
	return parser.eof() && std::isfinite(marks);
}

void displayMenu(std::ostream& output) {
	output << "\nStudent Management System\n"
	       << "1. Add student\n"
	       << "2. Display students\n"
	       << "3. Find student by ID\n"
	       << "4. Calculate average marks\n"
	       << "5. Find top student\n"
	       << "6. Exit\n";
}

}

StudentManagementApp::StudentManagementApp(
	IStudentManager& studentManager, std::istream& input, std::ostream& output)
	: studentManager_(studentManager), input_(input), output_(output) {}

void StudentManagementApp::run() {
	while (true) {
		displayMenu(output_);
		int choice = 0;
		if (!readInteger(input_, output_, "Choose an option: ", choice)) {
			if (!input_.eof()) {
				output_ << "Invalid menu choice. Enter a number from 1 to 6.\n";
				continue;
			}
			break;
		}

		if (choice == 1) {
			int studentId = 0;
			if (!readInteger(input_, output_, "Student ID: ", studentId)) {
				if (input_.eof()) {
					break;
				}
				output_ << "Invalid student ID.\n";
				continue;
			}

			output_ << "Student name: ";
			std::string studentName;
			if (!std::getline(input_, studentName)) {
				break;
			}

			double marks = 0.0;
			if (!readMarks(input_, output_, "Marks (0-100): ", marks)) {
				if (input_.eof()) {
					break;
				}
				output_ << "Invalid marks. Enter a number from 0 to 100.\n";
				continue;
			}

			if (studentManager_.addStudent(Student(studentId, studentName, marks))) {
				output_ << "Student added.\n";
			} else {
				output_ << "Could not add student. Check the ID, name, marks, and duplicate IDs.\n";
			}
		} else if (choice == 2) {
			studentManager_.displayStudents();
		} else if (choice == 3) {
			int studentId = 0;
			if (!readInteger(input_, output_, "Student ID to find: ", studentId)) {
				if (input_.eof()) {
					break;
				}
				output_ << "Invalid student ID.\n";
				continue;
			}

			const Student* student = studentManager_.findStudentById(studentId);
			if (student != nullptr) {
				output_ << "ID: " << student->getStudentId()
				        << ", Name: " << student->getStudentName()
				        << ", Marks: " << student->getMarks() << '\n';
			} else {
				output_ << "Student not found.\n";
			}
		} else if (choice == 4) {
			if (studentManager_.empty()) {
				output_ << "No students available.\n";
			} else {
				output_ << "Average marks: " << studentManager_.calculateAverageMarks() << '\n';
			}
		} else if (choice == 5) {
			const auto topStudent = studentManager_.findTopStudent();
			if (topStudent.has_value()) {
				output_ << "Top student: " << topStudent->getStudentName()
				        << " (ID: " << topStudent->getStudentId()
				        << ", Marks: " << topStudent->getMarks() << ")\n";
			} else {
				output_ << "No students available.\n";
			}
		} else if (choice == 6) {
			break;
		} else {
			output_ << "Invalid menu choice. Enter a number from 1 to 6.\n";
		}
	}

	output_ << "Goodbye.\n";
}