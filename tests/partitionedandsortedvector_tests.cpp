#include "../src/utils/partitionedandsortedvector.h"

#include <gtest/gtest.h>
#include <array>

using namespace Utils;

namespace
{

struct EvenPartitioner
{
    bool operator () (int v) const
    {
        return v % 2 == 0;
    }
};

struct Sorter
{
    bool operator () (int v1, int v2) const
    {
        return v1 < v2;
    }
};

constexpr auto ElementNumber{10};

auto createAndFillPaSVector()
{
    auto v{makePaSVector<int>(EvenPartitioner{}, Sorter{})};

    for(auto i = 0u; i < ElementNumber; ++ i)
    {
        v.pushBack(i);
    }

    return v;
}

}

TEST(PartitionedAndSortedVector, JustCreatedPaSVIsEmpty)
{
    auto v{makePaSVector<int>(EvenPartitioner{}, Sorter{})};

    EXPECT_TRUE(v.isEmpty());
    EXPECT_EQ(v.size(), 0);
}

TEST(PartitionedAndSortedVector, SubscriptOperatorReturnsIndexedElement)
{
    auto v{createAndFillPaSVector()};

    const auto index{rand() % v.size()};

    const auto element{v[index]};

    EXPECT_EQ(*(v.begin() + index), element);
}

TEST(PartitionedAndSortedVector, AtMethodReturnsIndexedElementWithinBounds)
{
    auto v{createAndFillPaSVector()};

    const auto index{rand() % v.size()};

    EXPECT_NO_THROW(v.at(index));

    const auto element{v.at(index)};

    EXPECT_EQ(*(v.begin() + index), element);
}

TEST(PartitionedAndSortedVector, AtMethodThrowsWithOutOfBoundsIndex)
{
    auto v{createAndFillPaSVector()};

    const auto index{v.size() * 2};

    EXPECT_THROW(v.at(index), std::out_of_range);
}

TEST(PartitionedAndSortedVector, PushBackAddsElementsInOrder)
{
    auto v{createAndFillPaSVector()};

    EXPECT_TRUE(!v.isEmpty());
    EXPECT_EQ(v.size(), ElementNumber / 2);

    for(auto i = 0u; i < v.size() - 1; ++ i)
    {
        EXPECT_TRUE(v[i] < v[i + 1]);
    }
}

TEST(PartitionedAndSortedVector, ClearEmptiesVector)
{
    auto v{createAndFillPaSVector()};

    EXPECT_TRUE(!v.isEmpty());
    EXPECT_EQ(v.size(), ElementNumber / 2);

    v.clear();

    EXPECT_TRUE(v.isEmpty());
    EXPECT_EQ(v.size(), 0);
}

TEST(PartitionedAndSortedVector, RemoveRemovesElements)
{
    auto v{createAndFillPaSVector()};

    const auto originalSize{v.size()};

    const auto elementToRemove{v[rand() % v.size()]};

    v.remove(std::find(v.begin(), v.end(), elementToRemove));

    EXPECT_EQ(v.size(), originalSize - 1);
    EXPECT_EQ(std::find(v.begin(), v.end(), elementToRemove), v.end());
}

TEST(PartitionedAndSortedVector, UpdatePartitionatesAndSortsElements)
{
    const std::array<int, ElementNumber / 2> NewValues{16, 200, 26, 16, 3};
    auto v{createAndFillPaSVector()};

    for(auto i = 0u; i < NewValues.size(); ++ i)
    {
        v[i] = NewValues[i];
    }

    EXPECT_TRUE(std::equal(v.begin(), v.end(), NewValues.begin(), NewValues.end()));

    v.update();

    EXPECT_EQ(v.size(), 4);
    EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));
}

