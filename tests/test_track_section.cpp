#include "test_helpers.hpp"

#include "../tracksim/track_section.hpp"

void run_track_section_tests() {
    TrackSection section;

    EXPECT_EQ(section.getState(), BlockState::Unknown);
    EXPECT_TRUE(!section.isLocked());
    EXPECT_TRUE(!section.safeToProceed());

    section.setState(BlockState::Clear);
    EXPECT_EQ(section.getState(), BlockState::Clear);
    EXPECT_TRUE(!section.safeToProceed());

    section.lock();
    EXPECT_TRUE(section.isLocked());
    EXPECT_TRUE(section.safeToProceed());

    section.setState(BlockState::Occupied);
    EXPECT_EQ(section.getState(), BlockState::Occupied);
    EXPECT_TRUE(!section.safeToProceed());

    section.unlock();
    EXPECT_TRUE(!section.isLocked());
    EXPECT_TRUE(!section.safeToProceed());
}
