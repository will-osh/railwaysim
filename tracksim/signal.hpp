#pragma once
#include <string>
#include "aspects.hpp"

#define RESET   "\033[0m"
#define REDBG    "\033[31m"  // Red background
#define YELLOWBG  "\033[33m"  // Yellow background
#define GREENBG   "\033[32m"  // Green background

class TrackSection;

class Signal {
    Signal* nextSignal{nullptr};
    Signal* previousSignal{nullptr};
    TrackSection* protectedSection{nullptr};
    int aspect{RED};

protected:
    void setAspectInternal(int a);
    virtual void updateFromNext();
    void propagateBackwards();
    bool canClearInterlocking() const;

public:
    Signal() = default;
    virtual ~Signal() = default;

    void setNext(Signal* next);

    void setProtectedSection(TrackSection* s);
    TrackSection* getProtectedSection() const;

    void onProtectedSectionBecomeUnsafe();
    virtual void onProtectedSectionBecameSafe();

    Signal* next() const;
    Signal* prev() const;

    int getAspect() const;
    std::string getStringAspect() const;

    void setAspect(int a);
};

class AutoSignal : public Signal {
protected:
    void updateFromNext() override;

public:
    void onProtectedSectionBecameSafe() override;
    void setNext(Signal& sig);
};
