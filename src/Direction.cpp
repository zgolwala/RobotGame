// Direction.cpp

#include "../include/Direction.h"
#include <algorithm>

// Define the direction map that relates string representations to their CompassDirection equivalent.
const std::unordered_map<std::string, CompassDirection> Direction::directionMap = {
    {"NORTH", CompassDirection::NORTH},
    {"EAST", CompassDirection::EAST},
    {"SOUTH", CompassDirection::SOUTH},
    {"WEST", CompassDirection::WEST}};

// Define the reversed direction map that relates CompassDirections to their string representation.
const std::unordered_map<CompassDirection, std::string> Direction::reversedDirectionMap = {
    {CompassDirection::NORTH, "NORTH"},
    {CompassDirection::EAST, "EAST"},
    {CompassDirection::SOUTH, "SOUTH"},
    {CompassDirection::WEST, "WEST"}};

// Convert a string direction to its CompassDirection equivalent.
CompassDirection Direction::fromString(const std::string &directionStr)
{
    if (directionMap.find(directionStr) != directionMap.end())
    {
        return directionMap.at(directionStr);
    }
    return CompassDirection::INVALID;
}

// Convert a CompassDirection to its string representation.
std::string Direction::toString(CompassDirection direction)
{
    if (reversedDirectionMap.find(direction) != reversedDirectionMap.end())
    {
        return reversedDirectionMap.at(direction);
    }
    return "INVALID";
}

// Calculate the direction resulting from a left rotation.
CompassDirection Direction::rotateLeft(CompassDirection currentDirection)
{
    // Define the order of directions to simplify rotation logic.
    static const std::vector<CompassDirection> directionOrder = {CompassDirection::NORTH, CompassDirection::EAST, CompassDirection::SOUTH, CompassDirection::WEST};
    static const size_t ONE_STEP = 1;

    size_t currentIndex = std::distance(directionOrder.begin(), std::find(directionOrder.begin(), directionOrder.end(), currentDirection));
    size_t nextIndex = (currentIndex + directionOrder.size() - ONE_STEP) % directionOrder.size(); // Move one step backward
    return directionOrder[nextIndex];
}

// Calculate the direction resulting from a right rotation.
CompassDirection Direction::rotateRight(CompassDirection currentDirection)
{
    static const std::vector<CompassDirection> directionOrder = {CompassDirection::NORTH, CompassDirection::EAST, CompassDirection::SOUTH, CompassDirection::WEST};
    static const size_t ONE_STEP = 1;

    size_t currentIndex = std::distance(directionOrder.begin(), std::find(directionOrder.begin(), directionOrder.end(), currentDirection));
    size_t nextIndex = (currentIndex + ONE_STEP) % directionOrder.size(); // Move one step forward
    return directionOrder[nextIndex];
}