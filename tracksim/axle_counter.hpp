#pragma once
#include "track_section.hpp"

class AxleCounter {
    int count{0};
    bool healthy{true};

public:
    void trainEntered();
    void trainExited();

    void fail();
    void reset();

    void applyTo(TrackSection& section) const;
};
