#pragma once

#include <stdexcept>
#include <string>

#define EXPECT_TRUE(expr) \
    do { \
        if (!(expr)) { \
            throw std::runtime_error(std::string("Expectation failed: ") + #expr + " at " + __FILE__ + ":" + std::to_string(__LINE__)); \
        } \
    } while (false)

#define EXPECT_EQ(actual, expected) EXPECT_TRUE((actual) == (expected))

#define EXPECT_THROW(stmt) \
    do { \
        bool threw = false; \
        try { \
            stmt; \
        } catch (...) { \
            threw = true; \
        } \
        if (!threw) { \
            throw std::runtime_error(std::string("Expected exception was not thrown by: ") + #stmt + " at " + __FILE__ + ":" + std::to_string(__LINE__)); \
        } \
    } while (false)
