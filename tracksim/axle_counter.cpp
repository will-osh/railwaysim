#include "axle_counter.hpp"

void AxleCounter::trainEntered() {
    if (healthy) {
        ++count;
    }
}

void AxleCounter::trainExited() {
    if (healthy && count > 0) {
        --count;
    }
}

void AxleCounter::fail() {
    healthy = false;
}

void AxleCounter::reset() {
    healthy = true;
}

void AxleCounter::applyTo(TrackSection& section) const {
    if (!healthy) {
        section.setState(BlockState::Failed);
    } else if (count > 0) {
        section.setState(BlockState::Occupied);
    } else {
        section.setState(BlockState::Clear);
    }
}
