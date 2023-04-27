#include "stringutils.h"
#include "exception.h"

#include <utf8.h>

namespace Utils
{

size_t length(const std::string& string)
{
    return utf8::distance(string.begin(), string.end());
}

std::string subString(const std::string& string, size_t startIndex, size_t length)
{
    try
    {
        auto beginIt{string.begin()};
        utf8::advance(beginIt, startIndex, string.end());

        auto endIt{beginIt};
        utf8::advance(endIt, length, string.end());

        return std::string{beginIt, endIt};
    }
    catch(const utf8::not_enough_room& ex)
    {
        THROW(RuntimeError{"Provided parameters are out of bounds (" + std::to_string(startIndex) + ", " + std::to_string(length) + ") against string of length " + std::to_string(Utils::length(string))});
    }
}

template<typename Iterator>
void skipCharactersLeft(Iterator& it, Iterator endIt, char characterToSkip)
{
    while(it != endIt && *it == characterToSkip)
    {
        utf8::next(it, endIt);
    }
}

template<typename Iterator>
void skipCharactersRight(Iterator& it, Iterator beginIt, Iterator endIt, char characterToSkip)
{
    utf8::prior(it, beginIt);

    while(it != beginIt && *it == characterToSkip)
    {
        utf8::prior(it, beginIt);
    }

    utf8::next(it, endIt);
}

std::vector<std::string> split(const std::string& string, char separator)
{
    std::vector<std::string> tokens;

    if(string.empty())
    {
        return tokens;
    }

    auto absoluteBegin{string.begin()};
    skipCharactersLeft(absoluteBegin, string.end(), separator);

    auto absoluteEnd{string.end()};
    skipCharactersRight(absoluteEnd, absoluteBegin, string.end(), separator);

    auto beginIt{absoluteBegin};

    auto endIt{absoluteBegin};

    std::string token;

    auto saveToken = [&]()
    {
        token.assign(beginIt, endIt);
        tokens.push_back(token);
        token.clear();
    };

    while(endIt != absoluteEnd)
    {
        if(*endIt == separator)
        {
            saveToken();

            skipCharactersLeft(endIt, absoluteEnd, separator);

            beginIt = endIt;
        }
        else
        {
            utf8::next(endIt, absoluteEnd);
        }
    }

    saveToken();

    return tokens;
}

void trim(std::string& string, char characterToTrim)
{
    if(string.empty())
    {
        return;
    }

    auto it{string.begin()};

    skipCharactersLeft(it, string.end(), characterToTrim);

    string.erase(string.begin(), it);

    it = string.begin();
    utf8::advance(it, length(string), string.end());

    skipCharactersRight(it, string.begin(), string.end(), characterToTrim);

    string.erase(it, string.end());
}

void replaceAll(std::string& string, const std::string& oldString, const std::string& newString)
{
    std::string::size_type position{0};
    while((position = string.find(oldString, position)) != std::string::npos)
    {
        string.replace(position, oldString.length(), newString);
        position += newString.length();
    }
}

}
