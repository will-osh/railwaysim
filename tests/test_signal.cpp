#include "test_helpers.hpp"

#include "../tracksim/signal.hpp"
#include "../tracksim/track_section.hpp"

void run_signal_tests() {
    {
        Signal freeSignal;
        freeSignal.setAspect(GREEN);
        EXPECT_EQ(freeSignal.getAspect(), GREEN);
    }

    {
        Signal interlocked;
        TrackSection section;
        section.setState(BlockState::Clear);
        interlocked.setProtectedSection(&section);

        EXPECT_THROW(interlocked.setAspect(GREEN));

        section.lock();
        interlocked.setAspect(GREEN);
        EXPECT_EQ(interlocked.getAspect(), GREEN);
    }

    {
        Signal nextSignal;
        AutoSignal autoSignal;

        autoSignal.setNext(nextSignal);
        EXPECT_EQ(autoSignal.getAspect(), YELLOW);

        nextSignal.setAspect(YELLOW);
        EXPECT_EQ(autoSignal.getAspect(), DOUBLE_YELLOW);

        nextSignal.setAspect(DOUBLE_YELLOW);
        EXPECT_EQ(autoSignal.getAspect(), GREEN);
    }

    {
        Signal nextSignal;
        nextSignal.setAspect(GREEN);

        AutoSignal protectedAuto;
        TrackSection section;
        protectedAuto.setProtectedSection(&section);
        protectedAuto.setNext(nextSignal);

        EXPECT_EQ(protectedAuto.getAspect(), RED);

        section.setState(BlockState::Clear);
        section.lock();
        EXPECT_EQ(protectedAuto.getAspect(), GREEN);

        section.setState(BlockState::Occupied);
        EXPECT_EQ(protectedAuto.getAspect(), RED);
    }
}
