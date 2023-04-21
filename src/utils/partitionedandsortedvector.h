#pragma once

#include <vector>
#include <algorithm>
#include <stdexcept>

namespace Utils
{

template<typename T, typename Partitioner, typename Sorter>
class PartitionedAndSortedVector
{
public:

    using V = std::vector<T>;

    PartitionedAndSortedVector(Partitioner partitioner, Sorter sorter) :
        mPartitioner{partitioner},
        mSorter{sorter},
        mPartitionEnd{mValues.end()}
    {
    }

    void pushBack(const T& value)
    {
        mValues.push_back(value);
        update();
    }

    void pushBack(T&& value)
    {
        mValues.push_back(std::move(value));
        update();
    }

    void remove(typename V::iterator it)
    {
        mValues.erase(it);
        update();
    }

    bool isEmpty() const
    {
        return size() == 0;
    }

    void clear()
    {
        mValues.clear();
        mPartitionEnd = mValues.end();
    }

    size_t size() const
    {
        return std::distance(mValues.begin(), typename V::const_iterator{mPartitionEnd});
    }

    // If you write the returned value, call update() manually
    T& operator [] (size_t index)
    {
        return mValues[index];
    }

    const T& operator [] (size_t index) const
    {
        return mValues[index];
    }

    T& at(size_t index)
    {
        if(index >= size())
        {
            throw std::out_of_range{"Provided index (" + std::to_string(index) + ") is out of bounds"};
        }
        return mValues[index];
    }

    const T& at(size_t index) const
    {
        if(index >= size())
        {
            throw std::out_of_range{"Provided index (" + std::to_string(index) + ") is out of bounds"};
        }
        return mValues[index];
    }

    // If you modify the values, call update()
    typename V::iterator begin()
    {
        return mValues.begin();
    }

    typename V::iterator begin() const
    {
        return mValues.begin();
    }

    typename V::const_iterator cbegin() const
    {
        return mValues.cbegin();
    }

    typename V::iterator end()
    {
        return begin() + size();
    }

    typename V::iterator end() const
    {
        return begin() + size();
    }

    typename V::const_iterator cend() const
    {
        return cbegin() + size();
    }

    void update()
    {
        mPartitionEnd = std::partition(mValues.begin(), mValues.end(), mPartitioner);
        std::sort(mValues.begin(), mPartitionEnd, mSorter);
    }

private:
    V mValues;
    Partitioner mPartitioner;
    Sorter mSorter;
    typename V::iterator mPartitionEnd;
};

template<typename T, typename Partitioner, typename Sorter>
PartitionedAndSortedVector<T, Partitioner, Sorter> makePaSVector(Partitioner partitioner, Sorter sorter)
{
    return PartitionedAndSortedVector<T, Partitioner, Sorter>{partitioner, sorter};
}

}
