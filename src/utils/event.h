#pragma once

#include <utility>

namespace Utils
{

// An Event is just a class which can contain certain data and can tell if it is has been triggered. If it is and user
// queries it with bool operator, then triggering flag is reset, so each event is "only one consumption"
template<typename DataType>
class Event
{
public:
    void setData(DataType&& data)
    {
        mData = std::move(data);
    }

    const DataType& data() const
    {
        return mData;
    }

    void trigger()
    {
        mTriggered = true;
    }

    operator bool()
    {
        const auto isTriggered{mTriggered};
        mTriggered = false;
        return isTriggered;
    }

private:
    bool mTriggered{false};
    DataType mData;
};

template<>
class Event<void>
{
public:
    void trigger()
    {
        mTriggered = true;
    }

    operator bool()
    {
        const auto isTriggered{mTriggered};
        mTriggered = false;
        return isTriggered;
    }

private:
    bool mTriggered{false};
};

}
