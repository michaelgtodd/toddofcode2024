#include <iostream>
#include <fstream>
#include <chrono>
#include <cctype>

#include <nlohmann/json.hpp>

#include "main.hpp"

using namespace std;
using namespace nlohmann;

int main (int argc, char* argv[])
{
    // std::ifstream input ("../input/raw_small_input.txt");
    std::ifstream input ("../input/raw_input.txt");

    auto total_begin = std::chrono::steady_clock::now();

    float part_one_seconds = 0;
    float part_two_seconds = 0;

    int p1_value = 0;
    int p2_value = 0;
    
    { // PART ONE   

        auto part_one_begin = std::chrono::steady_clock::now();

        int value = 0;

        char i = (char) input.get();
        while (i != std::char_traits<char>::eof())
        {
            if (i == 'm')
            {
                i = (char) input.get();
                if (i == 'u')
                {
                    i = (char) input.get();
                    if (i == 'l')
                    {
                        i = (char) input.get();
                        if (i == '(')
                        {
                            i = (char) input.get();
                            std::stringstream first_digit;
                            std::stringstream second_digit;
                            while (i != std::char_traits<char>::eof() && isdigit(i))
                            {
                                first_digit << i;
                                i = (char) input.get();
                            }
                            if (i == ',')
                            {
                                i = (char) input.get();
                                while (i != std::char_traits<char>::eof() && isdigit(i))
                                {
                                    second_digit << i;
                                    i = (char) input.get();
                                }
                                if (i == ')')
                                {
                                    try 
                                    {
                                        int first_number = stoi(first_digit.str());
                                        int second_number = stoi(second_digit.str());
                                        value += first_number * second_number;
                                    }
                                    catch ( ... )
                                    {
                                        std::cout << "Nah Bro" << std::endl;
                                    }
                                    
                                }
                            }
                        }
                    }
                }
            }
            else
            {
                i = (char) input.get();
            }
        }

        auto part_one_end = std::chrono::steady_clock::now();
        part_one_seconds = std::chrono::duration_cast<std::chrono::microseconds>(part_one_end - part_one_begin).count() / 1000000.0;

        p1_value = value;

    } // END PART ONE

    { // PART TWO

        auto part_two_begin = std::chrono::steady_clock::now();

        int value = 0;
        bool mul_enabled = true;
        
        input.clear();
        input.seekg(0, std::ios::beg);

        char i = (char) input.get();
        while (i != std::char_traits<char>::eof())
        {
            if (i == 'm')
            {
                i = (char) input.get();
                if (i == 'u')
                {
                    i = (char) input.get();
                    if (i == 'l')
                    {
                        i = (char) input.get();
                        if (i == '(')
                        {
                            i = (char) input.get();
                            std::stringstream first_digit;
                            std::stringstream second_digit;
                            while (i != std::char_traits<char>::eof() && isdigit(i))
                            {
                                first_digit << i;
                                i = (char) input.get();
                            }
                            if (i == ',')
                            {
                                i = (char) input.get();
                                while (i != std::char_traits<char>::eof() && isdigit(i))
                                {
                                    second_digit << i;
                                    i = (char) input.get();
                                }
                                if (i == ')')
                                {
                                    try 
                                    {
                                        int first_number = stoi(first_digit.str());
                                        int second_number = stoi(second_digit.str());
                                        if (mul_enabled)
                                        {
                                            value += first_number * second_number;
                                        }
                                    }
                                    catch ( ... )
                                    {
                                        std::cout << "Nah Bro" << std::endl;
                                    }
                                    
                                }
                            }
                        }
                    }
                }
            }
            else if (i == 'd')
            {
                i = (char) input.get();
                if (i == 'o')
                {
                    i = (char) input.get();
                    if (i == '(')
                    {
                        i = (char) input.get();
                        if (i == ')')
                        {
                            i = (char) input.get();
                            mul_enabled = true;
                        }
                    }
                    if (i == 'n')
                    {
                        i = (char) input.get();
                        if (i == '\'')
                        {
                            i = (char) input.get();
                            if(i == 't')
                            {
                                i = (char) input.get();
                                if (i == '(')
                                {
                                    i = (char) input.get();
                                    if (i == ')')
                                    {
                                        i = (char) input.get();
                                        mul_enabled = false;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            else
            {
                i = (char) input.get();
            }
        }
        
        auto part_two_end = std::chrono::steady_clock::now();
        part_two_seconds = std::chrono::duration_cast<std::chrono::microseconds>(part_two_end - part_two_begin).count() / 1000000.0;

        p2_value = value;

    } // END PART TWO

    auto total_end = std::chrono::steady_clock::now();
    float total_seconds = std::chrono::duration_cast<std::chrono::microseconds>(total_end - total_begin).count() / 1000000.0;
    
    std::cout << "Part One:\t" << p1_value << std::endl;
    std::cout << "Part Two:\t" << p2_value << std::endl;

    std::cout << "Part One Time: " << part_one_seconds << "s" << std::endl;
    std::cout << "Part Two Time: " << part_two_seconds << "s" << std::endl;
    std::cout << "Total Time: " << total_seconds << "s" << std::endl;


}
