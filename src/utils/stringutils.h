#pragma once

#include <string>
#include <vector>

namespace Utils
{

// UTF8 aware functions. Lengths are character and not byte related
size_t length(const std::string& string);
std::string subString(const std::string& string, size_t startIndex, size_t length);
std::vector<std::string> split(const std::string& string, char separator = ' ');
void trim(std::string& string, char characterToTrim = ' ');

}
