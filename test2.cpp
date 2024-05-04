#include <iostream>
#include <set>
#include <string>
#include <sstream>
#include <vector>

std::vector<std::string> divByLines(const std::string &str) noexcept
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(str);
    while (std::getline(tokenStream, token, ' '))
    {
        tokens.push_back(token);
    }
    return tokens;
}

int main()
{

    std::string strinul = "12 13 15 23 74";
    std::vector<std::string>  vec = divByLines(strinul);

    for (const auto& line : vec) {
        std::cout << std::stoi(line) << '\n';
        std::cout << line << '\n';
    }
}