#include <iostream>
#include <vector>

void run_track_section_tests();
void run_axle_counter_tests();
void run_signal_tests();

int main() {
    struct Suite {
        const char* name;
        void (*run)();
    };

    const std::vector<Suite> suites = {
        {"TrackSection", run_track_section_tests},
        {"AxleCounter", run_axle_counter_tests},
        {"Signal", run_signal_tests},
    };

    int failed = 0;

    for (const auto& suite : suites) {
        try {
            suite.run();
            std::cout << "[PASS] " << suite.name << "\n";
        } catch (const std::exception& ex) {
            ++failed;
            std::cout << "[FAIL] " << suite.name << ": " << ex.what() << "\n";
        } catch (...) {
            ++failed;
            std::cout << "[FAIL] " << suite.name << ": unknown exception\n";
        }
    }

    if (failed == 0) {
        std::cout << "All test suites passed.\n";
        return 0;
    }

    std::cout << failed << " suite(s) failed.\n";
    return 1;
}
