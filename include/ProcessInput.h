#ifndef PROCESSINPUT_H
#define PROCESSINPUT_H

#include <fstream>

#include "Robot.h"

// The ProcessInput class manages the command processing for the robot simulator.
// It reads, validates, and executes commands entered by the user.
class ProcessInput
{
public:
    // Enum representing possible command types
    enum CommandType
    {
        PLACE,
        MOVE,
        LEFT,
        RIGHT,
        REPORT,
        INVALID
    };

    // Default constructor
    ProcessInput();

    //Default Descrtructor
    ~ProcessInput();

    // Initiates the main command processing loop, prompting the user for input
    void run();

    // Processes the user input command and calls the appropriate robot action
    void processCommand(const std::string &input);

    // Determines the type of command provided by the user
    CommandType getCommandType(const std::string &command);

    // Displays the usage details for the available commands
    void displayUsage();

private:
    // Extracts and validates the PLACE command arguments from the input
    bool extractandvalidatePlaceArguments(const std::vector<std::string> &args, RobotData &inpdata);

    // Executes the PLACE command, placing the robot on the board in a specified position and direction
    void executePlaceRobot(std::vector<std::string> &tokens);

    // Displays a message indicating the success or failure of a robot action
    void displayMessage(const std::string &action, bool success);

    // Helper function to execute various robot commands
    void executeCommands(std::vector<std::string> tokens);

    //Handle replaying commands from a file
    void handleReplay();
    // Flag indicating whether the robot has been placed on the board
    bool toyPlaced;

    // Instance of the Robot class representing the robot being controlled
    Robot robot;

    //File to store the command history
    std::fstream commandHistory;
};

#endif // PROCESSINPUT_H
