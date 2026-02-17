#pragma once
#include <vector>
#include "aspects.hpp"

class Signal;

class TrackSection {
    BlockState state{BlockState::Unknown};
    bool locked{false};
    std::vector<Signal*> watchers;

    void notifyTransition(bool wasSafe, bool nowSafe);

public:
    void addWatcher(Signal* s);

    BlockState getState() const;

    void lock();
    void unlock();
    void setState(BlockState s);

    bool isLocked() const;
    bool safeToProceed() const;
};
