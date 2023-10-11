#include <gtest/gtest.h>
#include "../include/Direction.h"
#include "../include/Robot.h"
#include "../include/ProcessInput.h"
#include "../include/Utils.h"

// Simple test for the Direction utilities
TEST(DirectionUtilities, RotateLeftFromNorth) {
    ASSERT_EQ(Direction::rotateLeft(CompassDirection::NORTH), CompassDirection::WEST);
}

TEST(DirectionUtilities, RotateRightFromNorth) {
    ASSERT_EQ(Direction::rotateRight(CompassDirection::NORTH), CompassDirection::EAST);
}

// Test for the Robot movement
TEST(RobotTests, PlaceRobotValidPosition) {
    Robot robot;
    RobotData data = {1, 1, CompassDirection::NORTH};
    ASSERT_TRUE(robot.place(data));
}

TEST(RobotTests, PlaceRobotInvalidPosition) {
    Robot robot;
    RobotData data = {10, 10, CompassDirection::NORTH};  // Out of bounds
    ASSERT_FALSE(robot.place(data));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
