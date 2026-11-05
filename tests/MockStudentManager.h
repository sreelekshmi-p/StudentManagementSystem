#pragma once

#include "IStudentManager.h"

#include <gmock/gmock.h>

class MockStudentManager : public IStudentManager {
public:
	MOCK_METHOD(bool, addStudent, (const Student& student), (override));
	MOCK_METHOD(void, displayStudents, (), (const, override));
	MOCK_METHOD(const Student*, findStudentById, (int studentId), (const, override));
	MOCK_METHOD(double, calculateAverageMarks, (), (const, override));
	MOCK_METHOD(std::optional<Student>, findTopStudent, (), (const, override));
	MOCK_METHOD(bool, empty, (), (const, noexcept, override));
};