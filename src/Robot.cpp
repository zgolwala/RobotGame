#include "../include/Robot.h"
#include "../include/Direction.h"

// Default constructor initializes robot's position at (0,0) facing NORTH.
Robot::Robot() : roboData{0, 0, CompassDirection::NORTH}
{
}

// Place the robot at a specific position and direction.
bool Robot::place(RobotData &inpdata)
{
    // Check if the given position is valid.
    if (!isPositionValid(inpdata.xPos, inpdata.yPos))
    {
        return false;
    }
    // Update robot's position and direction.
    roboData.xPos = inpdata.xPos;
    roboData.yPos = inpdata.yPos;
    roboData.facingDirection = inpdata.facingDirection;

    return true;
}

// Move the robot one step in its current facing direction.
bool Robot::move()
{
    uint8_t new_x = roboData.xPos;
    uint8_t new_y = roboData.yPos;

    // Determine new position based on current facing direction.
    switch (roboData.facingDirection)
    {
    case CompassDirection::NORTH:
        new_y++;
        break;
    case CompassDirection::EAST:
        new_x++;
        break;
    case CompassDirection::SOUTH:
        new_y--;
        break;
    case CompassDirection::WEST:
        new_x--;
        break;
    case CompassDirection::INVALID:
        break; // Do nothing for INVALID direction.
    }

    // Check if new position is valid.
    if (isPositionValid(new_x, new_y))
    {
        roboData.xPos = new_x;
        roboData.yPos = new_y;
        return true;
    }

    return false;
}

// Rotate the robot 90 degrees to the left.
bool Robot::turnLeft()
{
    roboData.facingDirection = Direction::rotateLeft(roboData.facingDirection);
    return true;
}

// Rotate the robot 90 degrees to the right.
bool Robot::turnRight()
{
    roboData.facingDirection = Direction::rotateRight(roboData.facingDirection);
    return true;
}

// Report the robot's current position and facing direction.
std::string Robot::reportStatus() const
{
    return std::to_string(roboData.xPos) + "," + std::to_string(roboData.yPos) + "," + Direction::toString(roboData.facingDirection);
}

// Check if the provided (x,y) position is within the valid board bounds.
bool Robot::isPositionValid(uint8_t x, uint8_t y) const
{
    return x <= MAX_X && y <= MAX_Y;
}
