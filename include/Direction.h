// Direction.h

#ifndef DIRECTION_H
#define DIRECTION_H

#include <string>
#include <unordered_map>
#include <vector>

// Enum to represent the possible compass directions. INVALID is used for unrecognized input.
enum class CompassDirection
{
    NORTH = 0,
    EAST = 1,
    SOUTH = 2,
    WEST = 3,
    INVALID = -1
};

// The Direction class provides utility functions to manage and manipulate compass directions.
class Direction
{
public:
    // Converts a string representation of a direction to its CompassDirection equivalent.
    static CompassDirection fromString(const std::string &directionStr);

    // Converts a CompassDirection to its string representation.
    static std::string toString(CompassDirection direction);

    // Returns the direction that results from a left rotation from the current direction.
    static CompassDirection rotateLeft(CompassDirection currentDirection);

    // Returns the direction that results from a right rotation from the current direction.
    static CompassDirection rotateRight(CompassDirection currentDirection);

private:
    // A map to help convert from string to CompassDirection.
    static const std::unordered_map<std::string, CompassDirection> directionMap;

    // A map to help convert from CompassDirection to string.
    static const std::unordered_map<CompassDirection, std::string> reversedDirectionMap;
};

#endif // DIRECTION_H
