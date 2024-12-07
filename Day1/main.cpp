#include <cstddef>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

std::string get_input();
void divide_input(std::string input, std::vector<int>& left_list, std::vector<int>& right_list);
int total_distance(const std::vector<int>& left_list, const std::vector<int>& right_list);
int total_similarity(const std::vector<int>& left_list, const std::vector<int>& right_list);

int main() {
    std::vector<int> left_list, right_list;

    divide_input(get_input(), left_list, right_list);
    std::sort(left_list.begin(), left_list.end());
    std::sort(right_list.begin(), right_list.end());

    std::cout << "Response part 1: " << total_distance(left_list, right_list) << std::endl;
    std::cout << "Response part 2: " << total_similarity(left_list, right_list) << std::endl;
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

int total_distance(const std::vector<int>& left_list, const std::vector<int>& right_list) {
    int total_distance = 0;
    for (int i = 0; i < left_list.size(); i++) {
        total_distance += std::abs(left_list[i] - right_list[i]);
    }
    return total_distance;
}

int total_similarity(const std::vector<int>& left_list, const std::vector<int>& right_list) {
    int total_similarity = 0;

    size_t pos = 0;
    int last_element = -1;
    int appear_times = 0;
    for (int left_element : left_list) {
        if (left_element != last_element) {
            last_element = left_element;
            appear_times = 0;

            if (left_element < right_list[pos])
                continue;

            while (left_element >= right_list[pos]) {
                if (left_element == right_list[pos]) {
                    appear_times += 1;
                }
                pos += 1;
            }
        }
        total_similarity += left_element * appear_times;
    }

    return total_similarity;
}
