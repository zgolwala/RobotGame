#ifndef ROBOT_H
#define ROBOT_H

#include <string>

#include "Direction.h"

// Constants for board dimensions
constexpr auto MAX_X = 4;
constexpr auto MAX_Y = 4;

// Data structure for robot's attributes: position and facing direction.
struct RobotData
{
    uint8_t xPos;                     // X coordinate of the robot on the board.
    uint8_t yPos;                     // Y coordinate of the robot on the board.
    CompassDirection facingDirection; // Direction in which the robot is facing.
};

// Class representing a Robot on a 2D grid.
class Robot
{
private:
    RobotData roboData; // Data structure storing robot's current attributes.

public:
    // Default constructor.
    Robot();

    // Method to place the robot on the board at a specific position and direction.
    // Returns true if the placement is successful.
    bool place(RobotData &inputData);

    // Method to move the robot one step in its current direction.
    // Returns true if the movement is successful.
    bool move();

    // Method to rotate the robot 90 degrees to the left.
    // Returns true if the rotation is successful.
    bool turnLeft();

    // Method to rotate the robot 90 degrees to the right.
    // Returns true if the rotation is successful.
    bool turnRight();

    // Method to report the robot's current status.
    // Returns a string representing the robot's position and facing direction.
    std::string reportStatus() const;

    // Utility method to check if a given position (x, y) is valid on the board.
    // Returns true if the position is within board bounds.
    bool isPositionValid(uint8_t x, uint8_t y) const;
};

#endif // ROBOT_H
