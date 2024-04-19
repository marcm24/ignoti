#include "events.h"

// default constructor
Event::Event()
{
    type = "";
    firstp = "";
    secondp = "";
    order = 0;
}

// constructor
Event::Event(std::string atype, std::string afirstp, std::string asecondp, int aorder)
{
    type = atype;
    firstp = afirstp;
    secondp = asecondp;
    order = aorder;
}

// get functions
std::string Event::getType() const
{
    return type;
}

std::string Event::getFirst() const
{
    return firstp;
}

std::string Event::getSecond() const
{
    return secondp;
}

int Event::getOrder() const
{
    return order;
}

// set order function
void Event::setOrder(int in)
{
    order = in;
}

// comparison operator overload to sort by order of appearance
bool Event::operator<(Event other) const
{
    return order < other.getOrder();
}