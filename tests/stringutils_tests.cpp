#include "../src/utils/stringutils.h"
#include "../src/utils/exception.h"

#include <algorithm>
#include <gtest/gtest.h>

using namespace std::string_literals;

TEST(StringUtils, LengthReturnsCorrectLength)
{
    const auto length{Utils::length("hello")};

    EXPECT_EQ(length, 5);
}

TEST(StringUtils, LengthReturnsCorrectLengthWithNoASCIIStrings)
{
    const auto length{Utils::length("qué")};

    EXPECT_EQ(length, 3);
}

TEST(StringUtils, SubStringReturnsEmptySubString)
{
    const auto string{"¿hola qué tal?"s};
    const auto subString{Utils::subString(string, 0, 0)};
    EXPECT_EQ(subString, ""s);
}

TEST(StringUtils, SubStringReturnsSubStringWithLength1)
{
    const auto string{"¿hola qué tal?"s};
    const auto subString{Utils::subString(string, 0, 1)};
    EXPECT_EQ(subString, "¿"s);
}

TEST(StringUtils, SubStringReturnsSubStringAtMiddle)
{
    const auto string{"¿hola qué tal?"s};
    const auto subString{Utils::subString(string, 6, 3)};
    EXPECT_EQ(subString, "qué"s);
}

TEST(StringUtils, SubStringThrowsWithIncorrectBounds)
{
    const auto string{"¿hola qué tal?"s};
    EXPECT_THROW(Utils::subString(string, 0, Utils::length(string) + 10), Utils::Exception);
}

TEST(StringUtils, TrimWorksWithEmptyString)
{
    auto string{""s};
    Utils::trim(string, '#');

    EXPECT_EQ(string, ""s);
}

TEST(StringUtils, TrimWorksWithAStringWhichDoesNotNeedTrimming)
{
    auto string{"¿hola qué tal?"s};
    Utils::trim(string, '#');

    EXPECT_EQ(string, "¿hola qué tal?"s);
}

TEST(StringUtils, TrimRemovesCharactersFromBeginning)
{
    auto string{"###¿hola qué tal?"s};
    Utils::trim(string, '#');

    EXPECT_EQ(string, "¿hola qué tal?"s);
}

TEST(StringUtils, TrimRemovesCharactersFromEnd)
{
    auto string{"¿hola qué tal?####"s};
    Utils::trim(string, '#');

    EXPECT_EQ(string, "¿hola qué tal?"s);
}

TEST(StringUtils, TrimRemovesCharactersFromBothSides)
{
    auto string{"##¿hola qué tal?####"s};
    Utils::trim(string, '#');

    EXPECT_EQ(string, "¿hola qué tal?"s);
}

TEST(StringUtils, SplitWorksWithEmptyString)
{
    const auto string{""s};
    const auto tokens{Utils::split(string)};

    EXPECT_TRUE(tokens.empty());
}

TEST(StringUtils, SplitSplitsWithDefaultSeparator)
{
    const auto string{"¿hola qué tal?"s};
    const auto tokens{Utils::split(string)};

    EXPECT_EQ(tokens.size(), 3);

    EXPECT_EQ(tokens[0], "¿hola"s);
    EXPECT_EQ(tokens[1], "qué"s);
    EXPECT_EQ(tokens[2], "tal?"s);
}

TEST(StringUtils, SplitSplitsWithCustomSeparator)
{
    const auto string{"¿hola#qué#tal?"s};
    const auto tokens{Utils::split(string, '#')};

    EXPECT_EQ(tokens.size(), 3);

    EXPECT_EQ(tokens[0], "¿hola"s);
    EXPECT_EQ(tokens[1], "qué"s);
    EXPECT_EQ(tokens[2], "tal?"s);
}

TEST(StringUtils, SplitSplitsWithSeparatorAtTheBeginning)
{
    const auto string{"#¿hola#qué#tal?"s};
    const auto tokens{Utils::split(string, '#')};

    EXPECT_EQ(tokens.size(), 3);

    EXPECT_EQ(tokens[0], "¿hola"s);
    EXPECT_EQ(tokens[1], "qué"s);
    EXPECT_EQ(tokens[2], "tal?"s);
}

TEST(StringUtils, SplitSplitsWithSeparatorAtTheEnd)
{
    const auto string{"#¿hola#qué#tal?"s};
    const auto tokens{Utils::split(string, '#')};

    EXPECT_EQ(tokens.size(), 3);

    EXPECT_EQ(tokens[0], "¿hola"s);
    EXPECT_EQ(tokens[1], "qué"s);
    EXPECT_EQ(tokens[2], "tal?"s);
}

TEST(StringUtils, SplitSplitsWithSeparatorInBothSides)
{
    const auto string{"#¿hola#qué#tal?"s};
    const auto tokens{Utils::split(string, '#')};

    EXPECT_EQ(tokens.size(), 3);

    EXPECT_EQ(tokens[0], "¿hola"s);
    EXPECT_EQ(tokens[1], "qué"s);
    EXPECT_EQ(tokens[2], "tal?"s);
}

TEST(StringUtils, SplitSplitsWithSeparatorInBothSidesAndMoreThanOneWithin)
{
    const auto string{"#¿hola############qué###########tal?"s};
    const auto tokens{Utils::split(string, '#')};

    EXPECT_EQ(tokens.size(), 3);

    EXPECT_EQ(tokens[0], "¿hola"s);
    EXPECT_EQ(tokens[1], "qué"s);
    EXPECT_EQ(tokens[2], "tal?"s);
}

TEST(StringUtils, SplitDoesNotCreateEmptyStrings)
{
    const auto string{"Lorem fistrum jarl papaar papaar de la pradera jarl diodeno mamaar. Va usté muy cargadoo qué dise usteer tiene musho peligro te va a hasé pupitaa te voy a borrar el cerito. Va usté muy cargadoo apetecan fistro no puedor te va a hasé pupitaa no puedor benemeritaar no puedor ese hombree."s};
    const auto tokens{Utils::split(string)};
    auto predicate = [](const auto& string){ return string.empty(); };

    EXPECT_TRUE(std::none_of(tokens.begin(), tokens.end(), predicate));
}
