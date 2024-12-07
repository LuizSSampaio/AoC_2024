#include <cstddef>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

std::string get_input();
void divide_input(std::string input, std::vector<int>& left_list, std::vector<int>& right_list);
int distance(int left, int right);
int total_distance(std::vector<int>& left_list, std::vector<int>& right_list);

int main() {
    std::vector<int> left_list, right_list;

    divide_input(get_input(), left_list, right_list);
    std::sort(left_list.begin(), left_list.end());
    std::sort(right_list.begin(), right_list.end());

    std::cout << "Response: " << total_distance(left_list, right_list) << std::endl;
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

void divide_input(std::string input, std::vector<int>& left_list, std::vector<int>& right_list) {
    std::string delimiter = "   ";
    int token;
    size_t pos, replace_pos = 0;
    bool is_left = true;

    while ((replace_pos = input.find('\n', replace_pos)) != std::string::npos) {
        input.replace(replace_pos, 1, delimiter);
        replace_pos += delimiter.length();
    }

    while ((pos = input.find(delimiter)) != std::string::npos) {
        token = std::stoi(input.substr(0, pos));

        if (is_left) {
            left_list.push_back(token);
        } else {
            right_list.push_back(token);
        }

        input.erase(0, pos + delimiter.length());

        is_left = !is_left;
    }
}

int distance(int left, int right) {
    int distance = left - right;
    if (distance < 0) {
        distance *= -1;
    }

    return distance;
}

int total_distance(std::vector<int>& left_list, std::vector<int>& right_list) {
    int total_distance = 0;
    for (int i = 0; i < left_list.size(); i++) {
        total_distance += distance(left_list[i], right_list[i]);
    }
    return total_distance;
}
