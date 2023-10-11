// UTILS_H


#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>
#include <fstream>

// Splits the input string based on delimiters
// @param input: The string to be parse
// @return A vector of substrings
std::vector<std::string> parseCommand(const std::string &input);

// Converts the given string to lowercase
// @param str: The string to be converted
// @return A new string in lowercase
std::string toLower(const std::string str);

// Converts the given string to uppercase
// @param str: The string to be converted
// @return A new string in uppercase
std::string toUpper(const std::string str);

// Open a file 
// @param filePath: Path to the file to open
// @param mode : Mode to open the file in
// @return fstream that can be used

std::fstream openFile(const std::string& filePath, std::ios::openmode mode);

// Write to a file
// @param file : fstream obj of the file to write into
// @param message : The message to write to a file

void writeFile(std::fstream& file, const std::string& message);

#endif // UTILS_H
