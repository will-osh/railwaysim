#include "signal.hpp"
#include "track_section.hpp"

#include <iostream>

int main() {
    Signal a = Signal();
    AutoSignal b = AutoSignal();
    AutoSignal c = AutoSignal();
    AutoSignal d = AutoSignal();

    TrackSection sec;
    sec.setState(BlockState::Clear);
    b.setProtectedSection(&sec);

    a.setAspect(GREEN);

    d.setNext(c);
    c.setNext(b);
    b.setNext(a);

    std::cout << a.getStringAspect() << " ---- " << b.getStringAspect() << " ---- " << c.getStringAspect() << " ---- " << d.getStringAspect() << "\n";
    std::cout << "\n\n\n";
    
    sec.lock();
    std::cout << a.getStringAspect() << " ---- " << b.getStringAspect() << " ---- " << c.getStringAspect() << " ---- " << d.getStringAspect() << "\n";
    std::cout << "\n\n\n";

    return 0;
}
