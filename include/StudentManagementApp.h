#pragma once

#include "IStudentManager.h"

#include <iosfwd>

class StudentManagementApp {
public:
	StudentManagementApp(IStudentManager& studentManager, std::istream& input, std::ostream& output);

	void run();

private:
	IStudentManager& studentManager_;
	std::istream& input_;
	std::ostream& output_;
};