#include <iostream>
#include <fstream>
#include <set>

#include "main.hpp"
#include "nlohmann/json.hpp"

using namespace nlohmann;


int main (int argc, char* argv[])
{
    std::ifstream input ("../input/massaged_input.txt");
    // std::ifstream input ("../input/small_massaged_input.txt");

    json js = json::parse(input);

    std::multiset<int> list_1 = js["List1"];
    std::multiset<int> list_2 = js["List2"]; 

    
    std::cout << "Starting Part One:" << std::endl;

    auto i = list_1.begin();
    auto j = list_2.begin();

    uint32_t apart = 0;

    while (i != list_1.end())
    {
        apart += std::abs(*i - *j);
        int this_apart = std::abs(*i - *j);
        i++; j++;
    }

    std::cout << "Part One Answer\t" << apart << std::endl;
    

    i = list_1.begin();
    j = list_2.begin();

    uint32_t similarity = 0;

    while (i != list_1.end())
    {
        similarity += *i * list_2.count(*i);
        i++; j++;
    }

    std::cout << "Part Two Answer\t" << similarity << std::endl;
}
