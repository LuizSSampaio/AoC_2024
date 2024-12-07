#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::string get_input();
bool is_safe(std::vector<int> report);
int total_safe(std::string input);

int main() {
    std::cout << "Response part 1: " << total_safe(get_input()) << std::endl;
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

bool is_safe(std::vector<int> report) {
    bool last_increase;

    for (int i = 0; i < report.size() - 1; i++) {
        int difference = report[i] - report[i + 1];

        if (i == 0) {
            last_increase = (difference < 0);
        }

        if (std::abs(difference) < 1 || std::abs(difference) > 3)
            return false;

        if (last_increase != (difference < 0))
            return false;
    }

    return true;
}

int total_safe(std::string input) {
    int total_safe = 0;
    std::string report_token;
    int report_pos = 0;

    while ((report_pos = input.find('\n')) != std::string::npos) {
        report_token = input.substr(0, report_pos);
        report_token.push_back(' ');

        std::vector<int> report;
        int level_pos = 0;
        while ((level_pos = report_token.find(' ')) != std::string::npos) {
            report.push_back(std::stoi(report_token.substr(0, level_pos)));

            report_token.erase(0, level_pos + 1);
        }

        total_safe += is_safe(report);

        input.erase(0, report_pos + 1);
    }

    return total_safe;
}
