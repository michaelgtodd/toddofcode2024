#include <iostream>
#include <fstream>
#include <chrono>
#include <map>
#include <exception>
#include <stack>

#include <nlohmann/json.hpp>

#include "main.hpp"

using namespace std;
using namespace nlohmann;

std::pair<int, int> constrain (int i , int j, std::vector<std::vector<uint8_t>>& grid)
{
    int new_i = std::min(std::max (i, 0), (int) grid[0].size() - 1);
    int new_j = std::min(std::max (j, 0), (int) grid.size() - 1);

    if (i != new_i || j != new_j)
    {
        throw runtime_error("Nope");
    }
    return std::make_pair(i, j);

}

bool p1_check_direction(int i, int j, int i_dir, int j_dir, std::vector<std::vector<uint8_t>>& grid)
{
    bool passed = true;
    int i_check = i + i_dir;
    int j_check = j + j_dir;
    for (int value = 3; value > 0; value -- && passed)
    {
        try
        {
            std::pair<int, int> check_point = constrain(i_check, j_check, grid);
            if (grid[check_point.second][check_point.first] != value)
            {
                return false;
            }
        }
        catch( ... )
        {
            return false;
        }
        i_check = i_check + i_dir;
        j_check = j_check + j_dir;
    }
    return true;
}

bool p2_check_direction(int i, int j, int i_dir, int j_dir, std::vector<std::vector<uint8_t>>& grid)
{
    bool passed = true;
    int i_check = i + i_dir;
    int j_check = j + j_dir;
    for (int value = 3; value > 1; value -- && passed)
    {
        try
        {
            std::pair<int, int> check_point = constrain(i_check, j_check, grid);
            if (grid[check_point.second][check_point.first] != value)
            {
                return false;
            }
        }
        catch( ... )
        {
            return false;
        }
        i_check = i_check + i_dir;
        j_check = j_check + j_dir;
    }
    return true;
}

bool p2_check_criss_cross(int i, int j, std::vector<std::vector<uint8_t>>& grid)
{
    bool passed = grid[j-1][i-1] != 0 && grid[j+1][i+1] != 0 && grid[j-1][i+1] != 0 && grid[j+1][i-1] != 0;
    passed = passed && grid[j-1][i-1] != 3 && grid[j+1][i+1] != 3 && grid[j-1][i+1] != 3 && grid[j+1][i-1] != 3;
    passed = passed && grid[j-1][i-1] != grid[j+1][i+1] && grid[j-1][i+1] != grid[j+1][i-1];
    
    return passed;
}

void p2_fill_criss_cross(int i, int j, std::vector<std::vector<char>>& grid)
{
    grid[j][i] = 'X';
    grid[j-1][i-1] = 'X';
    grid[j+1][i+1] = 'X';
    grid[j+1][i-1] = 'X';
    grid[j-1][i+1] = 'X';
}

void print_result(std::vector<std::vector<char>>& result)
{
    for (auto j : result)
    {
        for (auto i : j)
        {
            std::cout << i;
        }
        std::cout << endl;
    }
}

void p1_fill_result(std::vector<std::vector<char>>& result, int i, int j, int i_dir, int j_dir)
{
    int value = 3;
    std::stack<char> word;
    word.push('X');
    word.push('M');
    word.push('A');
    word.push('S');
    result[j][i] = word.top();
    word.pop();
    int i_place = i + i_dir;
    int j_place = j + j_dir;
    for (int value = 3; value > 0; value--)
    {
        result[j_place][i_place] = word.top();
        word.pop();
        i_place = i_place + i_dir;
        j_place = j_place + j_dir;
    }
}

void p2_fill_result(std::vector<std::vector<uint8_t>>& result, int i, int j, int i_dir, int j_dir)
{
    int value = 2;
    std::stack<char> word;
    word.push(2);
    word.push(3);
    word.push(4);
    result[j][i] = word.top();
    word.pop();
    int i_place = i + i_dir;
    int j_place = j + j_dir;
    for (int value = 2; value > 0; value--)
    {
        result[j_place][i_place] = word.top();
        word.pop();
        i_place = i_place + i_dir;
        j_place = j_place + j_dir;
    }
}

