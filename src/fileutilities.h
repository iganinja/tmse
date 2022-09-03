#ifndef FILEUTILITIES_H
#define FILEUTILITIES_H

#include "document.h"

#include <vector>
#include <string>

namespace TMSE
{

std::vector<std::string> loadFile(const std::string& fileName);
void saveFile(const std::string& fileName, const std::string& data);

}

#endif // FILEUTILITIES_H
