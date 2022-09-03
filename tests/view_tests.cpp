#include "../src/view.h"
#include "../src/document.h"

#include <algorithm>
#include <gtest/gtest.h>

using namespace TMSE;
using namespace std::string_literals;

namespace
{
const std::vector<std::string> TestLines =
{
    "Lorem fistrum torpedor condemor la caidita por la gloria de mi madre pupita.",
    "Jarl se calle ustée pupita de la pradera. Jarl no te digo trigo por no llamarte Rodrigor de la pradera",
    "mamaar no te digo trigo por no llamarte Rodrigor. Te va a hasé pupitaa me cago en tus muelas llevame al sircoo a gramenawer.",
    "Al ataquerl diodenoo te va a hasé pupitaa por la gloria de mi madre fistro",
    "por la gloria de mi madre diodeno",
    "No te digo trigo por no llamarte Rodrigor",
    "amatomaa llevame al sircoo."
};
}

TEST(View, EmptyViewReturnsCorrectPositionAndWindow)
{
    Document document;

    View view{document};

    const View::DocumentCursorPosition Position{0, 0};

    EXPECT_EQ(view.documentCursorPosition(), Position);

    const View::RenderWindow Window{0, 0, 0, 0};

    EXPECT_EQ(view.renderWindow(), Window);
}