int main (int argc, char* argv[])
{
    std::ifstream input ("../input/raw_input.txt");
    // std::ifstream input ("../input/raw_small_input.txt");

    auto total_begin = std::chrono::steady_clock::now();

    float part_one_seconds = 0;
    float part_two_seconds = 0;

    int p1_value = 0;
    int p2_value = 0;
    std::vector<std::vector<uint8_t>> grid;
    grid.push_back(std::vector<uint8_t>());

    char i = input.get();
    while (i != std::char_traits<char>::eof())
    {
        if (i == 'X')
        {
            std::prev(grid.end())->push_back(1);
        }
        if (i == 'M')
        {
            std::prev(grid.end())->push_back(2);
        }
        if (i == 'A')
        {
            std::prev(grid.end())->push_back(3);
        }
        if (i == 'S')
        {
            std::prev(grid.end())->push_back(4);
        }
        if (i == '\n')
        {
            grid.push_back(std::vector<uint8_t>());
        }
        i = input.get();
    }

    
    std::vector<std::vector<char>> p1_result;
    std::vector<std::vector<uint8_t>> p2_result;
    std::vector<std::vector<char>> p2_result_two;
    for (auto i : grid)
    {
        p1_result.push_back(std::vector<char>());
        p2_result.push_back(std::vector<uint8_t>());
        p2_result_two.push_back(std::vector<char>());
        for (auto j : grid)
        {
            std::prev(p1_result.end())->push_back('.');
            std::prev(p2_result.end())->push_back(0);
            std::prev(p2_result_two.end())->push_back('.');
        }
    }

    { // PART ONE

        auto part_one_begin = std::chrono::steady_clock::now();

        int count = 0;

        for (int j = 0; j < grid.size(); j ++)
        {
            for (int i = 0; i < grid[j].size(); i++)
            {
                for (int x = -1; x < 2; x++)
                {
                    for (int y = -1; y < 2; y++)
                    {
                        if (y != 0 || x != 0)
                        {
                            if (grid[j][i] == 4)
                            {
                                if (p1_check_direction(i, j, x, y, grid))
                                {
                                    // std::cout << json(std::make_pair(i, j)) << " : " << json(std::make_pair(x,y)) << std::endl;
                                    // p1_fill_result(p1_result, i, j, x, y);
                                    count ++;
                                }
                            }
                        }
                    }
                }
            }
        }

        // print_result(p1_result);

        auto part_one_end = std::chrono::steady_clock::now();
        part_one_seconds = std::chrono::duration_cast<std::chrono::microseconds>(part_one_end - part_one_begin).count() / 1000000.0;

        p1_value = count;

    } // END PART ONE

    { // PART TWO

        auto part_two_begin = std::chrono::steady_clock::now();

        int count = 0;

        for (int j = 0; j < grid.size(); j ++)
        {
            for (int i = 0; i < grid[j].size(); i++)
            {
                for (int x = -1; x < 2; x++)
                {
                    for (int y = -1; y < 2; y++)
                    {
                        if (y != 0 && x != 0)
                        {
                            if (grid[j][i] == 4)
                            {
                                if (p2_check_direction(i, j, x, y, grid))
                                {
                                    // std::cout << json(std::make_pair(i, j)) << " : " << json(std::make_pair(x,y)) << std::endl;
                                    p2_fill_result(p2_result, i, j, x, y);
                                }
                            }
                        }
                    }
                }
            }
        }

        for (int j = 0; j < p2_result.size(); j ++)
        {
            for (int i = 0; i < p2_result[j].size(); i++)
            {
                if (p2_result[j][i] == 3)
                {
                    if (p2_check_criss_cross(i, j, p2_result))
                    {
                        count ++;
                        // p2_fill_criss_cross(i, j, p2_result_two);
                    }
                }
            }
        }

        // print_result(p2_result_two);
        
        auto part_two_end = std::chrono::steady_clock::now();
        part_two_seconds = std::chrono::duration_cast<std::chrono::microseconds>(part_two_end - part_two_begin).count() / 1000000.0;

        p2_value = count;

    } // END PART TWO

    auto total_end = std::chrono::steady_clock::now();
    float total_seconds = std::chrono::duration_cast<std::chrono::microseconds>(total_end - total_begin).count() / 1000000.0;
    
    std::cout << "Part One:\t" << p1_value << std::endl;
    std::cout << "Part Two:\t" << p2_value << std::endl;

    std::cout << "Part One Time: " << part_one_seconds << "s" << std::endl;
    std::cout << "Part Two Time: " << part_two_seconds << "s" << std::endl;
    std::cout << "Total Time: " << total_seconds << "s" << std::endl;


}
