#include "MockStudentManager.h"
#include "StudentManagementApp.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>
#include <string>

TEST(StudentManagementMockTests, ReportsSuccessfulStudentAddition) {
	testing::StrictMock<MockStudentManager> studentManager;
	std::istringstream input("1\n42\nNora Patel\n86.5\n6\n");
	std::ostringstream output;
	StudentManagementApp app(studentManager, input, output);

	EXPECT_CALL(studentManager, addStudent(testing::Truly([](const Student& student) {
		return student.getStudentId() == 42 && student.getStudentName() == "Nora Patel" &&
			student.getMarks() == 86.5;
	})))
		.WillOnce(testing::Return(true));

	app.run();

	EXPECT_NE(output.str().find("Student added."), std::string::npos);
}

TEST(StudentManagementMockTests, ReportsDependencyFailureWhenAdditionIsRejected) {
	testing::StrictMock<MockStudentManager> studentManager;
	std::istringstream input("1\n42\nNora Patel\n86.5\n6\n");
	std::ostringstream output;
	StudentManagementApp app(studentManager, input, output);

	EXPECT_CALL(studentManager, addStudent(testing::_)).WillOnce(testing::Return(false));

	app.run();

	EXPECT_NE(output.str().find("Could not add student."), std::string::npos);
}

TEST(StudentManagementMockTests, ReportsRejectedDuplicateRecord) {
	testing::StrictMock<MockStudentManager> studentManager;
	std::istringstream input("1\n42\nOriginal\n80\n1\n42\nDuplicate\n90\n6\n");
	std::ostringstream output;
	StudentManagementApp app(studentManager, input, output);
	testing::Sequence addSequence;

	EXPECT_CALL(studentManager, addStudent(testing::Truly([](const Student& student) {
		return student.getStudentId() == 42 && student.getStudentName() == "Original";
	})))
		.InSequence(addSequence)
		.WillOnce(testing::Return(true));
	EXPECT_CALL(studentManager, addStudent(testing::Truly([](const Student& student) {
		return student.getStudentId() == 42 && student.getStudentName() == "Duplicate";
	})))
		.InSequence(addSequence)
		.WillOnce(testing::Return(false));

	app.run();

	EXPECT_NE(output.str().find("Student added."), std::string::npos);
	EXPECT_NE(output.str().find("Could not add student."), std::string::npos);
}

TEST(StudentManagementMockTests, DoesNotCallManagerWhenStudentIdIsMalformed) {
	testing::StrictMock<MockStudentManager> studentManager;
	std::istringstream input("1\nnot-an-id\n6\n");
	std::ostringstream output;
	StudentManagementApp app(studentManager, input, output);

	EXPECT_CALL(studentManager, addStudent(testing::_)).Times(0);

	app.run();

	EXPECT_NE(output.str().find("Invalid student ID."), std::string::npos);
}

TEST(StudentManagementMockTests, CallsManagerOnceForEachValidAddition) {
	testing::StrictMock<MockStudentManager> studentManager;
	std::istringstream input("1\n42\nFirst\n80\n1\n43\nSecond\n90\n6\n");
	std::ostringstream output;
	StudentManagementApp app(studentManager, input, output);

	EXPECT_CALL(studentManager, addStudent(testing::_))
		.Times(2)
		.WillOnce(testing::Return(true))
		.WillOnce(testing::Return(true));

	app.run();

	const std::string outputText = output.str();
	const std::size_t firstSuccess = outputText.find("Student added.");
	ASSERT_NE(firstSuccess, std::string::npos);
	EXPECT_NE(outputText.find("Student added.", firstSuccess + 1), std::string::npos);
}