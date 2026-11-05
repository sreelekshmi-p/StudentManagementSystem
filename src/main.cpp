#include "StudentManagement.h"
#include "StudentManagementApp.h"

#include <iostream>

int main() {
    StudentManager studentManager;
    StudentManagementApp app(studentManager, std::cin, std::cout);
    app.run();
    return 0;
}