#include <iostream>

#ifndef __EVENTS_H
#define __EVENTS_H

// event class for storing the notification events. has the first person and second person member variables, type of event and the order as well. sorted by its order.

class Event
{
public:
    Event();
    Event(std::string atype, std::string afirstp, std::string asecondp, int aorder);

    std::string getType() const;
    std::string getFirst() const;
    std::string getSecond() const;
    int getOrder() const;
    void setOrder(int in);

    bool operator<(Event other) const;

private:
    std::string type;
    std::string firstp;
    std::string secondp;
    int order;
};

#endif