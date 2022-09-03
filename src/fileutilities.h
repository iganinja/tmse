#ifndef FILEUTILITIES_H
#define FILEUTILITIES_H

#include "document.h"

#include <vector>
#include <string>

namespace TMSE
{

Document loadFile(const std::string& fileName);
void saveFile(const std::string& fileName, const Document& document);

}

#endif // FILEUTILITIES_H
