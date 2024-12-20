#include <iostream>
#include <fstream>
#include <chrono>

#include <nlohmann/json.hpp>

#include "main.hpp"

using namespace std;
using namespace nlohmann;

int main (int argc, char* argv[])
{
    std::ifstream input ("../input/massaged_input.txt");
    // std::ifstream input ("../input/small_massaged_input.txt");

    json js = json::parse(input);

    auto total_begin = std::chrono::steady_clock::now();

    float part_one_seconds = 0;
    float part_two_seconds = 0;

    int p1_value = 0;
    int p2_value = 0;
    
    { // PART ONE

        auto part_one_begin = std::chrono::steady_clock::now();

        auto part_one_end = std::chrono::steady_clock::now();
        part_one_seconds = std::chrono::duration_cast<std::chrono::microseconds>(part_one_end - part_one_begin).count() / 1000000.0;

        p1_value = 0;

    } // END PART ONE

    { // PART TWO

        auto part_two_begin = std::chrono::steady_clock::now();
        
        auto part_two_end = std::chrono::steady_clock::now();
        part_two_seconds = std::chrono::duration_cast<std::chrono::microseconds>(part_two_end - part_two_begin).count() / 1000000.0;

        p2_value = 0;

    } // END PART TWO

    auto total_end = std::chrono::steady_clock::now();
    float total_seconds = std::chrono::duration_cast<std::chrono::microseconds>(total_end - total_begin).count() / 1000000.0;
    
    std::cout << "Part One:\t" << p1_value << std::endl;
    std::cout << "Part Two:\t" << p2_value << std::endl;

    std::cout << "Part One Time: " << part_one_seconds << "s" << std::endl;
    std::cout << "Part Two Time: " << part_two_seconds << "s" << std::endl;
    std::cout << "Total Time: " << total_seconds << "s" << std::endl;


}
