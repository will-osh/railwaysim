#include "test_helpers.hpp"

#include "../tracksim/axle_counter.hpp"

void run_axle_counter_tests() {
    AxleCounter counter;
    TrackSection section;

    section.lock();

    counter.applyTo(section);
    EXPECT_EQ(section.getState(), BlockState::Clear);

    counter.trainEntered();
    counter.applyTo(section);
    EXPECT_EQ(section.getState(), BlockState::Occupied);

    counter.trainExited();
    counter.applyTo(section);
    EXPECT_EQ(section.getState(), BlockState::Clear);

    counter.fail();
    counter.trainEntered();
    counter.applyTo(section);
    EXPECT_EQ(section.getState(), BlockState::Failed);

    counter.reset();
    counter.applyTo(section);
    EXPECT_EQ(section.getState(), BlockState::Clear);
}
