#include <iostream>
#include <stdexcept>

enum Aspect { RED=0, YELLOW=1, DOUBLE_YELLOW=2, GREEN=3 };

#include <iostream>

#define RESET   "\033[0m"
#define REDBG    "\033[31m"  // Red background
#define YELLOWBG  "\033[33m"  // Yellow background
#define GREENBG   "\033[32m"  // Green background

class Signal {
private:
    Signal* nextSignal{nullptr};
    Signal* previousSignal{nullptr};

    int aspect{RED};

protected:
    void setAspectInternal(int a) {
        if (a < RED || a > GREEN) throw std::out_of_range("Invalid aspect");
        if (aspect == a) return;    
        aspect = a;
        propagateBackwards();
    }

    virtual void updateFromNext() {}

    void propagateBackwards() {
        if (previousSignal) {
            previousSignal->updateFromNext();
        }
    }

public:
    Signal() = default;
    virtual ~Signal() = default;

    void setNext(Signal* next) {
        nextSignal = next;
        if (next) next->previousSignal = this;
    }

    Signal* next() const { return nextSignal; }
    Signal* prev() const { return previousSignal; }

    int getAspect() const { return aspect; }
    std::string getStringAspect() const {
        switch (aspect){
            case RED: return REDBG + std::string(" ● ") + RESET;
            case YELLOW: return YELLOWBG + std::string(" ● ") + RESET;
            case DOUBLE_YELLOW: return YELLOWBG + std::string(" ●  ● ") + RESET;
            case GREEN: return GREENBG + std::string(" ● ") + RESET;
            default: throw std::runtime_error("There was an error!");
        }
    }

    void setAspect(int a) {
        setAspectInternal(a); 
    }
};

class AutoSignal : public Signal {
protected:
    void updateFromNext() override {
        Signal* n = next();
        int newAspect = GREEN;

        if (!n) {
            newAspect = GREEN;
        } else {
            switch (n->getAspect()) {
                case RED:           newAspect = YELLOW;        break;
                case YELLOW:        newAspect = DOUBLE_YELLOW; break;
                case DOUBLE_YELLOW: newAspect = GREEN;         break;
                case GREEN:         newAspect = GREEN;         break;
            }
        }

        setAspectInternal(newAspect);
    }
public:
    void setNext(Signal& sig) {
        Signal::setNext(&sig);
        updateFromNext();
    }
};

int main() {
    Signal a = Signal();
    AutoSignal b = AutoSignal();
    AutoSignal c = AutoSignal();
    AutoSignal d = AutoSignal();

    d.setNext(c);
    c.setNext(b);
    b.setNext(a);

    std::cout << a.getStringAspect() << " ---- " << b.getStringAspect() << " ---- " << c.getStringAspect() << " ---- " << d.getStringAspect() << "\n";

    a.setAspect(YELLOW);
    std::cout << a.getStringAspect() << " ---- " << b.getStringAspect() << " ---- " << c.getStringAspect() << " ---- " << d.getStringAspect() << "\n";

    a.setAspect(DOUBLE_YELLOW);
    std::cout << a.getStringAspect() << " ---- " << b.getStringAspect() << " ---- " << c.getStringAspect() << " ---- " << d.getStringAspect() << "\n";

    a.setAspect(GREEN);
    std::cout << a.getStringAspect() << " ---- " << b.getStringAspect() << " ---- " << c.getStringAspect() << " ---- " << d.getStringAspect() << "\n";

    return 0;
}
