#include "track_section.hpp"
#include "signal.hpp"

void TrackSection::addWatcher(Signal* s) {
    watchers.push_back(s);
}

BlockState TrackSection::getState() const {
    return state;
}

void TrackSection::lock() {
    bool was = safeToProceed();
    locked = true;
    bool now = safeToProceed();
    notifyTransition(was, now);
}

void TrackSection::unlock() {
    bool was = safeToProceed();
    locked = false;
    bool now = safeToProceed();
    notifyTransition(was, now);
}

void TrackSection::setState(BlockState s) {
    bool was = safeToProceed();
    state = s;
    bool now = safeToProceed();
    notifyTransition(was, now);
}

bool TrackSection::isLocked() const {
    return locked;
}

bool TrackSection::safeToProceed() const {
    return state == BlockState::Clear && locked;
}

void TrackSection::notifyTransition(bool wasSafe, bool nowSafe) {
    if (wasSafe && !nowSafe) {
        for (Signal* sig : watchers) {
            if (sig) sig->onProtectedSectionBecomeUnsafe();
        }
    } else if (!wasSafe && nowSafe) {
        for (Signal* sig : watchers) {
            if (sig) sig->onProtectedSectionBecameSafe();
        }
    }
}
