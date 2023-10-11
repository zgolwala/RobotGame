// Implementation of the ProcessInput class.
// This class manages the command processing for the robot.
// It reads, validates, and executes commands entered by the user.
#include "../include/ProcessInput.h"

#include <iostream>
#include <filesystem>

#include "../include/Robot.h"
#include "../include/Utils.h"

namespace
{
    constexpr u_int8_t PLACE_ARGS = 4;
}
// Constructor: Initializes the Robot and sets toyPlaced to false
ProcessInput::ProcessInput()
    : toyPlaced(false),
      robot()
{
    commandHistory = openFile("command_history.txt", std::ios::out| std::ios::trunc); // For writing
}


// Destructor toi handle closing the file
ProcessInput::~ProcessInput()
{
    if (commandHistory)
    {
        commandHistory.close();
    }
}


// Main processing loop: Reads user input and processes the entered commands.
void ProcessInput::run()
{
    std::string input;

    displayUsage();
    std::cout << "Enter commands to control the toy robot, or type 'EXIT' to quit or type 'HELP' anytime to get the usage again:\n";

    while (true)
    {
        std::getline(std::cin, input);

        // Handle EXIT and HELP commands
        if (toUpper(input) == "EXIT")
        {
            std::cout << "Exiting the ROBOT GAME. Goodbye!\n";
            if(toyPlaced)
                writeFile(commandHistory,robot.reportStatus());
            break;
        }
        if (toUpper(input) == "HELP")
        {
            displayUsage();
            continue;
        }
        if (toUpper(input) == "REPLAY" || toUpper(input) == "REPLAY()")
        {
            handleReplay();
            break;
        }
        
        processCommand(input);
    }
}

void ProcessInput::handleReplay()
{
    std::string commandFilePath{};
    std::cout << "Please enter the path to the command file: ";
    std::getline(std::cin, commandFilePath);

    //OPen the file to read the commands
    std::fstream inputfile;
    inputfile = openFile(commandFilePath,std::ios::in);

    if(inputfile)
    {
        //Read the file
        std::string line;
        while (std::getline(inputfile, line)) {
            //Replay the commands
            std::cout <<"Replaying : " <<line <<std::endl;
            processCommand(line);
        }
        inputfile.close();

        std::cout << "Finished playing commands from file.\n";
    }
}

// Determines the command type based on user input
ProcessInput::CommandType ProcessInput::getCommandType(const std::string &command)
{
    std::string cmdLower = toLower(command); // Convert to lowercase for case-insensitive comparison

    // Compare command with known command types
    if (cmdLower == "place")
    {
        return PLACE;
    }
    if (cmdLower == "move")
    {
        return MOVE;
    }
    if (cmdLower == "left")
    {
        return LEFT;
    }
    if (cmdLower == "right")
    {
        return RIGHT;
    }
    if (cmdLower == "report")
    {
        return REPORT;
    }
    return INVALID;
}

// Splits input string into tokens and processes the command
void ProcessInput::processCommand(const std::string &input)
{
    writeFile(commandHistory, input);
    std::vector<std::string> tokens = parseCommand(input);

    if (tokens.empty())
    {
        std::cout << "Failed: Empty command" << std::endl;
        return;
    }
    executeCommands(tokens);
}

// Executes the appropriate robot action based on the command type
void ProcessInput::executeCommands(std::vector<std::string> tokens)
{
    std::string command{tokens[0]};
    CommandType commandType = getCommandType(command);

    if (!toyPlaced && commandType != CommandType::PLACE)
    {
        std::cout << "Place the Robot before any other commands" << std::endl;
        return;
    }

    // Execute robot actions based on command type
    switch (commandType)
    {
    case PLACE:
        executePlaceRobot(tokens);
        break;
    case MOVE:
        displayMessage(command, robot.move());
        break;
    case LEFT:
        displayMessage(command, robot.turnLeft());
        break;
    case RIGHT:
        displayMessage(command, robot.turnRight());
        break;
    case REPORT:
        std::cout << "Robot is currently at : " << robot.reportStatus() << std::endl;
        writeFile(commandHistory,robot.reportStatus());
        break;
    case INVALID:
        std::cout << "Failed: Invalid command" << std::endl;
        break;
    }
}

// Extracts and validates arguments for the PLACE command
bool ProcessInput::extractandvalidatePlaceArguments(const std::vector<std::string> &args, RobotData &inpdata)
{
    if (args.size() < PLACE_ARGS)
        return false;
    try
    {
        inpdata.xPos = std::stoi(args[1]);
        inpdata.yPos = std::stoi(args[2]);

        inpdata.facingDirection = Direction::fromString(toUpper(args[3]));
        if (inpdata.facingDirection == CompassDirection::INVALID)
        {
            std::cout << "Invalid Direction ";
            return false;
        }
    }
    catch (std::exception &e)
    {
        return false;
    }
    return true;
}

// Handles the PLACE command: Places the robot in a specific location and direction
void ProcessInput::executePlaceRobot(std::vector<std::string> &tokens)
{
    RobotData data;
    if (!extractandvalidatePlaceArguments(tokens, data))
    {
        std::cout << "Invalid PLACE arguments! i.e ==> place(X,Y,DIRECTION) . e.g --> PLACE(0,0,North)\n";
        return;
    }

    if (robot.place(data))
    {
        std::cout << "Successfully placed the toy at (" << std::to_string(data.xPos) << "," << std::to_string(data.yPos) << ") facing " << Direction::toString(data.facingDirection) << std::endl;

        if (!toyPlaced)
            toyPlaced = true;
    }
    else
    {
        std::cout << "Failed to place the toy." << std::endl;
    }
    displayUsage();
}

// Displays a message indicating success or failure of an action
void ProcessInput::displayMessage(const std::string &action, bool success)
{
    if (success)
    {
        std::cout << "Action [ " << action << " ] executed successfully." << std::endl;
    }
    else
    {
        std::cout << "Failed to execute the action [ " << action << " ] ." << std::endl;
    }
}

// Displays the usage details for the robot simulator
void ProcessInput::displayUsage()
{
    std::cout << "\n\n*****************************ROBOT GAME USAGE ********************************************\n";
    std::cout << "Available commands:\n";
    std::cout << "  place(X,Y,DIRECTION)  ==> Places the Robot at X,Y and FACING the mentioned Direction (NORTH , SOUTH , WEST & EAST)\n";
    std::cout << "  move()  ==>  Moves the robot by 1 unit in the direction it is facing unless that movement will cause the robot to fall off the grid\n";
    std::cout << "  left()  ==>  Rotates the robot 90° anticlockwise/counter clockwise \n";
    std::cout << "  right()  ==>  Rotate the robot 90° clockwise.\n";
    std::cout << "  report()  ==>  Outputs the robot's current grid location and facing direction\n";
    std::cout << "\n REPLAY - The ROBOT can be run in a REPLAY modde, Provide a path to a file containing a list of command that can be replayed. The game will exit once finished playing the file\n";
    std::cout << "*******************************************************************************************\n\n";
}
