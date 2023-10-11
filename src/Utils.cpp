#include "../include/Utils.h"
#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <fstream>

// Splits the input string based on the provided patterns (parentheses or commas).
std::vector<std::string> parseCommand(const std::string &in)
{
    // Using regex pattern for splitting based on ( , or )
    std::regex pattern("\\(|,|\\)");
    std::sregex_token_iterator it(in.begin(), in.end(), pattern, -1);
    std::sregex_token_iterator end;
    std::vector<std::string> tokens;

    for (; it != end; ++it)
    {
        std::string token = it->str();
        if (!token.empty())
        {
            tokens.push_back(token);
        }
    }

    return tokens;
}

// Converts the given string to lowercase.
std::string toLower(const std::string str)
{
    std::string result = str;
    // Applying std::transform with ::tolower to convert to lowercase
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

// Converts the given string to uppercase.
std::string toUpper(const std::string str)
{
    std::string result = str;
    // Applying std::transform with ::toupper to convert to uppercase
    std::transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

//Opens the file to given path in given mode
std::fstream openFile(const std::string& filePath, std::ios::openmode mode)
{
    std::fstream file;
    file.open(filePath, mode);
    if (!file) {
        std::cerr << "Error: Unable to open file '" << filePath << "'." << std::endl;
    }
    return file;
}

// Write the messege to the file
void writeFile(std::fstream& file, const std::string& message)
{
    if (file) {  // Check if the file stream is in a good state
        file << message << std::endl;
        if (!file) {
            std::cerr << "Error: Writing to the file failed." << std::endl;
        }
    }
}