**Robot Simulator Game**

**Introduction : **
The Robot Simulator is a simulation game that allows a user to interactively control a virtual robot on a grid. The user can place the robot on the grid, move it, turn it, and request its current status. The simulator also supports saving command history to a file and can replay a list of commands from a provided file.

**Features**

Command Processing: Interactively reads user input and processes commands for controlling the toy robot.
Supported Commands:
PLACE(X,Y,DIRECTION): Places the Robot at X,Y, facing the mentioned Direction (NORTH, SOUTH, WEST, EAST).
MOVE(): Moves the robot by one unit in the direction it's facing unless that movement will cause the robot to fall off the grid.
LEFT(): Rotates the robot 90° counter-clockwise.
RIGHT(): Rotates the robot 90° clockwise.
REPORT(): Outputs the robot's current grid location and facing direction.
Command History: All commands given to the robot are saved to a history file, allowing users to review robot movements.
File Replay: The simulator can read a file of commands and replay those commands, effectively replicating a previous session.

**Installation and Running**

Clone the Repository:

git clone https://github.com/zgolwala/RobotGame.git
cd <repository_directory>

**Compile:**

make

**Run the Simulator:**

./toy_robot

**Assumptions and Limitations**

**Techincal :**
This Game is test currently with a setup of WSL using ubuntu 22.04 distros. IT uses gcc version 11.4.0
This uses Google test framework for testcases. The testcases are very limited and can be expanded upon.
This need a UI and comprehensive logger to make it more extensive

**Functional:**
The commands are not case sensitive
Apart from the PLACE command , remaining commands can be used without the use of '()' at the end of the command.

**Test Plan and Stratergy:**
The feature to replay and store the command history has been added to help with testing. This feature can help setup a baseline behaviour and can be tested after every code modification.
The test included are not comprehensive and needs a bit of work. I have attached a test plan in test folder and more test cases can be written based on that.


