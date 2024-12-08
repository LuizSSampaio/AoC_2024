#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <sstream>

std::string get_input();
int multiply_total_result(std::string input);

int main() {
    std::cout << "Response part 1: " << multiply_total_result(get_input()) << std::endl;
    return 0;
}

std::string get_input() {
    std::ifstream inputFile("../input.txt");

    if (!inputFile.is_open())
        throw "Couldn't open input.txt";

    std::string str;
    std::string content;
    while (getline(inputFile, str)) {
        content += str;
        content.push_back('\n');
    }

    inputFile.close();
    return content;
}

int multiply_total_result(std::string input) {
    int total_result = 0;

    std::regex pattern(R"(mul\((\d{1,3}),(\d{1,3})\))");

    for (std::sregex_iterator it(input.begin(), input.end(), pattern), end; it != end; it++) {
        int first = std::stoi((*it)[1].str());
        int second = std::stoi((*it)[2].str());

        total_result += first * second;
    }

    return total_result;
}
