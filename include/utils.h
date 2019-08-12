#pragma once
#include <employee.h>
#include <nsp_types.h>
#include <ostream>
#include <string>

namespace nsp {
Grade stringToGrade(std::string);
std::string gradeToString(Grade);
std::ostream &operator<<(std::ostream &, const Employee &);
}
