#pragma once
#include "IObserver.h"

class ISubject
{
public:
    virtual ~ISubject() = default;
    virtual void attach(IObserver *observer) = 0;
    virtual void detach(IObserver *observer) = 0;
    virtual void notify(const std::string &event) = 0;
};