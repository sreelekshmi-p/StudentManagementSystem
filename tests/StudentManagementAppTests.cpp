#include "MockStudentManager.h"
#include "StudentManagementApp.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>
#include <string>

TEST(StudentManagementAppTests, ReportsSuccessfulStudentAddition) {
	MockStudentManager studentManager;
	std::istringstream input("1\n42\nNora Patel\n86.5\n6\n");
	std::ostringstream output;
	StudentManagementApp app(studentManager, input, output);

	EXPECT_CALL(studentManager, addStudent(testing::_))
		.WillOnce(testing::Truly([](const Student& student) {
			return student.getStudentId() == 42 && student.getStudentName() == "Nora Patel" &&
				student.getMarks() == 86.5;
		}));

	app.run();

	EXPECT_NE(output.str().find("Student added."), std::string::npos);
}

TEST(StudentManagementAppTests, ReportsRejectedStudentAddition) {
	MockStudentManager studentManager;
	std::istringstream input("1\n42\nNora Patel\n86.5\n6\n");
	std::ostringstream output;
	StudentManagementApp app(studentManager, input, output);

	EXPECT_CALL(studentManager, addStudent(testing::_)).WillOnce(testing::Return(false));

	app.run();

	EXPECT_NE(output.str().find("Could not add student."), std::string::npos);
}

TEST(StudentManagementAppTests, DoesNotCallManagerForMalformedStudentId) {
	MockStudentManager studentManager;
	std::istringstream input("1\nnot-an-id\n6\n");
	std::ostringstream output;
	StudentManagementApp app(studentManager, input, output);

	EXPECT_CALL(studentManager, addStudent(testing::_)).Times(0);

	app.run();

	EXPECT_NE(output.str().find("Invalid student ID."), std::string::npos);
}