#pragma once

#include "IStudentAdder.h"

#include <iosfwd>
#include <optional>

namespace StudentInput {

std::optional<int> readStudentId(std::istream& input, std::ostream& output);
bool addStudentFromInput(IStudentAdder& manager,
                         std::istream& input,
                         std::ostream& output);

} // namespace StudentInput