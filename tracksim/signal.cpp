#include "signal.hpp"
#include "track_section.hpp"

#include <stdexcept>

void Signal::setAspectInternal(int a) {
    if (a < RED || a > GREEN) {
        throw std::out_of_range("Invalid aspect");
    }

    if (aspect == a) {
        return;
    }

    if (a == RED || canClearInterlocking()) {
        aspect = a;
        propagateBackwards();
    } else {
        throw std::out_of_range("Tried to set aspect against interlocking!");
    }
}

void Signal::updateFromNext() {}

void Signal::propagateBackwards() {
    if (previousSignal) {
        previousSignal->updateFromNext();
    }
}

bool Signal::canClearInterlocking() const {
    if (!protectedSection) {
        return true;
    }

    return protectedSection->safeToProceed();
}

void Signal::setNext(Signal* next) {
    nextSignal = next;
    if (next) {
        next->previousSignal = this;
    }
}

void Signal::setProtectedSection(TrackSection* s) {
    protectedSection = s;
    if (protectedSection) {
        protectedSection->addWatcher(this);
    }
}

TrackSection* Signal::getProtectedSection() const {
    return protectedSection;
}

void Signal::onProtectedSectionBecomeUnsafe() {
    setAspectInternal(RED);
}

void Signal::onProtectedSectionBecameSafe() {}

Signal* Signal::next() const {
    return nextSignal;
}

Signal* Signal::prev() const {
    return previousSignal;
}

int Signal::getAspect() const {
    return aspect;
}

std::string Signal::getStringAspect() const {
    switch (aspect) {
    case RED:
        return REDBG + std::string(" ● ") + RESET + std::string(" ● ");
    case YELLOW:
        return std::string(" ● ") + YELLOWBG + std::string(" ● ") + RESET;
    case DOUBLE_YELLOW:
        return YELLOWBG + std::string(" ●  ● ") + RESET;
    case GREEN:
        return std::string(" ● ") + GREENBG + std::string(" ● ") + RESET;
    default:
        throw std::runtime_error("There was an error!");
    }
}

void Signal::setAspect(int a) {
    setAspectInternal(a);
}

void AutoSignal::updateFromNext() {
    if (!canClearInterlocking()) {
        setAspectInternal(RED);
        return;
    }

    Signal* n = next();
    int newAspect = GREEN;

    if (!n) {
        newAspect = GREEN;
    } else {
        switch (n->getAspect()) {
        case RED:
            newAspect = YELLOW;
            break;
        case YELLOW:
            newAspect = DOUBLE_YELLOW;
            break;
        case DOUBLE_YELLOW:
            newAspect = GREEN;
            break;
        case GREEN:
            newAspect = GREEN;
            break;
        }
    }

    setAspectInternal(newAspect);
}

void AutoSignal::onProtectedSectionBecameSafe() {
    updateFromNext();
}

void AutoSignal::setNext(Signal& sig) {
    Signal::setNext(&sig);
    updateFromNext();
}
